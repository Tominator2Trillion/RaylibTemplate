/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rayGui.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


static const int screenWidth = 800;
static const int screenHeight = 450;

Camera2D camera = { 0 };


// Update and draw game frame
void UpdateDrawFrame(void)
{   
    BeginDrawing();

    ClearBackground(RED);

    BeginMode2D(camera);
        

    EndMode2D();


    // screenWidth = GetScreenWidth();
    // screenHeight = GetScreenHeight();

    float titleFontSize = std::min(screenHeight/6, screenWidth/10);
    float titleX = screenWidth / 2;
    float titleY = screenHeight / 3;

    //float titleWidth = screenWidth/3*2;
    //float titleHeight = titleTexture.height * titleWidth / titleTexture.width;

    // DrawTexturePro(titleTexture, {0, 0, (float)titleTexture.width, (float)titleTexture.height}, {(float)screenWidth/2.0f, titleY, titleWidth, titleHeight}, {titleWidth/2, titleHeight/2}, 0, WHITE);

    //Buttons
    float buttonWidth = screenWidth / 4;
    float buttonHeight = screenHeight / 12;

    float buttonX = screenWidth / 2 - buttonWidth / 2;
    float buttonY = screenHeight / 2 + buttonHeight/2;

    float buttonSpacing = buttonHeight/5;

    rayGui::DrawButton(Rectangle{buttonX, buttonY, buttonWidth, buttonHeight}, "Start Game", WHITE, BLACK, BLACK, rayGui::rayMenuId == 0, []() {
        //currentGameState = GameState::MAIN_GAME;
    });

    buttonY += buttonHeight + buttonSpacing;

    rayGui::DrawButton({buttonX, buttonY, buttonWidth, buttonHeight}, "Settings", WHITE, BLACK, BLACK, rayGui::rayMenuId == 0, []() {
            rayGui::rayMenuId = 1;
    });

    buttonY += buttonHeight + buttonSpacing;

    rayGui::DrawButton({buttonX, buttonY, buttonWidth, buttonHeight}, "Credits", WHITE, BLACK, BLACK, rayGui::rayMenuId == 0, []() {
            rayGui::rayMenuId = 2;
    });

    buttonY += buttonHeight + buttonSpacing;

    rayGui::DrawButton({buttonX, buttonY, buttonWidth, buttonHeight}, "Exit", WHITE, BLACK, BLACK, rayGui::rayMenuId == 0, []() {
        CloseWindow();
    });

    switch(rayGui::rayMenuId) {
        case 1:{
            // show settings

            //panel
            // rayGui::SettingsPanel([]() {
            //     rayGui::rayMenuId = 0;
            // }); // runs in main func
            

            // TODO
            break;
        }
        case 2: {
            // show credits
    
            float creditsX = screenWidth / 4;
            float creditsY = screenHeight / 4;
            float creditsWidth = screenWidth / 2;
            float creditsHeight = screenHeight / 2;
    
            rayGui::InfoBox("Credits", "Code by: @chugget,\n@tominator2, @uj404\n\nGDD: @anemmeny\n\nMenu Music by: @1elienai", {creditsX, creditsY, creditsWidth, creditsHeight}, RED, WHITE, []() {
                rayGui::rayMenuId = 0;
            });
            break;
        }
    }

    EndDrawing();


}


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib game template");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    rayGui::font = LoadFontEx("resources/font/slkscr-Regular.ttf", 32, 0, 250);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    UnloadFont(rayGui::font);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}




