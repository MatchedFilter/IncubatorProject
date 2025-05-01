#include "Incubator/IncubatorData/PidData.h"

namespace Incubator
{
    void PidData::Reset()
    {
        m_P = 5.0;
        m_I = 0.0;
        m_D = 0.0;
    }

    void PidData::Copy(const PidData &other)
    {
        m_P = other.m_P;
        m_I = other.m_I;
        m_D = other.m_D;
    }


    bool PidData::Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const
    {
        bool bResult = false;
        if (writer.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) writer.Write8Bytes(m_P, MF::ENDIAN_TYPE_BIG);
            (void) writer.Write8Bytes(m_I, MF::ENDIAN_TYPE_BIG);
            (void) writer.Write8Bytes(m_D, MF::ENDIAN_TYPE_BIG);
        }
        return bResult;
    }

    bool PidData::Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader)
    {
        bool bResult = false;
        if (reader.GetRemainingSize() >= DATA_SIZE)
        {
            bResult = true;
            (void) reader.Read8Bytes(m_P, MF::ENDIAN_TYPE_BIG);
            (void) reader.Read8Bytes(m_I, MF::ENDIAN_TYPE_BIG);
            (void) reader.Read8Bytes(m_D, MF::ENDIAN_TYPE_BIG);
        }
        return bResult;
    }

} // namespace Incubator
