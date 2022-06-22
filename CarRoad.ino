

#define LED_PIN PA12
#define BTN_PIN PB4

int btnCount = 0;

/**
 * @description: setup
 */
void setup()
{
    // LED和按键引脚定义，默认上拉，低电平有效
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    attachInterrupt(BTN_PIN, btnHandler, FALLING);
}

/**
 * @description: loop
 */
void loop()
{
    if (btnCount == 1)
    {
        btnCount = 2;
        
    }
}

/**
 * @description: PB4按键中断处理函数
 */
void btnHandler()
{
    digitalWrite(LED_PIN, LOW);
    btnCount++;
}