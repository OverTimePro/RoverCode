#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
Servo ESCL;
Servo ESCR;
const int lightPin = A0;
const int recieverPin1 = 4;
const int recieverPin2 = 5;
const int trigPinF = 22;
const int echoPinF = 23;
const int trigPinL = 24;
const int echoPinL = 25;
const int trigPinR = 26;
const int echoPinR = 27;
const int trigPinFR = 28;
const int echoPinFR = 29;
const int trigPinFL = 30;
const int echoPinFL= 31;
const int trigPinB = 32;
const int echoPinB= 33;
//LF = left forwards and RF = right forwards

RF24 radio(7, 8);
const byte address[6] = "00001";

long duration;
int distance ;

int pwm_1;
int pwm_2;


void setup() {
  // setting up forward ultra-sonic sensor
  //ultra-sound sensor pins
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinFL, OUTPUT);
  pinMode(echoPinFL, INPUT);
  pinMode(trigPinFR, OUTPUT);
  pinMode(echoPinFR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(recieverPin1, INPUT);
  pinMode(recieverPin2, INPUT);
  //attaches esc to pin 
  ESCL.attach(2,1000,2000);
  ESCR.attach(3,1000,2000);
  Serial.begin(9600);
}

void loop()
{
  //pwm_1 = PulseIn(recieverPin1, HIGH);
  //pwm_2 = PulseIn(recieverPin2, HIGH);
  //if(pwm_1 == 0 && pwm_2 == 0){
  distance = CheckDistance(trigPinF, echoPinF)
  Serial.println(distance);
  ESCL.write(255
  )
    
    
    if(CheckDistance(trigPinF, echoPinF)> 0.4) && CheckDistance(trigPinFL, echoPinFL)> 0.2 && CheckDistance(trigPinFR, echoPinFR)> 0.2)
    {
      ESCL.write(255);
      ESCR.write(255);
    }
    else{
      ESCR.write(127);
      ESCL.write(127);
    }
    
    else if(CheckDistance(trigPinL, echoPinL)> 0.4 && CheckDistance(trigPinFL, , echoPinFL)> 0.2){
        //spin left
        ESCL.write(0);
        ESCR.write(255);
    }
    else if(CheckDistance(trigPinR, echoPinR)> 0.4 && CheckDistance(trigPinFR, echoPinFR)> 0.2){
      //spin right
      ESCR.write(0);
      ESCL.write(255);
    }
    else if(CheckDistance(trigPinB, echoPinB)> 0.3){
      ESCR.write(0);
      ESCL.write(0);
    }
    else{
      ESCR.write(127);
      ESCL.write(127);
    }
  //}
  //else{
    //take reciever stuff
  //}*/
}

int CheckDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
}

static bool radiosetup(const int ce_pin, const int csn_pin)
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

static bool data_package (char data_package[24])
{
  radio.write(&data_package, sizeof(data_package));
}

/*bool CheckLight(){
  if(analogueRead(lightPin) > 300){
    return true;
  }
  return false;
}*/
