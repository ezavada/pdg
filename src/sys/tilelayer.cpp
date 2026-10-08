// -----------------------------------------------
// tilelayer.cpp
// 
// tile functionality implementation
//
// Written by Ed Zavada, 2010-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------


#include "pdg_project.h"

#include "pdg/sys/os.h"
#include "pdg/sys/tilelayer.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"

#include "spritemanager.h"
#include "image-impl.h"
#include "collisiondetection.h"

#ifndef PDG_NO_GUI
#include "include-opengl.h"
#include "image-opengl.h"
#include "graphics-opengl.h"
#endif // ! PDG_NO_GUI

#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

//#define TILING_INTERNAL_DEBUG 1

#define PDG_TILE_LAYER_MAGIC_NUMBER    	0x10959843

#ifndef PDG_UNSAFE_SERIALIZATION
#define PDG_TAG_SERIALIZED_DATA
#endif

namespace pdg {

uint32 TileLayer::getSerializedSize(ISerializer* serializer) const {
	uint32 totalSize = 0;
#ifdef PDG_TAG_SERIALIZED_DATA
	totalSize += 4;  // size of request magic number
#endif
//	totalSize += 4; // size of action type (2), seat (1), and undoable (1)
	return totalSize;
}


void TileLayer::serialize(ISerializer* serializer) const {
#ifdef PDG_TAG_SERIALIZED_DATA
	serializer->serialize_4(PDG_TILE_LAYER_MAGIC_NUMBER);
#endif
}


void TileLayer::deserialize(IDeserializer* deserializer) {
#ifdef PDG_TAG_SERIALIZED_DATA
	uint32 tag = deserializer->deserialize_4();
	DEBUG_ASSERT(tag == PDG_TILE_LAYER_MAGIC_NUMBER, "OUT OF SYNC: expected tag for Tile Layer object");
#endif
}

void	
TileLayer::setWorldSize(long width, long height, bool repeatingX, bool repeatingY) {
	// save the world size and repeating flags
	mWorldWidth = width;
	mWorldHeight = height;
	mRepeatingX = repeatingX;
	mRepeatingY = repeatingY;
	
	setWorldBounds(Rect(mWorldWidth*mSrcTileWidth,mWorldHeight*mSrcTileHeight));
	mDataSize = mWorldWidth * mWorldHeight;
	
	// allocate a datablock for the layer
	mTileData = (uint8*) std::malloc( mDataSize );
	std::memset(mTileData, 0, mDataSize);
}

Rect
TileLayer::getWorldSize() {
	return Rect(mWorldWidth, mWorldHeight);
}
	
void
TileLayer::defineTileSet(int tileWidth, int tileHeight, Image* tiles, bool hasTransparency, bool flipTiles) {
	// save tile width and height
	mSrcTileWidth = tileWidth;
	mSrcTileHeight = tileHeight;
    setWorldBounds(Rect(mWorldWidth*mSrcTileWidth,mWorldHeight*mSrcTileHeight));
	mHasTransparency = hasTransparency;
  #ifndef PDG_NO_GUI
	mMipMode = GL_NEAREST;
  #endif // ! PDG_NO_GUI
	
	// calc and save number of tiles based on how many fit in image
	mSrcTileCountX = (int)(tiles->getWidth() / mSrcTileWidth);
	mSrcTileCountY = (int)(tiles->getHeight() / mSrcTileHeight);
	
	mUseFacing = !flipTiles && ((mSrcTileCountX * mSrcTileCountY) <= 64);
	
	mUseFlipping = flipTiles;
	if (!mUseFlipping) {
		mFlipHoriz = false;
		mFlipVert = false;
	} else {
		if (mSrcTileCountX <= 8) {
			mFlipHoriz = true;
		}
		if (mSrcTileCountY <= 8) {
			mFlipVert = true;
		}
		if (!mFlipVert && !mFlipHoriz) {
			mUseFlipping = false;
		}
	}

	// save ratio for drawing layer
	mTileWorldRatioX = (float)1/mSrcTileCountX;
	mTileWorldRatioY = (float)1/mSrcTileCountY;
	mPixelWorldRatioX = (float)1/tiles->getWidth();
	mPixelWorldRatioY = (float)1/tiles->getHeight();
	
	// issue debug warning if tiles don't fit evenly into image
	DEBUG_ONLY( 
	   if ( tiles->getWidth() % mSrcTileWidth != 0 ) {
		   DEBUG_PRINT("TileSet image width %d not evenly divisible by tile width %d",tiles->getWidth(), mSrcTileWidth);
	   }
	   if ( tiles->getHeight() % mSrcTileHeight != 0 ) {
		   DEBUG_PRINT("TileSet image height %d not evenly divisible by tile height %d", tiles->getHeight(), mSrcTileHeight);
	   }
	)
	
	// save image
	mTiles = tiles;
	mTiles->addRef();
	mTiles->setEdgeClamping(true);
}

void
TileLayer::loadMapData(const uint8* dataPtr, long mapWidth, long mapHeight, long dstX, long dstY) {
	// copy the data into the allocated block, row by row, starting at dstX, dstY
	// and taking mapWidth as row length to copy and mapHeight as number of rows to copy
	/*
	long length = mapWidth - dstX;
	uint8* ptr = mTileData + dstX;
	for (int i=dstY; i<mapHeight; i++) {
		memcpy(ptr, dataPtr, length);
		ptr += mapWidth;
	}
	*/
	
	memcpy(mTileData, dataPtr, mapWidth*mapHeight);
}

uint8*
TileLayer::getMapData(long mapWidth, long mapHeight, long srcX, long srcY) {
	// allocate a buffer and copy the rows of data starting at dstX, dstY into it
	// taking mapWidth as row length to copy and mapHeight as number of rows to copy
	// return NIL if the copy would go outside the bounds of the currently allocated world
	
	// one byte for each tile
	uint8 * data = (uint8 *) malloc(mapWidth*mapHeight);
	memcpy(data, mTileData, mapWidth*mapHeight);
	return data;
}

uint8
TileLayer::getTileTypeAt(long x, long y, TFacing* outFacing) const {
	// look up tile at specific position and return it's value
	if (outFacing) {
		*outFacing = facing_North;
	}
	if (mRepeatingX) {
		x = (x % mWorldWidth);
		if (x < 0) {
			x += mWorldWidth;
		}
	} else if ( (x < 0) || (x >= mWorldWidth) ) return 0;
	
	if (mRepeatingY) {
		y = (y % mWorldHeight);
		if (y < 0) {
			y += mWorldHeight;
		}
	} else if ( (y < 0) || (y >= mWorldHeight) ) return 0;
	
	uint32 index = x + (y  * mWorldWidth);
	
	if (index > mDataSize) return 0;
	uint8 t = mTileData[index];
	if (outFacing) {
		if (mUseFacing) {
			*outFacing = (TFacing)(t - (t & 0x3F));
		}
		if (mUseFlipping) {
			if (mFlipVert && mFlipHoriz) {
				*outFacing = (TFacing)(t - (t & 0x3F));
			} else {
				if (mFlipHoriz) {
					*outFacing = (TFacing)((t - (t & 0x7F))>>1);
				} else {
					*outFacing = (TFacing)(t - (t & 0x7F));
				}
			}
		}
	}
	return t;
}

void
TileLayer::setTileTypeAt(long x, long y, uint8 t, TFacing facing) {
	// set tile at specific position
	// be sure not to write outside our allocated data
	if (mRepeatingX) {
		x = (x % mWorldWidth);
		if (x < 0) {
			x += mWorldWidth;
		}
	} else if ( (x < 0) || (x >= mWorldWidth) ) return;
	
	if (mRepeatingY) {
		y = (y % mWorldHeight);
		if (y < 0) {
			y += mWorldHeight;
		}
	} else if ( (y < 0) || (y >= mWorldHeight) ) return;
	
	uint32 index = x + (y  * mWorldWidth);
	
	if (index > mDataSize) return;
	if (facing == facing_Ignore || (!mUseFacing && !mUseFlipping)) {
		// no flipping or facing
		mTileData[index] = t;
	} else if (mUseFacing || (mUseFlipping && mFlipVert && mFlipHoriz)) {
		// using facing or both horizontal and vertical flipping
		mTileData[index] = (t & 0x3F) + (facing & 0xC0);
	} else if (mUseFlipping) {
		// using one direction flipping only
		if (mFlipHoriz) {
			mTileData[index] = (t & 0x7F) + ((facing & 0x40) << 1);
		} else {
			mTileData[index] = (t & 0x7F) + (facing & 0x80);
		}
	}
}

uint32    
TileLayer::checkCollision(Sprite *movingSprite, uint8 alphaThreshold, bool shortCircuit, float *outCollisionMag) const {
	// get the sprite bounding box
	Sprite* inSprite = movingSprite;
	ImageImpl* spriteImage = inSprite->mFrames[inSprite->mCurrFrame].image;
	ImageImpl* spriteMaskImage = inSprite->mFrames[inSprite->mCurrFrame].collisionMask;
	if (spriteMaskImage == 0) {
		spriteMaskImage = spriteImage;
	}
//	Rect spriteRect = inSprite->mScaledFrameBounds;
	
	RotatedRect rotated = inSprite->getFrameRotatedBounds(inSprite->mCurrFrame);
    //(spriteRect, inSprite->getRotation());
	//rotated.setCenterOffset(Point(inSprite->mFrames[inSprite->mCurrFrame].centerOffsetX * z, inSprite->mFrames[inSprite->mCurrFrame].centerOffsetY * z));

//	float z = mZoom; // adjust for tile layer zoom

	Rect spriteMaskRect = spriteMaskImage->getImageBounds();
	spriteMaskRect.moveRight(inSprite->mCurrFrame * spriteMaskImage->getWidth());
	
	const pdg::Point tileSize = getTileSize();
	const float tWidth = tileSize.x; // * z;
	const float tHeight = tileSize.y; // * z;
	// calc rect of tiles to check
	Rect tileOverlap = rotated.getBounds();
	// expand the overlap area to be on a tileSize boundary
	const int left = int(tileOverlap.left / tWidth) * int(tWidth);
	const int top = int(tileOverlap.top / tHeight) * int(tHeight);
	// output data
	uint32 totalCollisionPts = 0;
	uint32 collisionPts = 0;
	uint32* collisionPtsPtr = (shortCircuit) ? 0 : &collisionPts;
	if (outCollisionMag) {
		*outCollisionMag = 0.0f;
	}
	float collisionMag = 0.0f;
	float* collisionMagPtr = (shortCircuit) ? 0 : &collisionMag;
	// now check the tiles we intersect
	for(int l = left; l < tileOverlap.right; l += tWidth) {
		for( int t = top; t < tileOverlap.bottom; t += tHeight) {
			TileLayer::TFacing facing;
			uint8 val = getTileTypeAt(l / tWidth, t / tHeight, &facing);
			if (val == 0) continue; // val == 0 is an empty tile, so don't collide against it
			if (mUseFacing && ((val & 63) == 0)) continue; // these are also empty tiles when using facing or flipping
			// assemble parameters
			Rect checkRect(Point(l, t), tWidth, tHeight);
			int tileRow = (val / mSrcTileCountX) % mSrcTileCountY;
			int tileCol = val % mSrcTileCountX;
			
			Rect tileImageRect;
			tileImageRect.top = tileRow * mSrcTileHeight; // * mZoom;
			tileImageRect.bottom = tileImageRect.top + mSrcTileHeight; // * mZoom;
			tileImageRect.left = tileCol * mSrcTileWidth; // * mZoom;
			tileImageRect.right = tileImageRect.left + mSrcTileWidth; // * mZoom;
			
			if (true == CollisionDetection::detectPixelCollision(rotated, checkRect, spriteMaskImage, mTiles, spriteMaskRect, 
																 tileImageRect, facing, alphaThreshold, collisionPtsPtr, collisionMagPtr) ) {
				if (shortCircuit) return 1;
				totalCollisionPts += collisionPts;
				*outCollisionMag += collisionMag;
			}
		}
	}
	return totalCollisionPts;
}

//#define ADJUST(n) floor(n)
//#define ADJUST(n) roundf(n)
#define ADJUST(n) n

#ifndef PDG_NO_GUI
void
TileLayer::drawLayer() {
    if (mHidden || !mPort) return;
    ScopedOffscreenDrawing offscreenDrawing(mPort);
    Port::ScreenDrawingScope screenDrawing(*mPort);
    if (!mTiles || !mTileData || !mDataSize || mSrcTileWidth<=0 || mSrcTileHeight<=0 ||
        mSrcTileCountX<=0 || mSrcTileCountY<=0 || mWorldWidth<=0 || mWorldHeight<=0) {
        SpriteLayer::drawLayer(); return;
    }
    const Rect clip=mPort->getClipRect();
    if (clip.empty()) return;
    const auto view=getViewTransform(), inverse=view.inverse();
    Quad visibleQuad(clip);
    for (auto& point:visibleQuad.points) point=inverse.transformPoint(point);
    const Rect visible=visibleQuad.getBounds();
    // Clamp finite maps before converting to tile indices. Repeating maps keep
    // negative indices so getTileTypeAt() can wrap them in world coordinates.
    auto tileIndex=[](double value) {
        if (!std::isfinite(value) || value<=double(std::numeric_limits<long>::min()) ||
            value>=double(std::numeric_limits<long>::max()))
            throw std::out_of_range("Camera view exceeds tile index range");
        return static_cast<long>(value);
    };
    const double left=std::floor(visible.left/mSrcTileWidth), top=std::floor(visible.top/mSrcTileHeight);
    const double right=std::ceil(visible.right/mSrcTileWidth), bottom=std::ceil(visible.bottom/mSrcTileHeight);
    const long x0=tileIndex(mRepeatingX?left:std::clamp(left,0.0,double(mWorldWidth)));
    const long y0=tileIndex(mRepeatingY?top:std::clamp(top,0.0,double(mWorldHeight)));
    const long x1=tileIndex(mRepeatingX?right:std::clamp(right,0.0,double(mWorldWidth)));
    const long y1=tileIndex(mRepeatingY?bottom:std::clamp(bottom,0.0,double(mWorldHeight)));
    rec_PixelXOffset=visible.left-std::floor(visible.left/mSrcTileWidth)*mSrcTileWidth;
    rec_PixelYOffset=visible.top-std::floor(visible.top/mSrcTileHeight)*mSrcTileHeight;

    Port* previousPort=mTiles->setPort(mPort);
    struct RestoreImagePort { Image* image; Port* port; ~RestoreImagePort() { image->setPort(port); } } restorePort{mTiles,previousPort};
    auto* image=static_cast<ImageOpenGL*>(mTiles);
    static_cast<PortImpl&>(*mPort).setOpenGLModesForDrawing(mHasTransparency,blendMode_Normal,image->usesPremultipliedAlpha());
    image->bindTexture(mMipMode);
    glColor4f(1,1,1,1);
    glBegin(GL_TRIANGLES);
    for (long y=y0;y<y1;++y) for (long x=x0;x<x1;++x) {
        TFacing facing;
        const uint8 encoded=getTileTypeAt(x,y,&facing);
        const unsigned mask=mUseFacing || (mUseFlipping&&mFlipHoriz&&mFlipVert)?0x3f:
            mUseFlipping&&(mFlipHoriz||mFlipVert)?0x7f:0xff;
        const unsigned tile=encoded&mask;
        if ((!tile&&mHasTransparency) || tile>=unsigned(mSrcTileCountX*mSrcTileCountY)) continue;
        const unsigned tx=tile%mSrcTileCountX, ty=tile/mSrcTileCountX;
        const float u0=tx*mTileWorldRatioX, v0=ty*mTileWorldRatioY;
        const float u1=(tx+1)*mTileWorldRatioX-mPixelWorldRatioX;
        const float v1=(ty+1)*mTileWorldRatioY-mPixelWorldRatioY;
        Point uv[4]={Point(u0,v0),Point(u1,v0),Point(u1,v1),Point(u0,v1)};
        if (mUseFacing) {
            const unsigned turns=unsigned(facing)/64;
            Point original[4]={uv[0],uv[1],uv[2],uv[3]};
            for (unsigned corner=0;corner<4;++corner) uv[corner]=original[(corner+4-turns)%4];
        } else if (mUseFlipping) {
            if (unsigned(facing)&flipped_Horizontal) { std::swap(uv[0],uv[1]);std::swap(uv[3],uv[2]); }
            if (unsigned(facing)&flipped_Vertical) { std::swap(uv[0],uv[3]);std::swap(uv[1],uv[2]); }
        }
        Quad quad(Rect(double(x)*mSrcTileWidth,double(y)*mSrcTileHeight,
                       double(x+1)*mSrcTileWidth,double(y+1)*mSrcTileHeight));
        for (auto& point:quad.points) point=view.transformPoint(point);
        // Independent triangles avoid the fixed-size strip buffer truncating
        // wide or rotated camera views, and avoid connections across empty tiles.
        for (unsigned corner:{0u,1u,2u,0u,2u,3u}) {
            glTexCoord2f(uv[corner].x,uv[corner].y);
            glVertex2f(quad.points[corner].x,quad.points[corner].y);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    SpriteLayer::drawLayer();
}
#endif // ! PDG_NO_GUI

void 
TileLayer::animateLayer(double msElapsed) {
	SpriteLayer::animateLayer(msElapsed);
}
	
Image* TileLayer::getTileSetImage(){
	Image* image = static_cast<Image*> (mTiles);
	return image;
}

Point TileLayer::getTileSize() const {
	return Point(mSrcTileWidth, mSrcTileHeight);
}
	
#ifndef PDG_NO_GUI
TileLayer::TileLayer(Port* port) 
	: SpriteLayer(port),
	mTiles(0),
	mTileData(0),
	mDataSize(0),
	mSrcTileWidth(0),
	mSrcTileHeight(0),
	mSrcTileCountX(0),
	mSrcTileCountY(0),
	mWorldHeight(0),
	mWorldWidth(0),
	mRepeatingX(false),
	mRepeatingY(false),
	mHasTransparency(false),
	mUseFacing(false),
	mUseFlipping(false)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mTileLayerScriptObj);
#endif
}
#endif // ! PDG_NO_GUI

TileLayer::TileLayer() 
	: SpriteLayer(),
	mTiles(0),
	mTileData(0),
	mDataSize(0),
	mSrcTileWidth(0),
	mSrcTileHeight(0),
	mSrcTileCountX(0),
	mSrcTileCountY(0),
	mWorldHeight(0),
	mWorldWidth(0),
	mRepeatingX(false),
	mRepeatingY(false),
	mHasTransparency(false),
	mUseFacing(false),
	mUseFlipping(false)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mTileLayerScriptObj);
#endif
}

TileLayer::~TileLayer()
{
	if (mTileData) {
		std::free(mTileData);
		mTileData = nullptr;
	}
	if (mTiles) {
		mTiles->release();
		mTiles = nullptr;
	}
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupTileLayerScriptObject(mTileLayerScriptObj);
#endif
}

#ifndef PDG_NO_GUI
TileLayer* createTileLayer(Port* port) {
//	DEBUG_ASSERT(port, "must have a pdg::Port");
	// create sprite manager singleton instance if necessary
	TileLayer* layer = SpriteManager::createTileLayer(port);
	SpriteManager::getSingletonInstance()->addLayer(layer);
	return layer;
}
#endif // ! PDG_NO_GUI

TileLayer* createTileLayer() {
	// create sprite manager singleton instance if necessary
	TileLayer* layer = SpriteManager::createTileLayer();
	SpriteManager::getSingletonInstance()->addLayer(layer);
	return layer;
}


} // end namespace pdg
