#ifndef SBTILES_H
#define SBTILES_H

#include "../include/sblib.h"
#include <raylib.h>

typedef enum {
  TILE_SELECTION,
  LEVEL_EDITING,

} SBT_STATE;

typedef struct {
  int currentLayer;
  Vector2 currentDrawSize;
  Camera2D cam;

  bool showTileLines;
  bool showAllLayers;

  int selectedTile;

  SBT_STATE currentState;

  Rectangle tileSelectionRec;

} SBTILES;

// Initialize sbTiles struct
void sbTilesInit(int windowWidth, int windowHeight);

// All main updates to sbTiles
void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos);

// All drawing to sbTiles
void sbTilesDraw(LevelData currentLevel, int drawTileWidth, int drawTileHeight);

#endif
