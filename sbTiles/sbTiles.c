#include "sbTiles.h"
#include <raylib.h>
#include <stdio.h>

SBTILES sbt;

void sbTilesInit() {
  sbt.currentDrawSize = (Vector2){0, 0};
  sbt.currentLayer = 0;
  sbt.selectedTile = 30;

  sbt.currentState = LEVEL_EDITING;

  sbt.tileSelectionRec = (Rectangle){0, 0, 250, 250};
}

void levelEditingUpdate(LevelData *currentLevel, Vector2 mousePos) {

  // Placing tiles
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 currentLevelSize = {
        currentLevel->layer[sbt.currentLayer].cols * sbt.currentDrawSize.x,
        currentLevel->layer[sbt.currentLayer].rows * sbt.currentDrawSize.y};
    Rectangle level = {0, 0, currentLevelSize.x, currentLevelSize.y};
    int y, x;
    if (CheckCollisionPointRec(mousePos, level)) {
      x = mousePos.x / sbt.currentDrawSize.x;
      y = mousePos.y / sbt.currentDrawSize.y;
      currentLevel->layer[sbt.currentLayer].data[y][x] = sbt.selectedTile;
    }
  }

  // Removing Tiles
  else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    Vector2 currentLevelSize = {
        currentLevel->layer[sbt.currentLayer].cols * sbt.currentDrawSize.x,
        currentLevel->layer[sbt.currentLayer].rows * sbt.currentDrawSize.y};
    Rectangle level = {0, 0, currentLevelSize.x, currentLevelSize.y};
    int y, x;
    x = mousePos.x / sbt.currentDrawSize.x;
    y = mousePos.y / sbt.currentDrawSize.y;
    if (CheckCollisionPointRec(mousePos, level) &&
        currentLevel->layer[sbt.currentLayer].data[y][x] >= 0) {
      currentLevel->layer[sbt.currentLayer].data[y][x] = -1;
    }
  }
}

void tileSelectionUpdate(LevelData *currentLevel, Vector2 mousePos) {
  if (IsKeyDown(KEY_UP)) {
    sbt.tileSelectionRec.width *= 1.025;

    sbt.tileSelectionRec.height *= 1.025;
  }

  else if (IsKeyDown(KEY_DOWN)) {
    sbt.tileSelectionRec.width *= 0.975;
    sbt.tileSelectionRec.height *= 0.975;
  }

  // Selecting new tile from tile selection
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mousePos, sbt.tileSelectionRec)) {
  }
}

void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos) {

  switch (sbt.currentState) {
  case TILE_SELECTION:
    if (IsKeyPressed(KEY_F2)) {
      sbt.currentState = LEVEL_EDITING;
    }

    tileSelectionUpdate(currentLevel, mousePos);

    break;

  case LEVEL_EDITING:
    levelEditingUpdate(currentLevel, mousePos);
    if (IsKeyPressed(KEY_F2)) {
      sbt.currentState = TILE_SELECTION;
    }

    break;
  }
}

void drawTileset(LevelData currentLevel) {

  Rectangle sourceRec = {
      0, 0, currentLevel.tileset.width * currentLevel.tileset.tileSize,
      currentLevel.tileset.height * currentLevel.tileset.tileSize};

  DrawTexturePro(currentLevel.tileset.texture, sourceRec, sbt.tileSelectionRec,
                 (Vector2){0, 0}, 0.0, WHITE);

  // Highlight current selected Tile
  Rectangle highlightRec = {
      (sbt.selectedTile % currentLevel.tileset.width) *
          (sbt.tileSelectionRec.width / currentLevel.tileset.width),
      (sbt.selectedTile / currentLevel.tileset.width) *
          (sbt.tileSelectionRec.height / currentLevel.tileset.height),
      sbt.tileSelectionRec.width / currentLevel.tileset.width,
      sbt.tileSelectionRec.height / currentLevel.tileset.height,
  };

  DrawRectangleRec(highlightRec, Fade(BLUE, 0.5));
}

void sbTilesDraw(LevelData currentLevel, int drawTileWidth,
                 int drawTileHeight) {

  switch (sbt.currentState) {
  case TILE_SELECTION:
    drawTileset(currentLevel);

    break;

  case LEVEL_EDITING:

    levelDataDraw(currentLevel, drawTileWidth, drawTileHeight);

    sbt.currentDrawSize = (Vector2){drawTileWidth, drawTileHeight};

    for (int i = 0; i < currentLevel.layer[sbt.currentLayer].rows; i++) {
      for (int j = 0; j < currentLevel.layer[sbt.currentLayer].cols; j++) {

        DrawLineEx((Vector2){j * drawTileWidth, 0},
                   (Vector2){j * drawTileWidth,
                             currentLevel.layer[sbt.currentLayer].rows *
                                 drawTileHeight},
                   5.0, YELLOW);

        DrawLineEx(
            (Vector2){0, i * drawTileHeight},
            (Vector2){drawTileWidth * currentLevel.layer[sbt.currentLayer].cols,
                      i * drawTileHeight},
            5.0, BLUE);
      }
    }

    break;
  }
}
