#include "Menu.h"
#include <SDL_ttf.h>

Button::Button(SDL_Rect rect, bool clickable)
    : m_Rect{rect}, m_IsClickable{clickable}
{}

bool Button::isMouseContained()
{
    if (!m_IsClickable) return false;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Point point{mouseX, mouseY};
    return SDL_PointInRect(&point, &m_Rect);
}

bool Button::isMouseClicked()
{
    if (!m_IsClickable) return false;

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Point point{mouseX, mouseY};
    return (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && SDL_PointInRect(&point, &m_Rect);
}

void Button::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);
    SDL_RenderFillRect(renderer, &m_Rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White border
    SDL_RenderDrawRect(renderer, &m_Rect);
}

namespace Menu {
    static Button startButton{{0, 0, 200, 60}, true};
    static Button endButton{{0, 0, 200, 60}, false};
    // static Button replayButton{{0, 0, 200, 60}, true};
    static TTF_Font* font = nullptr;

    void initMenu(int screenWidth, int screenHeight)
    {
        if (!font)
            font = TTF_OpenFont("../font.ttf", 24);

        int btnW = 300, btnH = 60;
        int centerX = (screenWidth - btnW) / 2;

        startButton = Button({centerX, screenHeight / 2 - 30, btnW, btnH}, true);
        endButton   = Button({centerX, screenHeight / 2 - 100, btnW, btnH}, true);
        // replayButton = Button({centerX, screenHeight / 2 + 40, btnW, btnH}, true);
    }

    void renderCenteredText(SDL_Renderer* renderer, const char* text, SDL_Rect area)
    {
        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface* surf = TTF_RenderText_Blended(font, text, white);
        if (!surf) return;

        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        if (!tex) return;

        SDL_Rect dst;
        SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
        dst.x = area.x + (area.w - dst.w) / 2;
        dst.y = area.y + (area.h - dst.h) / 2;

        SDL_RenderCopy(renderer, tex, nullptr, &dst);
        SDL_DestroyTexture(tex);
    }

    void drawStartMenu(SDL_Renderer* renderer)
    {
        startButton.draw(renderer);
        renderCenteredText(renderer, "START", startButton.getRect());
    }

    void updateStartMenu(GameState &gameState)
    {
        if (startButton.isMouseContained() && startButton.isMouseClicked())
        {
            gameState = GameState::RUNNING;
        }
    }

    void drawEndMenu(SDL_Renderer* renderer, GameState &gameState)
    {
        endButton.draw(renderer);
        if (gameState == GameState::GAME_OVER)
        {
            renderCenteredText(renderer, "GAME OVER", endButton.getRect());
        }
        else if (gameState == GameState::VICTORY)
        {
            renderCenteredText(renderer, "VICTORY!", endButton.getRect());
        }

        // replayButton.draw(renderer);
        // renderCenteredText(renderer, "Replay", replayButton.getRect());
    }

    void updateEndMenu(GameState &gameState)
    {
        if (endButton.isMouseContained() && endButton.isMouseClicked())
        {
            gameState = GameState::QUIT;
        }

        /*
        if (replayButton.isMouseContained() && replayButton.isMouseClicked())
        {
            gameState = GameState::RUNNING;
        }
        */
    }
}
