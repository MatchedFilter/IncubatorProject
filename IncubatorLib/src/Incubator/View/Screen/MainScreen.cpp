#include "Incubator/View/Screen/MainScreen.h"
#include "Incubator/IncubatorDependencies.h"
#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{

    TC2004::String80 MainScreen::GetTemperature() const
    {
        TC2004::String80 result;
        result.Clear();
        result += static_cast<int32_t>(m_TemperatureInCelcius);
        result += ".";
        result += static_cast<int32_t>(m_TemperatureInCelcius * 10.0) % static_cast<int32_t>(10L);
        return result;
    }

    TC2004::String80 MainScreen::GetTargetTemperature() const
    {
        TC2004::String80 result;
        const uint8_t currentDay = static_cast<uint8_t>(m_TimeInformationData.m_CurrentTimestampInSecond / (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
        const uint32_t temperatureInMilliCelcius = (currentDay >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount)) ? m_SettingsData.m_LastDaysTemperatureInMilliCelcius : m_SettingsData.m_TemperatureInMilliCelcius;
        result.Clear();
        result += static_cast<int32_t>(temperatureInMilliCelcius / static_cast<uint32_t>(1000UL));
        result += ".";
        result += static_cast<int32_t>((temperatureInMilliCelcius % static_cast<uint32_t>(1000UL)) / static_cast<uint32_t>(100UL));
        return result;
    }

    TC2004::String80 MainScreen::GetTargetHumidity() const
    {
        TC2004::String80 result;
        const uint8_t currentDay = static_cast<uint8_t>(m_TimeInformationData.m_CurrentTimestampInSecond / (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
        const uint8_t humidityInPercent = (currentDay >= (m_SettingsData.m_TotalIncubationDayCount - m_SettingsData.m_LastDaysCount)) ? m_SettingsData.m_LastDaysHumidityInPercentage : m_SettingsData.m_HumidityInPercentage;
        result.Clear();
        result += static_cast<int32_t>(humidityInPercent);
        return result;
    }

    void MainScreen::DisplayTemperatureInformation()
    {
        if (m_bIsTemperatureSet)
        {
            m_Lcd->MoveCursor(0U, 4U);
            if (false == (m_TemperatureInCelcius < 0.0))
            {
                m_Lcd->Print(TC2004::String80(" "));
            }
            else
            {
                m_Lcd->Print(TC2004::String80("    "));
                m_Lcd->MoveCursor(0U, 4U);
            }
            m_Lcd->Print(GetTemperature());
        }
        if (m_bIsIncubatorDataProvided)
        {
            m_Lcd->MoveCursor(0U, 12U);
            m_Lcd->Print(GetTargetTemperature());
            m_Lcd->Print(TC2004::TC2004_CHAR_DEGREE_SYMBOL);
            m_Lcd->Print(TC2004::String80("C  "));
        }
    }

    void MainScreen::StartToDisplayTemperatureInformation()
    {
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Sck: ---- / ----    "));
    }

    void MainScreen::DisplayTemperatureFailure()
    {
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Sck Hatas"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("          "));
        m_Lcd->MoveCursor(3U, 0U);
    }
    
    void MainScreen::DisplayHumidityInformation()
    {
        if (m_bIsHumiditySet)
        {
            m_Lcd->MoveCursor(1U, 5U);
            TC2004::String80 humidityString;
            humidityString.Clear();
            if (m_HumidityInPercent < 10U)
            {
                humidityString += " ";
            }
            humidityString += static_cast<int32_t>(m_HumidityInPercent);
            if (m_HumidityInPercent < 100U)
            {
                humidityString += " ";
            }
            m_Lcd->Print(humidityString);
        }
        if (m_bIsIncubatorDataProvided)
        {
            m_Lcd->MoveCursor(1U, 10U);
            m_Lcd->Print(GetTargetHumidity());
            m_Lcd->Print(TC2004::String80("%  "));
        }
    }

    void MainScreen::StartToDisplayHumidityInformation()
    {
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("Nem: -- / --        "));
    }

    void MainScreen::DisplayHumidityFailure()
    {
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("Nem Hatas"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("          "));
    }

    void MainScreen::DisplayTimeInformation()
    {
        if (m_bTimeInformationProvided)
        {
            DisplayDay();
            DisplayHour();
            DisplayMinute();
            DisplaySecond();
        }
    }

    void MainScreen::DisplayDay()
    {
        m_Lcd->MoveCursor(2U, 5U);
        TC2004::String80 dayString;
        dayString.Clear();
        
        const uint8_t currentDay = static_cast<uint8_t>(((Time::TimeUtils::GetIncubatorTimestampInSecond() / static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(24UL));
        if (currentDay < 10U)
        {
            dayString += " ";
        }
        dayString += static_cast<int32_t>(currentDay);
        m_Lcd->Print(dayString);

        dayString.Clear();
        m_Lcd->MoveCursor(2U, 10U);
        if (m_SettingsData.m_TotalIncubationDayCount < 10U)
        {
            dayString += " ";
        }
        dayString += static_cast<int32_t>(m_SettingsData.m_TotalIncubationDayCount);
        m_Lcd->Print(dayString);
    }

    void MainScreen::DisplayHour()
    {
        m_Lcd->MoveCursor(3U, 5U);
        const uint8_t currentHour = static_cast<uint8_t>(((Time::TimeUtils::GetIncubatorTimestampInSecond() / static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(60UL)) % static_cast<uint32_t>(24UL));
        TC2004::String80 hourString;
        hourString.Clear();
        if (currentHour < 10U)
        {
            hourString += " ";
        }
        hourString += static_cast<int32_t>(currentHour);
        m_Lcd->Print(hourString);
    }

    void MainScreen::DisplayMinute()
    {
        m_Lcd->MoveCursor(3U, 11U);
        const uint8_t currentMinute = static_cast<uint8_t>((Time::TimeUtils::GetIncubatorTimestampInSecond()/ static_cast<uint32_t>(60UL)) % static_cast<uint32_t>(60UL));
        TC2004::String80 minuteString;
        minuteString.Clear();
        if (currentMinute < 10U)
        {
            minuteString += " ";
        }
        minuteString += static_cast<int32_t>(currentMinute);
        m_Lcd->Print(minuteString);
    }

    void MainScreen::DisplaySecond()
    {
        m_Lcd->MoveCursor(3U, 16U);
        const uint8_t currentSecond = static_cast<uint8_t>(Time::TimeUtils::GetIncubatorTimestampInSecond() % static_cast<uint32_t>(60UL));
        TC2004::String80 secondString;
        secondString.Clear();
        if (currentSecond < 10U)
        {
            secondString += " ";
        }
        secondString += static_cast<int32_t>(currentSecond);
        m_Lcd->Print(secondString);
    }

    MainScreen::MainScreen() : 
        AScreen { SCREEN_TYPE_MAIN },
        m_Lcd { nullptr },
        m_bIsTemperatureSet { false },
        m_TemperatureInCelcius { 0.0 },
        m_bIsHumiditySet { false },
        m_HumidityInPercent { 0U },
        m_bIsIncubatorDataProvided { false },
        m_bIsSettingsProvided { false },
        m_bTimeInformationProvided { false },
        m_bModelValid { true },
        m_TemperatureUpdateStatus { UPDATE_STATUS_VALID },
        m_HumidityUpdateStatus { UPDATE_STATUS_VALID }
    {
    }

    MainScreen::~MainScreen()
    {
    }

    void MainScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
        OnInitial();
        m_ScreenInformationUpdateTimerTask.SetDurationInMillisecond(static_cast<uint32_t>(500UL));
        m_ScreenInformationUpdateTimerTask.Start();
    }

    void MainScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Sck: ---- / ----"));
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("Nem: -- / --"));
        m_Lcd->MoveCursor(2U, 0U);
        m_Lcd->Print(TC2004::String80("G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n: -- / --"));
        m_Lcd->MoveCursor(3U, 0U);
        m_Lcd->Print(TC2004::String80("Saat:-- Dk:-- S:--"));
    }

    void MainScreen::UpdateSettingsData(const SettingsData &data)
    {
        m_SettingsData.Copy(data);
        m_bIsSettingsProvided = true;
        if (m_bTimeInformationProvided)
        {
            m_bIsIncubatorDataProvided = true;
        }
    }

    void MainScreen::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_TimeInformationData.Copy(data);
        m_bTimeInformationProvided = true;
        if (m_bIsSettingsProvided)
        {
            m_bIsIncubatorDataProvided = true;
        }
    }

    void MainScreen::UpdateTemperature(const double &temperatureInCelcius)
    {
        if (UPDATE_STATUS_INVALID == m_TemperatureUpdateStatus)
        {
            m_TemperatureUpdateStatus = UPDATE_STATUS_VALID;
        }
        m_bIsTemperatureSet = true;
        m_TemperatureInCelcius = temperatureInCelcius;
    }

    void MainScreen::UpdateHumidity(const uint8_t &humidityInPercent)
    {
        if (UPDATE_STATUS_INVALID == m_HumidityUpdateStatus)
        {
            m_HumidityUpdateStatus = UPDATE_STATUS_VALID;
        }
        m_bIsHumiditySet = true;
        m_HumidityInPercent = humidityInPercent;
    }

    void MainScreen::OnTemperatureFailure()
    {
        if (m_bModelValid)
        {
            if (UPDATE_STATUS_INVALID != m_TemperatureUpdateStatus)
            {
                m_TemperatureUpdateStatus = UPDATE_STATUS_INVALID;
            }
        }
    }

    void MainScreen::OnHumidityFailure()
    {
        if (m_bModelValid)
        {
            if (UPDATE_STATUS_INVALID != m_HumidityUpdateStatus)
            {
                m_HumidityUpdateStatus = UPDATE_STATUS_INVALID;
            }
        }
    }

    void MainScreen::OnModelFailure()
    {
        if (m_bModelValid)
        {
            m_bModelValid = false;
            m_Lcd->Clear();
            m_Lcd->Print(TC2004::String80("HATA: NVM1"));
        }
    }


    void MainScreen::Run()
    {
        if (m_bModelValid)
        {
            if (m_ScreenInformationUpdateTimerTask.IsFinished())
            {
                m_ScreenInformationUpdateTimerTask.Start();
                if (UPDATE_STATUS_SCREEN_UPDATED == m_HumidityUpdateStatus)
                {
                    DisplayHumidityInformation();
                }
                else if (UPDATE_STATUS_VALID == m_HumidityUpdateStatus)
                {
                    m_HumidityUpdateStatus = UPDATE_STATUS_SCREEN_UPDATED;
                    StartToDisplayHumidityInformation();
                }
                else
                {
                    DisplayHumidityFailure();
                }

                if (UPDATE_STATUS_SCREEN_UPDATED == m_TemperatureUpdateStatus)
                {
                    DisplayTemperatureInformation();
                }
                else if (UPDATE_STATUS_VALID == m_TemperatureUpdateStatus)
                {
                    m_TemperatureUpdateStatus = UPDATE_STATUS_SCREEN_UPDATED;
                    StartToDisplayTemperatureInformation();
                }
                else
                {
                    DisplayTemperatureFailure();
                }

                DisplayTimeInformation();
            }
        }
    }

    void MainScreen::OnUserAction(const JoystickEvent & event)
    {
        if (event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_MENU);
        }
    }


} // namespace Incubator
