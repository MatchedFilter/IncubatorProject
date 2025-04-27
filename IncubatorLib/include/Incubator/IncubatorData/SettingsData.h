#ifndef INCUBATOR_INCUBATORDATA_SETTINGSDATA_H
#define INCUBATOR_INCUBATORDATA_SETTINGSDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
#include "IncubatorDataConstants.h"
namespace Incubator
{
    struct SettingsData
    {
    public:
        uint32_t m_TemperatureInMilliCelcius;
        uint32_t m_LastDaysTemperatureInMilliCelcius;
        uint8_t m_HumidityInPercentage;
        uint8_t m_LastDaysHumidityInPercentage;
        uint8_t m_TotalIncubationDayCount;
        uint8_t m_LastDaysCount;
        
        static constexpr uint32_t DATA_SIZE = static_cast<uint32_t>(
            sizeof(m_TemperatureInMilliCelcius) + 
            sizeof(m_LastDaysTemperatureInMilliCelcius) +
            sizeof(m_HumidityInPercentage) +
            sizeof(m_LastDaysHumidityInPercentage) +
            sizeof(m_TotalIncubationDayCount) +
            sizeof(m_LastDaysCount)
        );
        
    public:
        void Reset();
        void Copy(const SettingsData &other);
        bool Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const;
        bool Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader);
    };
    
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_SETTINGSDATA_H