#include "IRremote.h"
//Sherriff, K., 2012. IR Remote Library.

//IR Reciever
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

//motor pins
int motorOne = 5;
int motorOneForward = 6;
int motorOneBackward = 7;

int motorTwo = 10;
int motorTwoForward = 8;
int motorTwoBackward = 9;

//button variables
int button = 2;
int buttonState = 0;

//area integers
int xAxis;
int yAxis;
double Axis;
double Axis2;

//time variables
float startTime = 0;
float endTime = 0;
float Time = 0;

//One Move Distance
int oneMove = 500;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv' (brainy-bits, 2015)
decode_results results;      // create instance of 'decode_results' (brainy-bits, 2015)

void setup() {
//pin setup
pinMode(2, INPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);

Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  
if (irrecv.decode(&results)) // have we received an IR signal? (brainy-bits, 2015)

  {
    translateIR(); //calls function (brainy-bits, 2015)
    irrecv.resume(); // receive the next value (brainy-bits, 2015)
  }  

}

void motorForward(int i)
{
 digitalWrite(6, HIGH);
 digitalWrite(7,LOW);
 analogWrite(5, 200);
 digitalWrite(8, HIGH);
 digitalWrite(9,LOW);
 analogWrite(10, 200);
 //above, sets both left and right motors to rotate foward at a speed of 200.
 delay(i);//sets the delay to i.

 digitalWrite(6,LOW);
 digitalWrite(7, LOW);
 analogWrite(5, 0);
 digitalWrite(8,LOW);
 digitalWrite(9,LOW);
 analogWrite(10, 0);
 //above, sets both left and right motors to stop rotating and reduces speed to 0.
}

void motorLeft(int i)
{
  digitalWrite(8, HIGH);
  digitalWrite(9,LOW);
  analogWrite(10, 200);
  //above, sets the right motor only to move forward at a speed of 200.
  delay(i); //delays the method by a set integer to enable a 90 degree turn.
  
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  analogWrite(10, 0);
  //above, sets the right motor back to 0 speed.
}

void motorRight(int i)
{
  digitalWrite(6, HIGH);
  digitalWrite(7,LOW);
  analogWrite(5, 200);
  //above, sets the left motor only to move forward at a speed of 200.
  delay(i); //delays the method by a set integer to enable a 90 degree turn.
  
  digitalWrite(6,LOW);
  digitalWrite(7, LOW);
  analogWrite(5, 0);
  //above, sets the left motor back to 0 speed.
}

void motorReverse(int i)//method created called motorReverse
{ 
 digitalWrite(6, LOW);
 digitalWrite(7,HIGH);
 analogWrite(5, 200);
 digitalWrite(8, LOW);
 digitalWrite(9,HIGH);
 analogWrite(10, 200);
 //above, sets both the right and left motors to rotate backwards at a speed of 200.
 delay(i);
 
 digitalWrite(6,LOW);
 digitalWrite(7, LOW);
 analogWrite(5, 0);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 analogWrite(10, 0);
 //above, sets both left and right motors to stop rotating and reduces speed to 0.
}


void area() //creates a method called area
{
  Serial.println(yAxis);
  for (yAxis; yAxis > 0; yAxis--) {
    motorForward(oneMove);
    delay(10);
    }
    //A for loop that will make the detector move forward until the variable yAxis becomes 0.
    
    motorRight(800);
    //calls the motorRight method.
  Serial.println(yAxis);
    
    
  while(Axis>0){ //creates a while loop that continues while the Axis variable is greater than 0.
    
    for (xAxis; xAxis > 0; xAxis--) {
    motorForward(oneMove);
    delay(10);
    }
    //A for loop that will make the detector move forward until the variable xAxis becomes 0.

    motorRight(800); //calls  the motorRight method.
    Axis = Axis - 1; //sets the Axis variable to Axis -1
    motorForward(oneMove); //calls the motorForward method.
    motorRight(800); //calls the motorRight method.
    xAxis = Axis; //sets the xAxis variable to equal the Axis variable.

    for (xAxis; xAxis > 0; xAxis--) {
    motorForward(oneMove);
    delay(10);
    }
    //A for loop that will make the detector move forward until the variable xAxis becomes 0.

    motorLeft(700); //calls the motorLeft method.
    Axis = Axis - 1; //sets the Axis variable to Axis -1
    motorForward(oneMove); //calls the motorForward method.
    motorLeft(700); //calls the motorLeft method.
    xAxis = Axis; //sets the xAxis variable to equal Axis
    
  }  
}

