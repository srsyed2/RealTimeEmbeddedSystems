//In this ASensor.c file all the declared functions of the header file are defined.


#include <Asensor.h> //Including ASensor.h header file
#include <mbed.h> //Including mbed.h header file to be able to use the I2C functions
#include <stdio.h> //Including this header to be able to use string concatanation
#include <string.h>

int GetVersion(){

     char temp0[2] = {MAJOR_VERSION, MINOR_VERSION};
    // place to store received bytes
     char recvd[2] = 0x00;
   
    i2c.write(addrWrite, temp0, 2, false); //writing the address of the Major and Minor Version to the slave

    i2c.read(addrRead, &recvd, 2); //The master reads the 2 bytes of data of the major and minor version from registers
    wait_us(100000);

    uint16_t Version = atoi(strcat(recvd[0],recvd[1])); //converting the version from a char array with hex values to integer

    return Version; //returning the version
}


int GetTotalStrength(){
    
    char StrengthVal = 0x0000; // read bytes stored here
    char temp1[2] = {Touch_Strength_0, Touch_Strength_0}; //temp1 defined to have the register address of Touch Strength

    i2c.write(addrWrite, &temp1, 2, true); //Write ouch_Strength_0 to ouch_Strength_1 on the device
    i2c.read(addrRead, &StrengthVal, 2); //read 2bytes from Touch Strength reg
    return (int)(StrengthVal); //return int Strength Value
}


//Returns 0 if there is no event or an enumerated value indicating the event type defined by the bits in register addresses 0x000D – 0x000E in the sensor (see datasheet table 8.1)
int GetEvent(){
    
    char temp2[2] = {Event_0,Event_1}; //char array containing the address of the register responsible for Event data

    uint16_t init = 0b0000000000000001; //initialising the first bit to be high, for the whole byte
    char event2 = 0x0000; //read bytes stored here
    
     /* Creating an enum, for mapping each of the event type with an integer value
        For example when there is a horizontal right swipe, based on the both registers value will be 0000000000000000001000,
        this will return an integer value of 3 
      */

    enum sensor1{ 
                          
        SINGLE_TAP = 0;
        PRESS_AND_HOLD = 1;
        SWIPE _X- = 2;
        SWIPE _X+ = 3;
        SWIPE _Y+ = 4;
        SWIPE _Y- = 5;
        FINGER_TAP = 9; //9th bit of the byte refers to FINGER_TIP
        SCROLL = 10; //10th bit of the byte refers to FINGER_TIP
        ZOOM = 11; //11th bit of the byte refers to FINGER_TIP
    } event;

    
    i2c.write(addrWrite, temp2, 2, true); //Writing address of the event
    i2c.read(addrRead, &event2, 2); //Reading 2 bytes of Event data

    wait_us(1000);

    if(event2 && (init){  //Bitwise AND operation to find out if the 1st byte is only high
        event = SINGLE_TAP; 
        return event; //this will return a 0 which refers to the SINGLE TAP bit
    }
    
    elseif(event2 && (init << 1)){ //Bitwise AND operation to find out if the 2nd byte is only high
        event = PRESS_AND_HOLD;
        return event;   //this will return a 1 which refers to the PRESS_AND_HOLD bit
    }

   elseif(event2 && (init << 2)){   //Bitwise AND operation to find out if the 3rd byte is only high
        event = SWIPE _X-;
        return event; //this will return a 2 which refers to the SWIPE_X- bit
    }
    
    elseif(event2 && (init << 3)){ //Same idea goes for the rest
        event = SWIPE _X+;
        return event;
    }

    elseif(event2 && (init << 4)){
        event = SWIPE _Y+;
        return event;
    }

    elseif(event2 && (init << 5)){
        event = SWIPE _Y-;
        return event;
    }

     elseif(event2 && (init << 8)){
        event = FINGER_TAP;
        return event;
    }
    
    elseif(event2 && (init << 9)){
        event = SCROLL;
        return event;
    }

    elseif(event2 && init << 10)){
        event = ZOOM;
        return event;
    }

    else
        return 0;
}