
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
    //按键按下，亮灯开始循线前进，默认中间红外传感器在黑线位置
    if (btnCount >= 1)
    {
        ledOn();

        //车头右倾，要左转直到正向
        if (isCarRight())
        {
            //转弯前先停止，消除惯性抖动
            carStop();

            while (1)
            {
                carTurnLeft();
                if (isCarMiddle())
                {
                    carStop();
                    carForward();
                    break;
                }
                //转弯过程中如果3灯同时遇到黑线，说明是在T横线处转弯，判定停止
                else if (isCarReachEnd())
                {
                    clear();
                    break;
                }
            }
        }
        //车头左倾，要右转直到正向
        else if (isCarLeft())
        {
            //转弯前先停止，消除惯性抖动
            carStop();

            while (1)
            {
                carTurnRight();
                if (isCarMiddle())
                {
                    carStop();
                    carForward();
                    break;
                }
                //转弯过程中如果3灯同时遇到黑线，说明是在T横线处转弯，判定停止
                else if (isCarReachEnd())
                {
                    clear();
                    break;
                }
            }
        }
        //左中右3边同时遇到黑线，说明走到T形横线处，停止小车
        else if (isCarReachEnd())
        {
            clear();
        }
        //其他情况小车正常前进
        else
        {
            carForward();
        }
    }
}

/**
 * @description: PB4按键中断处理函数
 */
void btnHandler()
{
    btnCount++;
    delay(1000);
}

/**
 * @description: 停车、关灯、重置计数器
 */
void clear()
{
    carStop();
    ledOff();
    btnCount = 0;
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
 * @description: 车头是否右倾
 * @return true/false
 */
bool isCarRight()
{
    //左边遇黑线，车头右倾
    return ((LEFT_STAT == HIGH) && (RIGHT_STAT == LOW));
}

/**
 * @description: 车头是否左倾
 * @return true/false
 */
bool isCarLeft()
{
    //右边遇黑线，车头左倾
    return ((LEFT_STAT == LOW) && (RIGHT_STAT == HIGH));
}

/**
 * @description: 车头是否在黑线中间
 * @return true/false
 */
bool isCarMiddle()
{
    return ((LEFT_STAT == LOW) && (RIGHT_STAT == LOW) && (MID_STAT == HIGH));
}

/**
 * @description: 车头是否到达终点
 * @return true/false
 */
bool isCarReachEnd()
{
    // 3线遇黑，或者3线同时反射，判定达到T终点
    return ((LEFT_STAT == HIGH) && (RIGHT_STAT == HIGH) && (MID_STAT == HIGH));
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

    //小车移动有惯性，所以停止后要延时等一会儿
    delay(300);
}

/**
 * @description: 小车右转
 */
void carTurnRight()
{
    // digitalWrite(RIGHT0, LOW);
    // digitalWrite(RIGHT1, HIGH);
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

    // digitalWrite(LEFT0, LOW);
    // digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT0, LOW);
    digitalWrite(LEFT1, LOW);
}
