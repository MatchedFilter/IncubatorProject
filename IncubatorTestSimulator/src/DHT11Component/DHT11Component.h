#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Widgets/Slider.h"
#include "Widgets/OnOffWidget.h"

namespace IncubatorSim
{
    class DHT11Component
    {
    public:
        DHT11Component();
        ~DHT11Component();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        void GetHumidityPercentageAndTemperature(uint8_t &humidityPercentage, uint8_t &temperature);
        void HandleEvents(const SDL_Event &event);
        void Run();

        bool IsFailed() const { return false == m_WorkingWidget.IsOn(); }

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_ImageTexture;
        SDL_Texture *m_TextTexture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_TemperatureTextRect;
        SDL_Rect m_HumidityTextRect;
        Slider m_TemperatureSlider;
        Slider m_HumiditySlider;
        OnOffWidget m_WorkingWidget;
        TTF_Font *m_DHT11Font;

    private:
        int32_t m_HumidityPercentage;
        double m_TemperatureInCelcius;
        static const uint8_t TEMPERATURE_STRING_SIZE = 16;
        static const uint8_t HUMIDITY_STRING_SIZE = 16;
        char m_TemperatureStringValue[TEMPERATURE_STRING_SIZE];
        char m_HumidityStringValue[HUMIDITY_STRING_SIZE];
        bool m_bHovered;
        bool m_bPressed;
        bool m_bReleased;

    };
} // namespace IncubatorSim