#include "Incubator/IncubatorApp.h"
#include "Incubator/IncubatorDependencies.h"

namespace Incubator
{
    IncubatorApp::IncubatorApp() :
        m_InternalFlashModel ( static_cast<uint32_t>(0x0800C000UL) ),
        m_DHT11Sensor ( 0x00U ),
        m_TemperatureSensor ( 0x00U ),
        m_SHT31Sensor ( 0x00U )
    {
    }

    IncubatorApp::~IncubatorApp()
    {
    }

    void IncubatorApp::Initialize(void)
    {
        DelayInMillisecond(static_cast<uint32_t>(100UL));
        m_TemperatureSensor.Initialize(100.0);
        m_SHT31Sensor.Initialize();

        m_Lcd2004View.Initialize();
        m_EepromModel.Initialize();
        m_Presenter.Initialize(&m_Lcd2004View, &m_EepromModel, &m_InternalFlashModel);
    }

    void IncubatorApp::Run(void)
    {
        m_Presenter.Run();
    }

} // namespace Incubator
