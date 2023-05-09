#include "morse.h"

#include <stdint.h>

#include "pico/stdlib.h"

const char *char_to_morse(const char in)
{
  uint8_t code = (uint8_t) in;

  if (code == 32) return " ";

  if (code < 48 || code > 90) return "";

  code = code - 48;
  return MORSE_LUT[code];
}