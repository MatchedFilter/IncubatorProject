#include <cinttypes>
#include "IncubatorTestSimulator.h"
#include <chrono>
#include <thread>
#include <map>
#include "Eeprom24C/EepromI2CBuffer.h"
#include "Incubator/Model/FlashBuffer.h"
#include "SHT3X/ShtBuffer.h"
#include <fstream>

namespace IncubatorSim
{
    extern IncubatorTestSimulator g_IncubatorTestSimulator;
} // namespace IncubatorSim


namespace TC2004
{
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationInMillisecond));
    }

    bool SendCommand(const uint8_t id, const uint8_t command)
    {
        bool bResult = false;
        switch (id)
        {
        case 0:
        {
            bResult = true;
            IncubatorSim::g_IncubatorTestSimulator.SendCommandToTC2004(command);
            break;
        }
        
        default:
            break;
        }
        return bResult;
    }

    bool SendData(const uint8_t id, const uint8_t data)
    {
        bool bResult = false;
        switch (id)
        {
        case 0:
        {
            bResult = true;
            IncubatorSim::g_IncubatorTestSimulator.SendDataToTC2004(data);
            break;
        }
        
        default:
            break;
        }
        return bResult;
    }
} // namespace TC2004

namespace DHT11
{
    enum EnumDht11ReadingState
    {
        DHT11_READING_STATE_STARTED = 0,
        DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH_INITIAL = 1,
        DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH = 2,
        DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW_INITIAL = 3,
        DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW = 4,
        DHT11_READING_STATE_READING_LOW_TO_HIGH = 5,
        DHT11_READING_STATE_READING_HIGH_TO_LOW_INITIAL = 6,
        DHT11_READING_STATE_READING_HIGH_TO_LOW = 7,
    };

    static uint8_t s_Dht11ReadingCount = 0;
    static uint8_t s_Dht11Data[40] = { 0 };
    static std::chrono::_V2::system_clock::time_point s_DhtTimeStartPoint;
    static std::chrono::_V2::system_clock::time_point m_TestMicrosecondTimer;


    static EnumDht11ReadingState s_Dht11ReadingState;


    void StartTimer(const uint8_t id)
    {
    }
    
    void ResetTimer(const uint8_t id)
    {
        s_DhtTimeStartPoint = std::chrono::high_resolution_clock::now();
    }
    
    void StopTimer(const uint8_t id)
    {
    }
    
    uint32_t GetTimestampInMicrosecondFromTimer(const uint8_t id)
    {
        auto elapsed = std::chrono::high_resolution_clock::now() - s_DhtTimeStartPoint;
        uint32_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return microseconds;
    }
    
    void SetDataPinAsOutput(const uint8_t id)
    {
    }
    
    void SetDataPinAsHigh(const uint8_t id)
    {

    }

