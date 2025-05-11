#include "Incubator/View/Screen/SensorsStatusScreen.h"
#include <cassert>

namespace Incubator
{

    void SensorsStatusScreen::PrintSensorStatus(const EnumSensorStatus &sensorStatus)
    {
        if (SENSOR_STATUS_NO_ERROR == sensorStatus)
        {
            m_Lcd->Print(TC2004::String80("YOK"));
        }
        else
        {
            m_Lcd->Print(TC2004::String80("VAR"));
        }
    }

    SensorsStatusScreen::SensorsStatusScreen() : 
        AScreen { SCREEN_TYPE_SENSORS_STATUS },
        m_Lcd { nullptr },
        m_SelectedLine { SENSOR_STATUS_SCREEN_LINE_SHT31 }
    {
    }

    SensorsStatusScreen::~SensorsStatusScreen()
    {
    }

    void SensorsStatusScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
        m_SensorsStatusData.Reset();
        constexpr uint32_t SENSOR_STATUS_SCREEN_UPDATE_TIME_IN_MILLISECOND = static_cast<uint32_t>(500UL);
        m_SensorStatusScreenUpdateTimerTask.SetDurationInMillisecond(SENSOR_STATUS_SCREEN_UPDATE_TIME_IN_MILLISECOND);
    }

    void SensorsStatusScreen::OnInitial()
    {
        Reset();

        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Sens"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_O);
        m_Lcd->Print(TC2004::String80("r Durumlar"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("]"));
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("SHT31: HATA ..."));
        m_Lcd->MoveCursor(2U, 0U);
        m_Lcd->Print(TC2004::String80("NTC: HATA ..."));
        m_Lcd->MoveCursor(3U, 0U);
        m_Lcd->Print(TC2004::String80("DTH11: HATA ..."));
        m_SensorStatusScreenUpdateTimerTask.Start();
    }

    void SensorsStatusScreen::Run()
    {
        if (m_SensorStatusScreenUpdateTimerTask.IsFinished())
        {
            m_SensorStatusScreenUpdateTimerTask.Start();
            m_Lcd->MoveCursor(1U, 12U);
            PrintSensorStatus(m_SensorsStatusData.m_Sht31Status);
            m_Lcd->MoveCursor(2U, 10U);
            PrintSensorStatus(m_SensorsStatusData.m_NtcStatus);
            m_Lcd->MoveCursor(3U, 12U);
            PrintSensorStatus(m_SensorsStatusData.m_Dht11Status);
        }
    }

    void SensorsStatusScreen::OnUserAction(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            m_SensorStatusScreenUpdateTimerTask.Stop();
            SetNextScreen(SCREEN_TYPE_MENU);
        }
    }

    void SensorsStatusScreen::UpdateSensorsStatus(const SensorsStatusData &data)
    {
        m_SensorsStatusData.Copy(data);
    }

} // namespace Incubator
