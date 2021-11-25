#include <ASensor.h> //Including ASensor.h header file
#include <mbed.h> //Including mbed.h header file to be able to use the I2C functions

I2C i2c(PIN5, PIN6); //(SDA, SCL) //I2C initialised here
Ticker t; //Ticker Class object intantiated
PwmOut led(LED2); //LED2 instantiated with PwmOut for Q3

int main() {

  // put your setup code here, to run once:

  while(1) {

    int val = GetEvent(); // Question 1, part (d). Integer value of a certain event is returned to the "val" variable
    printf("%d", val); //value of the event is printed
    wait_us(500000);  //Waits for 0.5s. 500000 us is 0.5s.

    t.attach(&eventOut, 500ms); //Q2.a Using ticker attach to do a callback of a function which calls the function at evey 0.5seconds

    int led_Strn = GetTotalStrength(); //Q3. The GetTotalStrength() function sends an integer value of 
                                      //the accumulative Touch Strength from the sensor

    float tot_str = 1/65536; //creating another variable
    tot_str = tot_str * 1000; //(Since its going to be in mV I assume)

    char state[10] = {'B','D'}; //States of either BRIGHT AND DIM

    if(tot_str >= 0.57){ //Assuming the min value to be 0 and max to be 1. I am considering 0.57 to be the threshold. So any value above it will give us BRIGHT, else DIM
      led = tot_str;
      printf("%s", state[0]); //Printing the state 
      wait_us(1000);
    }
    else{
      led = tot_str; //storing the voltage 
      printf("%s",state[1]); //Printing the state 
      wait_us(1000);
    }

  }
}

void eventOut(){ //Function for decoding the event type from the decimal value that is returned from GetEvent()

  int tick_val; 
  tick_val = GetEvent(); //tick_val gets the int val from the GetEvent function

  switch(tick_val){ //Swtich cases are done based on the returned value
    
      case  0:
        printf("SINGLE_TAP"); //For instance if its 0, SINGLE TAP is printed/executed
        break;
      case  1:
        printf("PRESS_AND_HOLD"); //Similar ideas for the rest
        break;
      case  2:
        printf("SWIPE _X-");
        break;
      case  3:
        printf("SWIPE _X+");
        break;
      case  4:
        printf("SWIPE _Y+");
        break;
      case  5:
        printf("SWIPE _Y-");
        break;
      case  9:
        printf("2_FINGER_TAP");
        break;
      case  10:
        printf("SCROLL");
      break;
      case  11:
        printf("ZOOM");
      break;
      default:
        printf("No EVENT!");
      break;
  }

}


