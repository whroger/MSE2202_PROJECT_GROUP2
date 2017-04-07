//this is for the combined stuff


#include<Servo.h>
#include<ultrasonic.h>
#include<IRremote.h>
#include<Wire.h>

void function();

Servo servo_LMotor;
Servo servo_ShiftMotor;
Servo servo_SupportRod;
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_GripMotor;
Servo servo_GripArm;



//////////////////////////////////////////////////////////
Servo servo_LMotor2;
const int LMotor2=4;


unsigned int pytimer;
//////////////////////////////////////////////////////////


int testflag=1;
int stageflag=2;
int signalcount=0;


unsigned int chtimer;
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


const int LMotor=5;
const int ShiftMotor=7;
const int SupportRod=8;
const int GripArm=12;             ///
const int GripMotor=10;
const int LeftMotor=11;
const int RightMotor=9;          ////
//const int ultrasonic_Ping=3;
//const int ultrasonic_Data=4;
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
//  pinMode(ultrasonic_Ping,OUTPUT);
//  pinMode(ultrasonic_Data,INPUT);

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
  pinMode(ShiftMotor,OUTPUT);
  servo_ShiftMotor.attach(ShiftMotor);
  
  //set up IR & HE sensors
  pinMode(ir_sensor,INPUT);
  irrecv.enableIRIn();//Start the receiver
  pinMode(he_sensor,INPUT);

  pinMode(LMotor2,OUTPUT);
  servo_LMotor2.attach(LMotor2);

  //setup switch
  pinMode(A4,INPUT);

  //set up wire commucation
  Wire.begin(8);
  
}


void loop()
{
  function();
}



/**********************FUNCTION SPECIFICATION***********************/
void Moveforward()
{
  servo_RightMotor.writeMicroseconds(1800);
  servo_LeftMotor.writeMicroseconds(1800);
}

void Movebackward()
{
  servo_RightMotor.writeMicroseconds(1350);
  servo_LeftMotor.writeMicroseconds(1350);
}

void ClockwiseSpin()
{
  servo_RightMotor.writeMicroseconds(1300);
  servo_LeftMotor.writeMicroseconds(1800);
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
void function()
{
  if(stageflag==1)
{
  if(testflag==1)
  {
    if(chtimer==0)
      chtimer=millis();
    Moveforward();
    heVal=analogRead(he_sensor);
    Serial.println(heVal);
    if((heVal<480||heVal>600)||millis()-chtimer>7000)
    {
      testflag=2;
      hetimer=millis();
    }
    heVal=0;
  }
  else if(testflag==2)
  {
    servo_GripMotor.write(180);
    if(millis()-hetimer>1000)
      {
        
        testflag=3;
        hetimer=millis();
      }
}
  else if(testflag==3)
  {
      if(millis()-hetimer>2000)
      {
        stageflag=2;
        testflag=1;
        hetimer=millis();
      }
      else{
    servo_RightMotor.writeMicroseconds(1200);
    servo_LeftMotor.writeMicroseconds(1400);}
  }

}
else if(stageflag==2)
{
//  if(testflag==-2)
//  {
//    if(chtimer==0)
//      chtimer=millis();
//    Moveforward();
//    heVal=analogRead(he_sensor);
//    Serial.println(heVal);
//    if((heVal<480||heVal>600)||millis()-chtimer>7000)
//    {
//      testflag=-1;
//      hetimer=millis();
//    }
//    heVal=0;
//  }
//  else if(testflag==-1)
//  {
//    servo_GripMotor.write(180);
//    if(millis()-hetimer>1000)
//      {
//        
//        testflag=0;
//        hetimer=millis();
//      }
//}
//  else if(testflag==0)
//  {
//      if(millis()-hetimer>2000)
//      {
//        //stageflag=2;
//        testflag=1;
//        hetimer=millis();
//      }
//      else{
//    servo_RightMotor.writeMicroseconds(1200);
//    servo_LeftMotor.writeMicroseconds(1400);}
//  }
//
//}
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
    if(millis()-movetimer<1000){
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
      if(signalcount>70)
      
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
//    if(millis()-swtimer>800&&millis()-swtimer<2000)
//      {servo_RightMotor.writeMicroseconds(1800);
//      servo_LeftMotor.writeMicroseconds(1700);}
    else
      {
        stageflag=3;
        testflag=1;
      }
}

else if(stageflag==3)
{
  servo_LMotor.write(150);
  if(millis()-pytimer>800)
    servo_LMotor2.write(52);
  if(millis()-pytimer>1500&&millis()-pytimer<6000)
    servo_ShiftMotor.writeMicroseconds(1600);
  else if(millis()-pytimer>6000&&millis()-pytimer<6300)
    servo_ShiftMotor.writeMicroseconds(1400);
  else if(millis()-pytimer>6300&&millis()-pytimer<6600)
    servo_LMotor.write(125);
  else if(millis()-pytimer>6600&&millis()-pytimer<6900)
    servo_ShiftMotor.writeMicroseconds(1400);
  else if(millis()-pytimer>6900&&millis()-pytimer<7200)
    servo_LMotor.write(110);
  else if(millis()-pytimer>7200&&millis()-pytimer<7500)
  {
    servo_GripArm.write(1600);
  }
  else if(millis()-pytimer>7500&&millis()-pytimer<7800)
  {
    servo_GripMotor.write(0);
  }
  else if(millis()-pytimer>7800&&millis()-pytimer<8100)
  {
    servo_LMotor.write(150);
  }
  else
    Movebackward();
  
}}}


