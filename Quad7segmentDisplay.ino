// @fileName Quad7segmentDisplay.ino
// @author Melih Altun @2023

int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int delayTime = 2;
int numDisp[] = {0,0,0,0};

unsigned long currentMillis, previousMillis = 0; // previous time in milliseconds
const long interval = 1000; // interval in milliseconds

int sinkPin0 = 3,sinkPin1 = 4,sinkPin2 = 5,sinkPin3 = 6;   // digital pins used as current sinks

// 7 segment digits in hex 0-15
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

// init pins
void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(sinkPin0,OUTPUT);
  pinMode(sinkPin1,OUTPUT);
  pinMode(sinkPin2,OUTPUT);
  pinMode(sinkPin3,OUTPUT);
}

// function to display numbers on 7 segment
void Display(unsigned char num)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
}


// main loop
void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) { // check if interval has elapsed
    previousMillis = currentMillis; 
    incrementNum();
  } 
  for (int j = 0; j<8; j++) {
    // cycle between four sink pins pulling down one at a time
    digitalWrite(sinkPin0, HIGH);
    digitalWrite(sinkPin1, HIGH);
    digitalWrite(sinkPin2, HIGH);
    digitalWrite(sinkPin3, HIGH);
    switch(j) {
      case 0:
        digitalWrite(sinkPin0, LOW);
        break;
      case 2:
        digitalWrite(sinkPin1, LOW);
        break;
      case 4:
        digitalWrite(sinkPin2, LOW);
        break;
      case 6:
        digitalWrite(sinkPin3, LOW);
        break;
    }
    // show one mathing digit on quad 7 segment display
    Display(numDisp[j/2]);
    delay(delayTime);
  }
}

// increment the number with the [mm:ss] clock format
void incrementNum() {
  numDisp[3]++;
  if (numDisp[3] > 9) {
    numDisp[3] = 0;
    numDisp[2]++;
    if (numDisp[2] > 5) {
      numDisp[2] = 0;
      numDisp[1]++;
      if (numDisp[1] > 9) {
        numDisp[1] = 0;
        numDisp[0]++;
        if (numDisp[0] > 5)
          numDisp[0] = 0;
      }
    }
  }
}
