#ifndef PDG_IMAGE_FILE_H
#define PDG_IMAGE_FILE_H

#ifndef PDG_NO_GUI

// for rendering, so only include if we have a GUI

#include "pdg/sys/image.h"
#include "pdg/sys/port.h"
#include "pdg/sys/sprite.h"
#include "spriterengine/override/imagefile.h"

namespace pdg {

class PDGImageFile : public SpriterEngine::ImageFile
{
public:
    PDGImageFile(const std::string& initialFilePath, 
                 SpriterEngine::point initialDefaultPivot, 
                 Image* pdgImage, 
                 //Sprite* sprite,
                 Port* port);
    
    virtual ~PDGImageFile();
    
    // Override the renderSprite method to draw using PDG
    void renderSprite(SpriterEngine::UniversalObjectInterface* spriteInfo) override;
    
    // Get the underlying PDG image
    Image* getPDGImage() const { return mPDGImage; }

    //Sprite* getPDGSprite() const { return mSprite; }

private:
    Image* mPDGImage;
    //Sprite* mSprite;
    Port* mPort;
};

} // namespace pdg

#endif // !PDG_NO_GUI

#endif // PDG_IMAGE_FILE_H
