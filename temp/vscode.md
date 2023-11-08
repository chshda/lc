# VS code setup

## Windows

GCC/G++ setup:

[https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

* To use external console, modify launch.json `externalConsole` parameter.
* Modiy g++ args in g++ args in tasks.json
  * Add `-std=c++17` to support c++ 17
  * Add `-DLOCAL_PROJECT` to define local macro
  * Modify `-o` to change generated a.exe binary location
* Modify C++ setting to support c++ 17 features based on [this](https://code.visualstudio.com/docs/cpp/config-mingw#_adding-additional-cc-settings)
  * Set `Compiler path` to g++ path
  * Set `IntelliSense mode` to gcc-x64


* msys2 to install g++, gdb etc: https://www.msys2.org/

```bash
$ pacman -S mingw-w64-ucrt-x86_64-gcc
$ pacman -S mingw-w64-x86_64-gdb
```

Update to support c++20 to use ranges namespace like ranges::sort(a)