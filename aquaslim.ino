int sensorPin = A0;    
int sensorValue = 0;  

int relayPin = 8;    

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > 500) {  // Ajustar o valor conforme o teste
    digitalWrite(relayPin, HIGH);  // Liga o LED (bomba)
  } else {
    digitalWrite(relayPin, LOW);   // Desliga o LED (bomba)
  }
  
  delay(1000);
}
