#ifndef SBLIB_H
#define SBLIB_H
#include <raylib.h>

// CUSTOM ARRAY

typedef struct {
  int *data; // Main array
  int size;  // Total size
} SB_IntArray;

typedef struct {
  int **data; // Main Array
  int rows;
  int cols;
} SB_IntArray2D; // 2D int array carring size

// Initliaze and allocate intArray
void SB_IntArray_Init(SB_IntArray *array, int size);

// Free intArray memory
void SB_IntArray_Free(SB_IntArray *array);

// Initliaze and allocate intArray2D
void SB_IntArray2D_Init(SB_IntArray2D *array, int rows, int cols);

// Free intArray2D memory
void SB_IntArray2D_Free(SB_IntArray2D *array);

// Convert a csv file into an integer array
void SB_CsvToArray(SB_IntArray2D *array, const char *filename);

// CAMERA FUNCTIONS
// ****************************************************************8
void SB_CameraShake_Update(Camera2D *cam, int *screenShakeLenght,
                           int screenShakeStrenght, Vector2 windowSize);

// DRAWING ****************************************************************

void SB_GameResolution_Draw(Vector2 windowSize, RenderTexture2D *target,
                            Vector2 *mousePos);

// TIMED EVENT ****************************************************************

typedef struct {
  float timer;             // Tracks time
  float delay;             // Amount of time to wait
  bool triggered;          // Is it triggered?
  bool particlesTriggered; // Has particles been triggered?

  Sound soundEffect; // Sound effect triggered?
} SB_TimedEvent;     // Simple event with a time delay and tracking

// Reset and or Initliaze timedEvent
void SB_TimedEvent_Reset(SB_TimedEvent *event, float delay, Sound soundEffect);

// Update timedEvent
bool SB_TimedEvent_Update(SB_TimedEvent *event);

// PARTICLES
// ********************************************************************

#define SB_MAX_PARTICLES 1024

typedef enum {
  SB_PARTICLE_NORMAL, // Normal square or cirlces
  SB_PARTICLE_RING,   // Circular expanding ring
} SB_ParticleType;

typedef struct {
  SB_ParticleType type;

  // Normal particle variables
  Vector2 pos;
  bool active;
  float life;
  float lifeMax;
  Color color;
  Vector2 velocity;
  float size;

  // Expanding Specific variables
  float expandingRate;
  float ringThickness;

} SB_Particle;

typedef struct {
  SB_Particle pool[SB_MAX_PARTICLES];
} SB_ParticleSystem;

// Spawn normal particles
void SB_ParticleSystem_Spawn(SB_ParticleSystem *ps, Vector2 pos, float lifeMax,
                             Color color, Vector2 velocity, float size);

// Spawn expanding ring particle
void SB_ParticleSystem_SpawnExpandingRing(SB_ParticleSystem *ps, Vector2 pos,
                                          float lifeMax, Color color,
                                          float size, float expandingRate,
                                          float ringThickness);

// Update all particles
void SB_ParticleSystem_Update(SB_ParticleSystem *ps);

// Draw all particles
void SB_ParticleSystem_Draw(SB_ParticleSystem *ps);

// ANIMATIONS
// **********************************************************************

typedef struct {
  float timer; // Tracks time
  Texture2D texture;
  int frameSize;  // pixel size of each frame
  int frameCount; //  Total frames
  int currentFrame;
  int direction;
  int spriteSheetRow; // Y position on sprite sheet
} SB_Animation;

// Create animation
SB_Animation SB_Animation_Init(Texture2D texture, int frameSize, int frameCount,
                               int spriteSheetRow);

// Play and draw animation
void SB_Animation_Play(SB_Animation *animation, Rectangle destination,
                       int direction, float speed);

// Draw one specific frame from animation
void SB_Animation_DrawFrame(SB_Animation *animation, Rectangle destination,
                            int direction, int frameNum);

// Play animation once and return true when done
bool SB_Animation_PlayOnce(SB_Animation *animation, Rectangle destination,
                           int direction, float speed);

// LEVEL DATA - levelData.c
// *************************************************************************

typedef struct {
  Texture2D texture;
  int width;
  int height;

  int tileSize;

} SB_Tileset; // Tileset variable

typedef struct {
  SB_IntArray2D *layer;

  int layerCount;
  SB_Tileset tileset;

} SB_Level; // Level Data struct

// Initliaze level data struct f
SB_Level SB_Level_Init(int layers, SB_Tileset tileset, int arrayRows,
                       int arrayCols);

// Draw level Data - specificLayer meaning -1:Draw normally | anything else
// draw specific Layer only
void SB_Level_Draw(SB_Level level, int drawTileWidth, int drawTileHeight,
                   int drawLayer);

// Free level data
void SB_Level_Free(SB_Level *level);

// Initliaze tileset struct
SB_Tileset SB_Tileset_Init(Texture2D texture, int width, int height,
                           int tileSize);

#endif
