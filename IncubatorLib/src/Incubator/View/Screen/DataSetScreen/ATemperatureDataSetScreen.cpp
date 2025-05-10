#include "Incubator/View/Screen/DataSetScreen/ATemperatureDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    ATemperatureDataSetScreen::ATemperatureDataSetScreen(const EnumScreenType screenType) :
        ADataSetScreen( screenType )
    {
    }

    ATemperatureDataSetScreen::~ATemperatureDataSetScreen()
    {
    }

    TC2004::String80 ATemperatureDataSetScreen::GetTemperatureString(const uint32_t temperatureInMillicelcius)
    {
        TC2004::String80 result;
        result += static_cast<int32_t>(temperatureInMillicelcius / static_cast<uint32_t>(1000UL));
        result += ".";
        result += static_cast<int32_t>((temperatureInMillicelcius % static_cast<uint32_t>(1000UL)) / static_cast<uint32_t>(100UL));
        return result;
    }

    void ATemperatureDataSetScreen::PrintCurrentData() const
    {
        TC2004::String80 temperatureString = GetTemperatureString(GetCurrentTemperatureInMilliCelcius());
        m_Lcd->Print(temperatureString);
        m_Lcd->Print(TC2004::TC2004_CHAR_DEGREE_SYMBOL);
        m_Lcd->Print(TC2004::String80("C  "));
    }

    void ATemperatureDataSetScreen::PrintNewData() const
    {
        TC2004::String80 temperatureString = GetTemperatureString(GetChangedTemperatureInMilliCelcius());
        m_Lcd->Print(temperatureString);
        m_Lcd->Print(TC2004::TC2004_CHAR_DEGREE_SYMBOL);
        m_Lcd->Print(TC2004::String80("C  "));
    }

    void ATemperatureDataSetScreen::OnIncrementHighEvent()
    {
        const uint32_t nextTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius() + HIGH_INCREMENT_IN_MILLICELCIUS;
        uint32_t resultTemperatureInMilliCelcius = MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
        if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
        {
            resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
        }
        SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
    }

    void ATemperatureDataSetScreen::OnIncrementLowEvent()
    {
        const uint32_t nextTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius() + LOW_INCREMENT_IN_MILLICELCIUS;
        uint32_t resultTemperatureInMilliCelcius = MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
        if (nextTemperatureInMilliCelcius < MAX_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
        {
            resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
        }
        SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
    }

    void ATemperatureDataSetScreen::OnDecrementHighEvent()
    {
        const uint32_t changedTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius();
        uint32_t resultTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
        if (changedTemperatureInMilliCelcius > HIGH_INCREMENT_IN_MILLICELCIUS)
        {
            const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius - HIGH_INCREMENT_IN_MILLICELCIUS;
            if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
            {
                resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
            }
        }
        SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
    }

    void ATemperatureDataSetScreen::OnDecrementLowEvent()
    {
        const uint32_t changedTemperatureInMilliCelcius = GetChangedTemperatureInMilliCelcius();
        uint32_t resultTemperatureInMilliCelcius = MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS;
        if (changedTemperatureInMilliCelcius > LOW_INCREMENT_IN_MILLICELCIUS)
        {
            const uint32_t nextTemperatureInMilliCelcius = changedTemperatureInMilliCelcius - LOW_INCREMENT_IN_MILLICELCIUS;
            if (nextTemperatureInMilliCelcius > MIN_ALLOWED_TEMPEATURE_IN_MILLICELCIUS)
            {
                resultTemperatureInMilliCelcius = nextTemperatureInMilliCelcius;
            }
        }
        SetChangedTemperatureInMilliCelcius(resultTemperatureInMilliCelcius);
    }

    void ATemperatureDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_SettingsData);
    }

    EnumScreenType ATemperatureDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_TEMPERATURE_SETTINGS;
    }

} // namespace Incubator
