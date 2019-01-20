/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low accelerometer and
magnetometer data registers. They can be converted to units of g and
gauss using the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).
Example: An LSM303D gives a magnetometer X axis reading of 1982 with
its default full scale setting of +/- 4 gauss. The M_GN specification
in the LSM303D datasheet (page 10) states a conversion factor of 0.160
mgauss/LSB (least significant bit) at this FS setting, so the raw
reading of -1982 corresponds to 1982 * 0.160 = 317.1 mgauss =
0.3171 gauss.
In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
registers actually contain a left-aligned 12-bit number, so the lowest
4 bits are always 0, and the values should be shifted right by 4 bits
(divided by 16) to be consistent with the conversion factors specified
in the datasheets.
Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
with its default full scale setting of +/- 2 g. Dropping the lowest 4
bits gives a 12-bit raw value of -1009. The LA_So specification in the
LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
1009 mg = 1.009 g.
*/

#include <Wire.h>
#include <LSM303.h>
LSM303 compass;

float accelerationx[2] = {0,0}, accelerationy[2]= {0, 0};
float velocityx[2] = {0,0}, velocityy[2] = {0,0};
float positionX[2] = {0,0};
float positionY[2] = {0,0};
float positionZ[2] = {0,0};

float time_slot;
float curr_time=0;

char report[80];
float xBias = 0;
float yBias = 0;
float zBias = 0;
bool biased = false;
float G = -16144; //1g

float countx=0;
float county=0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop()
{
  compass.read();
  if(biased == false)
    {
      AutoCalibrate();
      biased = true;
    }
  /*
  Serial.print ("\tAx:");
  Serial.print (  ((float)compass.a.x-xBias)/16, 4) ;
  Serial.print ("\tAy:");
  Serial.print (  ((float)compass.a.y-yBias)/16, 4);*/
  
 // Serial.print ("\t Az:");
 // Serial.print (  ((float)compass.a.z-zBias)/16, 4);
  //Serial.print (  (float)compass.a.z);  
  Serial.println ("\t");
  //Serial.print ("\tAx:");
//  Serial.print (-compass.a.x/16) ;
//  Serial.print ("\tAy:");
  //Serial.print (  -((float)compass.a.y-yBias)/16, 4);
//  Serial.print (-compass.a.y/16) ;
//  Serial.print ("\t Az:");
//  Serial.print (  ((float)compass.a.z-zBias)/16, 4);
//Serial.print (  (float)compass.a.z);  
//  Serial.println ("\t");
//  Serial.println(report);
  time_slot = millis()-curr_time;
  accelerationy[1]=((float)compass.a.y-yBias)/16;
  accelerationx[1]=((float)compass.a.x-xBias)/16;
  curr_time = millis();
  if((accelerationx[1] < 40) && (accelerationx[1] > -40))
  {
    accelerationx[1] = 0;
  }
  if((accelerationy[1] < 40) && (accelerationy[1] > -40))
  {
    accelerationy[1] = 0;
  }
  
  position();
  movement_end_check();
//  Serial.print ("\tPx:");
//  Serial.print (  ((float)velocityx[1]), 4) ;
//  Serial.print ("\tPy:");
//  Serial.print (  ((float)velocityy[1]), 4);
//  Serial.println ("\n");
  delay(30);
}

void AutoCalibrate(){
  for (int i = 1; i<=100; i++){
    float xRaw = ((float)compass.a.x);
    float yRaw = ((float)compass.a.y);
    float zRaw = ((float)compass.a.z);
    xBias += xRaw;
    yBias += yRaw;
    zBias += zRaw;
    }
    xBias = xBias/100;
    yBias = yBias/100;
    zBias = zBias/100-G;
  }

void movement_end_check(void)
{
if (accelerationx[1]==0)
     { countx++;}
else { countx =0;}
if (countx>=25)
 {
 velocityx[1]=0;
 velocityx[0]=0;
 }
 if (accelerationy[1]==0)
 { county++;}
else { county =0;}
if (county>=25)
 {
 velocityy[1]=0;
 velocityy[0]=0;
 }
//  //we count the number of acceleration samples that equals cero
////if this number exceeds 25, we can assume that velocity is cero
////we do the same for the Y axis
}
void position()
{    
    //movement_end_check();
    //first X integration:
    velocityx[1] = velocityx[0] + (accelerationx[0] + (accelerationx[1] - accelerationx[0])/2)*time_slot/1000;
    //second X integration:
//    if( velocityx[1]< 15){velocityx[1] = 0;}
    
    positionX[1] = positionX[0] + (velocityx[0] + (velocityx[1] - velocityx[0])/2)*time_slot/1000;
    Serial.print( velocityx[0], 4) ;
    Serial.print ("\t");
    Serial.print( velocityx[1], 4) ;
    Serial.print ("\t");
    Serial.print (positionX[0]);
    Serial.print ("\t");
    Serial.print (positionX[1]);

    Serial.print("\n");
    //first Y integration:
    velocityy[1] = velocityy[0] + (accelerationy[0] + (accelerationy[1] - accelerationy[0])/2)*time_slot/1000;
    //second Y integration:
    positionY[1] = positionY[0] + (velocityy[0] + (velocityy[1] - velocityy[0])/2)*time_slot/1000;
    
    accelerationx[0] = accelerationx[1];  //The current acceleration value must be sent
    //to the previous acceleration
    accelerationy[0] = accelerationy[1];
    //acceleration value.
    
    velocityx[0] = velocityx[1];
    velocityy[0] = velocityy[1];

    positionX[0] = positionX[1];
    positionY[0] = positionY[1];
}
