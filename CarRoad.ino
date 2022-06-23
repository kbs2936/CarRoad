
// LED和按键引脚宏定义
#define LED_PIN PA12
#define BTN_PIN PB4
#define BOARD_LED_PIN PC13

//车轮电机引脚宏定义
#define RIGHT0 PA0
#define RIGHT1 PA1
#define LEFT0 PA2
#define LEFT1 PA3

//红外传感器引脚宏定义
#define IR_LEFT PB7
#define IR_MID PB8
#define IR_RIGHT PB9

#define LEFT_STAT digitalRead(IR_LEFT)
#define MID_STAT digitalRead(IR_MID)
#define RIGHT_STAT digitalRead(IR_RIGHT)

//按键中断计数器
int btnCount = 0;

/**
 * @description: setup
 */
void setup()
{
    //外部LED和按键引脚定义，默认上拉，低电平有效。板载LED默认下拉，也是低电平有效
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    attachInterrupt(BTN_PIN, btnHandler, LOW);
    pinMode(BOARD_LED_PIN, OUTPUT);
    ledOff();

    //车轮电机引脚设置
    pinMode(RIGHT0, OUTPUT);
    pinMode(RIGHT1, OUTPUT);
    pinMode(LEFT0, OUTPUT);
    pinMode(LEFT1, OUTPUT);
    carStop();

    //红外传感器引脚设置，低电平有效。遇到黑线没有收到反弹红外波时变高电平。
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_MID, INPUT);
    pinMode(IR_RIGHT, INPUT);
}

/**
 * @description: loop
 */
void loop()
{
    if (btnCount == 1)
    {
    }
    else if (btnCount >= 2)
    {
        btnCount = 0;
    }
    delay(100);

    if (LEFT_STAT == HIGH)
    {
        ledOn();
    }
    else
    {
        ledOff();
    }
}

/**
 * @description: PB4按键中断处理函数
 */
void btnHandler()
{
    btnCount++;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @description: 点亮LED
 */
void ledOn()
{
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BOARD_LED_PIN, LOW);
}

/**
 * @description: 熄灭LED
 */
void ledOff()
{
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BOARD_LED_PIN, HIGH);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @description: 小车前进
 */
void carForward()
{
    digitalWrite(RIGHT0, HIGH);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, HIGH);
    digitalWrite(LEFT1, LOW);
}

/**
 * @description: 小车停止
 */
void carStop()
{
    digitalWrite(RIGHT0, LOW);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, LOW);
    digitalWrite(LEFT1, LOW);
}

/**
 * @description: 小车右转
 */
void carTurnRight()
{
    digitalWrite(RIGHT0, LOW);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, HIGH);
    digitalWrite(LEFT1, LOW);
}

/**
 * @description: 小车左转
 */
void carTurnLeft()
{
    digitalWrite(RIGHT0, HIGH);
    digitalWrite(RIGHT1, LOW);

    digitalWrite(LEFT0, LOW);
    digitalWrite(LEFT1, LOW);
}