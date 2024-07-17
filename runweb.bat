

@echo off

cd web_build/raylib-cmake-template
start "" http://localhost:8000/raylib-cmake-template.html
python -m http.server --directory . 8000


