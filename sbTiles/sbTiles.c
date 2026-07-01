#include "sbTiles.h"

void sbTilesInit();

void sbTilesUpdate(LevelData *currentLevel, bool active, Vector2 mousePos) {}

void sbTilesDraw(LevelData currentLevel) {
  levelDataDraw(currentLevel, currentLevel.tileset.tileSize,
                currentLevel.tileset.tileSize);
}
