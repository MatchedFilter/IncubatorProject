#ifndef INCUBATOR_HUMIDITYDATASETSCREEN_H
#define INCUBATOR_HUMIDITYDATASETSCREEN_H
#include "TC2004/Lcd.h"
#include "AHumidityDataSetScreen.h"

namespace Incubator
{
    class HumidityDataSetScreen : public AHumidityDataSetScreen
    {
    public:
        HumidityDataSetScreen();
        ~HumidityDataSetScreen();

    protected:
        virtual uint8_t GetCurrentHumidityInPercentage() const final override;
        virtual uint8_t GetChangedHumidityInPercentage() const final override;
        virtual void SetChangedHumidityInPercentage(const uint8_t humidityInPercentage) final override;
    };
} // namespace Incubator

#endif // INCUBATOR_HUMIDITYDATASETSCREEN_H