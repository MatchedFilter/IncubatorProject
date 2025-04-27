#include "Incubator/IncubatorData/TimeInformationData.h"

namespace Incubator
{
    void TimeInformationData::Reset()
    {
        m_CurrentTimestampInSecond = static_cast<uint32_t>(0UL);
    }

    void TimeInformationData::Copy(const TimeInformationData &other)
    {
        m_CurrentTimestampInSecond = other.m_CurrentTimestampInSecond;
    }


    bool TimeInformationData::Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const
    {
        bool bResult = false;
        if (writer.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) writer.Write4Bytes(m_CurrentTimestampInSecond, MF::ENDIAN_TYPE_BIG);
        }
        return bResult;
    }

    bool TimeInformationData::Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader)
    {
        bool bResult = false;
        if (reader.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) reader.Read4Bytes(m_CurrentTimestampInSecond, MF::ENDIAN_TYPE_BIG);
        }
        return bResult;
    }

} // namespace Incubator
