
#define LED_PIN PA12
#define BTN_PIN PB4
#define BOARD_LED_PIN PC13

#define RIGHT0 PA0
#define RIGHT1 PA1

#define LEFT0 PA2
#define LEFT1 PA3

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

    //电机引脚
    pinMode(RIGHT0, OUTPUT);
    pinMode(RIGHT1, OUTPUT);
    pinMode(LEFT0, OUTPUT);
    pinMode(LEFT1, OUTPUT);
    wrightStop();
}

/**
 * @description: loop
 */
void loop()
{
    if (btnCount == 1)
    {
        ledOn();
        wrightForward();
    }
    else if (btnCount == 2)
    {
        ledOff();
        wrightBackward();
    }
    else if (btnCount >= 3)
    {
        btnCount = 0;
        wrightStop();
    }
    delay(100);
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

void wrightForward()
{
    digitalWrite(RIGHT0, HIGH);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, HIGH);
    digitalWrite(LEFT1, LOW);
}

void wrightBackward()
{
    digitalWrite(RIGHT0, LOW);
    digitalWrite(RIGHT1, HIGH);

    digitalWrite(LEFT0, LOW);
    digitalWrite(LEFT1, HIGH);
}

void wrightStop()
{
    digitalWrite(RIGHT0, LOW);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, LOW);
    digitalWrite(LEFT1, LOW);
}
