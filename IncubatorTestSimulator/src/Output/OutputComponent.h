#ifndef _ITS_OUTPUTCOMPONENT_H_
#define _ITS_OUTPUTCOMPONENT_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace IncubatorSim
{
    class OutputComponent
    {
    public:
        OutputComponent();
        ~OutputComponent();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos, int32_t width, int32_t height, const char *imagePath);
        void TurnOn() { m_bIsOn = true; }
        void TurnOff() { m_bIsOn = false; }
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_ImageTexture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_StatusRect;
        bool m_bIsOn;
    };
} // namespace IncubatorSim

#endif // _ITS_OUTPUTCOMPONENT_H_