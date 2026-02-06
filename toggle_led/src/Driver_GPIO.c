/*
 * Copyright (c) 2023 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Driver_GPIO.h"
#include "S32K144.h"

// Pin mapping
#define GPIO_MAX_PINS           160U
#define PIN_IS_AVAILABLE(n)     ((n) < GPIO_MAX_PINS)

//Pin Mapping Khai báo mảng địa chỉ thủ công (Tránh lỗi "undefined reference to GPIO_BASE_PTRS")
static GPIO_Type *const GPIO_Base_Ptrs[] = IP_GPIO_BASE_PTRS; // PTA, PTB, ...
static PORT_Type *const PORT_Base_Ptrs[] = IP_PORT_BASE_PTRS; // PORTA, PORTB, ...

// Setup GPIO Interface
static int32_t GPIO_Setup (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event) {
  int32_t result = ARM_DRIVER_OK;

// Helper lấy Port Index (0-4) từ Pin ID
#define GET_PORT_IDX(p) ((p) >> 5)
// Helper lấy Pin Index (0-31) trong Port
#define GET_PIN_IDX(p)  ((p) & 0x1F)

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);

    // 1. Cấp Clock cho Port tương ứng (PCC)
    // Port C (Button)
        IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1);
        IP_PORTC->PCR[pinIdx] &= ~PORT_PCR_MUX_MASK;
        IP_PORTC->PCR[pinIdx] |= PORT_PCR_MUX(1);
    
    // Port D (LED)
        IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
        IP_PORTD->PCR[pinIdx] &= ~PORT_PCR_MUX_MASK;
        IP_PORTD->PCR[pinIdx] |= PORT_PCR_MUX(1);
    
    (void)cb_event;

  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Direction
static int32_t GPIO_SetDirection (ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction) {
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);
    GPIO_Type *gpio = GPIO_Base_Ptrs[portIdx];
    
    switch (direction) {
      case ARM_GPIO_INPUT:
      // Xóa bit tương ứng trong PDDR (Port Data Direction Register) -> Input
        gpio->PDDR &= ~(1UL << pinIdx);
      // Cần đảm bảo Input Buffer được bật (thường mặc định trên S32K, nhưng kiểm tra PIDR)
        break;
      case ARM_GPIO_OUTPUT:
      // Set bit tương ứng trong PDDR -> Output
        gpio->PDDR |= (1UL << pinIdx);
        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Output Mode
static int32_t GPIO_SetOutputMode (ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode) {
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);
    // Chế độ Open Drain nằm ở thanh ghi PORT PCR, bit ODE (Open Drain Enable)

    switch (mode) {
      case ARM_GPIO_PUSH_PULL:
      // Tắt Open Drain (Bit 5 trong PCR)
        PORT_Base_Ptrs[portIdx]->PCR[pinIdx] &= ~PORT_PCR_DSE_MASK;
        break;
      case ARM_GPIO_OPEN_DRAIN:
      // Bật Open Drain
        PORT_Base_Ptrs[portIdx]->PCR[pinIdx] |= PORT_PCR_DSE_MASK;
        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Pull Resistor
static int32_t GPIO_SetPullResistor (ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor) {
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);
    // Cấu hình Pull nằm ở PORT PCR: PE (Pull Enable - bit 1) và PS (Pull Select - bit 0)

    // Reset cả 2 bit PE và PS trước
    PORT_Base_Ptrs[portIdx]->PCR[pinIdx] &= ~(PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
    switch (resistor) {
      case ARM_GPIO_PULL_NONE:
        break;
      case ARM_GPIO_PULL_UP:
      // Bật PE và Set PS = 1 (Pull Up)
      PORT_Base_Ptrs[portIdx]->PCR[pinIdx] |= (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
        break;
      case ARM_GPIO_PULL_DOWN:
      // Bật PE và Set PS = 0 (Pull Down)
        PORT_Base_Ptrs[portIdx]->PCR[pinIdx] |= PORT_PCR_PE_MASK;
        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Event Trigger
static int32_t GPIO_SetEventTrigger (ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger) {
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) {

    switch (trigger) {
      case ARM_GPIO_TRIGGER_NONE:
        break;
      case ARM_GPIO_TRIGGER_RISING_EDGE:
        break;
      case ARM_GPIO_TRIGGER_FALLING_EDGE:
        break;
      case ARM_GPIO_TRIGGER_EITHER_EDGE:
        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Output Level
static void GPIO_SetOutput (ARM_GPIO_Pin_t pin, uint32_t val) {

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);
    GPIO_Type *gpio = GPIO_Base_Ptrs[portIdx];
    if (val == 0) {
        // Clear Output: Write 1 to PCOR (Port Clear Output Register)
        gpio->PCOR = (1UL << pinIdx);
    } else {
        // Set Output: Write 1 to PSOR (Port Set Output Register)
        gpio->PSOR = (1UL << pinIdx);
    }
  }
}

// Get GPIO Input Level
static uint32_t GPIO_GetInput (ARM_GPIO_Pin_t pin) {
  uint32_t val = 0U;

  if (PIN_IS_AVAILABLE(pin)) {
    uint8_t portIdx = GET_PORT_IDX(pin);
    uint8_t pinIdx  = GET_PIN_IDX(pin);
  // Read PDIR (Port Data Input Register)
    if ((GPIO_Base_Ptrs[portIdx]->PDIR & (1UL << pinIdx)) != 0) {
        val = 1U;
    } 
  }
  return val;
}


// GPIO Driver access structure
ARM_DRIVER_GPIO Driver_GPIO0 = {
  GPIO_Setup,
  GPIO_SetDirection,
  GPIO_SetOutputMode,
  GPIO_SetPullResistor,
  GPIO_SetEventTrigger,
  GPIO_SetOutput,
  GPIO_GetInput
};
