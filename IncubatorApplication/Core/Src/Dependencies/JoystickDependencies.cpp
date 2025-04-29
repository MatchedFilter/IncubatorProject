#ifndef JOYSTICK_JOYSTICKDEPENDENCIES_H
#define JOYSTICK_JOYSTICKDEPENDENCIES_H
#include "Joystick/JoystickDependencies.h"
#include "Stm32Peripherals.h"

namespace Joystick
{
    void StartHorizontalAdc(const uint8_t id)
    {
        if (0x00U == id)
        {
            ADC_ChannelConfTypeDef sConfig = {0};
            sConfig.Channel = ADC_CHANNEL_2;
            sConfig.Rank = ADC_REGULAR_RANK_1;
            sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
            HAL_ADC_ConfigChannel(&hadc2, &sConfig);
            HAL_ADC_Start(&hadc2);
        }
    }

    void StartVertialAdc(const uint8_t id)
    {
        if (0x00U == id)
        {
            ADC_ChannelConfTypeDef sConfig = {0};
            sConfig.Channel = ADC_CHANNEL_3;
            sConfig.Rank = ADC_REGULAR_RANK_1;
            sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
            HAL_ADC_ConfigChannel(&hadc2, &sConfig);
            HAL_ADC_Start(&hadc2);
        }
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
		HAL_Delay(durationInMillisecond);
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t result = static_cast<uint32_t>(0x00U);
        if (0x00U == id)
        {
            result = HAL_ADC_GetValue(&hadc2);
        }
        return result;
    }

    uint8_t ReadSwitchState(const uint8_t id)
    {
        uint8_t result = 0x00U;
        if (0x00U == id)
        {
            result = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET;
        }
        return result;
    }
} // namespace Joystick

#endif // JOYSTICK_JOYSTICKDEPENDENCIES_H