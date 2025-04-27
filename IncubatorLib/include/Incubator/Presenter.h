#ifndef INCUBATOR_PRESENTER_H
#define INCUBATOR_PRESENTER_H
#include "DHT11/DHT11Sensor.h"
#include "NTC/TemperatureSensor.h"
#include "SHT3X/SHT31Sensor.h"
#include "Incubator/IView.h"
#include "Incubator/IModel.h"
namespace Incubator
{
    class Presenter
    {
    public:
        Presenter();
        ~Presenter();
        void Initialize(IView *view, IModel *model, IModel* spareModel);
        void Run(void);

    private:
        IView *m_View;
        IModel *m_Model;
        IModel *m_SpareModel;
        static constexpr uint32_t MAX_DHT11_FAILURE_COUNT = static_cast<uint32_t>(5UL);
        uint32_t m_Dht11FailureCount;
        DHT11::DHT11Sensor m_DHT11Sensor;
        SHT3X::SHT31Sensor m_SHT31Sensor;
        uint32_t m_NtcFailureCount;
        NTC::TemperatureSensor m_TemperatureSensor;

    private:
        bool DetermineTemperature(float &resultInCelcius, const float &dht11TemperatureInCelcius);
        
    };
} // namespace Incubator

#endif // INCUBATOR_PRESENTER_H