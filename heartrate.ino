#define LED_1 5
#define LED_2 6
#define LED_3 7

int dataNumber = 0;
const byte numChars = 32;
char receivedChars[numChars]; //stores received data
boolean heartData = false; //whether or not new data was received

void setup(){
  
  Serial.begin(9600);
  pinMode(LED_1, INPUT);
  pinMode(LED_2, INPUT);
  pinMode(LED_3, INPUT);
  
}

void loop(){
  received_heart();

  if (heartData){ //process new data
    dataNumber = atoi(receivedChars); //char conversion to int
    Serial.print("Received number (serial 1): ");
    Serial.println(dataNumber);
    turnOnLED(dataNumber);

    heartData = false;
  }
}

void received_heart(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && heartData == false){
    rc = Serial.read();

    if (rc != endMarker){ 
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars){
        ndx = numChars - 1;
      }
    }
    else{
      receivedChars[ndx] = '\0'; //terminate after each message
      ndx = 0;
      heartData = true; // set newData flag when EndMarket is received
    }
  }
}

void turnOnLED(int LEDNum){
  switch(LEDNum){
    case 1:
      set_pins(LED_1, LED_2);
      break;
    case 2:
      set_pins(LED_2, LED_1);
      break;
    case 3:
      set_pins(LED_2, LED_3);
      break;
    case 4:
       set_pins(LED_3, LED_2);
      break;
    case 5:
      set_pins(LED_1, LED_3);
      break;
    case 6:
      set_pins(LED_3, LED_1);
      break;
    default:
      reset_pins();
  }
}
  
void set_pins(int high_pin, int low_pin)
{
  reset_pins();
  pinMode(high_pin, OUTPUT);
    pinMode(low_pin, OUTPUT);
    digitalWrite(high_pin, HIGH);
    digitalWrite(low_pin, LOW);
 }

void reset_pins()
{
  pinMode(LED_1, INPUT);
  pinMode(LED_2, INPUT);
  pinMode(LED_3, INPUT);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
}
