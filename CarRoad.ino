

#define LED_PIN PA12
#define BTN_PIN PB4
#define BOARD_LED_PIN PC13

int btnCount = 0;

/**
 * @description: setup
 */
void setup()
{
    // LED和按键引脚定义，默认上拉，低电平有效。板载LED默认下拉，也是低电平有效
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    attachInterrupt(BTN_PIN, btnHandler, FALLING);
    pinMode(BOARD_LED_PIN, OUTPUT);
    ledOff();
}

/**
 * @description: loop
 */
void loop()
{
    if (btnCount % 2)
    {
        ledOn();
    }
    else
    {
        ledOff();
    }
    delay(500);
}

/**
 * @description: PB4按键中断处理函数
 */
void btnHandler()
{
    btnCount++;
}

void ledOn()
{
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BOARD_LED_PIN, LOW);
}

void ledOff()
{
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BOARD_LED_PIN, HIGH);
}
