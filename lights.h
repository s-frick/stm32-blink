#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdint.h>
typedef enum { LRED, LYELLOW, LGREEN } LIGHT;
typedef enum { RED, INTO_GREEN, GREEN, INTO_RED } STATE;
typedef enum { INTERRUPT } EVENT;
typedef enum { OFF, ON } LIGHT_STATE;

void setLight(LIGHT light, LIGHT_STATE);
void delay(uint32_t ms);

void start_lights();

#endif // LIGHTS_H
