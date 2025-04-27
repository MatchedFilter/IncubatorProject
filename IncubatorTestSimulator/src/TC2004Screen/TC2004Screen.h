#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace IncubatorSim
{
    class TC2004Screen
    {
    public:
        TC2004Screen();
        ~TC2004Screen();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        void SendCommand(uint8_t command);
        void SendData(uint8_t data);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        TTF_Font *m_TC2004ScreenFont;
        SDL_Surface *m_TC2004ScreenSurface;
        SDL_Texture *m_TC2004ScreenTexture;
        SDL_Rect m_ImagePositionRect;
        SDL_Rect m_TextInitialPositionRect;
        static constexpr const int32_t LINE_COUNT = 4;
        static constexpr const int32_t LINE_SIZE = 20;
        static constexpr const int32_t CURSOR_WIDTH = 35;
        static constexpr const int32_t ROW_WIDTH = 56;
        static constexpr const int32_t LINE_STRING_SIZE = LINE_SIZE * LINE_COUNT + sizeof('\0');
        Uint16 m_Lines[LINE_STRING_SIZE];
        
    private:
        bool m_bIsDisplayOn;
        bool m_bAutoCursorUsed;
        bool m_bMultiLinesUsed;
        uint8_t m_CursorCount;
        uint8_t m_MaxCursorSize;

    };
} // namespace IncubatorSim
