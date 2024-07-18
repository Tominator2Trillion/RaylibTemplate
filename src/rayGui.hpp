#pragma once

#include <raylib.h>
#include "settings.hpp"
#include "audioManager.hpp"
#include <functional>
#include <algorithm>
#include <iostream>

using std::string;

namespace rayGui {

    extern auto CleanUp() -> void;

    extern auto DrawButton(Rectangle button, std::string text, Color buttonColor, Color fontColor, Color highlightColor, bool isEnabled, std::function<void()> OnPress) -> void;
    extern auto DrawCenteredText(std::string text, Vector2 pos, int size, int spacing, Color col, bool centeredY) -> void;

    
    extern auto Slider(int value, Rectangle rect, int min, int max, Color empty, Color fill, Color textCol, bool showText = true) -> int;

    extern auto SettingsPanel(std::function<void()> CloseLogic) -> void;



    extern auto InfoBox(string titleText, string contentText, Rectangle rectangle, Color col, Color textColor, std::function<void()> CloseLogic) -> void;

    extern auto clamp(int value, int min, int max) -> int;

    extern bool buttonPressedThisFrame;
    
    //---------------------------------------------------------
    extern int rayMenuId;


    // ScrollView
    //---------------------------------------------------------
    extern bool elementsInteractable;

    extern Rectangle scrollView;
    extern Rectangle scrollBarRect;
    extern bool scrollViewActive;
    extern int currentScroll;
    extern int scrollheight;
    extern int handleMouseOffset;

    extern Color scrollBarColor;
    extern Color scrollViewColor;

    extern auto BeginScrollView(Rectangle rectangle, Color sVColor = RED, Color sBColor = GRAY) -> void;
    extern auto EndScrollView() -> void;
    extern auto ScrollViewLogic() -> void;
    extern auto InScrollView(Vector2 mousePos) -> bool;
    //---------------------------------------------------------


    extern Font font;
}