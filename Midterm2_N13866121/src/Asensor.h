
/* 
    RTES_Quiz 2
    Author: Syed Salman Rahman (N13866121)

/* 
This heaeder file contains all the declarations of the required functions  
and the Register addresses in memory that are required to perform the 3 functions 
*/

#define I2C_ADDRESS              0x74  //#define SENSOR_ADDRESS xxxx


#define IQS550_PRODUCT_NUM       0x20 //Product Number (For IQS550 Decimal 40 Version)

#define MINOR_VERSION            0x0005 //Register address of the Major Version
#define MAJOR_VERSION            0x0004 //Address of the Minor Version
#define Touch_Strength_0         0x001A //Address of the Touch Strength Byte1
#define Touch_Strength_1         0x001B //Address of the Touch Strength Byte2
#define Event_0                  0x000D //Address of the Event Byte1
#define Event_1                  0x000E //Address of the Event Byte1
                   
const int addrWrite       =   0xE8;  //#define slave Write
const int addrRead        =   0xE9;  //#define slave Read

//Returns Major Version.Minor Version of the sensor
int GetVersion();

//Returns the total strength (See datasheet table 8.1)
int GetTotalStrength();

//Returns 0 if there is no event or an enumerated value indicating the event type defined by the bits in register addresses 0x000D – 0x000E in the sensor (see datasheet table 8.1)
int GetEvent();