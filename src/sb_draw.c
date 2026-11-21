#include "../include/sblib.h"
#include "math.h"
#include <raylib.h>

void SB_GameResolution_Draw(Vector2 windowSize, RenderTexture2D *target){

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

  EndDrawing();
}

Vector2 SB_GameResolution_GetMouse(Vector2 windowSize){

  float scale = fmin((float)GetScreenWidth() / windowSize.x,
                     (float)GetScreenHeight() / windowSize.y);

  float scaledWidth = windowSize.x * scale;
  float scaledHeight = windowSize.y * scale;

  float offsetX = (GetScreenWidth() - scaledWidth) * 0.5f;
  float offsetY = (GetScreenHeight() - scaledHeight) * 0.5f;

  Vector2 mouse = GetMousePosition();
  mouse.x = (mouse.x - offsetX) / scale;
  mouse.y = (mouse.y - offsetY) / scale;
  
  return mouse;
}

