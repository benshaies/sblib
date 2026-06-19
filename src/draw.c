#include "../include/sblib.h"
#include "math.h"

void gameResolutionDraw(Vector2 windowSize, RenderTexture2D *target,
                        Vector2 *mousePos) {
  BeginDrawing();
  ClearBackground(WHITE);

  float scale = fmin((float)GetScreenWidth() / windowSize.x,
                     (float)GetScreenHeight() / windowSize.y);

  float scaledWidth = windowSize.x * scale;
  float scaledHeight = windowSize.y * scale;

  float offsetX = (GetScreenWidth() - scaledWidth) * 0.5f;
  float offsetY = (GetScreenHeight() - scaledHeight) * 0.5f;

  Rectangle src = {
      0, 0, (float)target->texture.width,
      -(float)target->texture.height // flip vertically
  };

  Rectangle dst = {offsetX, offsetY, scaledWidth, scaledHeight};

  DrawTexturePro(target->texture, src, dst, (Vector2){0, 0}, 0.0f, WHITE);

  *mousePos = GetMousePosition();

  mousePos->x = (mousePos->x - offsetX) / scale;
  mousePos->y = (mousePos->y - offsetY) / scale;

  EndDrawing();
}
