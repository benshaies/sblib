#include "include/sblib.h"
#include "sbTiles/sbTiles.h"
#include <raylib.h>
#include <stdio.h>

SB_Level level;

SB_Tileset tileset = {0};

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText(TextFormat("%d", level.layer[0].data[0][0]), 500, 500, 50, BLACK);

  EndDrawing();
}

void init() {
  InitWindow(1000, 1000, "sbLib Testing");
  SetTargetFPS(60);

  tileset = SB_Tileset_Init("../levelTileset.png", 18);
  level = SB_Level_Init(1, tileset, 1, 1);
}

int main() {

  init();

  while (!WindowShouldClose()) {

    draw();

    if (IsKeyPressed(KEY_W)) {
      SB_Level_Save(level, "test.sb");
    }

    if (IsKeyPressed(KEY_S)) {
      level = SB_Level_Load("test.sb");
    }

    if (IsKeyPressed(KEY_R)) {
      level.layer[0].data[0][0] = GetRandomValue(0, 5);
    }
  }

  return 0;
}
