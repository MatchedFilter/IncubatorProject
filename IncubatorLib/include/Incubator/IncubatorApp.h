#ifndef INCUBATOR_INCUBATORAPP_H
#define INCUBATOR_INCUBATORAPP_H
#include "TC2004/Lcd.h"
#include "Presenter/Presenter.h"
#include "View/Lcd2004View.h"
#include "Model/EepromModel.h"
#include "Model/InternalFlashModel.h"

#include "DHT11/DHT11Sensor.h"
#include "NTC/TemperatureSensor.h"
#include "SHT3X/SHT31Sensor.h"

namespace Incubator
{
    class IncubatorApp
    {
    public:
        IncubatorApp();
        ~IncubatorApp();
        void Initialize(void);
        void Run(void);

    private:
        Presenter m_Presenter;
        Lcd2004View m_Lcd2004View;
        EepromModel m_EepromModel;
        InternalFlashModel m_InternalFlashModel;
        DHT11::DHT11Sensor m_DHT11Sensor;
        NTC::TemperatureSensor m_TemperatureSensor;
        SHT3X::SHT31Sensor m_SHT31Sensor;
    };
} // namespace Incubator

#endif // INCUBATOR_INCUBATORAPP_H