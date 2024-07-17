

@echo off
cd web_build/raylib-cmake-template
start "" http://localhost:8000
python -m http.server --directory . 8000

PAUSE

