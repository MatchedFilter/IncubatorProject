#include "Incubator/IncubatorData/SettingsData.h"

namespace Incubator
{
    void SettingsData::Reset()
    {
        m_TemperatureInMilliCelcius = static_cast<uint32_t>(37500UL);
        m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(36900UL);
        m_HumidityInPercentage = 59U;
        m_LastDaysHumidityInPercentage = 67U;
        m_TotalIncubationDayCount = 21U;
        m_LastDaysCount = 3U;
    }

    void SettingsData::Copy(const SettingsData &other)
    {
        m_TemperatureInMilliCelcius             = other.m_TemperatureInMilliCelcius;
        m_LastDaysTemperatureInMilliCelcius     = other.m_LastDaysTemperatureInMilliCelcius;
        m_HumidityInPercentage                  = other.m_HumidityInPercentage;
        m_LastDaysHumidityInPercentage          = other.m_LastDaysHumidityInPercentage;
        m_TotalIncubationDayCount               = other.m_TotalIncubationDayCount;
        m_LastDaysCount                         = other.m_LastDaysCount;
    }



    bool SettingsData::Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const
    {
        bool bResult = false;
        if (writer.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) writer.Write4Bytes(m_TemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
            (void) writer.Write4Bytes(m_LastDaysTemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
            (void) writer.WriteByte(m_HumidityInPercentage);
            (void) writer.WriteByte(m_LastDaysHumidityInPercentage);
            (void) writer.WriteByte(m_TotalIncubationDayCount);
            (void) writer.WriteByte(m_LastDaysCount);
        }
        return bResult;
    }

    bool SettingsData::Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader)
    {
        bool bResult = false;
        if (reader.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) reader.Read4Bytes(m_TemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
            (void) reader.Read4Bytes(m_LastDaysTemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
            (void) reader.ReadByte(m_HumidityInPercentage);
            (void) reader.ReadByte(m_LastDaysHumidityInPercentage);
            (void) reader.ReadByte(m_TotalIncubationDayCount);
            (void) reader.ReadByte(m_LastDaysCount);
        }
        return bResult;
    }

} // namespace Incubator
