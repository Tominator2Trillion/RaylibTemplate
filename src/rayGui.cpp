#include "rayGui.hpp"
#include "settings.hpp"
#include "audioManager.hpp"
#include <functional>
#include <iostream>
#include <string> 

using std::string;



namespace rayGui {
    auto DrawButton(Rectangle button, string text, Color buttonColor, Color fontColor, Color highlightColor, bool isEnabled, std::function<void()> OnPress) -> void {
        if(scrollViewActive)
            button.y -= currentScroll;
        DrawRectangleRec(button, buttonColor);
        DrawCenteredText(text.c_str(), {button.x + button.width / 2, button.y + button.height / 2}, (int)(button.height / 2.5f), 0, fontColor, true);
        if (isEnabled && !buttonPressedThisFrame && CheckCollisionPointRec(GetMousePosition(), button)) {
            if(!CheckCollisionPointRec({GetMousePosition().x-GetMouseDelta().x,GetMousePosition().y- GetMouseDelta().y}, button)) {
                audio::PlaySoundOneShot(HOVER_SOUND);
                //audio::PlaySoundOneShot(CLICK_SOUND);
            }

            DrawRectangleLinesEx(button, 2, highlightColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                buttonPressedThisFrame = true;
                OnPress();
                audio::PlaySoundOneShot(CLICK_SOUND);
                //Play Click Sound (if enabled)
            }
        }
        if(scrollViewActive)
            scrollheight = std::max((int)(button.y + currentScroll + button.height), scrollheight);
    }

    bool buttonPressedThisFrame = false;


    auto CleanUp() -> void {
        buttonPressedThisFrame = false;
    }

    Font font = { 0 };


    auto DrawCenteredText(string text, Vector2 pos, int size, int spacing, Color col, bool centeredY) -> void {
        Vector2 boundSize = MeasureTextEx(font, text.c_str(), size, spacing);
        float offsetX =  -boundSize.x / 2;
        float offsetY = centeredY?-boundSize.y / 2:0;
        DrawTextEx(font, text.c_str(), {pos.x + offsetX, pos.y + offsetY}, size, spacing, col);
    }

    auto Slider(int value, Rectangle rect, int min, int max, Color empty, Color fill, Color textCol, bool showText) -> int {
        DrawRectangleRec(rect, empty);
        float percent = (value - min) / (float)(max - min);
        if(value >= max)
            percent = 1;
        DrawRectangleRec({rect.x, rect.y, rect.width * percent, rect.height}, fill);

        if(showText) {
            string text = std::to_string(value);
            int fontSize = (int)(rect.height * 0.8f);
            Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 1);
            Vector2 textPos = {rect.x + rect.width/2, rect.y + rect.height / 2 - textSize.y / 2};
            DrawText(text.c_str(), (int)(textPos.x-textSize.x/2), (int)textPos.y, fontSize, textCol);
        }

        if (elementsInteractable && CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            float percentX = (GetMousePosition().x - rect.x) / rect.width;
            value = (int)round(percentX * (max - min) + min);
        }

