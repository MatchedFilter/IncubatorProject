#include "IncubatorTestSimulator.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include "Utils/IncubatorTestSimulatorUtils.h"

namespace IncubatorSim
{
    IncubatorTestSimulator::IncubatorTestSimulator() : 
        m_Window { nullptr },
        m_Renderer { nullptr },
        m_SimulatorStartTimestampInMillisecond { -1 }
    {
    }

    IncubatorTestSimulator::~IncubatorTestSimulator()
    {
        if (m_Window != nullptr)
        {
            SDL_DestroyWindow(m_Window);
        }
        if (m_Renderer != nullptr)
        {
            SDL_DestroyRenderer(m_Renderer);
        }
        IMG_Quit();
        SDL_Quit();
    }

    void IncubatorTestSimulator::SendDataToTC2004(uint8_t data)
    {
        m_TC2004Screen.SendData(data);
    }

    void IncubatorTestSimulator::SendCommandToTC2004(uint8_t command)
    {
        m_TC2004Screen.SendCommand(command);
    }

    bool IncubatorTestSimulator::GetHumidityPercentageAndTemperatureInCelcius(uint8_t &humidityPercentage, uint8_t &temperatureInCelcius)
    {
        m_DHT11Component.GetHumidityPercentageAndTemperature(humidityPercentage, temperatureInCelcius);
        return true;
    }

    bool IncubatorTestSimulator::GetFromSHT32(double &humidityPercentage, double &temperatureInCelcius)
    {
        m_SHT31Component.GetHumidityPercentageAndTemperature(humidityPercentage, temperatureInCelcius);
        return true;
    }


    bool IncubatorTestSimulator::GetTemperatureInCelcius(double &temperatureInCelcius)
    {
        temperatureInCelcius = m_NTCComponent.GetTemperature();
        return true;
    }

