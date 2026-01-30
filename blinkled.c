void blink_LED(int cycle_ms)
{
    //bat led
    GPIO_clearPin(15);
    delay_ms(cycle_ms/2);
    //tat led
    GPIO_setPin(15);
    delay_ms(cycle_ms/2)
}

void main()
{
    //cau hinh GPIO
    GPIO_int();
    //tat Led
    GPIO_setPin(15);
    //blink led
    Blink_LED(3000);
}

//Driver
#define GPIO (001)
enum mode
{
    INPUT,
    OUTPUT
};

void GPIO_int(void)
{
    // Cap clock cho Port
    Hw_GPIO_enableClock();
    // Cau hinh gpio
    Hw_GPIO_setMode(GPIO);
    // Cau hinh output
    Hw_GPIO_setDirection(OUTPUT);

}

void GPIO_setPin(int pin)
void GPIO_clearPin(int pin)

//HAL 
void HW_GPIO_enable _clock(void)
{
    IP_PCC_PORTD_CGC = 1;
}

void Hw_GPIO_setMode(int mode)
{
    IP_PORTD->PCR[15] = mode;
}

void Hw_GPIO_setDirection(enum mode direction)
{
    IP_PTD->PODR = direction;
}