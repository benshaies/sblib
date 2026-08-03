#include "include/sblib.h"
#include "sbTiles/sbTiles.h"
#include <raylib.h>
#include <stdio.h>

Texture2D tilesetTexture;

Camera2D cam;

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  EndDrawing();
}

void init() {
  InitWindow(1000, 1000, "sbLib Testing");
  SetTargetFPS(60);

  tilesetTexture = LoadTexture("../levelTileset.png");
}

int main() {

  init();
  while (!WindowShouldClose()) {
    draw();
  }

  return 0;
}
