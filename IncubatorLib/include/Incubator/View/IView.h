#ifndef INCUBATOR_IVIEW_H
#define INCUBATOR_IVIEW_H
#include <cinttypes>
#include "Incubator/IncubatorData/PidData.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "IPidDataChangedEventHandler.h"
#include "ISettingsDataChangedEventHandler.h"
#include "ITimeInformationDataChangedEventHandler.h"
namespace Incubator
{
    class IView
    {
    public:
        virtual bool Initialize(IPidDataChangedEventHandler *pidDataChangedEventHandler,
            ISettingsDataChangedEventHandler *settingsDataChangedEventHandler,
            ITimeInformationDataChangedEventHandler *timeInformationDataChangedEventHandler) = 0;
        virtual void UpdateTemperature(const double temperatureInCelcius) = 0;
        virtual void OnTemperatureFailure() = 0;
        virtual void UpdateHumidity(const uint8_t humidityInPercent) = 0;
        virtual void OnHumidityFailure() = 0;
        virtual void UpdatePidData(const PidData &data) = 0;
        virtual void UpdateSettingsData(const SettingsData &data) = 0;
        virtual void UpdateTimeInformationData(const TimeInformationData &data) = 0;
        virtual void OnModelFailure() = 0;
        
    };
} // namespace Incubator

#endif // INCUBATOR_IVIEW_H