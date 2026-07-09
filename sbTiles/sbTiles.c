#include "sbTiles.h"
#include <raylib.h>
#include <stdio.h>

SBTILES sbt;

void sbTilesInit() {
  sbt.currentDrawSize = (Vector2){0, 0};
  sbt.currentLayer = 0;
}

void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos) {

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Vector2 currentLevelSize = {
        currentLevel->layer[sbt.currentLayer].cols * sbt.currentDrawSize.x,
        currentLevel->layer[sbt.currentLayer].rows * sbt.currentDrawSize.y};
    Rectangle level = {0, 0, currentLevelSize.x, currentLevelSize.y};
    int y, x;
    if (CheckCollisionPointRec(mousePos, level)) {
      x = mousePos.x / sbt.currentDrawSize.x;
      y = mousePos.y / sbt.currentDrawSize.y;
      currentLevel->layer[sbt.currentLayer].data[y][x] = 30;
    }
  }
}

void sbTilesDraw(LevelData currentLevel, int drawTileWidth,
                 int drawTileHeight) {

  levelDataDraw(currentLevel, drawTileWidth, drawTileHeight);

  sbt.currentDrawSize = (Vector2){drawTileWidth, drawTileHeight};

  for (int i = 0; i < currentLevel.layer[sbt.currentLayer].rows; i++) {
    for (int j = 0; j < currentLevel.layer[sbt.currentLayer].cols; j++) {

      DrawLineEx(
          (Vector2){j * drawTileWidth, 0},
          (Vector2){j * drawTileWidth,
                    currentLevel.layer[sbt.currentLayer].rows * drawTileHeight},
          5.0, YELLOW);

      DrawLineEx(
          (Vector2){0, i * drawTileHeight},
          (Vector2){drawTileWidth * currentLevel.layer[sbt.currentLayer].cols,
                    i * drawTileHeight},
          5.0, BLUE);
    }
  }
}
