#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


const int TRIG_PIN = 2;
const int ECHO_PIN = 3;


const int GREEN_PIN  = 4;  
const int BLUE_PIN   = 5;   
const int YELLOW_PIN = 6;   
const int ORANGE_PIN = 7;   
const int RED_PIN    = 8;   

const int BUZZER_PIN = 9;   

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_PIN,  OUTPUT);
  pinMode(BLUE_PIN,   OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(ORANGE_PIN, OUTPUT);
  pinMode(RED_PIN,    OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Distance Meter");
  delay(1500);
  lcd.clear();
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1; 
  return duration * 0.034 / 2;  
}

void allLedsOff() {
  digitalWrite(GREEN_PIN,  LOW);
  digitalWrite(BLUE_PIN,   LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(ORANGE_PIN, LOW);
  digitalWrite(RED_PIN,    LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  long distance = measureDistance();

 
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  if (distance < 0) {
    lcd.print("Out of range");
    lcd.setCursor(0, 1);
    lcd.print("                "); 
  } else {
    lcd.print(distance);
    lcd.print(" cm   ");          

    lcd.setCursor(0, 1);
    if      (distance > 100) lcd.print("Status: GREEN   ");
    else if (distance > 80)  lcd.print("Status: BLUE    ");
    else if (distance > 70)  lcd.print("Status: YELLOW  ");
    else if (distance > 60)  lcd.print("Status: ORANGE  ");
    else if (distance > 50)  lcd.print("Status: RED+BUZ ");
    else                     lcd.print("Status: RED+BUZ ");
  }

  allLedsOff();

  if (distance > 0) {
    if      (distance > 100) digitalWrite(GREEN_PIN,  HIGH);
    else if (distance > 80)  digitalWrite(BLUE_PIN,   HIGH);
    else if (distance > 70)  digitalWrite(YELLOW_PIN, HIGH);
    else if (distance > 60)  digitalWrite(ORANGE_PIN, HIGH);
    else {                  
      digitalWrite(RED_PIN,    HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }

  delay(200); 
}