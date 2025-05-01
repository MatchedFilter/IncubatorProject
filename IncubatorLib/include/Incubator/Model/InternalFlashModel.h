#ifndef INCUBATOR_INTERNALFLASHMODEL_H
#define INCUBATOR_INTERNALFLASHMODEL_H
#include "IModel.h"

namespace Incubator
{
    class InternalFlashModel : public IModel
    {
    public:
        InternalFlashModel(const uint32_t flashBaseAddress);
        ~InternalFlashModel();
        virtual bool Update(const PidData &data) override;
        virtual bool Update(const SettingsData &data) override;
        virtual bool Update(const TimeInformationData &data) override;
        virtual bool Get(PidData &data) override;
        virtual bool Get(SettingsData &data) override;
        virtual bool Get(TimeInformationData &data) override;

    private:
        const uint32_t m_FlashBaseAddress;
    };
} // namespace Incubator

#endif // INCUBATOR_INTERNALFLASHMODEL_H