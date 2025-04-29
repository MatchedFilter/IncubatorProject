#include "NTC/NTCDependencies.h"
#include "Stm32Peripherals.h"

namespace NTC
{
    void StartAdc(const uint8_t id);
    uint32_t ReadAdc(const uint8_t id);

    void StartAdc(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_ADC_Start(&hadc1);
        }
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t result = static_cast<uint32_t>(0UL);
        if (id == 0x00U)
        {
            result =  HAL_ADC_GetValue(&hadc1);
        }
        return result;
    }
} // namespace NTC

