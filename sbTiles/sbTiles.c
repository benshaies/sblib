#include "sbTiles.h"
#include <raylib.h>

int currentLayer = 0;
bool active = false;

void sbTilesInit();

void sbTilesUpdate(LevelData *currentLevel, bool active, Vector2 mousePos) {}

void sbTilesDraw(LevelData currentLevel, int drawTileWidth,
                 int drawTileHeight) {

  levelDataDraw(currentLevel, drawTileWidth, drawTileHeight);

  for (int i = 0; i < currentLevel.layer[currentLayer].rows; i++) {
    for (int j = 0; j < currentLevel.layer[currentLayer].cols; j++) {

      DrawLineEx(
          (Vector2){j * drawTileWidth, 0},
          (Vector2){j * drawTileWidth,
                    currentLevel.layer[currentLayer].rows * drawTileHeight},
          5.0, YELLOW);

      DrawLineEx(
          (Vector2){0, i * drawTileHeight},
          (Vector2){drawTileWidth * currentLevel.layer[currentLayer].cols,
                    i * drawTileHeight},
          5.0, BLUE);
    }
  }
}
