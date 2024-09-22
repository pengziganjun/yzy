#include <Servo.h>
#include<Wire.h>
#include"UI.h"
#include"start.h"
#include"setting.h"
//天桥
#define sky_X_go 2
#define sky_X_back 3

#define sky_Y_go 4
#define sky_Y_back 5
//升降
#define down 6
#define up 7
//摇杆数据
#define X A0
#define Y A1
//爪子舵机
#define claw1 10
#define claw2 11

#define down_claw 8

//投币
#define start 13

Servo myservo1;
Servo myservo2;

int start_date;
int down_claw_date;
int x ;
int y ;
int jk = 0;
int l;
int r;
int mn = 1;
void zhuawawa() {
  x = analogRead(X);
  y = analogRead(Y);
  down_claw_date = digitalRead(down_claw);
  start_date = 1;
  //下爪
  if (down_claw_date == 0   ) {
    DOWN();
    delay(2000);
    myservo1.write(r);//-
    myservo2.write(l);//+
    delay (800);
    UP();
    delay(3000);
    myservo1.write(150);//right
    myservo2.write(30);//left
    start_date = 0;
  }



  //天桥运动
  if (y <= 1023 && y > 650) {
    x_turn1();
  }
  if (y >= 0 && y < 400) {
    x_turn2();
  }
  if (y >= 400 && y < 650) {
    digitalWrite(sky_X_go, HIGH);
    digitalWrite(sky_X_back, HIGH);
  }
  if (x <= 1023 && x > 650) {
    y_turn1();
  }
  if (x >= 0 && x < 400) {
    y_turn2();
  }
  if (x >= 400 && x < 650) {
    digitalWrite(sky_Y_go, HIGH);
    digitalWrite(sky_Y_back, HIGH);
  }




}

void DOWN() {

  digitalWrite(down, HIGH);
  digitalWrite(up, LOW);


}
void UP() {

  digitalWrite(down, LOW);
  digitalWrite(up, HIGH);

}
void STOP() {
  digitalWrite(down, HIGH);
  digitalWrite(up, HIGH);
}
void y_turn1() {

  digitalWrite(sky_Y_go, HIGH);
  digitalWrite(sky_Y_back, LOW);

}
void y_turn2() {

  digitalWrite(sky_Y_go, LOW);
  digitalWrite(sky_Y_back, HIGH);

}
void x_turn1() {

  digitalWrite(sky_X_go, HIGH);
  digitalWrite(sky_X_back, LOW);

}
void x_turn2() {

  digitalWrite(sky_X_go, LOW);
  digitalWrite(sky_X_back, HIGH);

}

void setup() {
  Serial.begin(115200);

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  l = 90;
  r = 90;
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(sky_X_go, OUTPUT);
  pinMode(sky_X_back, OUTPUT);
  pinMode(sky_Y_go, OUTPUT);
  pinMode(sky_Y_back, OUTPUT);
  pinMode(down_claw, INPUT_PULLUP);
  pinMode(start, INPUT);
  myservo1.write(150);
  myservo2.write(30);
  //  digitalWrite(sky_X_go, LOW);//初始化端口输出为低电平
  //  digitalWrite(sky_X_back, LOW);//初始化端口输出为低电平
  //  digitalWrite(sky_Y_go, LOW);//初始化端口输出为低电平
  //  digitalWrite(sky_Y_back, LOW);//初始化端口输出为低电平
  myservo1.attach(claw1);
  myservo2.attach(claw2);

}

