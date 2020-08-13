#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

SoftwareSerial toESP(2, 3); //Rx, Tx
Servo myservo; // membuat objek servo di library Servo.h
int pos = 0; // geser servopada posisi 0 derajat
LiquidCrystal_I2C lcd(0x27,20,4);
#define trigPin 6
#define echoPin 5
#define trigPin2 11
#define echoPin2 10
int penuh;

void setup() {
  myservo.attach(9); //definisikan pin yang digunakan untuk mengontrol motor servo adalah pin 9

    lcd.begin();                      // initialize the lcd 
    lcd.backlight();
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println("Ultra 1");
  Serial.print(distance);
  Serial.println(" cm");

  //ultra 2
  long duration2, distance2;
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  Serial.println("Ultra 2");
  Serial.print(distance2);
  Serial.println(" cm");
  delay(500);
  if (distance2<=6){
    lcd.setCursor(0,0);
    lcd.print("Tempat Sampah                  ");
    lcd.setCursor(0,1);
    lcd.print("Penuh                   ");
    myservo.write(80);
    Serial.println("Tempat Sampah Penuh");
    penuh = 1;
    toESP.println(penuh);
  }else if (distance2>=7 ){
    Serial.println("Tempat Sampah Tidak Penuh");
        if (distance<=6){
        myservo.write(0); // mengatur posisi servo berdasarkan nilai dari for loop
        lcd.setCursor(0,0);
    //    lcd.print(distance);
        lcd.print("Tempat Sampah                                    ");
        lcd.setCursor(0,1);
        lcd.print("Terbuka                  ");
        delay(1000);
    //  Serial.print(distance);
    //  Serial.println(" cm");
        Serial.println("Tempat Sampah Terbuka");
        delay(1000);       
   }
   if (distance>=7){
     myservo.write(80); // mengatur posisi servo berdasarkan nilai dari for loop          
    lcd.setCursor(0,0);
//    lcd.print(distance);
    lcd.print("Tempat Sampah                                     ");
    lcd.setCursor(0,1);
    lcd.print("Tertutup");
    delay(1000);
//  Serial.print(distance);
//  Serial.println(" cm");
    Serial.println("Tempat Sampah Tertutup");
    delay(1000);
    }
    
    }
  
}
