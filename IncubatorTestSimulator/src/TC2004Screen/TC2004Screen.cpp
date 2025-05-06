#include "TC2004Screen.h"

namespace IncubatorSim
{
    static constexpr const char *TC2004_FONT_PATH = "resources/fonts/Fira_Code/static/FiraCode-Regular.ttf";
    static constexpr const uint32_t TC2004Screen_FONT_SIZE = 32UL;
    static constexpr const char *TC2004_IMAGE_PATH = "resources/images/TC2004.png";
    
    static constexpr const uint8_t _2LINES_4_BIT_MODE_CMD = 0x28U;
    static constexpr const uint8_t AUTO_CURSOR_SHIFT_TO_RIGHT_CMD = 0x06U;
    static constexpr const uint8_t DISPLAY_ON_CMD = 0x0CU;
    static constexpr const uint8_t DISPLAY_OFF_CMD = 0x08U;
    static constexpr const uint8_t CLEAR_SCREEN_CMD = 0x01U;
    static constexpr const uint8_t GOTO_LINE_1_CMD = 0x80U;
    static constexpr const uint8_t GOTO_LINE_1_END_CMD = 0x8FU;
    static constexpr const uint8_t GOTO_LINE_2_CMD = 0xC0U;
    static constexpr const uint8_t GOTO_LINE_2_END_CMD = 0xCFU;
    static constexpr const uint8_t GOTO_NEXT_CHAR = 0x14U;
    
    static constexpr const uint8_t TC2004_CHAR_LOWER_I = 0x00U;
    static constexpr const uint8_t TC2004_CHAR_LOWER_U = 0x01U;
    static constexpr const uint8_t TC2004_CHAR_LOWER_O = 0x02U;
    static constexpr const uint8_t TC2004_CHAR_LOWER_G = 0x03U;
    static constexpr const uint8_t TC2004_CHAR_LOWER_C = 0x04U;
    static constexpr const uint8_t TC2004_CHAR_UPPER_O = 0x05U;
    static constexpr const uint8_t TC2004_CHAR_DEGREE_SYMBOL = 0xDFU;
    static constexpr const uint8_t TC2004_CHAR_ARROW_SYMBOL = 0x7EU;

    TC2004Screen::TC2004Screen() :
        m_Renderer { nullptr },
        m_TC2004ScreenFont { nullptr },
        m_TC2004ScreenSurface { nullptr },
        m_TC2004ScreenTexture { nullptr },
        m_Lines { 0 },
        m_bIsDisplayOn { false },
        m_bAutoCursorUsed { false },
        m_bMultiLinesUsed { false },
        m_CursorCount { 0 },
        m_MaxCursorSize { LINE_SIZE * 2U}
    {
    }

    TC2004Screen::~TC2004Screen()
    {
        if (m_TC2004ScreenSurface != nullptr)
        {
            SDL_FreeSurface(m_TC2004ScreenSurface);
        }
        if (m_TC2004ScreenTexture != nullptr)
        {
            SDL_DestroyTexture(m_TC2004ScreenTexture);
        }
        if (m_TC2004ScreenFont != nullptr)
        {
            TTF_CloseFont(m_TC2004ScreenFont);
        }
    }


    bool TC2004Screen::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
    {
        bool bResult = true;
        m_Renderer = renderer;
    
        m_ImagePositionRect.x = xPos;
        m_ImagePositionRect.y = yPos;
        m_ImagePositionRect.w = 890; // 678
        m_ImagePositionRect.h = 538; // 286
    
        m_TextInitialPositionRect.x = m_ImagePositionRect.x + 94; // 60
        m_TextInitialPositionRect.y = m_ImagePositionRect.y + 146; // 92
    
        m_TC2004ScreenFont = TTF_OpenFont(TC2004_FONT_PATH, TC2004Screen_FONT_SIZE);
        if (m_TC2004ScreenFont == nullptr)
        {
            bResult = false;
        }
    
        if (bResult)
        {
            m_TC2004ScreenSurface = IMG_Load(TC2004_IMAGE_PATH);
            if (m_TC2004ScreenSurface == nullptr)
            {
                bResult = false;
            }
        }
        
        m_TC2004ScreenTexture = SDL_CreateTextureFromSurface(m_Renderer, m_TC2004ScreenSurface);
        return bResult;
    }