    void SetDataPinAsLow(const uint8_t id)
    {
        s_Dht11ReadingState = DHT11_READING_STATE_STARTED;
        s_Dht11ReadingCount = 0;
    }
    
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationInMillisecond));
    }
    
    void SetDataPinAsInput(const uint8_t id)
    {
    }
    
    uint8_t ReadDataPin(const uint8_t id)
    {
        int dataPinValue;
        switch (s_Dht11ReadingState)
        {
        case DHT11_READING_STATE_STARTED:
            dataPinValue = 0;
            s_Dht11ReadingState = DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH;
            break;

        case DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH:
            {
                if (GetTimestampInMicrosecondFromTimer(0) < 80)
                {
                    dataPinValue = 0;
                }
                else
                {
                    dataPinValue = 1;
                    s_Dht11ReadingState = DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW;
                }
            }
            break;


        case DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW:
            {
                uint8_t humidityPercentage, temperatureInCelcius;
                bool bDhtValidity = IncubatorSim::g_IncubatorTestSimulator.GetHumidityPercentageAndTemperatureInCelcius(humidityPercentage, temperatureInCelcius);
                uint8_t checkSum = humidityPercentage + temperatureInCelcius;
                s_Dht11Data[0] = (humidityPercentage & 0b10000000) != 0;
                s_Dht11Data[1] = (humidityPercentage & 0b01000000) != 0;
                s_Dht11Data[2] = (humidityPercentage & 0b00100000) != 0;
                s_Dht11Data[3] = (humidityPercentage & 0b00010000) != 0;
                s_Dht11Data[4] = (humidityPercentage & 0b00001000) != 0;
                s_Dht11Data[5] = (humidityPercentage & 0b00000100) != 0;
                s_Dht11Data[6] = (humidityPercentage & 0b00000010) != 0;
                s_Dht11Data[7] = (humidityPercentage & 0b00000001) != 0;
                s_Dht11Data[16] = (temperatureInCelcius & 0b10000000) != 0;
                s_Dht11Data[17] = (temperatureInCelcius & 0b01000000) != 0;
                s_Dht11Data[18] = (temperatureInCelcius & 0b00100000) != 0;
                s_Dht11Data[19] = (temperatureInCelcius & 0b00010000) != 0;
                s_Dht11Data[20] = (temperatureInCelcius & 0b00001000) != 0;
                s_Dht11Data[21] = (temperatureInCelcius & 0b00000100) != 0;
                s_Dht11Data[22] = (temperatureInCelcius & 0b00000010) != 0;
                s_Dht11Data[23] = (temperatureInCelcius & 0b00000001) != 0;
                s_Dht11Data[32] = (checkSum & 0b10000000) != 0;
                s_Dht11Data[33] = (checkSum & 0b01000000) != 0;
                s_Dht11Data[34] = (checkSum & 0b00100000) != 0;
                s_Dht11Data[35] = (checkSum & 0b00010000) != 0;
                s_Dht11Data[36] = (checkSum & 0b00001000) != 0;
                s_Dht11Data[37] = (checkSum & 0b00000100) != 0;
                s_Dht11Data[38] = (checkSum & 0b00000010) != 0;
                s_Dht11Data[39] = (checkSum & 0b00000001) != 0;
                if (GetTimestampInMicrosecondFromTimer(0) < 80)
                {
                    dataPinValue = 1;
                }
                else
                {
                    if (bDhtValidity)
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                    else
                    {
                        if (GetTimestampInMicrosecondFromTimer(0) < 90)
                        {
                            dataPinValue = 1;
                        }
                        else
                        {
                            dataPinValue = 0;
                            s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                        }
                    }
                }
            }
            break;

        case DHT11_READING_STATE_READING_LOW_TO_HIGH:
                dataPinValue = 1;
                if (GetTimestampInMicrosecondFromTimer(0) < 20)
                {
                    dataPinValue = 0;
                }
                else
                {
                    dataPinValue = 1;
                    s_Dht11ReadingState = DHT11_READING_STATE_READING_HIGH_TO_LOW;
                }
            break;

        case DHT11_READING_STATE_READING_HIGH_TO_LOW:
            {
                if (!s_Dht11Data[s_Dht11ReadingCount])
                {
                    if (GetTimestampInMicrosecondFromTimer(0) < 23UL)
                    {
                        dataPinValue = 1;
                    }
                    else
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingCount++;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                }
                else
                {
                    if (GetTimestampInMicrosecondFromTimer(0) < 75UL)
                    {
                        dataPinValue = 1;
                    }
                    else
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingCount++;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                }
            }
            break;
        
        default:
            dataPinValue = 0;
            break;
        }
        return dataPinValue;
    }

} // namespace DHT11

namespace Incubator
{
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationInMillisecond));
    }
} // namespace Incubator

namespace NTC
{
    void StartAdc(const uint8_t id);
    uint32_t ReadAdc(const uint8_t id);

