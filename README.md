# Donkey Kong-Inspired Embedded Game

University microprocessors project using **C**, **PlatformIO**, and an **STM32 Nucleo-F031K6** board.

## Overview

The project uses low-level GPIO input, sprite data and display functions to implement a small arcade-style game. The source includes movement controls, graphical rendering, a jumping sprite, and collision/position checks.

## Technology
- C and CMSIS
- STM32 Nucleo-F031K6 (`nucleo_f031k6`)
- PlatformIO
- Bitmap artwork and sprite data

## Source layout
- `src/` — program and display source code
- `assets/` — graphics and conversion helper
- `additional-artwork/` — separate artwork files from the project folder
- `platformio.ini` — original build configuration

## Build
Open the repository folder in VS Code with PlatformIO installed. Select the `nucleo_f031k6` environment and build the project. Running it requires compatible board and display hardware; this archive has not been hardware-tested here.

## Project provenance
This archive was prepared from the `graphics_demo (1).zip` copy supplied in the original coursework folder. A second `graphics_demo.zip` copy was also present, and it differs in code. Verify which version is the final submission before publishing. Attribute any instructor starter code and contributions by teammates as appropriate, and check university rules before making coursework public.
