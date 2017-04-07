#include<Servo.h>
#include<ultrasonic.h>
#include<IRremote.h>
#include<Wire.h>

Servo servo_LMotor2;
Servo servo_LMotor;
Servo servo_ShiftMotor;
Servo servo_SupportRod;
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_GripMotor;
Servo servo_GripArm;

int testflag=1;
int stageflag=10;
int signalcount=0;

unsigned int swVal;
unsigned int switchcount;
unsigned int swtimer;
unsigned int hetimer;
unsigned int signaltimer;
unsigned int movetimer;
unsigned int griptimer;
unsigned int irVal;
unsigned int heVal;
unsigned int usVal;


const int LMotor=6;
const int ShiftMotor=7;
const int SupportRod=8;
const int GripArm=9;
const int GripMotor=10;
const int LeftMotor=11;
const int RightMotor=12;
//const int ultrasonic_Ping=3;
//const int ultrasonic_Data=4;
const int LMotor2=7;
const int ir_sensor=2;
const int he_sensor=A5;

//set up for communication
const int wirecPort=A7;
unsigned int wireVal;

//ir sensor set
IRrecv irrecv(ir_sensor);
decode_results irresults;

//function definitions
void Moveforward();
void ClockwiseSpin();
void CounterClockwiseSpin();
void getirVal();

void setup() {
  Serial.begin(9600);
  //set up ultrasonic sensors
  //pinMode(ultrasonic_Ping,OUTPUT);
  //pinMode(ultrasonic_Data,INPUT);

  //set up drive motors
  pinMode(RightMotor,OUTPUT);
  servo_RightMotor.attach(RightMotor);
  pinMode(LeftMotor,OUTPUT);
  servo_LeftMotor.attach(LeftMotor);

  //set up grip motor
  pinMode(GripMotor,OUTPUT);
  servo_GripMotor.attach(GripMotor);
  pinMode(GripArm,OUTPUT);
  servo_GripArm.attach(GripArm);

  //set up support rod motor
  pinMode(SupportRod,OUTPUT);
  servo_SupportRod.attach(SupportRod);

  //set up L motors
  pinMode(LMotor,OUTPUT);
  servo_LMotor.attach(LMotor);
  pinMode(LMotor2,OUTPUT);
  servo_LMotor2.attach(LMotor2);
  pinMode(ShiftMotor,OUTPUT);
  servo_ShiftMotor.attach(ShiftMotor);
  
  //set up IR & HE sensors
  pinMode(ir_sensor,INPUT);
  irrecv.enableIRIn();//Start the receiver
  pinMode(he_sensor,INPUT);

  //setup switch
  pinMode(A4,INPUT);

  //set up wire commucation
  Wire.begin(8);
  
}
/*
void loop(){
  if(stageflag==1)
  {
    usVal=Ping(ultrasonic_Ping,ultrasonic_Data);
    //for the cube
    heVal=analogRead(he_sensor);
    if(heVal>600)
      {
        griptimer=millis();
        stageflag++;
      }
    //for dring straightly
    if(0){
      servo_RightMotor.writeMicroseconds(1680);
      servo_LeftMotor.writeMicroseconds(1680);
    }
    else if(0){
      servo_RightMotor.writeMicroseconds(1680);
      servo_LeftMotor.writeMicroseconds(1680);
    }
    else if(1){
      servo_RightMotor.writeMicroseconds(1680);
      servo_LeftMotor.writeMicroseconds(1680);
    }
  }
  else if(stageflag==2)
  {
    //to be filled
    servo_GripMotor.write(0);
    if(millis()-griptimer>0)
    {
      griptimer=millis();
      stageflag++; 
    }
  }
  else if(stageflag==3)
  {
    //to be filled
    servo_GripArm.write(0);
    if(millis()-griptimer>0)
    {
      griptimer=millis();
      stageflag++; 
    }
  }
  else if(stageflag==4)
  {
    if(irrecv.decode(&irresults))
    {
      irVal=(irresults.value,DEC);
      irrecv.resume();
    }
    if(irVal!=0)
      stageflag++;
    ClockwiseSpin();
  }
  else if(stageflag==5)
  {
    Moveforward();  
    //if() stage++;     3 wires detect at the same moment
    //else if()  stage=++;       ir senses and some wires detects
    //else if()  stage++;    if and ultrasonic stuff combined 
    //set a timer, after 3 secs, if no signal is detected, stageflag--
  }
  else if(stageflag==6)
  {
    //  
  }
  
}*/

//function test
void loop() {
    //move function test 
    if(stageflag==1)
    {
      //servo_LMotor.write(150);
      Moveforward();
      Serial.println("functioning");
    }
    //infrared sensor test
    else if(stageflag==2)
    {
      if(irrecv.decode(&irresults))
      {
        //irVal=(irresults.value,DEC);
        irVal=irresults.value;
        irrecv.resume();
      }
      Serial.println(irVal);
      delay(200);
      irVal=0;
    }
    //hall effect sensor test
    else if(stageflag==3)
    {
      heVal=analogRead(he_sensor);
      Serial.println(heVal);
      delay(200);
    }
    //ultrasonic test
    else if(stageflag==4)
    {
      //usVal=Ping(ultrasonic_Ping,ultrasonic_Data);
      Serial.println(usVal);
    }
    //wire function test
    else if(stageflag==5)
    {
      wireVal=Wire.read();  
    }  
    //cube capture test
    else if(stageflag==6)
    {
      servo_GripMotor.write(94);
      servo_RightMotor.writeMicroseconds(1900); 
    }
    //support rod test
    else if(stageflag==7)
    {
      servo_SupportRod.writeMicroseconds(2000);
    }
    //Lplate angle test
    else if(stageflag==8)
    {
      servo_LMotor.write(180);
    }
    //front shift system test
    else if(stageflag==9)
    {
      servo_ShiftMotor.writeMicroseconds(1900);
    }
    
    //function insertion test
    else if(stageflag==10)
    {
      function5();
    }
    
}

