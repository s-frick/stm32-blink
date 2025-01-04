#include "lights.h"

typedef struct {
  STATE state;
  uint32_t timer;
} TSTATE;

void entry_red(TSTATE *s) {
  setLight(LRED, ON);
  setLight(LYELLOW, OFF);
  setLight(LGREEN, OFF);
  s->state = RED;
  s->timer = 0;
}

void entry_into_green(TSTATE *s) {
  setLight(LRED, ON);
  setLight(LYELLOW, ON);
  setLight(LGREEN, OFF);
  s->state = INTO_GREEN;
  s->timer = 0;
}

void entry_green(TSTATE *s) {
  setLight(LRED, OFF);
  setLight(LYELLOW, OFF);
  setLight(LGREEN, ON);
  s->state = GREEN;
  s->timer = 0;
}

void entry_into_red(TSTATE *s) {
  setLight(LRED, OFF);
  setLight(LYELLOW, ON);
  setLight(LGREEN, OFF);
  s->state = INTO_GREEN;
  s->timer = 0;
}

void start_lights() {
  TSTATE state = {RED, 0};
  entry_red(&state);

  while (1) {
    entry_red(&state);
    delay(15 * 1000);
    entry_into_green(&state);
    delay(500);
    entry_green(&state);
    delay(15 * 1000);
    entry_into_red(&state);
    delay(2 * 1000);
  }
}
