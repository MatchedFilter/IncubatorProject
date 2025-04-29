#ifndef INCUBATOR_HUMIDITYCONTROLLER_H
#define INCUBATOR_HUMIDITYCONTROLLER_H
#include <cinttypes>
#include "EnumState.h"
namespace Incubator
{
    class HumidityController
    {
    public:
        HumidityController();
        ~HumidityController();
        void SetHumidityThresholds(const uint8_t upperThresholdInPercentage, const uint8_t lowerThresholdInPercentage);
        EnumState Control(const uint8_t &humidityInPercentage);
        void UpdateHumidityFailStatus(const bool bIsFailed);

    private:
        bool m_bIsHumidityValid;
        uint8_t m_UpperThresholdInPercentage;
        uint8_t m_LowerThresholdInPercentage;
        uint32_t m_OnTimeInMillisecond;
        uint32_t m_OffTimeInMillisecond;
        uint64_t m_StartTimeInMillisecond;
        EnumState m_LastState;
    };
} // namespace Incubator

#endif // INCUBATOR_HUMIDITYCONTROLLER_H