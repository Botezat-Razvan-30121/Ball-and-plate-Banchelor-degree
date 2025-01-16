#include <Servo.h> 
#include <stdint.h>

#include "TouchScreen.h"
#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 350);
double Xmin=57;
  double Xmax=963;
  double Ymax=930;
  double Ymin=60;
 
  double Xmm=171.5;
  double Ymm=130;
  double Xconversion=Xmm/(Xmax-Xmin);
  double Yconversion=Ymm/(Ymax-Ymin);
  double Errorx, Errory,Setpointy, Setpointx;

 Servo Servo1; 
 Servo Servo2;
 // Declare the Servo pin 
int servoPin1 = 3; 
int servoPin2=2;

 float e[20];
  float c[20];
  float e1[20];
  float c1[20];

  int squareCoords[][2] = {
  {350,350}, // Punctul 1
  {350, 760}, // Punctul 2
  {760, 760}, // Punctul 3
  {760, 350}, // Punctul 4
  };
  double t = 0.0; // Parametrul de interpolare între puncte
int currentPointIndex = 0; // Indexul punctului curent
int nextPointIndex = 1; // Indexul punctului următor
 
 
void setup() {
  Serial.begin(115200);
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2);
  Serial.begin(115200);
  for(int i=0;i<20;i++){
    e[i]=0;
    c[i]=0;
  }
  for(int i=0;i<20;i++){
    e1[i]=0;
    c1[i]=0;
  }
  
}

void loop() {
  
  
  TSPoint p = ts.getPoint();
  if (p.z > ts.pressureThreshhold){

  //  Setpointx = squareCoords[currentPointIndex][0] * (1 - t) + squareCoords[nextPointIndex][0] * t;
  // Setpointy = squareCoords[currentPointIndex][1] * (1 - t) + squareCoords[nextPointIndex][1] * t;
  //t += 0.014; // Ajustează această valoare pentru a controla viteza de deplasare între puncte
  //if (t >= 1.0) {
 //  t = 0.0; // Resetează parametrul de interpolare
  // currentPointIndex = nextPointIndex;
  // nextPointIndex = (nextPointIndex + 1) % (sizeof(squareCoords) / sizeof(squareCoords[0])); // Treci la următorul punct, ciclic
   //             }
Setpointx=500;
Setpointy=500;




    e[2]=e[1];
    e[1]=e[0];
    e[0]=Setpointy-p.y;
    c[2]=c[1];
     c[1]=c[0];

     e1[2]=e1[1];
    e1[1]=e1[0];
    e1[0]=Setpointx-p.x;
    c1[2]=c1[1];
     c1[1]=c1[0];

      Errorx=e1[0];
      Errory=e[0];
    
       c[0]=0.4274*c[1]+0.4274*e[0]-0.3895*e[1];// zoh, wm=7,0.1*Hr si Te=33
       c1[0]=0.4274*c1[1]+0.4374*e1[0]-0.3895*e1[1];

      

    Servo2.write(round(c[0])+96);
    Servo1.write(round(-c1[0]+105));
    delay(33);
  

  //Serial.print("Abatere = "); Serial.print(e[0]);
   // Serial.print("\tY = "); Serial.print(p.y);
    //Serial.print("\tCommand = "); Serial.println(c[0]);
  Serial.print(" ");Serial.print(Errorx*Xconversion);   Serial.print(" mm,");  Serial.print(round(c1[0]));  Serial.print("  , ");   Serial.print(Errory*Yconversion);Serial.print(" mm,"); Serial.print(round(c[0]));  Serial.print("  ,");Serial.print(p.x);Serial.print("  ,");Serial.print(p.y);Serial.print("  , ");Serial.print(500);Serial.print("  , ");Serial.print(500);
  Serial.print("\n");
  }


 
 
  
 }
 

