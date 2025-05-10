#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
    void IncubatorInformationData::Reset()
    {
        m_PidData.Reset();
        m_SettingsData.Reset();
        m_TimeInformationData.Reset();
    }

    void IncubatorInformationData::Copy(const IncubatorInformationData &other)
    {
        m_PidData.Copy(other.m_PidData);
        m_SettingsData.Copy(other.m_SettingsData);
        m_TimeInformationData.Copy(other.m_TimeInformationData);
    }

} // namespace Incubator
