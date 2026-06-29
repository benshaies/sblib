#include "include/sblib.h"
#include <raylib.h>
#include <stdio.h>

LevelData level;

Tileset tileset;
Texture2D tilesetTexture;

Camera2D cam;

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  levelDataDraw(level, cam, 50, 50);

  EndDrawing();
}

void init() {
  InitWindow(1000, 1000, "sbLib Testing");
  SetTargetFPS(60);

  tilesetTexture = LoadTexture("../levelTileset.png");

  tileset = tilesetInit(tilesetTexture, 8, 8, 16);

  level = levelDataInit(1, tileset, 10, 10);

  for (int i = 0; i < level.layer[0].rows; i++) {
    for (int j = 0; j < level.layer[0].cols; j++) {
      level.layer[0].data[i][j] = 0;
    }
  }
}

int main() {

  init();
  while (!WindowShouldClose()) {
    draw();
  }

  return 0;
}