    void StartAdc(const uint8_t )
    {
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t adcValue = 0;
        if (id == 0U)
        {
            static const std::map<double, double> TEMPERATURE_RESISTANCE_LOOK_UP_MAP = {
                std::make_pair<double, double>(2.78, 302466.0),
                std::make_pair<double, double>(3.89, 285206.0),
                std::make_pair<double, double>(5.00, 269035.0),
                std::make_pair<double, double>(6.11, 253877.0),
                std::make_pair<double, double>(7.22, 239664.0),
                std::make_pair<double, double>(8.33, 226331.0),
                std::make_pair<double, double>(9.44, 213819.0),
                std::make_pair<double, double>(10.56, 201971.0),
                std::make_pair<double, double>(11.67, 190946.0),
                std::make_pair<double, double>(12.78, 180588.0),
                std::make_pair<double, double>(13.89, 170853.0),
                std::make_pair<double, double>(15.00, 161700.0),
                std::make_pair<double, double>(16.11, 153092.0),
                std::make_pair<double, double>(17.22, 144992.0),
                std::make_pair<double, double>(18.33, 137367.0),
                std::make_pair<double, double>(19.44, 130189.0),
                std::make_pair<double, double>(20.56, 123368.0),
                std::make_pair<double, double>(21.67, 117000.0),
                std::make_pair<double, double>(22.78, 110998.0),
                std::make_pair<double, double>(23.89, 105338.0),
                std::make_pair<double, double>(25.00, 100000.0),
                std::make_pair<double, double>(26.11, 94963.0),
                std::make_pair<double, double>(27.22, 90208.0),
                std::make_pair<double, double>(28.33, 85719.0),
                std::make_pair<double, double>(29.44, 81479.0),
                std::make_pair<double, double>(30.56, 77438.0),
                std::make_pair<double, double>(31.67, 73654.0),
                std::make_pair<double, double>(32.78, 70076.0),
                std::make_pair<double, double>(33.89, 66692.0),
                std::make_pair<double, double>(35.00, 63491.0),
                std::make_pair<double, double>(36.11, 60461.0),
                std::make_pair<double, double>(37.22, 57594.0),
                std::make_pair<double, double>(38.33, 54878.0),
                std::make_pair<double, double>(39.44, 52306.0),
                std::make_pair<double, double>(40.56, 49847.0),
                std::make_pair<double, double>(41.67, 47538.0),
                std::make_pair<double, double>(42.78, 45349.0),
                std::make_pair<double, double>(43.89, 43273.0),
                std::make_pair<double, double>(45.00, 41303.0),
                std::make_pair<double, double>(46.11, 39434.0),
                std::make_pair<double, double>(47.22, 37660.0),
                std::make_pair<double, double>(48.33, 35976.0),
                std::make_pair<double, double>(49.44, 34376.0),
                std::make_pair<double, double>(50.56, 32843.0),
                std::make_pair<double, double>(51.67, 31399.0),
                std::make_pair<double, double>(52.78, 30027.0),
                std::make_pair<double, double>(53.89, 28722.0),
                std::make_pair<double, double>(55.00, 27481.0)
            };
            double temperatureInCelcius;
            if (IncubatorSim::g_IncubatorTestSimulator.GetTemperatureInCelcius(temperatureInCelcius))
            {
                auto tempIt = TEMPERATURE_RESISTANCE_LOOK_UP_MAP.upper_bound(temperatureInCelcius);
                if (tempIt == TEMPERATURE_RESISTANCE_LOOK_UP_MAP.begin())
                {
                    adcValue = 4095;
                }
                else if (tempIt == TEMPERATURE_RESISTANCE_LOOK_UP_MAP.end())
                {
                    adcValue = 1;
                }
                else
                {
                    double upperTemperature = tempIt->first;
                    double upperValue = tempIt->second;
                    tempIt--;
                    double lowerTemperature = tempIt->first;
                    double lowerValue = tempIt->second;
                    double resistance = lowerValue - ((lowerValue - upperValue) * (temperatureInCelcius - lowerTemperature) / (upperTemperature - lowerTemperature));
                    adcValue = static_cast<uint32_t>((4095.0 * 100000.0) / (100000.0 + resistance));
                }
            }
        }
        return adcValue;
    }
} // namespace NTC

namespace Eeprom24C
{
    static constexpr const int32_t EEPROM24C32_SIZE = 32 * 8; // Just 8 pages
    static uint8_t s_EepromBuffer[EEPROM24C32_SIZE];

    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer);
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size);
    void DelayInMillisecond(const uint32_t durationInMillisecond);

    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer)
    {
        bool bResult = false;
        if (id == 0x00U)
        {

            std::ifstream eeprom24C32InFile ("Eeprom24C32.bin", std::ios::in | std::ios::binary);
            if (eeprom24C32InFile.is_open())
            {
                eeprom24C32InFile.read((char*)s_EepromBuffer, sizeof(s_EepromBuffer));
                eeprom24C32InFile.close();
                std::ofstream eeprom24C32OutFile ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
                if (eeprom24C32OutFile.is_open())
                {
                    bResult = true;
                    memcpy(&s_EepromBuffer[addressToWrite], i2cBuffer.m_Buffer, i2cBuffer.m_Size);
                    eeprom24C32OutFile.write((const char*)s_EepromBuffer, sizeof(s_EepromBuffer));
                    eeprom24C32OutFile.close();
                }
            }
        }
        return bResult;
    }
    
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size)
    {
        bool bResult = false;
        if (id == 0x00U)
        {

            std::ifstream eeprom24C32File ("Eeprom24C32.bin", std::ios::in | std::ios::binary);
            if (eeprom24C32File.is_open())
            {
                bResult = true;
                eeprom24C32File.read((char*)s_EepromBuffer, sizeof(s_EepromBuffer));
                eeprom24C32File.close();
                i2cBuffer.m_Size = size;
                memcpy(i2cBuffer.m_Buffer, &s_EepromBuffer[addressToRead], i2cBuffer.m_Size);
            }
        }
        return bResult;
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationInMillisecond));
    }

} // namespace Eeprom24C


