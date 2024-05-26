/**
  ******************************************************************************
  * @file    STM32_stdlib_emulator.h
  * @author  Lightcone
  * @version V1.0.0
  * @date    2024-05-25
  * @brief   STM32标准库模拟器
  ******************************************************************************
  */
#ifndef __STM32_STDLIB_EMULATOR_H
#define __STM32_STDLIB_EMULATOR_H

#define MCU_STM32F103C
#define STM32F10X_LD
#define USE_STDPERIPH_DRIVER
#define __CC_ARM

void __dsb(int);

#endif /* __STM32_STDLIB_EMULATOR_H */