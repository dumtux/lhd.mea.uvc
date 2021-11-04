#include <Wire.h>

#define LED1 P2_0  // no PWM
#define LED2 P2_1
#define LED3 P2_2
#define LED4 P2_3  // no PWM
#define LED5 P2_4
#define LED6 P2_5

#define CTRL      P1_3
#define CHARGE    P1_4
#define BAT_SENSE P1_2
#define UVC_EN    P1_6

#define DURATION 300000

bool sterilizing = false;
int timer = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(UVC_EN, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(UVC_EN, LOW);

  pinMode(CTRL, INPUT_PULLUP);
  pinMode(CHARGE, INPUT);
  attachInterrupt(CTRL, ISR_ctrl, CHANGE);


//  pinMode(CHARGE, INPUT);
//  pinMode(BAT_SENSE, INPUT);
//  pinMode(UVC_EN, OUTPUT);
}

void ISR_ctrl() {
    if (digitalRead(CTRL) == HIGH) {
        digitalWrite(LED4, LOW);
        digitalWrite(UVC_EN, LOW);
        sterilizing = false;
        timer = 0;
    } else {
        sterilizing = true;
        timer = 0;
    }
}


void loop() {
    if (timer > DURATION) {
        sterilizing = false;
        timer = 0;
    }

    for (int i = 0; i < 25; i++) {
        if (digitalRead(CHARGE) == LOW) {
            analogWrite(LED2, i*10);
            analogWrite(LED3, i*10);
        } else {
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
        }
        if (digitalRead(CTRL) == LOW && sterilizing) {
            analogWrite(LED5, i*10);
            analogWrite(LED6, i*10);
            digitalWrite(LED4, HIGH);
            digitalWrite(UVC_EN, HIGH);
            timer+= 40;
        } else {
            digitalWrite(LED5, LOW);
            digitalWrite(LED6, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(UVC_EN, LOW);
        }
        delay(40);
    }
    for (int i = 25; i >=0; i--) {
        if (digitalRead(CHARGE) == LOW) {
            analogWrite(LED2, i*10);
            analogWrite(LED3, i*10);
        } else {
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
        }
        if (digitalRead(CTRL) == LOW && sterilizing) {
            analogWrite(LED5, i*10);
            analogWrite(LED6, i*10);
            digitalWrite(LED4, HIGH);
            digitalWrite(UVC_EN, HIGH);
            timer += 40;
        } else {
            digitalWrite(LED5, LOW);
            digitalWrite(LED6, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(UVC_EN, LOW);
        }
        delay(40);
    }
}
