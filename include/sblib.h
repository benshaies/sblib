#ifndef SBLIB_H
#define SBLIB_H
#include <raylib.h>

// CUSTOM ARRAY

typedef struct {
  int *data; // Main array
  int size;  // Total size
} intArray;

typedef struct {
  int **data; // Main Array
  int rows;
  int cols;
} intArray2D; // 2D int array carring size

// Initliaze and allocate intArray
void intArrayInit(intArray *array, int size);

// Free intArray memory
void freeIntArray(intArray *array);

// Initliaze and allocate intArray2D
void intArray2DInit(intArray2D *array, int rows, int cols);

// Free intArray2D memory
void freeIntArray2DInit(intArray2D *array);

// Convert a csv file into an integer array
void csvToArray(intArray2D *array, const char *filename);

// CAMERA FUNCTIONS
// ****************************************************************8
void updateCameraShake(Camera2D *cam, int *screenShakeLenght,
                       int screenShakeStrenght, Vector2 windowSize);

// DRAWING ****************************************************************

void gameResolutionDraw(Vector2 windowSize, RenderTexture2D *target,
                        Vector2 *mousePos);

// TIMED EVENT ****************************************************************

typedef struct {
  float timer;             // Tracks time
  float delay;             // Amount of time to wait
  bool triggered;          // Is it triggered?
  bool particlesTriggered; // Has particles been triggered?

  Sound soundEffect; // Sound effect triggered?
} timedEvent;        // Simple event with a time delay and tracking

// Reset and or Initliaze timedEvent
void resetTimedEvent(timedEvent *event, float delay, Sound soundEffect);

// Update timedEvent
bool updateTimedEvent(timedEvent *event);

// PARTICLES
// ********************************************************************

#define MAX_PARTICLES 1024

typedef enum {
  NORMAL,         // Normal square or cirlces
  EXPANDING_RING, // Circular expanding ring
} ParticleType;

typedef struct {
  ParticleType type;

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

} Particle;

typedef struct {
  Particle pool[MAX_PARTICLES];
} ParticleSystem;

// Spawn normal particles
void spawnParticles(ParticleSystem *ps, Vector2 pos, float lifeMax, Color color,
                    Vector2 velocity, float size);

// Spawn expanding ring particle
void spawnParticlesExpandingRing(ParticleSystem *ps, Vector2 pos, float lifeMax,
                                 Color color, float size, float expandingRate,
                                 float ringThickness);

// Update all particles
void updateParticles(ParticleSystem *ps);

// Draw all particles
void drawParticles(ParticleSystem *ps);

// ANIMATIONS
// **********************************************************************

typedef struct {
  float timer; // Tracks time
  Texture2D texture;
  int size;       // pixel size of each frame
  int frameCount; //  Total frames
  int currentFrame;
  int direction;
  int yPos; // Y position on sprite sheet
} Animation;

// Create animation
void animationInit(Animation *animation, float timer, Texture2D texture,
                   int size, int frameCount, int currentFrame, int yPos);

// Play and draw animation
void playAnimation(Animation *animation, Rectangle destination, int direction,
                   float speed);

// Draw one specific frame from animation
void drawAnimatrionFrame(Animation *animation, Rectangle destination,
                         int direction, int frameNum);

// Play animation once and return true when done
bool playAnimationOnce(Animation *animation, Rectangle destination,
                       int direction, float speed);

// LEVEL DATA - levelData.c
// *************************************************************************

typedef struct {
  Texture2D texture;
  int width;
  int height;

  int tileSize;

} Tileset;

typedef struct {
  intArray2D *layer;

  int layerCount;
  Tileset tileset;

} LevelData;

LevelData levelDataInit(int layers, Tileset tileset, int arrayRows,
                        int arrayCols);

void levelDataDraw(LevelData level, int drawTileWidth, int drawTileHeight);

void levelDataFree(LevelData *level);

Tileset tilesetInit(Texture2D texture, int width, int height, int tileSize);

#endif
