#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
    void IncubatorInformationData::Reset()
    {
        m_SettingsData.Reset();
        m_TimeInformationData.Reset();
    }

    void IncubatorInformationData::Copy(const IncubatorInformationData &other)
    {
        m_SettingsData.Copy(other.m_SettingsData);
        m_TimeInformationData.Copy(other.m_TimeInformationData);
    }


    bool IncubatorInformationData::Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const
    {
        bool bResult = false;
        if (writer.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) m_SettingsData.Serialize(writer);
            (void) m_TimeInformationData.Serialize(writer);
        }
        return bResult;
    }

    bool IncubatorInformationData::Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader)
    {
        bool bResult = false;
        if (reader.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) m_SettingsData.Deserialize(reader);
            (void) m_TimeInformationData.Deserialize(reader);
        }
        return bResult;
    }

} // namespace Incubator
