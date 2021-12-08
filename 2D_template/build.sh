#!/bin/bash
gcc main.c -o main $(pkg-config --cflags --libs sdl2 SDL2_gfx)
