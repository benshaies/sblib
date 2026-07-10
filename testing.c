#include "include/sblib.h"
#include "sbTiles/sbTiles.h"
#include <raylib.h>
#include <stdio.h>

LevelData level;

Tileset tileset;
Texture2D tilesetTexture;

Camera2D cam;

intArray array;

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  sbTilesDraw(level, 100, 100);

  EndDrawing();
}

void init() {
  InitWindow(1000, 1000, "sbLib Testing");
  SetTargetFPS(60);

  tilesetTexture = LoadTexture("../levelTileset.png");

  tileset = tilesetInit(tilesetTexture, 8, 8, 16);

  level = levelDataInit(1, tileset, 10, 10);

  sbTilesInit();
}

int main() {

  init();
  while (!WindowShouldClose()) {
    draw();

    sbTilesUpdate(&level, GetMousePosition());
  }

  return 0;
}
