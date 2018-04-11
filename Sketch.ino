#define CELL_1 A0
#define CELL_2 A1
#define CELL_3 A2
#define buzzer 8

float C1;
float C2;
float C3;

float cellLimit = 3.3;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadVoltages();
  
  printInfo();

  if (C1 < cellLimit || C2 < cellLimit || C3 < cellLimit)
  {
    count++;
    if (count >= 5)
      beep(true);
    else
      beep(false);
  }
  else
  {
    count = 0;
  }
  
  delay(500);
}

float ReadVoltageC1(float val)
{
  float res = analogRead(val);
  res = res * (5.0 / 1023.0);

  return (res);
}

float ReadVoltageC2(float val)
{
  float res = analogRead(val);
  res = (res + 0.10) * (5.0 / 1023.0);

  return (res);
}

void ReadVoltages()
{
  C1 = ReadVoltageC1(CELL_1);
  C2 = ReadVoltageC2(CELL_2);
  C3 = ReadVoltageC1(CELL_3);
}

void beep(float action)
{
  if (action)
  {
    tone(buzzer, 5000, 200);
    delay(300);

    ReadVoltages();

    printInfo();
    Serial.println("BEEPING");
    
    if (C1 < cellLimit || C2 < cellLimit || C3 < cellLimit)
      beep(true);
    else
    {
      if (count > 0)
      {
        count--;
        beep(true);
      }
    }
      
  }
}

void printInfo()
{
  Serial.println("Cell 1 : " + String(C1) + "V");
  Serial.println("Cell 2 : " + String(C2) + "V");
  Serial.println("Cell 3 : " + String(C3) + "V");
  Serial.println("Count beeper : " + String(count));
}
