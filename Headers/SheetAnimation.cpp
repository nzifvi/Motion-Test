#include "sheetanimation.h"
#include "raylib.h"
#include "raymath.h"
#include <memory>

/*void SheetAnim::Aloading(int totframes, std::shared_ptr<Texture2D> texture) {
    spriteSheet = texture;
    totalFrames = totframes;

    frameWidth = spriteSheet->width/totalFrames;
    frameHeight = spriteSheet->height;
    frameIndex = 0;

    frameTime = 0.0f;
    updateTime = 1.0f/12.0f;
}*/

/*void SheetAnim::Alogic(float directionX, bool isAnim,float frameWidth,float frameHeight, int frameIndex, float frameTime, float updateTime) {
        if (isAnim == true) {
            frameTime += GetFrameTime();
            if (frameTime >= updateTime) {
                frameTime = 0.0f;
                frameIndex++;
                if (frameIndex >= totalFrames) {
                    frameIndex = 0;
                }
            }
        }
         sourceRect.width = frameWidth;

        if (directionX < 0) {
            sourceRect.width = -frameWidth;
        } else {
            sourceRect.width = frameWidth;
        }

        sourceRect.x = frameIndex * frameWidth;
        sourceRect.y = 0.0f;
        sourceRect.height = frameHeight;

}*/


