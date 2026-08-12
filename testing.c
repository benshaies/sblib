#include "include/sblib.h"
#include "sbTiles/sbTiles.h"
#include <raylib.h>
#include <stdio.h>

SB_Level level;

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  EndDrawing();
}

void init() {
  InitWindow(1000, 1000, "sbLib Testing");
  SetTargetFPS(60);
}

int main() {

  init();

  SB_Level_Save(level, "../testing.sblevel");

  return 0;
}
