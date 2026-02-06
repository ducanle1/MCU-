#include "S32K144.h"
#include "Driver_GPIO.h"

// --- Định nghĩa Mapping Chân (Pin Mapping) ---
// Công thức: Port Index * 32 + Pin Index
// Port A=0, B=1, C=2, D=3, E=4

#define PORT_C_OFFSET  (64U)  // 2 * 32
#define PORT_D_OFFSET  (96U)  // 3 * 32

// Button Pins
#define BTN_1_PIN      (PORT_C_OFFSET + 12U) // PTC12
#define BTN_2_PIN      (PORT_C_OFFSET + 13U) // PTC13

// LED Pins
#define LED_RED_PIN    (PORT_D_OFFSET + 15U) // PTD15
#define LED_GREEN_PIN  (PORT_D_OFFSET + 16U) // PTD16

// Khai báo Driver (được định nghĩa trong Driver_GPIO.c)
extern ARM_DRIVER_GPIO Driver_GPIO0;

// Hàm delay đơn giản (Blocking)
void delay_ms(volatile uint32_t count) {
    while(count--) {
        volatile uint32_t j = 1000;
        while(j--);
    }
}

int main(void) {
    // 1. Khởi tạo (Setup) và cấu hình LED
    // LED RED
    Driver_GPIO0.Setup(LED_RED_PIN, NULL);
    Driver_GPIO0.SetDirection(LED_RED_PIN, ARM_GPIO_OUTPUT);
    Driver_GPIO0.SetOutputMode(LED_RED_PIN, ARM_GPIO_PUSH_PULL);
    Driver_GPIO0.SetOutput(LED_RED_PIN, 1); // Tắt LED ban đầu (Active Low)

    // LED GREEN
    Driver_GPIO0.Setup(LED_GREEN_PIN, NULL);
    Driver_GPIO0.SetDirection(LED_GREEN_PIN, ARM_GPIO_OUTPUT);
    Driver_GPIO0.SetOutputMode(LED_GREEN_PIN, ARM_GPIO_PUSH_PULL);
    Driver_GPIO0.SetOutput(LED_GREEN_PIN, 1); // Tắt LED ban đầu

    // 2. Khởi tạo và cấu hình Button
    // Button 1 (PTC12)
    Driver_GPIO0.Setup(BTN_1_PIN, NULL);
    Driver_GPIO0.SetDirection(BTN_1_PIN, ARM_GPIO_INPUT);
    Driver_GPIO0.SetPullResistor(BTN_1_PIN, ARM_GPIO_PULL_UP); // Kéo lên vì nhấn button nối đất

    // Button 2 (PTC13)
    Driver_GPIO0.Setup(BTN_2_PIN, NULL);
    Driver_GPIO0.SetDirection(BTN_2_PIN, ARM_GPIO_INPUT);
    Driver_GPIO0.SetPullResistor(BTN_2_PIN, ARM_GPIO_PULL_UP);

    // Biến lưu trạng thái LED (1 = OFF, 0 = ON)
    uint32_t led_red_state = 1;
    uint32_t led_green_state = 1;
    
    // Biến lưu trạng thái nút nhấn trước đó (để phát hiện cạnh xuống)
    uint32_t btn1_last = 1; 
    uint32_t btn2_last = 1;

    while(1) {
        // --- Xử lý Button 1 & LED Đỏ ---
        uint32_t btn1_curr = Driver_GPIO0.GetInput(BTN_1_PIN);
        
        // Kiểm tra sự kiện nhấn (Falling Edge: Từ 1 xuống 0)
        if (btn1_last == 1 && btn1_curr == 0) {
            // Đảo trạng thái LED
            led_red_state = !led_red_state; // 1->0 hoặc 0->1
            Driver_GPIO0.SetOutput(LED_RED_PIN, led_red_state);
            
            // Chống rung phím (Debounce) đơn giản
            delay_ms(50); 
        }
        btn1_last = btn1_curr;

        // --- Xử lý Button 2 & LED Xanh ---
        uint32_t btn2_curr = Driver_GPIO0.GetInput(BTN_2_PIN);
        
        if (btn2_last == 1 && btn2_curr == 0) {
            led_green_state = !led_green_state;
            Driver_GPIO0.SetOutput(LED_GREEN_PIN, led_green_state);
            
            delay_ms(50);
        }
        btn2_last = btn2_curr;
    }
}