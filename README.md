-----------------------------------



-----------------------------------
## Setup

Intall Ninja: https://ninja-build.org/
Install Emscripten: https://emscripten.org/docs/getting_started/downloads.html


Run the following command to setup the web build:
```sh
cmake -B web_build -G Ninja -DPLATFORM=Web "-DCMAKE_TOOLCHAIN_FILE=C:/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"
```
_Replace "C:/emsdk" to the path of emsdk(emscripten) on your computer_


-----------------------------------
## Running 

### Visual Studio Code

Automatic building and running is setup for Visual Studio Code

Cntrl + Shift + P -> Run task ->  BUILD_RUN_WEB
--
1. Copies the resource to the output
2. Builds the project
3. Hosts and opens the application
--

BUILD_WEB -> Only copies resources and builds
RUN_WEB -> Only hosts and opens the application

### Non-Visual Studio Code

1. Copy src/resources to web_build/resources

This can be done automatically with:
```sh
xcopy "src\resources" "web_build\resources\" /s /e /i /y
```

2. Build
```sh
cmake --build web_build
```

3. Run/Host

```sh
cd web_build/raylib-cmake-template
python -m http.server --directory . 8000
```

4. Open http://localhost:8000/raylib-cmake-template.html in your browser

-----------------------------------