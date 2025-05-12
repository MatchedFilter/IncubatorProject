#include "Incubator/IncubatorData/AdminData.h"

namespace Incubator
{
    void AdminData::Reset()
    {
        m_P = static_cast<int32_t>(600L);
        m_I = static_cast<int32_t>(0L);
        m_D = static_cast<int32_t>(0L);
        m_UpperHumidityDifference = 3U;
        m_LowerHumidityDifference = 3U;
    }

    void AdminData::Copy(const AdminData &other)
    {
        m_P = other.m_P;
        m_I = other.m_I;
        m_D = other.m_D;
        m_UpperHumidityDifference = other.m_UpperHumidityDifference;
        m_LowerHumidityDifference = other.m_LowerHumidityDifference;
    }


    bool AdminData::Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const
    {
        bool bResult = false;
        if (writer.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) writer.Write4Bytes(m_P, MF::ENDIAN_TYPE_BIG);
            (void) writer.Write4Bytes(m_I, MF::ENDIAN_TYPE_BIG);
            (void) writer.Write4Bytes(m_D, MF::ENDIAN_TYPE_BIG);
            (void) writer.WriteByte(m_UpperHumidityDifference);
            (void) writer.WriteByte(m_LowerHumidityDifference);

        }
        return bResult;
    }

    bool AdminData::Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader)
    {
        bool bResult = false;
        if (reader.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) reader.Read4Bytes(m_P, MF::ENDIAN_TYPE_BIG);
            (void) reader.Read4Bytes(m_I, MF::ENDIAN_TYPE_BIG);
            (void) reader.Read4Bytes(m_D, MF::ENDIAN_TYPE_BIG);
            (void) reader.ReadByte(m_UpperHumidityDifference);
            (void) reader.ReadByte(m_LowerHumidityDifference);
        }
        return bResult;
    }

} // namespace Incubator
