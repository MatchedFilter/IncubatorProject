#ifndef INCUBATOR_EEPROMMODEL_H
#define INCUBATOR_EEPROMMODEL_H
#include "IModel.h"
#include "Eeprom24C/Eeprom24C32.h"

namespace Incubator
{
    class EepromModel : public IModel
    {
    public:
        EepromModel();
        ~EepromModel();
        void Initialize();
        virtual bool Update(const SettingsData &data) override;
        virtual bool Update(const TimeInformationData &data) override;
        virtual bool Get(SettingsData &data) override;
        virtual bool Get(TimeInformationData &data) override;

    private:
        Eeprom24C::Eeprom24C32 m_Eeprom24C32;
    };
} // namespace Incubator

#endif // INCUBATOR_EEPROMMODEL_H