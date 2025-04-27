#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Widgets/Slider.h"

namespace IncubatorSim
{
    class NTCComponent
    {
    public:
        NTCComponent();
        ~NTCComponent();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        inline double GetTemperature() { return m_TemperatureInDegree; }
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_ImageTexture;
        SDL_Texture *m_TextTexture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_TextRect;
        Slider m_Slider;
        TTF_Font *m_NTCFont;

    private:
        double m_TemperatureInDegree;
        static const uint8_t TEMPERATURE_STRING_SIZE = 16;
        char m_TemperatureStringValue[TEMPERATURE_STRING_SIZE];

    };
} // namespace IncubatorSim
