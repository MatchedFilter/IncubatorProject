#include "DHT11/DHT11Dependencies.h"
#include "Stm32Peripherals.h"



namespace DHT11
{
    void StartTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
            __HAL_TIM_SET_COUNTER(&htim4, 0);
            HAL_TIM_Base_Start(&htim4);
        }
    }

    void ResetTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
	        __HAL_TIM_SET_COUNTER(&htim4, 0);
        }
    }

    void StopTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
	        HAL_TIM_Base_Stop(&htim4);
        }
    }

    uint32_t GetTimestampInMicrosecondFromTimer(const uint8_t id)
    {
    	uint32_t result = static_cast<uint32_t>(0UL);
        if (id == 0x00U)
        {
        	result = static_cast<uint32_t>(__HAL_TIM_GET_COUNTER(&htim4));
        }
        return result;
    }

    void SetDataPinAsOutput(const uint8_t id)
    {
        if (id == 0x00U)
        {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_InitStruct.Pin = GPIO_PIN_8;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
}

    void SetDataPinAsHigh(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        }
    }

    void SetDataPinAsLow(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
        }
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }

    void SetDataPinAsInput(const uint8_t id)
    {
        if (id == 0x00U)
        {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_InitStruct.Pin = GPIO_PIN_8;
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
    }

    uint8_t ReadDataPin(const uint8_t id)
    {
        uint8_t result = 0x02U;
        if (id == 0x00U)
        {
            result = static_cast<uint8_t>(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8));
        }
        return result;
    }

} // namespace DHT11

