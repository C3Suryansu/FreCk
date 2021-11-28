#include <SoftwareSerial.h> //For communication with ESP-32
//Constant Declaration
const int ch4 = A0; // Connect AO of MQ4 with Analog channel 0 pin (A0) of Arduino
int ch4_val_th; // stores analog output of MQ4 sensor (for threshold)
int ch4_current; //Stores current value of MQ4 sensor
int diff; //Stores the differnece between the threshold value and current value of MQ4 sensor
float api; //API value recieved from ESP-32
int mean; //Stores the mean of API value and difference in case of single subject mode of operation

const int mode_switch = 11; //Mode selector switch
//LEDs for 9-bit ADC

const int LED0 = 4;
const int LED1 = 5;
const int LED2 = 6;
const int LED3 = 7;
const int LED4 = 8;
const int LED5 = 9;
const int LED6 = 10;

//Setup software serial
SoftwareSerial myPort(2, 3); // RX, TX

void setup()
{
  pinMode(ch4, INPUT); //Analog value of Methane sensor as input
  pinMode(mode_switch, INPUT); //To check the mode of operation
  //LEDs as OUTPUT
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);


  Serial.begin(9600); //Serial communication for debugging
  myPort.begin(9600); //Communication begins with ESP32 
  }

  void loop ()
  {
    //Read & display input from methane sensor
    delay(10000); //For the methane value to get stabilised
    ch4_val_th = analogRead(ch4); //Threshold value of Methane sensor
    //Serial.println(ch4_val); //For debugging
    while (digitalRead(mode_switch) == LOW) //Single subject under test mode
    {
      if (myPort.available())
      {
        api = myPort.read();
        Serial.println(api); //For debugging
        ch4_current = analogRead(ch4); //Current value of methane sensor
        Serial.println(ch4_current); //For debugging
        diff = map((ch4_current-ch4_val_th),0,200,0,100); //Differnce between current value of mthane sensor and threshold value
        mean = (api+diff)/2; //Mean value
        led_disp(mean); //Displays result on LED
      }
      else
        continue;
    }
    while (digitalRead(mode_switch) != LOW) //Multiple subjects under test mode
    {
     delay(10000); //Stabilise methane sensor value when subjected to food under test 
     ch4_current = analogRead(ch4); //Current value of methane sensor
     diff = map((ch4_current-ch4_val_th),0,200,0,100); //Differnce between current value of mthane sensor and threshold value
     led_disp(diff); //Displays result on LED
     }
  }

  void led_disp(int output)
  {
    //Controlling LEDs based on sensor value
    //Equivalent to 9-bit ADC
    digitalWrite(LED0, output>0?HIGH:LOW);
    digitalWrite(LED1, output>20?HIGH:LOW);
    digitalWrite(LED2, output>40?HIGH:LOW);
    digitalWrite(LED3, output>50?HIGH:LOW);
    digitalWrite(LED4, output>60?HIGH:LOW);
    digitalWrite(LED5, output>80?HIGH:LOW);
    digitalWrite(LED6, output>100?HIGH:LOW);
    delay(10000); //Remains in the state for 10 second until led reset
    //Reset all LEDs
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
  }
 
