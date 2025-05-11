#pragma once
#include "SDL2/SDL.h"
#include <cinttypes>

namespace IncubatorSim
{
    class OnOffWidget
    {
    public:
        OnOffWidget();
        ~OnOffWidget() = default;
        void Initialize(SDL_Renderer *renderer, int32_t xPos = 0, int32_t yPos = 0, int32_t width = 10, int32_t height = 10);
        void SetOnOffWidgetColor(SDL_Color color);
        void SetOnOffWidgetBgFrameColor(SDL_Color color);
        inline bool IsOn() const { return m_bIsOn; }
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        bool m_bIsOn;
        bool m_bHovered;
        bool m_bPressed;
        SDL_Rect m_OnOffWidgetRect;
    };
} // namespace IncubatorSim