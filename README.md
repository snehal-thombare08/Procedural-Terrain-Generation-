# 🌍 Procedural Terrain Generator in C++ with SFML

A real-time procedural terrain generator built from scratch using C++ and SFML 3.0. Uses Perlin Noise algorithm to generate infinite, explorable worlds with multiple biomes.

![Terrain Preview](https://raw.githubusercontent.com/snehal-thombare08/Procedural-Terrain-Generation-/main/screenshot.png)

## ✨ Features

- **Perlin Noise Algorithm** — Smooth, natural-looking terrain generation
- **6 Octave Noise** — Detailed terrain with multiple levels of detail
- **8 Biomes** — Deep water, shallow water, beach, grass, forest, mountain rock, high rock, snow
- **Infinite World** — Explore endlessly in any direction
- **Real-time Navigation** — WASD movement with smooth scrolling
- **Zoom In/Out** — See the big picture or zoom into details
- **Random Seed** — Generate a completely new world instantly
- **60 FPS** — Smooth real-time rendering

## 🗺️ Biomes

| Color | Biome |
|-------|-------|
| 🔵 Dark Blue | Deep Water |
| 🔵 Light Blue | Shallow Water |
| 🟡 Beige | Sand / Beach |
| 🟢 Light Green | Grass Plains |
| 🟢 Dark Green | Forest |
| 🟤 Brown | Mountain Rock |
| ⬜ Light Brown | High Rock |
| ⬜ White | Snow Peaks |

## 🛠️ Built With

- **C++17**
- **SFML 3.0.2** — Window and graphics rendering
- **CMake** — Build system
- **MinGW (GCC 16.1)** — Compiler
- **Perlin Noise** — Custom implementation from scratch

## 📁 Project Structure

```
Procedural-Terrain-Generation/
├── src/
│   └── main.cpp       # Full terrain generator source code
├── CMakeLists.txt     # CMake build configuration
├── .gitignore
└── README.md
```

## 🚀 How to Build

### Prerequisites
- [MinGW-w64](https://www.mingw-w64.org/)
- [CMake](https://cmake.org/)
- [vcpkg](https://github.com/microsoft/vcpkg) with SFML installed

### Install SFML via vcpkg
```bash
vcpkg install sfml:x86-mingw-dynamic
```

### Build Steps
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake \
         -DSFML_DIR=C:/vcpkg/installed/x86-mingw-dynamic/share/sfml \
         -DCMAKE_C_COMPILER="C:/mingw64/mingw32/bin/gcc.exe" \
         -DCMAKE_CXX_COMPILER="C:/mingw64/mingw32/bin/g++.exe" \
         -G "MinGW Makefiles"
mingw32-make
```

### Run
```bash
.\TerrainGen.exe
```

> **Note:** Copy SFML debug DLLs to build folder before running:
> ```bash
> copy "C:\vcpkg\installed\x86-mingw-dynamic\debug\bin\*.dll" ".\build\"
> ```

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move Up |
| `S` | Move Down |
| `A` | Move Left |
| `D` | Move Right |
| `+` | Zoom In |
| `-` | Zoom Out |
| `R` | Generate New Random World |
| `Esc` | Close Window |

## 📐 Algorithm Details

- **Perlin Noise** — Gradient noise function for smooth terrain
- **Octave Layering** — 6 octaves with 0.5 persistence for natural detail
- **Height Mapping** — Normalized 0-1 height values mapped to biome colors
- **Tile Rendering** — 4x4 pixel tiles for performance optimization

## 👤 Author

**Snehal Thombare**  
GitHub: [@snehal-thombare08](https://github.com/snehal-thombare08)
