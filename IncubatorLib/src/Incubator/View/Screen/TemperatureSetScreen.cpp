#include "Incubator/View/Screen/TemperatureSetScreen.h"
#include "TC2004/String80.h"

namespace Incubator
{

    TC2004::String80 TemperatureSetScreen::GetTemperatureString(const uint32_t temperatureInMillicelcius)
    {
        TC2004::String80 result;
        result += static_cast<int32_t>(temperatureInMillicelcius / static_cast<uint32_t>(1000UL));
        result += ".";
        result += static_cast<int32_t>((temperatureInMillicelcius % static_cast<uint32_t>(1000UL)) / static_cast<uint32_t>(100UL));
        return result;
    }

    void TemperatureSetScreen::OnSaveStateEnter()
    {
        m_Lcd->MoveCursor(2U, 0U);
        m_Lcd->Print(TC2004::String80("Kaydedilsin mi?"));

        m_Lcd->MoveCursor(3U, 0U);
        if (QUESTION_SELECTION_NO == m_QuestionSelection)
        {
            m_Lcd->Print(TC2004::String80(" Evet        [Hay"));
            m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
            m_Lcd->Print(TC2004::String80("r]"));
        }
        else if (QUESTION_SELECTION_YES == m_QuestionSelection)
        {
            m_Lcd->Print(TC2004::String80("[Evet]        Hay"));
            m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
            m_Lcd->Print(TC2004::String80("r "));
        }
        else
        {
            // intentionally left blank
        }
    }

    void TemperatureSetScreen::HandleForSaveState(const JoystickEvent &event)
    {
        if (event.bIsButtonPressed)
        {
            if (QUESTION_SELECTION_YES == m_QuestionSelection)
            {
                SetNextScreen(SCREEN_TYPE_MENU);
                m_DataChangedEventHandlers.m_SettingsDataChangedEventHandler->OnUpdate(m_ChangedSettingsData);
            }
            else
            {
                SetNextScreen(SCREEN_TYPE_TEMPERATURE_SETTINGS);
            }
        }
        else
        {
            if (QUESTION_SELECTION_NO == m_QuestionSelection)
            {
                if (event.bIsLeftPressed)
                {
                    m_QuestionSelection = QUESTION_SELECTION_YES;
                    m_Lcd->MoveCursor(3U, 0U);
                    m_Lcd->Print(TC2004::String80("["));
                    m_Lcd->MoveCursor(3U, 5U);
                    m_Lcd->Print(TC2004::String80("]"));
                    m_Lcd->MoveCursor(3U, 13U);
                    m_Lcd->Print(TC2004::String80(" "));
                    m_Lcd->MoveCursor(3U, 19U);
                    m_Lcd->Print(TC2004::String80(" "));
                }
            }
            else
            {
                if (event.bIsRightPressed)
                {
                    m_QuestionSelection = QUESTION_SELECTION_NO;
                    m_Lcd->MoveCursor(3U, 0U);
                    m_Lcd->Print(TC2004::String80(" "));
                    m_Lcd->MoveCursor(3U, 5U);
                    m_Lcd->Print(TC2004::String80(" "));
                    m_Lcd->MoveCursor(3U, 13U);
                    m_Lcd->Print(TC2004::String80("["));
                    m_Lcd->MoveCursor(3U, 19U);
                    m_Lcd->Print(TC2004::String80("]"));
                }
            }
        }   
    }