    void TC2004Screen::SendCommand(uint8_t command)
    {
        switch (command)
        {
        case _2LINES_4_BIT_MODE_CMD:
            m_bMultiLinesUsed = true;
            m_MaxCursorSize = LINE_COUNT * LINE_SIZE;
            break;
        case AUTO_CURSOR_SHIFT_TO_RIGHT_CMD:
            m_bAutoCursorUsed = true;
            break;
        case DISPLAY_ON_CMD:
            m_bIsDisplayOn = true;
            break;
        case DISPLAY_OFF_CMD:
            m_bIsDisplayOn = false;
            break;
        case CLEAR_SCREEN_CMD:
            {
                memset(m_Lines, 0, sizeof(m_Lines));
                m_CursorCount = 0;
            }
            break;
        case GOTO_NEXT_CHAR:
            m_CursorCount = (m_CursorCount + 1U) % m_MaxCursorSize;
            break;
        default:
        {
            if ((command >= GOTO_LINE_1_CMD) && (command <= GOTO_LINE_1_END_CMD))
            {
                const uint8_t column = command - GOTO_LINE_1_CMD;
                m_CursorCount = column;
            }
            else if ((command >= GOTO_LINE_2_CMD) && (command <= GOTO_LINE_2_END_CMD))
            {
                const uint8_t column = command - GOTO_LINE_2_CMD;
                m_CursorCount = ((LINE_SIZE * 2U) % m_MaxCursorSize) + column;;
            }
            break;
        }
        }
    }

    void TC2004Screen::SendData(uint8_t data)
    {
        switch (data)
        {
        case TC2004_CHAR_LOWER_I:
            m_Lines[m_CursorCount] = (char16_t)0x0131;
            break;
    
        case TC2004_CHAR_LOWER_U:
            m_Lines[m_CursorCount] = (char16_t)0x00FC;
            break;
    
        case TC2004_CHAR_LOWER_O:
            m_Lines[m_CursorCount] = (char16_t)0x00F6;
            break;
    
        case TC2004_CHAR_LOWER_G:
            m_Lines[m_CursorCount] = (char16_t)0x011F;
            break;

        case TC2004_CHAR_LOWER_C:
            m_Lines[m_CursorCount] = (char16_t)0x00E7;
            break;

        case TC2004_CHAR_UPPER_O:
            m_Lines[m_CursorCount] = (char16_t)0x00D6;
            break;

        case TC2004_CHAR_DEGREE_SYMBOL:
            m_Lines[m_CursorCount] = (char16_t)0x00B0;
            break;
    
        case TC2004_CHAR_ARROW_SYMBOL:
            m_Lines[m_CursorCount] = (char16_t)0x2192;
            break;
        
        default:
            m_Lines[m_CursorCount] = data;
            break;
        }
        if (m_bAutoCursorUsed)
        {
            m_CursorCount = (m_CursorCount + 1) % m_MaxCursorSize;
        }
    }

    void TC2004Screen::Run()
    {
        SDL_RenderCopy(m_Renderer, m_TC2004ScreenTexture, NULL, &m_ImagePositionRect);
        for (uint8_t i = 0; i < m_MaxCursorSize; i++)
        {
            SDL_Rect charRect;

            uint8_t columnNo = i % LINE_SIZE;
            uint8_t rowNo = i / LINE_SIZE;
            switch (rowNo)
            {
            case 0U:
                rowNo = 0U;
                break;
            case 1U:
                rowNo = 2U;
                break;
            case 2U:
                rowNo = 1U; 
                break;
            case 3:
                rowNo = 3U;
            
            default:
                break;
            }
            charRect.x = m_TextInitialPositionRect.x + columnNo * CURSOR_WIDTH;
            charRect.y = m_TextInitialPositionRect.y + rowNo * ROW_WIDTH;
            charRect.w = CURSOR_WIDTH;
            charRect.h = ROW_WIDTH;
            

            if (m_bIsDisplayOn)
            {
                if (m_Lines[i] == 0 )
                {
                    constexpr const Uint16 EMPTY_STRING[] = {(Uint16)' ', (Uint16)'\0' }; 
                    SDL_Surface *surfaceText = TTF_RenderUNICODE_LCD(m_TC2004ScreenFont ,EMPTY_STRING, {0, 0, 0}, {0, 0, 255});
                    SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
                    SDL_FreeSurface(surfaceText);
                    SDL_RenderCopy(m_Renderer, textureText, NULL, &charRect);
                    SDL_DestroyTexture(textureText);
                }
                else
                {
                    Uint16 charToPrint[] = {m_Lines[i], '\0'};
                    const SDL_Color foregroundColor = m_bMultiLinesUsed ? SDL_Color{0, 0, 0} : SDL_Color{255, 255, 255} ;
                    SDL_Surface *surfaceText = TTF_RenderUNICODE_LCD(m_TC2004ScreenFont ,charToPrint, foregroundColor, {0, 0, 255});
                    SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
                    SDL_FreeSurface(surfaceText);
                    SDL_RenderCopy(m_Renderer, textureText, NULL, &charRect);
                    SDL_DestroyTexture(textureText);
                }
            }
        }
    }

} // namespace IncubatorSim


