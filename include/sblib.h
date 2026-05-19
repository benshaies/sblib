#ifndef SBLIB_H
#define SBLIB_H
#include <raylib.h>

// CUSTOM ARRAY

typedef struct {
  int *data;
  int size;
} SBIntArray;

typedef struct {
  int **data;
  int rows;
  int cols;
} SBIntArray2D;

void sbIntArrayInit(SBIntArray *array, int size);

void sbIntArray2DInit(SBIntArray2D *array, int rows, int cols);

void sbCsvToArray(SBIntArray2D *array, const char *filename);

// CAMERA FUNCTIONS
// ****************************************************************8
void sbUpdateCameraShake(Camera2D *cam, int *screenShakeLenght,
                         int screenShakeStrenght, Vector2 windowSize);

// DRAWING ****************************************************************

void sbGameResolutionDraw(Vector2 windowSize, RenderTexture2D *target,
                          Vector2 *mousePos);

// TIMED EVENT ****************************************************************

typedef struct {
  float timer;
  float delay;
  bool triggered;
  bool particlesTriggered;

  Sound soundEffect;
} sbTimedEvent;

void resetTimedEvent(sbTimedEvent *event, float delay, Sound soundEffect);

bool updateTimedEvent(sbTimedEvent *event);

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

void drawAnimationFrame(Animation *animation, Rectangle destination,
                        int direction, int frameNum);

bool playAnimationOnce(Animation *animation, Rectangle destination,
                       int direction, float speed);

#endif
