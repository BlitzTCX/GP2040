# GP2040 - Multi-platform Gamepad Firmware for RP2040 microcontrollers

The goal of GP2040 is to provide multi-platform compatibility for RP2040-based game controllers.

## Features

* Supports the following input modes:
  * Nintendo Switch
  * XInput (PC, Android, Raspberry Pi)
  * DirectInput (PC, Mac, PS3)
* Left and Right stick emulation via D-pad inputs
* 3 SOCD cleaning modes - Neutral, Up Priority (a.k.a. Hitbox), Second Input Priority
* Low input latency, with default 1000 Hz (1 ms) polling rate in all modes
* Save options to internal memory

## Performance

One of the highest priorities of GP2040 is low input latency. Why bother building a custom controller if it's just a laggy, input-missing mess?

Input latency is tested using the methodology outlined at [WydD's inputlag.science website](https://inputlag.science/controller/methodology), using the default 1000 Hz (1 ms) polling rate in the firmware.

| Mode | Poll Rate | Min | Max | Avg | Stdev | % on time | %1f skip | %2f skip |
| - | - | - | - | - | - | - | - | - |
| All | 1 ms | 0.56 ms | 1.59 ms | 0.96 ms | 0.28 ms | 95.28% | 4.72% | 0% |

## Development

The project is built using the PlatformIO VS Code plugin along with the [Wiz-IO Raspberry Pi Pico](https://github.com/Wiz-IO/wizio-pico) platform package, using the baremetal (Pico SDK) configuration. Only the Pico SDK is utilized, so there are no external dependencies at this time.

### Board Definition

There are two simple options for building GP2040 for your board. You can either edit an existing board definition, or create your own and configure PlatformIO to build it.

#### Existing Board

Once you have the project loaded into PlatformIO, edit the `include/definitions/RP2040Board.h` file to map your GPIO pins. Then from the VS Code status bar, use the PlatformIO environment selector to choose `env:raspberry-pi-pico`.

#### Create New Board

You can also add a new board definition to `include/definitions`. If you do, perform the following:

* Create new board definition file in `include/definitions` with your pin configuration and options.
* Add `#define` for your new board in `include/definitions/BoardConfig.h`.
* Add option to `src/RP2040Gamepad.cpp` in the `BOARD_DEFINITION` selection logic.
* Add a new environment to the `platformio.ini`
  * Copy from existing environment and rename
  * Replace `BOARD_DEFINITION=#` with the number in the `BoardConfig.h` file.

You will now have a new build environment target for PlatformIO. Use the VS Code status bar to select your new environment target.

### LED Configuration

If your board has WS2812 (or similar) LEDs, these can be configured in your board definition by setting the following:

| Name             | Description                  | Optional? |
| ---------------- | ---------------------------- | --------- |
| BOARD_LEDS_PIN   | Data PIN for your LED strand | No        |
| BOARD_LEDS_COUNT | Total LEDs in your strand    | No        |
| LEDS_BASE_ANIMATION_FIRST_PIXEL | The index for the first pixel in your base animation. If you have additional LEDs that aren't part of the base animation, this is your chance to leave them out of it. By default, this is 0. | Yes |
| LEDS_BASE_ANIMATION_LAST_PIXEL | Same as above, but the index for the final pixel. By default, this is 11... 12 LEDs for 12 buttons on a standard stickless layout. | Yes |
| LEDS_BASE_ANIMATION | This can be either "RAINBOW", "CHASE" or "STATIC" to set your base animation | Yes |
| LEDS_RAINBOW_CYCLE_TIME | For "RAINBOW," this sets how long (in ms) it takes to cycle from one color step to the next | Yes |
| LEDS_CHASE_CYCLE_TIME | For "CHASE," this sets how long (in ms) it takes to move from one pixel to the next | Yes |
| LEDS_STATIC_COLOR_COLOR | For "STATIC", this sets the static color. This is a uint32_t value. This should be friendlier, I know. | Yes |

### Building the Project

You should now be able to build or upload the project to you RP2040 board from the Build and Upload status bar icons. You can also open the PlatformIO tab and select the actions to execute for a particular environment. Output folders are defined in the `platformio.ini` file, but they should all default to a path under `.pio/build/${env:NAME}`.

## Usage

GP2040 uses a generic button labeling for gamepad state, which is then converted to the appropriate input type before sending. Here are the mappings of generic buttons to each supported platform/layout:

| GP2040  | XInput | Switch  | PS3          | DirectInput  | Arcade |
| ------- | ------ | ------- | ------------ | ------------ | ------ |
| B1      | A      | B       | Cross        | 2            | K1     |
| B2      | B      | A       | Circle       | 3            | K2     |
| B3      | X      | Y       | Square       | 1            | P1     |
| B4      | Y      | X       | Triangle     | 4            | P2     |
| L1      | LB     | L       | L1           | 5            | P4     |
| R1      | RB     | R       | R1           | 6            | P3     |
| L2      | LT     | ZL      | L2           | 7            | K4     |
| R2      | RT     | ZR      | R2           | 8            | K3     |
| S1      | Back   | Minus   | Select       | 9            | Coin   |
| S2      | Start  | Plus    | Start        | 10           | Start  |
| L3      | LS     | LS      | L3           | 11           | LS     |
| R3      | RS     | RS      | R3           | 12           | RS     |
| A1      | Guide  | Home    | -            | 13           | -      |
| A2      | -      | Capture | -            | 14           | -      |

Any button references in this documentation will use the `XInput` labels for clarity.

### Home Button

If you do not have a dedicated Home button, you can activate it via the **`BACK + START + UP`** button combination.

### Input Modes

To change the input mode, **hold one of the following buttons as the controller is plugged in:**

* **`RS`** for DirectInput/PS3
* **`BACK`** for Nintendo Switch
* **`START`** for XInput

Input mode is saved across power cycles.

### D-Pad Modes

You can switch between the 3 modes for the D-Pad **while the controller is in use by pressing one of the following combinations:**

* **`BACK + START + DOWN`** - D-Pad
* **`BACK + START + LEFT`** - Emulate Left Analog stick
* **`BACK + START + RIGHT`** - Emulate Right Analog stick

D-Pad mode is saved across power cycles.

### SOCD Modes

Simultaneous Opposite Cardinal Direction (SOCD) cleaning will ensure the controller doesn't send invalid directional inputs to the computer/console, like Left + Right at the same time. There are 3 modes to choose from **while the controller is in use by pressing one of the following combinations:**

* **`LS + RS + UP`** - **Up Priority mode**: Up + Down = Up, Left + Right = Neutral (Hitbox behavior)
* **`LS + RS + DOWN`** - **Neutral mode**: Up + Down = Neutral, Left + Right = Neutral
* **`LS + RS + LEFT`** - **Last Input Priority (Last Win)**: Hold Up then hold Down = Down, then release and re-press Up = Up. Applies to both axes.

SOCD mode is saved across power cycles.

## Acknowledgements

* Ha Thach's excellent [TinyUSB library](https://github.com/hathach/tinyusb) examples
* Thomas Fredericks' [Bounce2 Arduino library](https://github.com/thomasfredericks/Bounce2)
* fluffymadness's [tinyusb-xinput](https://github.com/fluffymadness/tinyusb-xinput) sample
* Kevin Boone's [blog post on using RP2040 flash memory as emulated EEPROM](https://kevinboone.me/picoflash.html)