#include "include/sblib.h"
#include <raylib.h>
#include <stdio.h>

LevelData level;

Tileset tileset;

int main() {
  InitWindow(500, 500, "sbLib Testing");
  SetTargetFPS(60);

  level = levelDataInit(1, tileset, 10, 5);
  printf("%d\n", level.layerCount);
  printf("%d\n", level.layer[0].data[0][0]);

  return 0;
}