void loop() {
over:
  jk = 0;
   mn = 1;
beginning:
  oled.clearDisplay();
  board();
  age();
  star_t();
  settin_g();
  jianto_u();
  oled.display();
  //choice = 0;
  //投币判断
  start_date = digitalRead(start);
  //下爪键&&确定键&&摇杆选择键
  x = analogRead(X);
  y = analogRead(Y);
  down_claw_date = digitalRead(down_claw);
  if (x <= 1023 && x > 650) {
    int m = x;
    choice = choice + 25;
    if (choice > 40) {
      choice = choice - 25;
    }
  }
  if (x >= 0 && x < 400) {
    int n = x;
    choice = choice - 25;
    if (choice <= 0) {
      choice = choice + 25;
    }
  }

  while (down_claw_date == 0 && choice == 10) {
    int ll;
    start_date = digitalRead(start);
    ll = start_date;
    oled.clearDisplay();
    xiongma_o();
    oled.display();


    //游戏开始
    delay(2);
    while (ll == 1) {
      x = analogRead(X);
      y = analogRead(Y);
      oled.clearDisplay();
      xiazhuazile();
      oled.display();
      delay(2);
      down_claw_date = digitalRead(down_claw);
      //start_date = 1;
      delay(10);
      //下爪
      if (down_claw_date == 0   ) {
        DOWN();
        delay(6600);
        myservo1.write(r);
        myservo2.write(l);
        delay (100);
        UP();
        delay(6700);
        STOP();
       
        while (mn == 1) {
          x = analogRead(X);
          y = analogRead(Y);
          down_claw_date = digitalRead(down_claw);
          if (y <= 1023 && y > 650) {
            x_turn1();
          }
          if (y >= 0 && y < 400) {
            x_turn2();
          }
          if (y >= 400 && y < 650) {
            digitalWrite(sky_X_go, HIGH);
            digitalWrite(sky_X_back, HIGH);
          }
          if (x <= 1023 && x > 650) {
            y_turn1();
          }
          if (x >= 0 && x < 400) {
            y_turn2();
          }
          if (x >= 400 && x < 650) {
            digitalWrite(sky_Y_go, HIGH);
            digitalWrite(sky_Y_back, HIGH);
          }
          if (down_claw_date == 0   ) {
            delay(200);
            if (down_claw_date == 0   ) {

              myservo1.write(150);
              myservo2.write(30);
              mn = 0;
            }
          }
        }


        ll = 0;
        goto over;
      }

      Serial.println("x坐标");
      Serial.println(x);
      Serial.println("y坐标");
      Serial.println(y);

      //天桥运动
      if (y <= 1023 && y > 650) {
        x_turn1();
      }
      if (y >= 0 && y < 400) {
        x_turn2();
      }
      if (y >= 400 && y < 650) {
        digitalWrite(sky_X_go, HIGH);
        digitalWrite(sky_X_back, HIGH);
      }
      if (x <= 1023 && x > 650) {
        y_turn1();
      }
      if (x >= 0 && x < 400) {
        y_turn2();
      }
      if (x >= 400 && x < 650) {
        digitalWrite(sky_Y_go, HIGH);
        digitalWrite(sky_Y_back, HIGH);
      }

    }
    jk = jk + 1;
    down_claw_date = 0;
    if (jk == 100) {
      down_claw_date = 1;
      jk = 0;
    }
  }


  if (down_claw_date == 0 && choice == 35) {
    delay(200);
    if (down_claw_date == 0 && choice == 35) {

      while (1) {
        oled.clearDisplay();
        nand_u();
        fanhu_i();
        jianto_u();
        oled.display();
        delay(20);
        x = analogRead(X);
        y = analogRead(Y);
        if (x <= 1023 && x > 650) {
          int m = x;
          choice = choice + 25;
          if (choice > 40) {
            choice = choice - 25;
          }
        }
        if (x >= 0 && x < 400) {
          int n = x;
          choice = choice - 25;
          if (choice <= 0) {
            choice = choice + 25;
          }
        }
        down_claw_date = digitalRead(down_claw);
        //点击难度
        if (down_claw_date == 0 && choice == 10) {
          delay(200);
          if (down_claw_date == 0 && choice == 10) {
            while (1) {
              //oled显示部分
              oled.clearDisplay();
              jianda_n();
              kunna_n();
              jianto_u();
              oled.display();
              delay(20);
              x = analogRead(X);
              y = analogRead(Y);
              if (x <= 1023 && x > 650) {
                int m = x;
                choice = choice + 25;
                if (choice > 40) {
                  choice = choice - 25;
                }
              }
              if (x >= 0 && x < 400) {
                int n = x;
                choice = choice - 25;
                if (choice <= 0) {
                  choice = choice + 25;
                }
              }
              down_claw_date = digitalRead(down_claw);
              //难度选择/////////////////////////////
              if (down_claw_date == 0 && choice == 10) {
                delay(200);
                if (down_claw_date == 0 && choice == 10) {
                  l = 90;
                  r = 90;
                  goto beginning;
                }
              }
              if (down_claw_date == 0 && choice == 35) {
                delay(200);
                if (down_claw_date == 0 && choice == 35) {
                  l = 70;
                  r = 110;
                  goto beginning;
                }
              }

              /////////////////////////////
            }
          }
        }
        //返回
        if (down_claw_date == 0 && choice == 35) {
          delay(200);
          if (down_claw_date == 0 && choice == 35) {
            goto beginning;
          }
        }
      }
    }
  }


  Serial.println("x坐标");
  Serial.println(x);
  Serial.println("y坐标");
  Serial.println(y);
  Serial.println("下爪信号");
  Serial.println(down_claw_date);
  Serial.println("开始游戏信号");
  Serial.println(start_date);
  delay(50);

}
