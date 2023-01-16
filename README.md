# Overview

This is a Ray-Tracer which is extremly similar to the one I wrote in Java. Just wanted to make sure I can re-write any java code into cpp.

Fully supports Windows (full UI and stuff) - NOW SUPPORTS GCC (tested on windows only). Linux works in `Legacy mode` which would output the rendered image onto the terminal, macOS was not tested.

# Requirements
- [CMake](https://cmake.org/)
- x64 Compiler (DOES NOT WORK WITH x86 COMPILERS!!!) (Currently `only` tested with [Visual Studio 22 Build Tools](https://visualstudio.microsoft.com/downloads/) and [MinGW GCC](https://github.com/niXman/mingw-builds-binaries/releases))
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows)


## Getting Started
Once you've cloned the repo, setup cmake with `cmake -S . -B build`. The binaries should be automatically copied in to the bin folder (no mater the build config or platform). 

### 3rd party libaries
- [Walnut](https://github.com/TheCherno/Walnut)
- [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h)
- [L2DFileDialog](https://github.com/Limeoats/L2DFileDialog)

### Demo Renders
![Demo 1](https://github.com/AbduEhab/Coal-RayTracer/blob/main/Renders/Ch12_RefractiveScene.jpg)
