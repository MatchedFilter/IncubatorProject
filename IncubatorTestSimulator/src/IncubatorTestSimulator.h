#pragma once
#include "TC2004Screen/TC2004Screen.h"
#include "DHT11Component/DHT11Component.h"
#include "SHT31Component/SHT31Component.h"
#include "NTCComponent/NTCComponent.h"
#include "JoystickButton/JoystickButton.h"
#include "Output/OutputComponent.h"

namespace IncubatorSim
{
    class IncubatorTestSimulator
    {
    public:
        IncubatorTestSimulator();
        ~IncubatorTestSimulator();
        void SendDataToTC2004(uint8_t data);
        void SendCommandToTC2004(uint8_t command);
        inline int64_t GetSimulatorStartTimestampInMillisecond() const { return m_SimulatorStartTimestampInMillisecond; }
        void SetSimulatorStartTimestampInMillisecond(int64_t timestampInMillisecond) { m_SimulatorStartTimestampInMillisecond = timestampInMillisecond; }
        bool GetHumidityPercentageAndTemperatureInCelcius(uint8_t &humidityPercentage, uint8_t &temperatureInCelcius);
        bool GetFromSHT32(double &humidityPercentage, double &temperatureInCelcius);
        bool GetTemperatureInCelcius(double &temperatureInCelcius);
        void GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed, bool &bSwitchPressed);
        void UpdateHeaterStatus(bool bIsOn);
        void UpdateHumidityGeneratorStatus(bool bIsOn);

        void Initialize();
        void HandleEvents(SDL_Event &event);
        void Run();
    
    private:
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        TC2004Screen m_TC2004Screen;
        DHT11Component m_DHT11Component;
        SHT31Component m_SHT31Component;
        NTCComponent m_NTCComponent;
        JoystickButton m_JoystickButton;
        OutputComponent m_HumidityGeneratorComponent;
        OutputComponent m_HeaterCompoenent;
        int64_t m_SimulatorStartTimestampInMillisecond;

    private:
        void InitializeTime();
        void InitializeEeprom24C32();
        void InitializeInternalFlash();
        void CreateEeprom24C32();
        void CreateInternalFlash();
    };

} // namespace IncubatorSim
