//
//  main.c
//  ideahacks
//
//  Created by Susie Tan on 1/19/19.
//  Copyright © 2019 Susie Tan. All rights reserved.
//

#include <stdio.h>

signed int accelerationx[2] = {4, 4}, accelerationy[2]= {2, 4};
signed long velocityx[2] = {0,0}, velocityy[2] = {0,0};
signed long positionX[2] = {0,0};
signed long positionY[2] = {0,0};
signed long positionZ[2] = {0,0};
unsigned char direction;
unsigned long sstatex,sstatey;

void position(void);


int main() {
    position();
    printf("%d, %d\n", velocityx[0], velocityx[1]);
    printf("%d, %d", positionX[0], positionX[1]);
    
}

/******************************************************************************************
 This function transforms acceleration to a proportional position by integrating
 the acceleration data twice. It also adjusts sensibility by multiplying the
 "positionX" and "positionY" variables.
 This integration algorithm carries error, which is compensated in the "movenemt_end_check" subroutine.
 Faster sampling frequency implies less error but requires more memory. Keep in mind that the same process
 is applied to the X and Y axis.
 
 *****************************************************************************************/

void position(void)
{
    /*unsigned char count2 ;
     count2 = 0;
     do {
     ADC_GetAllAxis();
     accelerationx[1] = accelerationx[1] + Sample_X; //filtering routine for noise attenuation
     accelerationy[1] = accelerationy[1] + Sample_Y; //64 samples are averaged. The resulting
     //average represents the acceleration of
     //an instant
     count2++;
     } while (count2 != 0x40);
     
     accelerationx[1] = accelerationx[1] >> 6;
     accelerationy[1] = accelerationy[1] >> 6;
     // 64 sums of the acceleration sample
     // division by 64
     accelerationx[1] = accelerationx[1] - (int)sstatex; //eliminating zero reference
     //offset of the acceleration data
     accelerationy[1] = accelerationy[1] - (int)sstatey; // to obtain positive and negative
     //acceleration
     if ((accelerationx[1] <= 3) && (accelerationx[1] >= -3)) //Discrimination window applied
     {
     accelerationx[1] = 0; // to the X axis acceleration
     }
     //variable
     if ((accelerationy[1] <= 3) && (accelerationy[1] >= -3))
     {
     accelerationy[1] = 0;
     }*/
    
    //first X integration:
    velocityx[1] = velocityx[0] + accelerationx[0] + ((accelerationx[1] - accelerationx[0]) >> 1);
    //second X integration:
    positionX[1] = positionX[0] + velocityx[0] + ((velocityx[1] - velocityx[0]) >> 1);
    //first Y integration:
    velocityy[1] = velocityy[0] + accelerationy[0] + ((accelerationy[1] - accelerationy[0]) >> 1);
    //second Y integration:
    positionY[1] = positionY[0] + velocityy[0] + ((velocityy[1] - velocityy[0]) >> 1);
    
    accelerationx[0] = accelerationx[1];  //The current acceleration value must be sent
    //to the previous acceleration
    accelerationy[0] = accelerationy[1];
    //acceleration value.
    
    velocityx[0] = velocityx[1];
    velocityy[0] = velocityy[1];
    /*positionX[1] = positionX[1] << 18;
     //is a sensibility adjustment.
     positionY[1] = positionY[1] << 18;
     //particular situation
     data_transfer();
     
     positionX[1] = positionX[1] >> 18;
     positionY[1] = positionY[1] >> 18;
     movement_end_check();*/
    
    positionX[0] = positionX[1];
    positionY[0] = positionY[1];
    //variable in order to introduce the new
    //Same done for the velocity variable
    //The idea behind this shifting (multiplication)
    //Some applications require adjustments to a
    //i.e. mouse application
    //once the variables are sent them must return to
    //their original state
    //actual position data must be sent to the
    //previous position
    direction = 0;
}
