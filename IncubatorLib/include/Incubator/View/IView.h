#ifndef INCUBATOR_IVIEW_H
#define INCUBATOR_IVIEW_H
#include <cinttypes>
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
    class IView
    {
    public:
        virtual void Initialize(void) = 0;
        virtual void UpdateTemperature(const double temperature) = 0;
        virtual void OnTemperatureFailure(const uint8_t errorCode) = 0;
        virtual void UpdateHumidity(const double humidity) = 0;
        virtual void OnHumidityFailure(const uint8_t errorCode) = 0;
        virtual void UpdateSettingsData(const SettingsData &data) = 0;
        virtual void UpdateTimeInformationData(const TimeInformationData &data) = 0;
        
    };
} // namespace Incubator

#endif // INCUBATOR_IVIEW_H