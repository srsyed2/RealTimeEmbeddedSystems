//References
// PwmOut https://os.mbed.com/docs/mbed-os/v6.9/apis/pwmout.html
// AnalogIn https://os.mbed.com/docs/mbed-os/v6.15/apis/i-o-apis.html
/*  Signal Graphing
* In this exercise you must utilize a timer/ticker to monitor the Analog ADC pins and sample their values.
* Set up PB_0 for PwmOut and set up PB_1 for AnalogIn. Initiate a PWM signal of 1Hz with a 20% duty cycle on PB_0.
* When sampling, you must short the pins PB_0 and PB_1. One method is to utilize jumper JP2 that comes with your board!
* For this task, you will sample the ADC for 5 seconds at 500 samples/second. Store your samples in a buffer and then output the buffer to the terminal.
* From the terminal, record and graph your collected data in either Matlab or Python (Using matplotlib libraries)
* and submit the resulting graph as a jpg/png as part of this assignment. Remember to label the x & y axis correctly.
* you must be able to show that the frequency of the square wave is as expected
*/
// recommended steps:
// create a PWMOut on PB_0
// create a ticker to read from the an AnalogIn on PB_1
// set up a way to write to a buffer in the ticker callback
// output values in the main loop



#include <mbed.h>

PwmOut pw1(PB_0); // Set up PWM at Pin PB_0
AnalogIn ain(PB_1); // Set up ADC AnalogIn at Pin PB_1
Ticker t;              //Instantiating the Ticker class

int flag = 1; //declaring a flag which will trigger intaking values from AnalogIn
int i = 0; //index is initially set to 0
float buf[2500]; //Setting up a float buffer array to store values
void readanalog(void);

int main() {

  pw1.period(1);        //1 second period, Since T = 1/f
  pw1.write(0.20);      //20% Duty Cycle. 20% high, 80% low
 
  t.attach(&readanalog, 2ms); //ticker is set to callback readanalog function every 2ms

  while(1) {
    if(flag == 1){
        buf[i] = ain.read();
			  i++;
			  flag = 0; //value of flag is set back to 0
      }
      //ThisThread::sleep_for(2); //to block the current thread for specified duration

      //Print the buffer array
      if(i>=2500) { //once the index reaches 2500 (meaning 2500 samples, the loop starts printing the values)
			  printf("\n\r\n\r");
			  printf("data = [");
			    for(int index2 = 0; index2< 2500; index2++){
				    printf("%d,", (int)(1000*buf[index2])); //Multiplied by 1000 so that the number is significant enough and is converted to integer
			    }
			    printf("]\n\r\n\r");
      }
  }
}

void readanalog(){ //Function which keeps setting up flag to "1"
  if(i>=2500){ 
    flag = 0;
  } else flag = 1;
}


//Program without ticker. Simple loops to take input in an array and then output the array of data


// #include <mbed.h>

// PwmOut pw1(PB_0);
// AnalogIn ain(PB_1);

// int buf[2500];

// int main() {

//   pw1.period(1);        //1 second period
//   pw1.write(0.20);       //20% poiy Cycle
 
//   while(1) {
          //data input

//       for (int i = 0; i < 2500; i++) {
//       buf[i] = ain.read();
//       wait_us(2000);
//     }

//     // printing on the terminal

//     printf("data = [");
//     for (int i = 0; i < 2500; i++) {
//       printf("%d,", (int)(1000*buf[i]));
//     }
//     printf("]\n\r\n\r");
//   }
// }