        return value;
    }

    auto SettingsPanel(std::function<void()> CloseLogic) -> void {
        float panelX = GetScreenWidth() / 4;
        float panelY = GetScreenHeight() / 4;
        float panelWidth = GetScreenWidth() / 2;
        float panelHeight = GetScreenHeight() / 2;

        DrawRectangle(panelX, panelY, panelWidth, panelHeight, RED);
        DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 2, WHITE);

        float currentX = panelX + 10;
        float currentY = panelY + 10;

        float size = panelHeight/10;

        rayGui::DrawCenteredText("Master Volume", {panelX + panelWidth / 2, panelY + 10}, size/3*2, 0, WHITE, false);

        currentY += size;

        settings::masterVolume = rayGui::Slider(settings::masterVolume*100.0f, {currentX, currentY, panelWidth - size/3*2, size/3*2}, 0, 100.0f, WHITE,GRAY, BLACK, true)/100.0f;

        currentY += size;

        rayGui::DrawCenteredText("Music Volume", {panelX + panelWidth / 4, currentY}, size/3, 0, WHITE, false);

        rayGui::DrawCenteredText("SFX Volume", {panelX + panelWidth / 4*3, currentY}, size/3, 0, WHITE, false);

        currentY += size/3*2;

        settings::musicVolume = rayGui::Slider(settings::musicVolume*100.0f, {currentX, currentY, panelWidth / 2 - size/3*2, size/3*2}, 0, 100.0f, WHITE,GRAY, BLACK, true)/100.0f;

        settings::sfxVolume = rayGui::Slider(settings::sfxVolume*100.0f, {currentX + panelWidth / 2, currentY, panelWidth / 2 - size/3*2, size/3*2}, 0, 100.0f, WHITE,GRAY, BLACK, true)/100.0f;
        
        
        //top right close button
        rayGui::DrawButton({panelX + panelWidth - size, panelY + size/3, size/3*2, size/3*2}, "X", RED, WHITE, WHITE, true, CloseLogic); 
    }

     auto InfoBox(string titleText, string contentText, Rectangle rectangle, Color col, Color textColor, std::function<void()> CloseLogic) -> void {
       
        DrawRectangleRec(rectangle, col);
        DrawRectangleLinesEx(rectangle, 2, textColor);
        DrawCenteredText(titleText, {rectangle.x + rectangle.width / 2, rectangle.y + rectangle.height/12}, rectangle.height/8, 0, textColor,false);
        DrawCenteredText(contentText, {rectangle.x + rectangle.width / 2, rectangle.y + rectangle.height/3.5f}, rectangle.height/16, 0, textColor,false);

        if (!buttonPressedThisFrame) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseLogic();
                buttonPressedThisFrame = true;
            }
        }
        if(scrollViewActive)
            scrollheight = std::max((int)(rectangle.y + currentScroll + rectangle.height), scrollheight);
    }

    // ScrollView
    //---------------------------------------------------------
    
    bool elementsInteractable = true;

    Rectangle scrollView;
    Rectangle scrollBarRect;
    bool scrollViewActive;
    int currentScroll;
    int scrollheight;
    int handleMouseOffset;

    Color scrollBarColor;
    Color scrollViewColor;

    auto BeginScrollView(Rectangle rectangle, Color sVColor, Color sBColor) -> void {
        scrollBarColor = sBColor;
        scrollViewColor = sVColor;
        BeginScissorMode((int)rectangle.x, (int)rectangle.y, (int)rectangle.width, (int)rectangle.height);
        scrollBarRect = {rectangle.x + rectangle.width, rectangle.y, rectangle.width / 20, rectangle.height};
        scrollViewActive = true;
        scrollView = rectangle;
        DrawRectangleRec(rectangle, scrollViewColor);
        elementsInteractable = CheckCollisionPointRec(GetMousePosition(), rectangle);
    }

    auto EndScrollView() -> void {
        EndScissorMode();
        scrollViewActive = false;
        scrollheight -= (int)scrollView.y;
        ScrollViewLogic();
        elementsInteractable = true;
    }

    auto ScrollViewLogic() -> void {
        if (scrollheight > scrollView.height) {
            // bar
            DrawRectangleRec(scrollBarRect, scrollBarColor);
            // handle
            float handleHeight = scrollView.height / (float)scrollheight * scrollView.height;
            float handleY = (currentScroll / (float)scrollheight) * scrollView.height;
            DrawRectangleRec({scrollBarRect.x, scrollBarRect.y + handleY, scrollBarRect.width, handleHeight}, Color {(static_cast<unsigned char>(scrollBarColor.r+50)), (static_cast<unsigned char>(scrollBarColor.g+50)), (static_cast<unsigned char>(scrollBarColor.b+50)), 255});
            if (CheckCollisionPointRec(GetMousePosition(), scrollBarRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                     handleMouseOffset = (int)(GetMousePosition().y - (scrollBarRect.y + handleY));
                }
            }

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(GetMousePosition(), scrollBarRect)) {
                     float newY = GetMousePosition().y - handleMouseOffset - scrollBarRect.y;
                     currentScroll = (int)(newY / scrollView.height * scrollheight);
                }
            }

            if (InScrollView(GetMousePosition())) {
                if (IsKeyPressed(KEY_UP)) {
                    currentScroll -= GetScreenHeight() / 25;
                } else if (IsKeyPressed(KEY_DOWN)) {
                    currentScroll += GetScreenHeight() / 25;
                }
            }

            currentScroll = clamp(currentScroll, 0, scrollheight - scrollView.height);
        }
    }

    auto InScrollView(Vector2 mousePos) -> bool {
        return CheckCollisionPointRec(mousePos, scrollView);
    }

    //---------------------------------------------------------





    // Utility
    //---------------------------------------------------------
    auto clamp(int value, int min, int max) -> int {
        return std::max(min, std::min(value, max));
    }

    //menu
    int rayMenuId{0};
    //---------------------------------------------------------
    
    


}


