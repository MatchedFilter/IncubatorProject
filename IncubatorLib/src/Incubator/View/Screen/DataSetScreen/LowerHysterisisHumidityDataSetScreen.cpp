#include "Incubator/View/Screen/DataSetScreen/LowerHysterisisHumidityDataSetScreen.h"
#include <cassert>

namespace Incubator
{
    LowerHysterisisHumidityDataSetScreen::LowerHysterisisHumidityDataSetScreen() :
        AHysterisisHumidityDataSetScreen( SCREEN_TYPE_DATA_SET_LOWER_HYSTERISIS )
    {
    }

    LowerHysterisisHumidityDataSetScreen::~LowerHysterisisHumidityDataSetScreen()
    {
    }

    uint8_t LowerHysterisisHumidityDataSetScreen::GetCurrentDifference() const
    {
        return m_CurrentIncubatorInformationData->m_PidData.m_LowerHumidityDifference;
    }

    uint8_t LowerHysterisisHumidityDataSetScreen::GetChangedDifference() const
    {
        return m_ChangedIncubatorInformationData->m_PidData.m_LowerHumidityDifference;
    }

    void LowerHysterisisHumidityDataSetScreen::SetChangedDifference(const uint8_t &difference)
    {
        m_ChangedIncubatorInformationData->m_PidData.m_LowerHumidityDifference = difference;
    }

} // namespace Incubator
