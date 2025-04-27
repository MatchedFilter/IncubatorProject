#ifndef INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H
#define INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H
#include "SettingsData.h"
#include "TimeInformationData.h"
namespace Incubator
{
    struct IncubatorInformationData
    {
    public:
        SettingsData m_SettingsData;
        TimeInformationData m_TimeInformationData;

        static constexpr uint32_t DATA_SIZE = SettingsData::DATA_SIZE + TimeInformationData::DATA_SIZE;

    public:
        void Reset();
        void Copy(const IncubatorInformationData &other);
        bool Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const;
        bool Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader);
    };
    
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_INCUBATORINFORMATIONDATA_H