#include "Widgets/OnOffWidget.h"
#include "Utils/IncubatorTestSimulatorUtils.h"
#include <cstring>

namespace IncubatorSim
{
    OnOffWidget::OnOffWidget() : 
        m_Renderer { nullptr },
        m_bIsOn { true },
        m_bHovered { false },
        m_bPressed { false },
        m_OnOffWidgetRect { 0, 0, 0, 0 }
    {
    }

    void OnOffWidget::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos, int32_t width, int32_t height)
    {
        m_OnOffWidgetRect.x = xPos;
        m_OnOffWidgetRect.y = yPos;
        m_OnOffWidgetRect.w = width;
        m_OnOffWidgetRect.h = height;
        m_Renderer = renderer;
    }


    void OnOffWidget::HandleEvents(const SDL_Event &event)
    {

        if (event.motion.x < m_OnOffWidgetRect.x + m_OnOffWidgetRect.w && event.motion.x > m_OnOffWidgetRect.x && 
            event.motion.y < m_OnOffWidgetRect.y + m_OnOffWidgetRect.h && event.motion.y > m_OnOffWidgetRect.y)
        {
            m_bHovered = true;
            IncubatorTestSimulatorUtils::SetCursor(SDL_SYSTEM_CURSOR_HAND);
        }
        else
        {
            m_bHovered = false;
            IncubatorTestSimulatorUtils::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
        }
        
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            if (m_bHovered)
            {
                m_bPressed = true;
            }
        }
            break;

        case SDL_MOUSEBUTTONUP:
            m_bPressed = false;
            break;
        
        default:
            break;
        }

        if (m_bPressed)
        {
            int xPos = event.motion.x;
            if (m_bIsOn)
            {
                m_bIsOn = false;
            }
            else
            {
                m_bIsOn = true;
            }
        }
    }

    void OnOffWidget::Run()
    {
        if (m_bIsOn)
        {
            SDL_SetRenderDrawColor(m_Renderer, 25, 240, 30, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 200, 25, 30, 255);
        }
        SDL_RenderFillRect(m_Renderer, &m_OnOffWidgetRect);
    }
} // namespace IncubatorSim
