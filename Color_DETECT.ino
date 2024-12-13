#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define s0 2       
#define s1 3  
#define s2 4
#define s3 5
#define out 10

LiquidCrystal_I2C lcd(0x27,16,2);
int Red = 0, Blue = 0, Green = 0;
int cm = 0, distance = 0;
int buzzer = 7;

const int trigPin = 12; 
const int echoPin = 13;  

void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.setCursor(2,0); 
  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop()
{
  lcd.setCursor(2,0);
  distance = getDistance();
  if (distance>=5){
    Serial.println("Far");
    lcd.print("Distance: Far");
    digitalWrite(buzzer, LOW);
  }
  else {
    lcd.print("Distance: Close");
    Serial.println("Close");
    digitalWrite(buzzer, LOW);
    digitalWrite(buzzer, HIGH);
  }
  lcd.setCursor(2,1);
  GetColors();
  if (Green >= 50 && Red < 20 && Blue < 20){
    lcd.print("Color: White");
    Serial.println("Green");
    lcd.clear();
  }
  else if (Red <= 15 && Green <= 15 && Blue <= 15) {
    lcd.print("Color: Unknown");
    Serial.println("Unknown");
    lcd.clear();
  }
  else if (Red < Blue && Red <= Green && Red < 23){
    lcd.print("Color: Red");
    Serial.println("Red");
  }
  else if (Blue < Green && Blue < Red && Blue < 20){
    lcd.print("Color: Blue");
    Serial.println("Blue");
  }
  else if (Green < Red && Green - Blue <= 8){
    lcd.print("Color: Green");
    Serial.println("White");
  }
  else {
    lcd.print("Color: Unknown");
    Serial.println("Unknown");
  }
  delay(2000);
  lcd.clear();
}

void GetColors()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);
  digitalWrite(s3, HIGH);
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);
  digitalWrite(s2, HIGH);
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);
}

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  cm = pulseIn(echoPin, HIGH) * 0.034 / 2;
  return cm;
}
