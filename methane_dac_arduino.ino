//Code by Swastik Khuntia
//For FreCk
//Interfacing of MQ4 snsor and programmed 9-bit ADC

//Constant Declaration
const int ch4 = A0; // Connect AO of MQ4 with Analog channel 0 pin (A0) of Arduino
int ch4_val; // stores analog output of MQ4 sensor
//LEDs for 9-bit ADC
const int LED0 = 2;
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;
const int LED4 = 6;
const int LED5 = 7;
const int LED6 = 8;
const int LED7 = 9;
const int LED8 = 10;

void setup()
{
  pinMode(ch4, INPUT); //Analog value of Methane sensor as input
  //LEDs as OUTPUT
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);

  Serial.begin(9600); //Serial communication for debugging
  }

  void loop ()
  {
    //Read & display input from mthane sensor
    ch4_val = analogRead(ch4);
    Serial.println(ch4_val);
    //Controlling LEDs based on sensor value
    //Equivalent to 9-bit ADC
    digitalWrite(LED0, ch4_val>50?HIGH:LOW);
    digitalWrite(LED1, ch4_val>100?HIGH:LOW);
    digitalWrite(LED2, ch4_val>150?HIGH:LOW);
    digitalWrite(LED3, ch4_val>190?HIGH:LOW);
    digitalWrite(LED4, ch4_val>210?HIGH:LOW);
    digitalWrite(LED5, ch4_val>240?HIGH:LOW);
    digitalWrite(LED6, ch4_val>270?HIGH:LOW);
    digitalWrite(LED7, ch4_val>300?HIGH:LOW);
    digitalWrite(LED8, ch4_val>500?HIGH:LOW);

    delay(500); //Checks and displays methane concentration every second
  }