    void TemperatureSetScreen::HandleForSetState(const JoystickEvent &event)
    {
        if (event.bIsButtonPressed)
        {
            m_bIsInSaveState = true;
            OnSaveStateEnter();
        }
        else
        {
            constexpr uint32_t MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS = static_cast<uint32_t>(55000UL);
            constexpr uint32_t MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS = static_cast<uint32_t>(15000UL);
            constexpr uint32_t HIGH_INCREMENT_IN_MILLICELCIUS = static_cast<uint32_t>(1000UL);
            constexpr uint32_t LOW_INCREMENT_IN_MILLICELCIUS = static_cast<uint32_t>(100UL);

            uint32_t &changedTemperatureInMilliCelcius = m_bIsForLastDays ? m_ChangedSettingsData.m_LastDaysTemperatureInMilliCelcius : m_ChangedSettingsData.m_TemperatureInMilliCelcius;
            if (event.bIsUpPressed)
            {
                const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius + HIGH_INCREMENT_IN_MILLICELCIUS;
                if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
                {
                    changedTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
                }
                else
                {
                    changedTemperatureInMilliCelcius = MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                }
            }
            else if (event.bIsDownPressed)
            {
                if (changedTemperatureInMilliCelcius > HIGH_INCREMENT_IN_MILLICELCIUS)
                {
                    const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius - HIGH_INCREMENT_IN_MILLICELCIUS;
                    if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
                    {
                        changedTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
                    }
                    else
                    {
                        changedTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                    }
                }
                else
                {
                    changedTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                }
            }
            else if (event.bIsRightPressed)
            {
                const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius + LOW_INCREMENT_IN_MILLICELCIUS;
                if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
                {
                    changedTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
                }
                else
                {
                    changedTemperatureInMilliCelcius = MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                }
            }
            else if (event.bIsLeftPressed)
            {
                if (changedTemperatureInMilliCelcius > LOW_INCREMENT_IN_MILLICELCIUS)
                {
                    const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius - LOW_INCREMENT_IN_MILLICELCIUS;
                    if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
                    {
                        changedTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
                    }
                    else
                    {
                        changedTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                    }
                }
                else
                {
                    changedTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
                }
            }
            else
            {
                // intentionally left blank
            }
            m_Lcd->MoveCursor(1U, 6U);
            m_Lcd->Print(GetTemperatureString(changedTemperatureInMilliCelcius));
            m_Lcd->Print(TC2004::String80("   "));
        }
    }

    TemperatureSetScreen::TemperatureSetScreen(DataChangedEventHandlers &eventHandlers,
            SettingsData &changedSettingsData,
            const SettingsData &currentSettingsData,
            bool bIsForLastDays) : 
        AScreen { m_bIsForLastDays ? SCREEN_TYPE_TEMPERATURE_SET_LAST_DAYS : SCREEN_TYPE_TEMPERATURE_SET },
        m_Lcd { nullptr },
        m_DataChangedEventHandlers { eventHandlers },
        m_QuestionSelection { QUESTION_SELECTION_NO },
        m_ChangedSettingsData { changedSettingsData },
        m_CurrentSettingsData { currentSettingsData },
        m_bIsForLastDays { bIsForLastDays },
        m_bIsInSaveState { false }
    {
    }

    TemperatureSetScreen::~TemperatureSetScreen()
    {
    }

    void TemperatureSetScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void TemperatureSetScreen::OnInitial()
    {
        Reset();
        m_bIsInSaveState = false;
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Eski: "));
        m_ChangedSettingsData.Copy(m_CurrentSettingsData);
        const uint32_t currentTemperature = m_bIsForLastDays ? m_CurrentSettingsData.m_LastDaysTemperatureInMilliCelcius : m_CurrentSettingsData.m_TemperatureInMilliCelcius;
        m_Lcd->Print(GetTemperatureString(currentTemperature));
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("Yeni: "));
        const uint32_t newTemperature = m_bIsForLastDays ? m_ChangedSettingsData.m_LastDaysTemperatureInMilliCelcius : m_ChangedSettingsData.m_TemperatureInMilliCelcius;
        m_Lcd->Print(GetTemperatureString(newTemperature));
    }

    void TemperatureSetScreen::Reset()
    {
        AScreen::Reset();
        m_QuestionSelection = QUESTION_SELECTION_NO;
    }

    void TemperatureSetScreen::Run()
    {
        // intentionally left blank
    }

    void TemperatureSetScreen::OnUserAction(const JoystickEvent &event)
    {
        if (m_bIsInSaveState)
        {
            HandleForSaveState(event);
        }
        else
        {
            HandleForSetState(event);
        }
    }


} // namespace Incubator
