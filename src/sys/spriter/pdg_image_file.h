#ifndef PDG_IMAGE_FILE_H
#define PDG_IMAGE_FILE_H

#ifndef PDG_NO_GUI

// for rendering, so only include if we have a GUI

#include "pdg/sys/image.h"
#include "pdg/sys/port.h"
#include "pdg/sys/spritelayer.h"
#include "spriterengine/override/imagefile.h"

namespace pdg {

class SpriteLayer;
class PDGImageFile : public SpriterEngine::ImageFile
{
public:
    PDGImageFile(const std::string& initialFilePath, 
                 SpriterEngine::point initialDefaultPivot, 
                 Image* pdgImage);
    
    virtual ~PDGImageFile();
    
    class LayerScope {
    public:
        explicit LayerScope(SpriteLayer* layer);
        ~LayerScope();
    private: SpriteLayer* mPrevious;
    };
    // Artwork and Spriter debug objects share the active Sprite drawing frame.
    static SpriteLayer* currentDrawingLayer();

    // Override the renderSprite method to draw using PDG
    void renderSprite(SpriterEngine::UniversalObjectInterface* spriteInfo) override;
    
    // Get the underlying PDG image
    Image* getPDGImage() const { return mPDGImage; }


private:
    Image* mPDGImage;
};

} // namespace pdg

#endif // !PDG_NO_GUI

#endif // PDG_IMAGE_FILE_H
