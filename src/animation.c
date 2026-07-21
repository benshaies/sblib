#include "../include/sblib.h"

SB_Animation SB_Animation_Init(Texture2D texture, int frameSize, int frameCount,
                               int spriteSheetRow) {

  SB_Animation animation;

  animation.timer = 0;
  animation.texture = texture;
  animation.frameSize = frameSize;
  animation.frameCount = frameCount;
  animation.currentFrame = 0;
  animation.spriteSheetRow = spriteSheetRow;

  return animation;
}

void playAnimation(Animation *animation, Rectangle destination, int direction,
                   float speed) {

  animation->timer += GetFrameTime();
  if (animation->timer >= speed) {
    animation->currentFrame++;
    animation->timer = 0;

    if (animation->currentFrame >= animation->frameCount) {
      animation->currentFrame = 0;
    }
  }

  Rectangle frameRec = {animation->currentFrame * animation->size,
                        animation->yPos, direction * animation->size,
                        animation->size};
  DrawTexturePro(animation->texture, frameRec, destination, (Vector2){0, 0},
                 0.0f, WHITE);
}

void drawAnimationFrame(Animation *animation, Rectangle destination,
                        int direction, int frameNum) {

  Rectangle frameRec = {frameNum * animation->size, animation->yPos,
                        direction * animation->size, animation->size};
  DrawTexturePro(animation->texture, frameRec, destination, (Vector2){0, 0},
                 0.0f, WHITE);
}

bool playAnimationOnce(Animation *animation, Rectangle destination,
                       int direction, float speed) {

  // Only advance if not fini
  if (animation->currentFrame < animation->frameCount - 1) {
    animation->timer += GetFrameTime();

    if (animation->timer >= speed) {
      animation->timer = 0;
      animation->currentFrame++;
    }
  }

  Rectangle frameRec = {animation->currentFrame * animation->size,
                        animation->yPos, direction * animation->size,
                        animation->size};

  DrawTexturePro(animation->texture, frameRec, destination, (Vector2){0, 0},
                 0.0f, WHITE);

  // Check if finished
  if (animation->currentFrame >= animation->frameCount - 1) {
    animation->currentFrame = 0; // reset for next time
    return true;
  }

  return false;
}
