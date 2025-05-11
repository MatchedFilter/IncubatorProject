#include "Incubator/View/Screen/DataSetScreen/AHysterisisHumidityDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    AHysterisisHumidityDataSetScreen::AHysterisisHumidityDataSetScreen(const EnumScreenType screenType) :
        ADataSetScreen( screenType )
    {
    }

    AHysterisisHumidityDataSetScreen::~AHysterisisHumidityDataSetScreen()
    {
    }

    TC2004::String80 AHysterisisHumidityDataSetScreen::GetHysterisisValueString(const uint8_t difference)
    {
        TC2004::String80 result;
        result += static_cast<int32_t>(difference);
        return result;
    }

    void AHysterisisHumidityDataSetScreen::PrintCurrentData() const
    {
        TC2004::String80 valueString = GetHysterisisValueString(GetCurrentDifference());
        m_Lcd->Print(valueString);
    }

    void AHysterisisHumidityDataSetScreen::PrintNewData() const
    {
        TC2004::String80 valueString = GetHysterisisValueString(GetChangedDifference());
        valueString += "    ";
        m_Lcd->Print(valueString);
    }

    void AHysterisisHumidityDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextValue = GetChangedDifference() + HIGH_INCREMENT_CONSTANT;
        uint8_t resultValue = MAX_ALLOWED_CONSTANT;
        if (nextValue < MAX_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        SetChangedDifference(resultValue);
    }

    void AHysterisisHumidityDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextValue = GetChangedDifference() + LOW_INCREMENT_CONSTANT;
        uint8_t resultValue = MAX_ALLOWED_CONSTANT;
        if (nextValue < MAX_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        SetChangedDifference(resultValue);
    }

    void AHysterisisHumidityDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedValue = GetChangedDifference();
        uint8_t resultValue = MIN_ALLOWED_CONSTANT;
        if (changedValue > HIGH_INCREMENT_CONSTANT)
        {
            const uint8_t nextValue = changedValue - HIGH_INCREMENT_CONSTANT;
            if (nextValue > MIN_ALLOWED_CONSTANT)
            {
                resultValue = nextValue;
            }
        }
        SetChangedDifference(resultValue);
    }

    void AHysterisisHumidityDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedValue = GetChangedDifference();
        uint8_t resultValue = MIN_ALLOWED_CONSTANT;
        if (changedValue > LOW_INCREMENT_CONSTANT)
        {
            const uint8_t nextValue = changedValue - LOW_INCREMENT_CONSTANT;
            if (nextValue > MIN_ALLOWED_CONSTANT)
            {
                resultValue = nextValue;
            }
        }
        SetChangedDifference(resultValue);
    }

    void AHysterisisHumidityDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_AdminData);
    }

    EnumScreenType AHysterisisHumidityDataSetScreen::GetNextScreenForYesSelection() const
    {
        return SCREEN_TYPE_HYSTERISIS_HUMIDITY;
    }


    EnumScreenType AHysterisisHumidityDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_HYSTERISIS_HUMIDITY;
    }

} // namespace Incubator
