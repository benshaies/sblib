#include "../include/sblib.h"

void sbResetTimedEvent(sbTimedEvent *event, float delay, Sound soundEffect) {
  event->triggered = false;
  event->delay = delay;
  event->timer = 0.0f;
  event->particlesTriggered = false;

  event->soundEffect = soundEffect;
}

bool sbUpdateTimedEvent(sbTimedEvent *event) {
  if (!event->triggered) {
    event->timer += GetFrameTime();

    if (event->timer >= event->delay) {
      event->triggered = true;
      PlaySound(event->soundEffect);
    }
  }

  return event->triggered;
}
