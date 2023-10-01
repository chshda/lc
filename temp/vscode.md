# VS code setup

## Windows

GCC/G++ setup:

[https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

* To use external console, modify launch.json externalConsole parameter.
* Add `-DLOCAL_PROJECT` to g++ args in tasks.json to define local macro.
* Modify `-o` in g++ args to change generated a.exe binary location.