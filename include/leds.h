/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "BoardConfig.h"
#include <vector>
#include "AnimationStation.hpp"
#include "NeoPico.hpp"
#include "gamepad.h"
#include "enums.h"
#include "gp2040.h"

#ifndef BOARD_LEDS_PIN
#define BOARD_LEDS_PIN -1
#endif

#ifndef LED_FORMAT
#define LED_FORMAT LED_FORMAT_GRB
#endif

#ifndef LEDS_PER_PIXEL
#define LEDS_PER_PIXEL 1
#endif

#ifndef LED_LAYOUT
#define LED_LAYOUT LED_LAYOUT_ARCADE_BUTTONS
#endif

#ifndef LEDS_BRIGHTNESS
#define LEDS_BRIGHTNESS 75
#endif

#ifndef LEDS_RAINBOW_CYCLE_TIME
#define LEDS_RAINBOW_CYCLE_TIME 40
#endif

#ifndef LEDS_CHASE_CYCLE_TIME
#define LEDS_CHASE_CYCLE_TIME 85
#endif

#ifndef LEDS_STATIC_COLOR_COLOR
#define LEDS_STATIC_COLOR_COLOR ColorRed
#endif

#ifndef LED_BRIGHTNESS_MAXIMUM
#define LED_BRIGHTNESS_MAXIMUM 128
#endif

#ifndef LED_BRIGHTNESS_STEPS
#define LED_BRIGHTNESS_STEPS 5
#endif

#ifndef LEDS_DPAD_LEFT
#define LEDS_DPAD_LEFT  -1
#endif

#ifndef LEDS_DPAD_DOWN
#define LEDS_DPAD_DOWN  -1
#endif

#ifndef LEDS_DPAD_RIGHT
#define LEDS_DPAD_RIGHT -1
#endif

#ifndef LEDS_DPAD_UP
#define LEDS_DPAD_UP    -1
#endif

#ifndef LEDS_BUTTON_B1
#define LEDS_BUTTON_B1  -1
#endif

#ifndef LEDS_BUTTON_B2
#define LEDS_BUTTON_B2  -1
#endif

#ifndef LEDS_BUTTON_B3
#define LEDS_BUTTON_B3  -1
#endif

#ifndef LEDS_BUTTON_B4
#define LEDS_BUTTON_B4  -1
#endif

#ifndef LEDS_BUTTON_R1
#define LEDS_BUTTON_R1  -1
#endif

#ifndef LEDS_BUTTON_L1
#define LEDS_BUTTON_L1  -1
#endif

#ifndef LEDS_BUTTON_L2
#define LEDS_BUTTON_L2  -1
#endif

#ifndef LEDS_BUTTON_R2
#define LEDS_BUTTON_R2  -1
#endif

#ifndef LEDS_BUTTON_S1
#define LEDS_BUTTON_S1  -1
#endif

#ifndef LEDS_BUTTON_S2
#define LEDS_BUTTON_S2  -1
#endif

#ifndef LEDS_BUTTON_L3
#define LEDS_BUTTON_L3  -1
#endif

#ifndef LEDS_BUTTON_R3
#define LEDS_BUTTON_R3  -1
#endif

#ifndef LEDS_BUTTON_A1
#define LEDS_BUTTON_A1  -1
#endif

#ifndef LEDS_BUTTON_A2
#define LEDS_BUTTON_A2  -1
#endif

void configureAnimations(AnimationStation *as);
AnimationHotkey animationHotkeys(Gamepad *gamepad);
PixelMatrix createLedButtonLayout(LEDLayout layout, int ledsPerPixel);
PixelMatrix createLedButtonLayout(LEDLayout layout, std::vector<uint8_t> *positions);

extern PixelMatrix matrix;

class LEDModule : public GPModule {
public:
  void setup();
  void loop();
  void process(Gamepad *gamepad);
  void trySave();
	uint32_t frame[100];
};

#endif
