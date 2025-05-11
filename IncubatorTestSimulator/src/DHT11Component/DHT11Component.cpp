#include "DHT11Component.h"
#include "Utils/IncubatorTestSimulatorUtils.h"


namespace IncubatorSim
{
    static constexpr const char * DHT11_IMAGE_PATH = "resources/images/DHT11.png";
    static constexpr const char *DHT11_FONT_PATH = "resources/fonts/Fira_Code/static/FiraCode-Regular.ttf";
    static constexpr const int32_t DHT11_FONT_SIZE = 32;

    DHT11Component::DHT11Component() :
        m_Renderer { nullptr },
        m_ImageTexture { nullptr },
        m_TextTexture { nullptr },
        m_DHT11Font { nullptr },
        m_HumidityPercentage { 50 },
        m_TemperatureInCelcius { 25.0 },
        m_TemperatureStringValue { 0 },
        m_HumidityStringValue { 0 },
        m_bHovered { false },
        m_bPressed { false }
    {
    }

    DHT11Component::~DHT11Component()
    {
        if (m_ImageTexture != nullptr)
        {
            SDL_DestroyTexture(m_ImageTexture);
        }
        if (m_TextTexture != nullptr)
        {
            SDL_DestroyTexture(m_TextTexture);
        }
    }

    bool DHT11Component::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
    {
        bool bResult = true;
        m_Renderer = renderer;

        m_ImageRect.x = xPos;
        m_ImageRect.y = yPos;
        m_ImageRect.w = 128;
        m_ImageRect.h = 128;

        m_TemperatureTextRect.x = m_ImageRect.x;
        m_TemperatureTextRect.y = m_ImageRect.y + 100;
        m_TemperatureTextRect.w = 60;
        m_TemperatureTextRect.h = 30;

        m_HumidityTextRect.x = m_ImageRect.x;
        m_HumidityTextRect.y = m_ImageRect.y + 140;
        m_HumidityTextRect.w = 60;
        m_HumidityTextRect.h = 30;

        m_TemperatureSlider.Initialize(m_Renderer, m_ImageRect.x, m_ImageRect.y + 130, 120, 7, 20);
        m_HumiditySlider.Initialize(m_Renderer, m_ImageRect.x, m_ImageRect.y + 170, 120, 7, 20);

        m_WorkingWidget.Initialize(renderer,
            m_ImageRect.x + m_ImageRect.w - 4,
            m_ImageRect.y + 4,
            10, 10
        );

        m_DHT11Font = TTF_OpenFont(DHT11_FONT_PATH, DHT11_FONT_SIZE);
        if (m_DHT11Font == nullptr)
        {
            bResult = false;
        }

        if (bResult)
        {
            SDL_Surface *dht11Surface = IMG_Load(DHT11_IMAGE_PATH);
            if (dht11Surface == nullptr)
            {
                bResult = false;
            }
            else
            {
                m_ImageTexture = SDL_CreateTextureFromSurface(m_Renderer, dht11Surface);
                SDL_FreeSurface(dht11Surface);
            }
        }

        return bResult;
    }

    void DHT11Component::GetHumidityPercentageAndTemperature(uint8_t &humidityPercentage, uint8_t &temperature)
    {
        humidityPercentage = m_HumidityPercentage;
        temperature = m_TemperatureInCelcius;
    }


    void DHT11Component::HandleEvents(const SDL_Event &event)
    {
        m_WorkingWidget.HandleEvents(event);
        m_TemperatureSlider.HandleEvents(event);
        m_HumiditySlider.HandleEvents(event);
    }

    void DHT11Component::Run()
    {
        SDL_RenderCopy(m_Renderer, m_ImageTexture, NULL, &m_ImageRect);
        m_WorkingWidget.Run();
        m_TemperatureSlider.Run();
        m_HumiditySlider.Run();

        m_TemperatureInCelcius = (static_cast<double>(m_TemperatureSlider.GetSliderValue()) / 5.0) + 25.0;
        sprintf(m_TemperatureStringValue, "%.02lf", m_TemperatureInCelcius);
        SDL_Surface *temperatureSurfaceText = TTF_RenderText_Solid(m_DHT11Font ,m_TemperatureStringValue, {30, 213, 30});
        SDL_Texture *temperatureTextureText = SDL_CreateTextureFromSurface(m_Renderer, temperatureSurfaceText);
        SDL_FreeSurface(temperatureSurfaceText);
        SDL_RenderCopy(m_Renderer, temperatureTextureText, NULL, &m_TemperatureTextRect);

        
        m_HumidityPercentage = m_HumiditySlider.GetSliderValue();
        sprintf(m_HumidityStringValue, "%%%2d", m_HumidityPercentage);
        SDL_Surface *humiditySurfaceText = TTF_RenderText_Solid(m_DHT11Font ,m_HumidityStringValue, {30, 213, 30});
        SDL_Texture *humidityTextureText = SDL_CreateTextureFromSurface(m_Renderer, humiditySurfaceText);
        SDL_FreeSurface(humiditySurfaceText);
        SDL_RenderCopy(m_Renderer, humidityTextureText, NULL, &m_HumidityTextRect);
        SDL_DestroyTexture(humidityTextureText);
}
} // namespace IncubatorSim
