#ifndef INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H
#define INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
#include "IncubatorDataConstants.h"
namespace Incubator
{
    struct TimeInformationData
    {
    public:
        uint32_t m_CurrentTimestampInSecond;

        static constexpr uint32_t DATA_SIZE = static_cast<uint32_t>(sizeof(m_CurrentTimestampInSecond));

    public:
        void Reset();
        void Copy(const TimeInformationData &other);
        bool Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const;
        bool Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader);
    };
    
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H