#ifndef INCUBATOR_DAYDATASETSCREEN_H
#define INCUBATOR_DAYDATASETSCREEN_H
#include "TC2004/Lcd.h"
#include "ADataSetScreen.h"

namespace Incubator
{
    class DayDataSetScreen : public ADataSetScreen
    {
    public:
        DayDataSetScreen();
        ~DayDataSetScreen();

    protected:
        virtual void PrintCurrentData() const final override;
        virtual void PrintNewData() const final override;
        virtual void OnIncrementHighEvent() final override;
        virtual void OnIncrementLowEvent() final override;
        virtual void OnDecrementHighEvent() final override;
        virtual void OnDecrementLowEvent() final override;
        virtual void NotifyChangedData() final override;
        virtual EnumScreenType GetNextScreenForNoSelection() const final override;

    private:
        static constexpr uint8_t MIN_ALLOWED_DAY_COUNT = 1U;
        static constexpr uint8_t HIGH_INCREMENT_COUNT = 10U;
        static constexpr uint8_t LOW_INCREMENT_COUNT = 1U;

    private:
        static uint8_t GetDayFromSecond(const uint32_t &second);
        void SetSecondFromDayCount(const uint8_t &dayCount);
        
    };
} // namespace Incubator

#endif // INCUBATOR_DAYDATASETSCREEN_H