namespace Incubator
{
    uint64_t GetTimestampInMillisecond();
    bool WriteToFlash(const uint32_t flashBaseAddress, const uint32_t offset, const FlashBuffer &buffer);
    bool ReadFromFlash(const uint32_t baseAddress, const uint32_t offset, FlashBuffer &buffer, const uint32_t size);

    static uint64_t s_ApplicationStartTimeInMillisecond;
    static bool s_bIsTimeInitialized = false;
    static constexpr const int32_t INTERNALFLASH_SIZE = 32 * 8; // Just 256 Byte
    static uint8_t s_InternalFlashBuffer[INTERNALFLASH_SIZE];

    uint64_t GetTimestampInMillisecond()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        uint64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        if (!s_bIsTimeInitialized)
        {
            s_bIsTimeInitialized = true;
            s_ApplicationStartTimeInMillisecond = milliseconds;
        }
        return milliseconds - s_ApplicationStartTimeInMillisecond;
    }

    bool WriteToFlash(const uint32_t flashBaseAddress, const uint32_t offset, const FlashBuffer &buffer)
    {
        bool bResult = false;
        const uint32_t addressToWrite = offset;

        std::ifstream InternalFlashInFile ("InternalFlash.bin", std::ios::in | std::ios::binary);
        if (InternalFlashInFile.is_open())
        {
            InternalFlashInFile.read((char*)s_InternalFlashBuffer, sizeof(s_InternalFlashBuffer));
            InternalFlashInFile.close();
            std::ofstream InternalFlashOutFile ("InternalFlash.bin", std::ios::out | std::ios::binary);
            if (InternalFlashOutFile.is_open())
            {
                bResult = true;
                memcpy(&s_InternalFlashBuffer[addressToWrite], reinterpret_cast<const void*>(buffer.m_Words), (buffer.m_Size * 4UL));
                InternalFlashOutFile.write((const char*)s_InternalFlashBuffer, sizeof(s_InternalFlashBuffer));
                InternalFlashOutFile.close();
            }
        }
        return bResult;
    }
    bool ReadFromFlash(const uint32_t baseAddress, const uint32_t offset, FlashBuffer &buffer, const uint32_t size)
    {
        bool bResult = false;
        const uint32_t addressToRead = offset;

        std::ifstream internalFlashFile ("InternalFlash.bin", std::ios::in | std::ios::binary);
        if (internalFlashFile.is_open())
        {
            bResult = true;
            internalFlashFile.read((char*)s_InternalFlashBuffer, sizeof(s_InternalFlashBuffer));
            internalFlashFile.close();
            buffer.m_Size = size;
            memcpy(buffer.m_Words, &s_InternalFlashBuffer[addressToRead], (size * 4UL));
        }
        return bResult;
    }

    void TurnOnHeater()
    {
        IncubatorSim::g_IncubatorTestSimulator.UpdateHeaterStatus(true);
    }

    void TurnOffHeater()
    {
        IncubatorSim::g_IncubatorTestSimulator.UpdateHeaterStatus(false);
    }

    void TurnOnHumidityGenerator()
    {
        IncubatorSim::g_IncubatorTestSimulator.UpdateHumidityGeneratorStatus(true);
    }

    void TurnOffHumidityGenerator()
    {
        IncubatorSim::g_IncubatorTestSimulator.UpdateHumidityGeneratorStatus(false);
    }


} // namespace Incubator

