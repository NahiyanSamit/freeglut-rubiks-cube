# Rubik's Cube Simulator

A 3D interactive Rubik's Cube simulator built with OpenGL and FreeGLUT.

## Features

- 3D animated Rubik's cube with smooth rotations
- Interactive camera controls (orbit, zoom)
- Layer rotations with visual animations
- Reset functionality

## Requirements

- OpenGL
- FreeGLUT
- GLU
- C++11 compatible compiler

## Build

```bash
make
```

## Run

```bash
./rubiks_cube
```

## Controls

- **Mouse**: Left drag to orbit camera, mouse wheel to zoom, right click to reset
- **R**: Reset camera and cube
- **H**: Show help

### Layer Rotations
- **Key alone**: Clockwise rotation
- **Shift + Key**: Counter-clockwise rotation

| Key | Layer |
|-----|-------|
| U | Top layer |
| M | Middle horizontal |
| D | Bottom layer |
| L | Left layer |
| C | Center vertical |
| X | Right layer |
| F | Front layer |
| B | Back layer |

## Clean

```bash
make clean
```
