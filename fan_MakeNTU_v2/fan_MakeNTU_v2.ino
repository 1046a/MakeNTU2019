#include <Servo.h>
#include <Stepper.h>

#define X_DIR 5
#define Y_DIR 6
#define X_STP 2
#define Y_STP 3
#define EN 8

#define servo_pin 9

Servo myservo;
Stepper stepper(100, 13, 12, 11, 10);

int pos = 0; // variable to store the servo position
int degree;  // for incoming serial data
char some_input;
bool triggered = false;
bool _x = true;
bool _y = false;
bool neck_motor = false;
bool detected_human = false;
// int counter = 0;
//int num;
volatile byte state = LOW;

void initialTimer()
{
    TIMSK2 = (TIMSK2 & B11111110) | 0x06;
    TCCR2B = (TCCR2B & B11111000) | 0x07;
     OCR2A = 128;
     OCR2B = 256;
}

ISR(TIMER2_COMPA_vect)
{
//   if(detected_human){
     // stepper.step(200);
     //Serial.println("final in");
  // }
}

ISR(TIMER2_COMPB_vect)
{
}
// ISR(TIMER2_OVF_vect)
// {
//     if(detected_human){
//       stepper.step(200);
//       state = !state;
//       digitalWrite(13, state);
//     }
// }

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    //delay(10);

    pinMode(X_DIR, OUTPUT);
    pinMode(X_STP, OUTPUT);
    pinMode(Y_DIR, OUTPUT);
    pinMode(Y_STP, OUTPUT);
    // digitalWrite(X_DIR, true);
    // digitalWrite(Y_DIR, false);
    //digitalWrite(X_STP, LOW);
    //digitalWrite(Y_STP, LOW);
    //digitalWrite(X_DIR, false);
    //digitalWrite(Y_DIR, false);
    //pinMode(LED_BUILTIN, OUTPUT);

    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);

    //pinMode(servo_pin, OUTPUT);
    //digitalWrite(servo_pin, HIGH);

    myservo.attach(servo_pin);
    myservo.write(180);

    stepper.setSpeed(140);
    initialTimer();
}

void moving(bool _x, bool _y)
{
    digitalWrite(X_DIR, _x);
    digitalWrite(Y_DIR, _y);
    // //delay(10);
    // for (int i = 0; i < 200; i++) // 200 steps making a round
    // {
    //     digitalWrite(X_STP, LOW);
    //     digitalWrite(Y_STP, LOW);
    //     delayMicroseconds(1000); // notice that it's microseconds
    //     digitalWrite(X_STP, HIGH);
    //     digitalWrite(Y_STP, HIGH);
    //     delayMicroseconds(1000);
    // }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(X_STP, LOW);
        digitalWrite(Y_STP, LOW);
        delayMicroseconds(10000); // notice that it's microseconds
        digitalWrite(X_STP, HIGH);
        digitalWrite(Y_STP, HIGH);
        delayMicroseconds(10000);
    }
}

void servoRotate()
{
    //val = map(val, 0, 1023, 0, 180);
    for (int i = 0; i < 180; i++)
    {
        myservo.write(i);
        delay(10);
    }
    for (int i = 180; i >= 0; i--)
    {
        myservo.write(i);
        delay(10);
    }
    // degree++;
    // myservo.write(degree);
}

void loop()
{
    if (Serial.available())
    {
        some_input = Serial.read();
        Serial.write(some_input);
        switch (some_input)
        {
        case 'o':
            // fan turn off
            detected_human = false;
            break;
        case 'n':
            Serial.println("final");
            detected_human = true;
            break;
        case '+':
            // turn right
            Serial.println("hey");
            triggered = true;
            _x = true;
            _y = false;
            break;
        case '-':
            // turn left
            triggered = true;
            _x = false;
            _y = true;
            break;
        case 'a':
            //Serial.println("hi");
            neck_motor = true;
            break;
        case 'm':
            neck_motor = false;
            break;
        default:
            break;
        }
    }
    if (triggered)
    {
        Serial.println("ey");
        moving(_x, _y);
        triggered = false;
    }
    if (neck_motor)
    {
        servoRotate();
        //Serial.println("servo");
    }
    if(detected_human)
      stepper.step(200);
    //servoRotate();
    //moving();
    // if (Serial.available())
    // {
    //     num = Serial.read() - '0';
    //     Serial.println(num);
    //     light(num);
    // }
    //stepper.step(100);
    //delay(1000);
}