void Auto(){
//method called auto is created
  while(buttonState == LOW) {
   startTime = millis();
   motorForward(oneMove);
   Serial.println(digitalRead(2));
   buttonState = digitalRead(2);
   } //this while loop intiates the time to begin counting, while the button has not been pressed

  endTime = millis(); //sets endTime to equal the final time in Millis
  Serial.println(endTime);
  Time = endTime - startTime; //sets Time to equal endTime take startTime
  yAxis = Time / 350; //sets yAxis to equal Time divided by 350
  Axis = yAxis; //sets Axis to equal yAxis
  startTime = 0; //resets startTime
  endTime = 0; //resets endTime

    motorReverse(oneMove/4); //calls the motorReverse function with a reduced int
    motorRight(800); //calles the motorRight function
    buttonState = digitalRead(2);

  while (buttonState == LOW) {
    startTime = millis();
    motorForward(oneMove);
    Serial.println(digitalRead(2));
    buttonState = digitalRead(2);
    } //intiates the time while loop again

  endTime = millis();
  Serial.println(endTime);
  Time = endTime - startTime;
  xAxis = Time  / 350;
  Axis2 = xAxis;
 
    motorReverse(oneMove/4);
    motorRight(800);
    buttonState = digitalRead(2);
  //does the same as the last run through but sets the xAxis to the new value
    
  while(Axis>0){
//A while loop that carries the detector through previously used code so that it can calculate an area on its own. 
    motorForward(oneMove);
    motorRight(800);
    
  for (xAxis; xAxis > 0; xAxis--) {
    motorForward(oneMove);
    delay(10);
    } //A for loop that allows the detector to move forward aslong as xAxis is greater than 0

    motorLeft(700);
    Axis = Axis - 1; //removes one from the Axis variable
    motorForward(oneMove);
    motorLeft(700);
    xAxis = Axis2; //sets xAxis to equal Axis2

  for (xAxis; xAxis > 0; xAxis--) {
    motorForward(oneMove);
    delay(10);
    } //A for loop that allows the detector to move forward aslong as xAxis is greater than 0

    motorRight(800);
    Axis = Axis -1;
    motorForward(oneMove);
    motorRight(800);
    xAxis = Axis2;

   for (xAxis; xAxis > 0; xAxis--) {
    motorForward(oneMove);
    delay(10);
    } //A for loop that allows the detector to move forward aslong as xAxis is greater than 0

    xAxis = Axis2;
    
  }

    motorRight(800); //This is extra code that helps the detector cover area that hasnt been covered when on a larger scale. Here to...
    motorRight(800);
  for (yAxis; yAxis > 0; yAxis--) {
    motorForward(oneMove);
    delay(10);
    }
    
    motorLeft(700);
    
  for (yAxis; yAxis > 0; yAxis--) {
    motorForward(oneMove);
    delay(10);
    }  //here
}


void translateIR() // takes action based on IR code received. All the case ID's and surrounding code in translateIR is from brainy-bits (brainy-bits, 2015), but has been changed to include code linking to movement

// describing Remote IR codes 

{

  switch(results.value)

  {
  //the code below are related to the messages sent by the IR Remote as seen below they have been edited to either call a method or to set variables. 
  //Some have not changed as they are not in use.
  case 0xFF629D: motorForward(oneMove); break;
  case 0xFF22DD: motorLeft(600);    break;
  case 0xFF02FD: Serial.println(" -OK-");    break;
  case 0xFFC23D: motorRight(700);   break;
  case 0xFFA857: motorReverse(oneMove); break;
  case 0xFF6897: Serial.println(" 0");    break;
  case 0xFF9867: area();    break;
  case 0xFFB04F: Auto();    break;
  case 0xFF30CF: yAxis = 1; xAxis = 1; Axis = 1;  break;
  case 0xFF18E7: yAxis = 2; xAxis = 2; Axis = 2;    break;
  case 0xFF7A85: yAxis = 3; xAxis = 3; Axis = 3;    break;
  case 0xFF10EF: yAxis = 4; xAxis = 4; Axis = 4;    break;
  case 0xFF38C7: yAxis = 5; xAxis = 5; Axis = 5;    break;
  case 0xFF5AA5: yAxis = 6; xAxis = 6; Axis = 6;    break;
  case 0xFF42BD: yAxis = 7; xAxis = 7; Axis = 7;    break;
  case 0xFF4AB5: yAxis = 8; xAxis = 8; Axis = 8;    break;
  case 0xFF52AD: yAxis = 9; xAxis = 9; Axis = 9;    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  
  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} 

/*
Brainy-bits, 2015. Using an IR Remote and sensor with an Arduino [online]. Available from: https://www.brainy-bits.com/ir-remote-arduino/ [Accessed 9th March 2020].

Sherriff, K., 2012. Infrared remote library for Arduino: send and receive infrared signals with multiple protocols [online]. Available from: https://github.com/z3t0/Arduino-IRremote [Accessed 9th March 2020].
*/
