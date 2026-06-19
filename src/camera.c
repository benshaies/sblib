#include "../include/sblib.h"
#include <raylib.h>
#include <raymath.h>

void updateCameraShake(Camera2D *camera, int *screenShakeLenght,
                       int screenShakeStrenght, Vector2 windowSize) {
  if (screenShakeLenght > 0) {
    screenShakeLenght--;
    camera->offset =
        (Vector2){camera->offset.x +
                      GetRandomValue(-screenShakeStrenght, screenShakeStrenght),
                  camera->offset.y + GetRandomValue(-screenShakeStrenght,
                                                    screenShakeStrenght)};
  } else {
    // camera.offset = (Vector2){GAME_WIDTH/2, GAME_HEIGHT/2};
    camera->offset.x =
        Lerp(camera->offset.x, windowSize.x / 2, 5 * GetFrameTime());
    camera->offset.y =
        Lerp(camera->offset.y, windowSize.y / 2, 5 * GetFrameTime());
  }
}