/**********************FUNCTION SPECIFICATION***********************/
void Moveforward()
{
  servo_RightMotor.writeMicroseconds(1800);
  servo_LeftMotor.writeMicroseconds(1800);
}

void ClockwiseSpin()
{
  servo_RightMotor.writeMicroseconds(1630);
  servo_LeftMotor.writeMicroseconds(1350);
}

void CounterClockwiseSpin()
{
  servo_RightMotor.writeMicroseconds(1350);
  servo_LeftMotor.writeMicroseconds(0);
}

void Stop()
{
  servo_RightMotor.writeMicroseconds(0);
  servo_LeftMotor.writeMicroseconds(0);
}
void getirVal()
{
  if(irrecv.decode(&irresults))
  {
    //irVal=(irresults.value,DEC);
    irVal=irresults.value;
    irrecv.resume();
  }
}
/**********************FUNCTION SPECIFICATION***********************/






void function1()  //Move forward and search the cube
{
  Moveforward();
  heVal=analogRead(he_sensor);
  if(heVal>60)
    stageflag++;
}

void function2()
{
  //stage2 to grab the cube
  servo_GripMotor.write(0);
}

void function3()//spin to find the direction of the pyramid
{
  //consider to add another flag to control the spin direction
  ClockwiseSpin();
  irVal=(irresults.value,DEC);
  irrecv.resume();
  if(irVal==1||irVal==2)
    {
      irVal=0;
      stageflag++;
    }
}

void function4() //approach the pyramid while searching
{
  Moveforward();
  irVal=(irresults.value,DEC);
  irrecv.resume();
  irVal--;
  wireVal=Wire.read();
  if((irVal<-1)||(irVal>1&&irVal<3))
  {
    stageflag--;
  }
  else if(wireVal==1)
  {
    stageflag++;
  }
}
//Pyramid retrieve test.
void function5()
{
  //Serial.println(testflag);
  //capture the pyramid
  if(testflag==1){
    irVal=0;
    ClockwiseSpin();
    getirVal();
    //Serial.println(irVal);
    if(irVal!=0){
      testflag=2; 
      movetimer=millis();
      signalcount=0;
    }
    irVal=0;
  }
  else if(testflag==2){
    if(millis()-movetimer<1000){        //1000
      irVal=0;
      getirVal();
      if(irVal!=0){
        signalcount++;
        Serial.print("count is ");
        Serial.println(signalcount);
      }
      irVal=0;
      Stop();
    }
    else{
      if(signalcount>70)      //70
      
      {
        testflag=3;
        movetimer=millis();
      }
      else
        testflag=1;
    }
  }
  else if(testflag==3)
  {
    //if(millis()-movetimer>100)
    if(1)
    {
      testflag=4;
      movetimer=millis();
    }
    else
      ClockwiseSpin();
  }
  else if(testflag==4)
  {
    if(millis()-movetimer>1500)
    {
     testflag=1;
    }
    else
      Moveforward();
    //if(analogRead(A4)==1023)
    swVal=analogRead(A4);
    if(swVal>1015)
    {
      testflag=5;
      swtimer=millis();
    }
    swVal=0;
  }
//  else if(testflag==5)
//  {
//    if(millis()-switchtimer<500)
//    {
//      
//      if(analogRead(A4)==1023)
//        switchcount++;
//    }
//    else
//    {
//      if(0)
//        testflag=6;
//      else
//        testflag=1;
//    }
//    Moveforward();
//  }
  else if(testflag==5)
  {
    if(millis()-swtimer<800)
      Moveforward();
    //swVal=analogRead(A4);
    //to be filled.
    //Serial.println(swVal);
    if(millis()-swtimer>800&&millis()-swtimer<2000)
      {servo_RightMotor.writeMicroseconds(1800);
      servo_LeftMotor.writeMicroseconds(1700);}
    else
      Stop();
  }
}


//ifrared signal gathering
void function6()
{
  if(testflag==1)
  {
    signalcount=0;
    signaltimer=millis();
    testflag++;
    Serial.println(1);
  }
  else if(testflag==2)
  {
    if(millis()-signaltimer<1000)
    {
      if(irrecv.decode(&irresults))
      {
        //irVal=(irresults.value,DEC);
        irVal=irresults.value;
        irrecv.resume();
      }
      if(irVal!=0)
      {
        signalcount++;
        Serial.print("count is ");
        Serial.println(signalcount);
      }
      irVal=0;
    }
    else
    {
      if(signalcount>=10)
        testflag=3;
      else
        testflag=1;
    }
  }
  else if(testflag=3)
    Serial.println(3);
}

void function7()
{
  Stop();
}

void function8()
{
  if(testflag==1)
  {
    Moveforward();
    heVal=analogRead(he_sensor);
    Serial.println(heVal);
    if(heVal<450||heVal>600)
    {
      testflag=2;
      hetimer=millis();
    }
    heVal=0;
  }
  else if(testflag==2)
  {
    servo_GripMotor.write(180);
    if(millis-hetimer>1000)
      testflag=3;
  }
  else
    Stop();
}

void function9()
{
  //heVal=analogRead(he_sensor);
  getirVal();
  Serial.println(irVal);
  delay(200);
}




