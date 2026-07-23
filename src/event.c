#include "../include/sblib.h"

void SB_TimedEvent_Reset(SB_TimedEvent *event, float delay, Sound soundEffect) {
  event->triggered = false;
  event->delay = delay;
  event->timer = 0.0f;
  event->particlesTriggered = false;

  event->soundEffect = soundEffect;
}

bool SB_TimedEvent_Update(SB_TimedEvent *event) {
  if (!event->triggered) {
    event->timer += GetFrameTime();

    if (event->timer >= event->delay) {
      event->triggered = true;
      PlaySound(event->soundEffect);
    }
  }

  return event->triggered;
}
