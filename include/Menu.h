#pragma once
#include <SDL.h>
#include "Game.h"

template <typename T>
struct Vector2 {
    T x, y;
};

class Button {
public:
    Button(SDL_Rect rect, bool clickable);
    bool isMouseContained();
    bool isMouseClicked();
    void draw(SDL_Renderer* renderer) const;

    SDL_Rect getRect() const { return m_Rect; }

private:
    SDL_Rect m_Rect;
    bool m_IsClickable;
};

namespace Menu {
    void initMenu(int screenWidth, int screenHeight);
    void drawStartMenu(SDL_Renderer* renderer);
    void updateStartMenu(GameState &gameState);
    void drawEndMenu(SDL_Renderer* renderer);
    void updateEndMenu(GameState &gameState);
}