namespace SHT3X
{ 
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size);

    static constexpr uint8_t NRCS5_LOOK_UP_TABLE[] = {
        0x00U, 0x31U, 0x62U, 0x53U, 0xC4U, 0xF5U, 0xA6U, 0x97U,
        0xB9U, 0x88U, 0xDBU, 0xEAU, 0x7DU, 0x4CU, 0x1FU, 0x2EU,
        0x43U, 0x72U, 0x21U, 0x10U, 0x87U, 0xB6U, 0xE5U, 0xD4U,
        0xFAU, 0xCBU, 0x98U, 0xA9U, 0x3EU, 0x0FU, 0x5CU, 0x6DU,
        0x86U, 0xB7U, 0xE4U, 0xD5U, 0x42U, 0x73U, 0x20U, 0x11U,
        0x3FU, 0x0EU, 0x5DU, 0x6CU, 0xFBU, 0xCAU, 0x99U, 0xA8U,
        0xC5U, 0xF4U, 0xA7U, 0x96U, 0x01U, 0x30U, 0x63U, 0x52U,
        0x7CU, 0x4DU, 0x1EU, 0x2FU, 0xB8U, 0x89U, 0xDAU, 0xEBU,
        0x3DU, 0x0CU, 0x5FU, 0x6EU, 0xF9U, 0xC8U, 0x9BU, 0xAAU,
        0x84U, 0xB5U, 0xE6U, 0xD7U, 0x40U, 0x71U, 0x22U, 0x13U,
        0x7EU, 0x4FU, 0x1CU, 0x2DU, 0xBAU, 0x8BU, 0xD8U, 0xE9U,
        0xC7U, 0xF6U, 0xA5U, 0x94U, 0x03U, 0x32U, 0x61U, 0x50U,
        0xBBU, 0x8AU, 0xD9U, 0xE8U, 0x7FU, 0x4EU, 0x1DU, 0x2CU,
        0x02U, 0x33U, 0x60U, 0x51U, 0xC6U, 0xF7U, 0xA4U, 0x95U,
        0xF8U, 0xC9U, 0x9AU, 0xABU, 0x3CU, 0x0DU, 0x5EU, 0x6FU,
        0x41U, 0x70U, 0x23U, 0x12U, 0x85U, 0xB4U, 0xE7U, 0xD6U,
        0x7AU, 0x4BU, 0x18U, 0x29U, 0xBEU, 0x8FU, 0xDCU, 0xEDU,
        0xC3U, 0xF2U, 0xA1U, 0x90U, 0x07U, 0x36U, 0x65U, 0x54U,
        0x39U, 0x08U, 0x5BU, 0x6AU, 0xFDU, 0xCCU, 0x9FU, 0xAEU,
        0x80U, 0xB1U, 0xE2U, 0xD3U, 0x44U, 0x75U, 0x26U, 0x17U,
        0xFCU, 0xCDU, 0x9EU, 0xAFU, 0x38U, 0x09U, 0x5AU, 0x6BU,
        0x45U, 0x74U, 0x27U, 0x16U, 0x81U, 0xB0U, 0xE3U, 0xD2U,
        0xBFU, 0x8EU, 0xDDU, 0xECU, 0x7BU, 0x4AU, 0x19U, 0x28U,
        0x06U, 0x37U, 0x64U, 0x55U, 0xC2U, 0xF3U, 0xA0U, 0x91U,
        0x47U, 0x76U, 0x25U, 0x14U, 0x83U, 0xB2U, 0xE1U, 0xD0U,
        0xFEU, 0xCFU, 0x9CU, 0xADU, 0x3AU, 0x0BU, 0x58U, 0x69U,
        0x04U, 0x35U, 0x66U, 0x57U, 0xC0U, 0xF1U, 0xA2U, 0x93U,
        0xBDU, 0x8CU, 0xDFU, 0xEEU, 0x79U, 0x48U, 0x1BU, 0x2AU,
        0xC1U, 0xF0U, 0xA3U, 0x92U, 0x05U, 0x34U, 0x67U, 0x56U,
        0x78U, 0x49U, 0x1AU, 0x2BU, 0xBCU, 0x8DU, 0xDEU, 0xEFU,
        0x82U, 0xB3U, 0xE0U, 0xD1U, 0x46U, 0x77U, 0x24U, 0x15U,
        0x3BU, 0x0AU, 0x59U, 0x68U, 0xFFU, 0xCEU, 0x9DU, 0xACU
    };

    static uint8_t CalculateCrc(const ShtBuffer &buffer, const uint32_t crcStartIndex, const uint32_t crcSize)
    {
        uint8_t crc = 0xFFU;
        if (crcSize > static_cast<uint32_t>(0U))
        {
            const uint32_t lastIndex = crcStartIndex + (crcSize - static_cast<uint32_t>(1UL));
            if (lastIndex < ShtBuffer::MAX_SHT_BUFFER_SIZE)
            {
                for (uint32_t i = static_cast<uint32_t>(0UL); i < crcSize; i++)
                {
                    const uint8_t index = static_cast<uint8_t>(crc ^ buffer.m_Buffer[i + crcStartIndex]);
                    crc = static_cast<uint8_t>(NRCS5_LOOK_UP_TABLE[index] ^ static_cast<uint8_t>(crc << 8U));
                }
            }
        }
        return crc;
    }

    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size)
    {
        bool bResult = false;
        if (id == 0x00U)
        {
            bResult = true;
            double temperatureInCelcius, humidityInPercentage;
            IncubatorSim::g_IncubatorTestSimulator.GetFromSHT32(humidityInPercentage, temperatureInCelcius);
            
            constexpr double MULTIPLIER_CONSTANT = static_cast<double>(0xFFFFU) - 1.0;

            const uint16_t rawTemperature = static_cast<uint16_t>(((temperatureInCelcius + 45.0) / 175.0) * MULTIPLIER_CONSTANT);
            const uint16_t rawHumidity = static_cast<uint16_t>((humidityInPercentage / 100.0) * MULTIPLIER_CONSTANT);
            
            buffer.m_Buffer[0] = static_cast<uint8_t>(rawTemperature >> 8U);
            buffer.m_Buffer[1] = static_cast<uint8_t>(rawTemperature);
            buffer.m_Buffer[3] = static_cast<uint8_t>(rawHumidity >> 8U);
            buffer.m_Buffer[4] = static_cast<uint8_t>(rawHumidity);
            
            const uint8_t crcTemperature = CalculateCrc(buffer, 0, 2);
            const uint8_t crcHumidity = CalculateCrc(buffer, 3, 2);
            buffer.m_Buffer[2] = crcTemperature;
            buffer.m_Buffer[5] = crcHumidity;
        }
        return bResult;
    }
} // namespace SHT3X


