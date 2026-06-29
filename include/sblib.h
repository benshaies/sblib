#ifndef SBLIB_H
#define SBLIB_H
#include <raylib.h>

// CUSTOM ARRAY

typedef struct {
  int *data;
  int size;
} intArray;

typedef struct {
  int **data;
  int rows;
  int cols;
} intArray2D;

void intArrayInit(intArray *array, int size);

void intArray2DInit(intArray2D *array, int rows, int cols);

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
  float timer;
  float delay;
  bool triggered;
  bool particlesTriggered;

  Sound soundEffect;
} timedEvent;

void resetTimedEvent(timedEvent *event, float delay, Sound soundEffect);

bool updateTimedEvent(timedEvent *event);

// PARTICLES
// ********************************************************************

#define MAX_PARTICLES 1024

typedef enum {
  NORMAL,
  EXPANDING_RING,
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

void spawnParticles(ParticleSystem *ps, Vector2 pos, float lifeMax, Color color,
                    Vector2 velocity, float size);

void spawnParticlesExpandingRing(ParticleSystem *ps, Vector2 pos, float lifeMax,
                                 Color color, float size, float expandingRate,
                                 float ringThickness);

void updateParticles(ParticleSystem *ps);

void drawParticles(ParticleSystem *ps);

// ANIMATIONS
// **********************************************************************

typedef struct {
  float timer;
  Texture2D texture;
  int size;
  int frameCount;
  int currentFrame;
  int direction;
  int yPos;
} Animation;

void animationInit(Animation *animation, float timer, Texture2D texture,
                   int size, int frameCount, int currentFrame, int yPos);

void playAnimation(Animation *animation, Rectangle destination, int direction,
                   float speed);

void drawAnimatrionFrame(Animation *animation, Rectangle destination,
                         int direction, int frameNum);

bool playAnimationOnce(Animation *animation, Rectangle destination,
                       int direction, float speed);

#endif

// LEVEL DATA - levelData.c
// *************************************************************************

typedef struct {
  Texture2D texture;
  int width;
  int height;
  int tileWidth;
  int tileHeight;
} Tileset;

typedef struct {
  intArray2D *layer;
  int arrayRows;
  int arrayCols;

  int layerCount;
  Tileset tileset;

  int tilesetSize;
} LevelData;

LevelData levelDataInit(int layers, Tileset tileset, int arrayRows,
                        int arrayCols);

void levelDataDraw(LevelData *level, Camera2D cam);

Tileset tilesetInit(Texture2D texture, int width, int height, int tileWidth,
                    int tileHeight);
