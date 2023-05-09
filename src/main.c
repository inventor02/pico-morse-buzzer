#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "config.h"
#include "morse.h"

static uint clk_sys_hz;
static uint pwm_slice;
static uint pwm_chan;

static void init() 
{
  stdio_init_all();
  clk_sys_hz = clock_get_hz(clk_sys);
  printf("System clock is at %d Hz\n", clk_sys_hz);

  gpio_set_function(PIN_PWM, GPIO_FUNC_PWM);

  pwm_config config = pwm_get_default_config();
  pwm_config_set_clkdiv(&config, (float) clk_sys_hz / PWM_TARGET_FREQ);
  
  uint16_t pwm_wrap = PWM_TARGET_FREQ / PWM_TARGET_NOTE_HZ - 1;
  pwm_config_set_wrap(&config, pwm_wrap);

  pwm_slice = pwm_gpio_to_slice_num(PIN_PWM);
  pwm_chan = pwm_gpio_to_channel(PIN_PWM);

  uint16_t pwm_lvl = pwm_wrap * PWM_DUTY;

  pwm_init(pwm_slice, &config, false);
  pwm_set_chan_level(pwm_slice, pwm_chan, pwm_lvl);
}

static void play_dot()
{
  pwm_set_enabled(pwm_slice, true);
  sleep_ms(SLP_DOT);
  pwm_set_enabled(pwm_slice, false);
}

static void play_dash()
{
  pwm_set_enabled(pwm_slice, true);
  sleep_ms(SLP_DASH);
  pwm_set_enabled(pwm_slice, false);
}

static void play_char(const char *morse)
{
  for (int i = 0; i < MORSE_MAX_CHAR_LEN; i++)
  {
    const char c = morse[i];

    if (c == ' ')
    {
      sleep_ms(SLP_SPACE);
      continue;
    }
    else if (c == '.')
    {
      play_dot();
    }
    else if (c == '-')
    {
      play_dash();
    }
    else if (c == '\0')
    {
      break;
    }

    sleep_ms(SLP_BIT);
  }
  
  sleep_ms(SLP_CHAR);
}

void main()
{
  init();

  for (;;)
  {
    for (int i = 0; i < strlen(MORSE_TEXT); i++)
    {
      const char *morse = char_to_morse(MORSE_TEXT[i]);
      play_char(morse);
    }

    sleep_ms(SLP_WAIT);
  }
}