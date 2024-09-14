// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 4, en = 3, d4 = 2, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



#define ph_Pin A0
#define relayPin1 A1
#define relayPin2 A2
#define relayPin3 A3


float calibration = 21.34 + 5.20;  //change this value to calibrate
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;

float phValue;
int count = 0;


void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("PH Sensor");

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);

  for(int i = 0; i < 30; i++)
  {
     ph_Sensor();
     delay(1000);
  }

}


void loop() {
  count++;
  ph_Sensor();
  delay(1000);

  if(count > 30)
  {
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, LOW);
    digitalWrite(relayPin3, LOW);
    count = 31;
  }
  else if(count )

  if (phValue < 5.00) {
    digitalWrite(relayPin1, HIGH);
    digitalWrite(relayPin2, LOW);
    digitalWrite(relayPin3, LOW);
  } else if (phValue > 6.0 && phValue < 8.5) {
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, HIGH);
    digitalWrite(relayPin3, LOW);
  } else if (phValue > 8.50) {
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, LOW);
    digitalWrite(relayPin3, HIGH);
  }

}


void ph_Sensor() {
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(ph_Pin);
    delay(10);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
    avgValue = 0;
    for (int i = 2; i < 8; i++)
      avgValue += buf[i];
    float pHVol = (float)avgValue * 4.8 / 1023.0 / 6;
    phValue = -5.70 * pHVol + calibration;

   if(phValue < 6.5 )
   {
    phValue = phValue * 0.6;
   }
   else if(phValue > 6 && phValue < 7.8)
   {
    phValue = phValue * 1.03;
   }
   else if(phValue > 7.8)
   {
    phValue = phValue * 1.3;
   }


    Serial.print("phValue   : ");
    lcd.setCursor(0, 0);
    lcd.print("PH_Value: ");
    lcd.print(phValue);
    lcd.print("  ");
    Serial.println(phValue);
  }
}
