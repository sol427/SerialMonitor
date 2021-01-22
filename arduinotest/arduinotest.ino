int i = 0;
char serialInput = 0;
int nbRecu = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.print("qwertyuiopasdfghjklzxcvbnm123456789");
//  Serial.print(i);/
  Serial.print("\n");
//  i++;/

  if(Serial.available() > 0) {
    serialInput = Serial.read();
//    nbRecu ++/
    
    Serial.print(serialInput);
  }

  delay(1000);

}
