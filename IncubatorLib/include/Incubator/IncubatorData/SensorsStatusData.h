#ifndef INCUBATOR_SENSORSSTATUSDATA_H
#define INCUBATOR_SENSORSSTATUSDATA_H
#include "EnumSensorStatus.h"

namespace Incubator
{
    struct SensorsStatusData
    {
    public:
        EnumSensorStatus m_Sht31Status;
        EnumSensorStatus m_NtcStatus;
        EnumSensorStatus m_Dht11Status;

        inline void Reset()
        {
            m_Sht31Status = SENSOR_STATUS_ERROR;
            m_NtcStatus = SENSOR_STATUS_ERROR;
            m_Dht11Status = SENSOR_STATUS_ERROR;
        }
        
        inline void Copy(const SensorsStatusData &other)
        {
            m_Sht31Status = other.m_Sht31Status;
            m_NtcStatus = other.m_NtcStatus;
            m_Dht11Status = other.m_Dht11Status;
        }
    };    
} // namespace Incubator

#endif // INCUBATOR_SENSORSSTATUSDATA_H