namespace Joystick
{
    void StartHorizontalAdc(const uint8_t id);
    void StartVertialAdc(const uint8_t id);
    void DelayInMillisecond(const uint32_t durationInMillisecond);
    uint32_t ReadAdc(const uint8_t id);
    uint8_t ReadSwitchState(const uint8_t id);

    enum class EnumJoystickDirection
    {
        DIRECTION_HORIZONTAL,
        DIRECTION_VERTICAL,
        DIRECTION_NONE,
    };

    static EnumJoystickDirection s_JoystickDirection = EnumJoystickDirection::DIRECTION_NONE;

    void StartHorizontalAdc(const uint8_t id)
    {
        s_JoystickDirection = EnumJoystickDirection::DIRECTION_HORIZONTAL;
    }

    void StartVertialAdc(const uint8_t id)
    {
        s_JoystickDirection = EnumJoystickDirection::DIRECTION_VERTICAL;
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationInMillisecond));
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t result = 4095UL / 2UL;
        bool bUpKeyPressed, bDownKeyPressed, bRightKeyPressed, bLeftKeyPressed, bSwitchPressed = false;
        IncubatorSim::g_IncubatorTestSimulator.GetJoystickData(bUpKeyPressed, bDownKeyPressed, bRightKeyPressed, bLeftKeyPressed, bSwitchPressed);

        switch (s_JoystickDirection)
        {
        case EnumJoystickDirection::DIRECTION_HORIZONTAL:
        {
            if (bRightKeyPressed)
            {
                result = 4000UL;
            }
            else if (bLeftKeyPressed)
            {
                result = 0UL;
            }
            else
            {
            }
            break;
        }
        case EnumJoystickDirection::DIRECTION_VERTICAL:
        {
            if (bUpKeyPressed)
            {
                result = 4000UL;
            }
            else if (bDownKeyPressed)
            {
                result = 0UL;
            }
            else
            {
            }
            break;
        }
        
        case EnumJoystickDirection::DIRECTION_NONE:
        default:
            break;
        }
        return result;
    }

    uint8_t ReadSwitchState(const uint8_t id)
    {
        bool bUpKeyPressed, bDownKeyPressed, bRightKeyPressed, bLeftKeyPressed, bSwitchPressed = false;
        IncubatorSim::g_IncubatorTestSimulator.GetJoystickData(bUpKeyPressed, bDownKeyPressed, bRightKeyPressed, bLeftKeyPressed, bSwitchPressed);
        return bSwitchPressed;
    }

} // namespace Joystick