    void IncubatorTestSimulator::GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed, bool &bSwitchPressed)
    {
        m_JoystickButton.GetJoystickData(upKeyPressed, downKeyPressed, rightKeyPressed, leftKeyPressed, bSwitchPressed);
    }

    void IncubatorTestSimulator::UpdateHeaterStatus(bool bIsOn)
    {
        if (bIsOn)
        {
            m_HeaterCompoenent.TurnOn();
        }
        else
        {
            m_HeaterCompoenent.TurnOff();
        }
    }

    void IncubatorTestSimulator::UpdateHumidityGeneratorStatus(bool bIsOn)
    {
        if (bIsOn)
        {
            m_HumidityGeneratorComponent.TurnOn();
        }
        else
        {
            m_HumidityGeneratorComponent.TurnOff();
        }
    }

    void IncubatorTestSimulator::Initialize()
    {
        InitializeTime();
        InitializeEeprom24C32();
        InitializeInternalFlash();
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL could not be initialized" << std::endl;
            exit(127);
        }

        m_Window = SDL_CreateWindow("Incubator Test Simulator",
            100,
            100,
            1280,
            800,
            SDL_WINDOW_SHOWN);

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

        if (TTF_Init() == -1)
        {
            std::cerr << "Unable to Init ttf" << std::endl;
            exit(127);
        }
        int flags = IMG_INIT_PNG;
        int initStatus = IMG_Init(flags);
        if ((initStatus & flags) != flags)
        {
            std::cerr << "Unable to Initialize IMG" << std::endl;
            exit(127);
        }
        if (!m_TC2004Screen.Initialize(m_Renderer, 0, 0))
        {
            std::cerr << "Unable to initialize TC2004 Sreen" << std::endl;
            exit(127);
        }

        if (!m_DHT11Component.Initialize(m_Renderer, 900, 10))
        {
            std::cerr << "Unable to initialize DHT11TestComponent" << std::endl;
            exit(127); 
        }

        if (!m_NTCComponent.Initialize(m_Renderer, 900, 150))
        {
            std::cerr << "Unable to initialize NTCComponent" << std::endl;
            exit(127); 
        }

        if (!m_SHT31Component.Initialize(m_Renderer, 900, 300))
        {
            std::cerr << "Unable to initialize SHT31TestComponent" << std::endl;
            exit(127); 
        }

        if (!m_JoystickButton.Initialize(m_Renderer, 100, 550))
        {
            std::cerr << "Unable to initialize JoystickButton" << std::endl;
            exit(127);
        }

        if (!m_HumidityGeneratorComponent.Initialize(m_Renderer, 400, 550, 128, 128, "resources/images/Humidity_Generator.png"))
        {
            std::cerr << "Unable to initialize HumidityGeneratorTestComponent" << std::endl;
            exit(127);
        }
        if (!m_HeaterCompoenent.Initialize(m_Renderer, 700, 550, 128, 64, "resources/images/Carbonfiber_Heater.png"))
        {
            std::cerr << "Unable to initialize CarbonFiberHeaterTestComponent" << std::endl;
            exit(127);
        }
        IncubatorTestSimulatorUtils::Initialize();

    }

    void IncubatorTestSimulator::HandleEvents(SDL_Event &event)
    {
        m_JoystickButton.HandleEvents(event);
        m_DHT11Component.HandleEvents(event);
        m_SHT31Component.HandleEvents(event);
        m_NTCComponent.HandleEvents(event);
    }

    void IncubatorTestSimulator::Run()
    {
        SDL_RenderClear(m_Renderer);
        m_TC2004Screen.Run();
        m_JoystickButton.Run();
        m_DHT11Component.Run();
        m_SHT31Component.Run();
        m_NTCComponent.Run();
        m_HumidityGeneratorComponent.Run();
        m_HeaterCompoenent.Run();
        SDL_SetRenderDrawColor(m_Renderer, 0x20, 0x20, 0x20, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(m_Renderer);
    }

    void IncubatorTestSimulator::InitializeTime()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        m_SimulatorStartTimestampInMillisecond = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    void IncubatorTestSimulator::InitializeEeprom24C32()
    {
        std::ifstream eeprom24C32File ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
        if (!eeprom24C32File.is_open())
        {
            CreateEeprom24C32();
        }
        eeprom24C32File.open("Eeprom24C32.bin", std::ios::out | std::ios::binary);
        if (!eeprom24C32File.is_open())
        {
            std::cerr << "Unable to open Eeprom24C32.bin file!" << std::endl;
            exit(127);
        }

        eeprom24C32File.close();
    }

    void IncubatorTestSimulator::InitializeInternalFlash()
    {
        std::ifstream internalFlashFile ("InternalFlash.bin", std::ios::out | std::ios::binary);
        if (!internalFlashFile.is_open())
        {
            CreateInternalFlash();
        }
        internalFlashFile.open("InternalFlash.bin", std::ios::out | std::ios::binary);
        if (!internalFlashFile.is_open())
        {
            std::cerr << "Unable to open InternalFlash.bin file!" << std::endl;
            exit(127);
        }

        internalFlashFile.close();
    }


    void IncubatorTestSimulator::CreateEeprom24C32()
    {
        std::ofstream eeprom24C32File ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
        if (!eeprom24C32File.is_open())
        {
            std::cerr << "Unable to crate Eeprom24C32.bin file!" << std::endl;
            exit(127);
        }
        constexpr const int32_t EEPROM24C32_SIZE = 32 * 8; // Just 8 pages
        uint8_t emptyBuffer[EEPROM24C32_SIZE];
        memset(emptyBuffer, 0xFF, EEPROM24C32_SIZE);
        eeprom24C32File.write((const char*) emptyBuffer, EEPROM24C32_SIZE);
        eeprom24C32File.close();
    }

    void IncubatorTestSimulator::CreateInternalFlash()
    {
        std::ofstream internalFlashFile ("InternalFlash.bin", std::ios::out | std::ios::binary);
        if (!internalFlashFile.is_open())
        {
            std::cerr << "Unable to crate InternalFlash.bin file!" << std::endl;
            exit(127);
        }
        constexpr const int32_t INTERNALFLASH_SIZE = 32 * 8; // Just 8 pages
        uint8_t emptyBuffer[INTERNALFLASH_SIZE];
        memset(emptyBuffer, 0xFF, INTERNALFLASH_SIZE);
        internalFlashFile.write((const char*) emptyBuffer, INTERNALFLASH_SIZE);
        internalFlashFile.close();
    }

} // namespace IncubatorSim
