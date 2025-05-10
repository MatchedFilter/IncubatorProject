#ifndef INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H
#define INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H
#include "SettingsData.h"
#include "TimeInformationData.h"
#include "PidData.h"
namespace Incubator
{
    struct IncubatorInformationData
    {
    public:
        PidData m_PidData;
        SettingsData m_SettingsData;
        TimeInformationData m_TimeInformationData;

    public:
        void Reset();
        void Copy(const IncubatorInformationData &other);
    };
    
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H