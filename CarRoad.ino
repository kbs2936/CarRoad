

#define LED_PIN PA12
#define BTN_PIN PB4
#define BOARD_LED_PIN PC13

int btnCount = 0;

/**
 * @description: setup
 */
void setup()
{
    // LED和按键引脚定义，默认上拉，低电平有效
    // pinMode(LED_PIN, OUTPUT);
    // pinMode(BTN_PIN, INPUT);
    pinMode(BOARD_LED_PIN, OUTPUT);
    // attachInterrupt(BTN_PIN, btnHandler, LOW);
}

/**
 * @description: loop
 */
void loop()
{
    // if (btnCount > 0)
    // {
    //     // btnCount = 2;
    //     // delay(1000);
    //     digitalWrite(LED_PIN, LOW);
    //     digitalWrite(BOARD_LED_PIN, LOW);
    //     delay(1000);
    //     return;
    // }

    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(1000);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(1000);
}

/**
 * @description: PB4按键中断处理函数
 */
void btnHandler()
{
    btnCount++;
}
