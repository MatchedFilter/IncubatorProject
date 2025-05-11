#include "Incubator/View/Screen/DataSetScreen/IDataSetScreen.h"
#include <cassert>

namespace Incubator
{

    IDataSetScreen::IDataSetScreen() :
        APidDataSetScreen( SCREEN_TYPE_DATA_SET_I )
    {
    }

    IDataSetScreen::~IDataSetScreen()
    {
    }

    int32_t IDataSetScreen::GetCurrentValue() const
    {
        return m_CurrentIncubatorInformationData->m_PidData.m_I;
    }

    int32_t IDataSetScreen::GetChangedValue() const
    {
        return m_ChangedIncubatorInformationData->m_PidData.m_I;
    }

    void IDataSetScreen::SetChangedValue(const int32_t value)
    {
        m_ChangedIncubatorInformationData->m_PidData.m_I = value;
    }

} // namespace Incubator
