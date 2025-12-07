#ifndef SHEETANIMATION_H
#define SHEETANIMATION_H
#include <raylib.h>
#include <memory>

struct SheetAnim {
    std::shared_ptr<Texture2D> spriteSheet;
    int totalFrames;
    float frameWidth;
    float frameHeight;
    int frameIndex;


    float frameTime;
    float updateTime;

    Rectangle sourceRect;

    //void Aloading(int totframes, std::shared_ptr<Texture2D> texture);
    void Alogic(float directionX, bool isAnim,float frameWidth,float frameHeight, int frameIndex, float frameTime, float updateTime);
};

#endif //SHEETANIMATION_H
