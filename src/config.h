#pragma once

#include <stdint.h>

static const char MORSE_TEXT[] = "HELLO WORLD";

static const uint8_t PIN_PWM = 18u;
static const uint32_t PWM_TARGET_FREQ = 1000000ul;
static const uint16_t PWM_TARGET_NOTE_HZ = 440u;

static const float PWM_DUTY = 0.5f;

static const uint SLP_BIT = 50u;
static const uint SLP_CHAR = 150u;
static const uint SLP_SPACE = 350u;

static const uint SLP_DOT = 50u;
static const uint SLP_DASH = 150u;

static const uint16_t SLP_WAIT = 10000u;