#include "Incubator/IncubatorDependencies.h"
#include "Stm32Peripherals.h"

extern "C"
{
    uint64_t GetTimestampInMillisecondForStm32(void);
}

namespace Incubator
{
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }


    bool WriteToFlash(const uint32_t flashBaseAddress, const uint32_t offset, const FlashBuffer &buffer)
    {
        bool bResult = false;

        if ((buffer.m_Size < FlashBuffer::MAX_WORD_SIZE) && (buffer.m_Size > static_cast<uint32_t>(0UL)))
        {
            FlashBuffer currentBuffer;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < FlashBuffer::MAX_WORD_SIZE; i++)
            {
                currentBuffer.m_Words[i] = static_cast<uint32_t>(0xFFFFFFFFUL);
            }
            (void) ReadFromFlash(flashBaseAddress, static_cast<uint32_t>(0x0UL), currentBuffer, FlashBuffer::MAX_WORD_SIZE);
            currentBuffer.m_Size = FlashBuffer::MAX_WORD_SIZE;
            const uint32_t wordOffset = offset / static_cast<uint32_t>(sizeof(uint32_t));
            for (uint32_t i = static_cast<uint32_t>(0UL); i < buffer.m_Size; i++)
            {
                const uint32_t currentBufferIndex = wordOffset + i;
                currentBuffer.m_Words[currentBufferIndex] = buffer.m_Words[i];
            }

            HAL_FLASH_Unlock();

            FLASH_EraseInitTypeDef eraseInit;
            uint32_t sectorError;

            eraseInit.TypeErase     = FLASH_TYPEERASE_PAGES;
            eraseInit.PageAddress   = flashBaseAddress;
            eraseInit.NbPages       = 1;

            if (HAL_OK == HAL_FLASHEx_Erase(&eraseInit, &sectorError))
            {
                bool bValid = true;
                for (uint32_t i  = static_cast<uint32_t>(0UL); i < currentBuffer.m_Size; i++)
                {
                    const uint32_t writeAddress = flashBaseAddress + (i * static_cast<uint32_t>(sizeof(uint32_t)));
                    if (HAL_OK != HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, writeAddress, currentBuffer.m_Words[i]))
                    {
                        bValid = false;
                        break;
                    }
                }
                bResult = bValid;
            }
            HAL_FLASH_Lock();
        }
        return bResult;
    }


    bool ReadFromFlash(const uint32_t baseAddress, const uint32_t offset, FlashBuffer &buffer, const uint32_t size)
    {
        bool bResult = false;
        if ((size <= FlashBuffer::MAX_WORD_SIZE) && (size > static_cast<uint32_t>(0UL)))
        {
            const uint32_t address = baseAddress + offset;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < size; i++)
            {
                volatile uint32_t *readAddress = reinterpret_cast<volatile uint32_t*>(address + (i * static_cast<uint32_t>(sizeof(uint32_t))));
                buffer.m_Words[i] = *readAddress;
            }
            for (uint32_t i = static_cast<uint32_t>(0UL); i < size; i++)
            {
                if (buffer.m_Words[i] != 0xFFFFFFFFUL)
                {
                    bResult = true;
                    break;
                }
            }
            if (bResult)
            {
                buffer.m_Size = size;
            }
        }
        return bResult;
    }

    uint64_t GetTimestampInMillisecond()
    {
    	return GetTimestampInMillisecondForStm32();
    }

    void TurnOnHeater()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }

    void TurnOffHeater()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }

    void TurnOnHumidityGenerator()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    }

    void TurnOffHumidityGenerator()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    }

    void EnableMotor()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    }

    void DisableMotor()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    }

} // namespace Incubator
