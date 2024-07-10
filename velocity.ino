const int latchPin = 3;
const int clockPin = 4;
const int dataPin = 2;

byte progressBar[] = {0b00000000,0b00000001,0b00000011,0b00000111,0b00001111,
                   0b00011111,0b00111111, 0b01111111, 0b11111111};
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  if (Serial.available() > 0) {

     char vel = Serial.read();
      
     if (vel >= '0' && vel <= '8') {
      int index = vel - '0'; 
      Serial.print("Change velocity: ");
      Serial.println(index);

      velOutput(index);
    }

  }
}


void velOutput(int index) { 
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, progressBar[index]);
  digitalWrite(latchPin, HIGH);
}
