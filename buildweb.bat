

@echo off

xcopy "src\resources" "web_build\resources\" /s /e /i /y

cmake --build web_build

