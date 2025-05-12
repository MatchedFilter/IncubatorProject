#include "Incubator/View/Screen/DataSetScreen/APidDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    APidDataSetScreen::APidDataSetScreen(const EnumScreenType screenType) :
        ADataSetScreen( screenType )
    {
    }

    APidDataSetScreen::~APidDataSetScreen()
    {
    }

    TC2004::String80 APidDataSetScreen::GetPidValueString(const int32_t value)
    {
        
        TC2004::String80 result;
        const int32_t positiveValue = (value < 0) ? -value: value;
        if (value < 0)
        {
            result += "-";
        }
        result += positiveValue / static_cast<int32_t>(10L);
        result += ".";
        result += positiveValue % static_cast<int32_t>(10L);
        result += "    ";
        return result;
    }

    void APidDataSetScreen::PrintCurrentData() const
    {
        TC2004::String80 valueString = GetPidValueString(GetCurrentValue());
        m_Lcd->Print(valueString);
    }

    void APidDataSetScreen::PrintNewData() const
    {
        TC2004::String80 valueString = GetPidValueString(GetChangedValue());
        m_Lcd->Print(valueString);
    }

    void APidDataSetScreen::OnIncrementHighEvent()
    {
        const int32_t nextValue = GetChangedValue() + HIGH_INCREMENT_CONSTANT;
        int32_t resultValue = MAX_ALLOWED_CONSTANT;
        if (nextValue < MAX_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        SetChangedValue(resultValue);
    }

    void APidDataSetScreen::OnIncrementLowEvent()
    {
        const int32_t nextValue = GetChangedValue() + LOW_INCREMENT_CONSTANT;
        int32_t resultValue = MAX_ALLOWED_CONSTANT;
        if (nextValue < MAX_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        SetChangedValue(resultValue);
    }

    void APidDataSetScreen::OnDecrementHighEvent()
    {
        const int32_t changedValue = GetChangedValue();
        int32_t resultValue = MIN_ALLOWED_CONSTANT;
        const int32_t nextValue = changedValue - HIGH_INCREMENT_CONSTANT;
        if (nextValue > MIN_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        SetChangedValue(resultValue);
    }

    void APidDataSetScreen::OnDecrementLowEvent()
    {
        const int32_t changedValue = GetChangedValue();
        int32_t resultValue = MIN_ALLOWED_CONSTANT;
        const int32_t nextValue = changedValue - LOW_INCREMENT_CONSTANT;
        if (nextValue > MIN_ALLOWED_CONSTANT)
        {
            resultValue = nextValue;
        }
        
        SetChangedValue(resultValue);
    }

    void APidDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_AdminData);
    }

    EnumScreenType APidDataSetScreen::GetNextScreenForYesSelection() const
    {
        return SCREEN_TYPE_TEMPERATURE_PID;
    }

    EnumScreenType APidDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_TEMPERATURE_PID;
    }

} // namespace Incubator
