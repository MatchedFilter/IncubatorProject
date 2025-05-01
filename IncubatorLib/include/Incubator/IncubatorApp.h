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
#include "Time/TimerTask.h"

#include "Controller/TemperatureController.h"
#include "Controller/HumidityController.h"

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
        Time::TimerTask m_SensorReadTimerTask;
        uint8_t m_Dht11FailCount;
        uint8_t m_Sht31FailCount;
        uint8_t m_NtcFailCount;
        double m_PrevDht11Temp;
        double m_PrevDht11Humidity;
        double m_PrevSht31Temp;
        double m_PrevSht31Humidity;
        double m_PrevNtc;
        static constexpr uint32_t SENSOR_READ_TIMEOUT_IN_MILLISECOND = static_cast<uint32_t>(25UL);
        bool m_SettingsValid;
        SettingsData m_SettingsData;
        TemperatureController m_TemperatureController;
        HumidityController m_HumidityController;

    private:
        bool ReadSht31(double &temperatureInCelcius, double &humidityInPercent);
        bool ReadDht11(double &temperatureInCelcius, double &humidityInPercent);
        bool ReadNtc(double &temperatureInCelcius, const double &sht31Temp, const double &dht11Temp);
        void ReadSensors(bool &bTemperatureValid, double &temperatureInCelcius, bool &bHumidityValid, double &humidityInPercent); 
        void UpdatePresenter(const bool &bTemperatureValid, const double &temperatureInCelcius, const bool &bHumidityValid, const double &humidityInPercent);
        bool GetDesiredTemperature(double &desiredTemperatureInCelcius);
        bool GetDesiredHumidity(double &desiredHumidityInPercent);
        void ControlTemperature(const bool &bTemperatureValid, const double &temperatureInCelcius);

    };
} // namespace Incubator

#endif // INCUBATOR_INCUBATORAPP_H