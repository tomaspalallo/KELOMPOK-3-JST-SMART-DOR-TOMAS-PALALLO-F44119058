#include <LiquidCrystal.h>
#include <Servo.h>
#define sensorLightPin    A2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo window;

int servo = 9;
int tsensor = A0;
int pump = 7; 
int buzzer = 8; 
int led = 6;
int reset = 10;
int ldr = A1;
int c = 0;
int state = 0;
int gas_pin= A2;
float gas_data= A2;
 
void setup() 
{
  //pinMode(13,OUTPUT);
  window.attach(servo);
  pinMode(ldr, INPUT);
  pinMode(tsensor, INPUT);
  pinMode(pump,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(reset,INPUT);
  window.write(0);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Fire & Smoke");
  lcd.setCursor(2,1);
  lcd.print("Alarm System");
  delay(1000);
  lcd.clear();
  
}

void loop()
{
  
  if(gas_data<100){
  gas_data=analogRead(gas_pin);
  window.write(0);
  digitalWrite(buzzer,LOW);
  digitalWrite(led,LOW);
  lcd.setCursor(0, 0);
  lcd.print("Smoke Detector");
  lcd.setCursor(0,1);
  	lcd.print("Gas : ");
  	lcd.setCursor(6, 1);
  	lcd.print(gas_data);  
  }
  
  
  if(gas_data>200){
    gas_data=analogRead(gas_pin);
    window.write(180);
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
    lcd.setCursor(2,0);
    lcd.print("Smoke Detector");
    lcd.setCursor(0,1);
    lcd.print("   DANGER!!!!");
    delay(500);
    lcd.clear();
  }
  
  float voltage = analogRead(tsensor) * 5; //sensor temp
  voltage /= 1024.0;
  float temp = (voltage - 0.5) * 100;
  Serial.println(temp);
  
  int light = analogRead(ldr);  //sensor cahaya
  Serial.println(light);
  if (light > 900 && temp > 100 && c == 0)
  {
    window.write(180); //memutar servo ke 180 derajat
    digitalWrite(pump,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);     
    lcd.setCursor(0,0);
    lcd.print("Fire! Fire! Fire!");
    lcd.setCursor(0,1);
    lcd.print("Call : 113    ");
    delay(1000);
    lcd.clear();
   
  }
  
  delay(200);
  
  
  state = digitalRead(reset);
  if  (state == 1)
  {
    //digitalWrite(13,HIGH);
    window.write(0); //memutar kembali servo ke 0 derajat
    digitalWrite(pump,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(led,LOW);
    lcd.clear();
    c = 1;
    delay(1000);
    c=0;
  }
  delay(200); 
}      