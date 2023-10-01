# VS code setup

## Windows

GCC/G++ setup:

[https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

* To use external console, modify launch.json `externalConsole` parameter.
* Modiy g++ args in g++ args in tasks.json
  * Add `-std=c++17` to support c++ 17
  * Add `-DLOCAL_PROJECT` to define local macro
  * Modify `-o` to change generated a.exe binary location