#ifndef INCUBATOR_TEMPERATURECONTROLLER_H
#define INCUBATOR_TEMPERATURECONTROLLER_H
#include <cinttypes>
namespace Incubator
{
    class TemperatureController
    {
    public:
        TemperatureController();
        ~TemperatureController();
        void SetDesiredTemperature(const double desiredTemperatureInCelcius);
        double Control(const double &temperatureInCelcius, const uint32_t &timeDifferenceInMillisecond);
        void OnTemperatureFailure();

    private:
        bool m_bIsTemperatureValid;
        double m_DesiredTemperatureInCelcius;
        double m_PreviousTemperatureInCelcius;
        double m_PConstant;
        double m_IConstant;
        double m_DConstant;
    };
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURECONTROLLER_H