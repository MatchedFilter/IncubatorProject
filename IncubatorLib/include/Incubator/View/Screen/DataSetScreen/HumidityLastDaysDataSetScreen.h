#ifndef INCUBATOR_HUMIDITYLASTDAYSDATASETSCREEN_H
#define INCUBATOR_HUMIDITYLASTDAYSDATASETSCREEN_H
#include "TC2004/Lcd.h"
#include "AHumidityDataSetScreen.h"

namespace Incubator
{
    class HumidityLastDaysDataSetScreen : public AHumidityDataSetScreen
    {
    public:
        HumidityLastDaysDataSetScreen();
        ~HumidityLastDaysDataSetScreen();

    protected:
        virtual uint8_t GetCurrentHumidityInPercentage() const final override;
        virtual uint8_t GetChangedHumidityInPercentage() const final override;
        virtual void SetChangedHumidityInPercentage(const uint8_t humidityInPercentage) final override;
    };
} // namespace Incubator

#endif // INCUBATOR_HUMIDITYLASTDAYSDATASETSCREEN_H