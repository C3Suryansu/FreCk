const int AO_Pin=0; // Connect AO of MQ4 with Analog channel 0 pin (A0) of Arduino
const int DO_Pin=8; // Connect DO of MQ4 with Digital pin 8 (D8) of Arduino
const int Led_Pin=13; // Connect an LED with D13 pin of Arduino
int threshold_value; // A variable to store digital output of MQ4
int AO_Out; // stores analog output of MQ4 sensor

void setup() {
Serial.begin(115200);  // Initialize serial communictation with a baud rate of 115200
pinMode(DO_Pin, INPUT); // Configure D8 pin as a digital input pin
pinMode(Led_Pin, OUTPUT); //Configure D3 pin as a digital output pin
}

void loop()
{
AO_Out= analogRead(AO_Pin); // Take Analog output measurement sample from AO pin of MQ4 sensor
threshold_value= digitalRead(DO_Pin); //Read digital output of MQ4 sensor
Serial.print("Methane Conentration: ");
Serial.println(AO_Out);//prints the methane value
Serial.print("threshold_value: ");
Serial.print(threshold_value);//prints the threshold_value reached as either LOW or HIGH (above or underneath)
delay(100);
if (threshold_value== HIGH){
digitalWrite(Led_Pin, HIGH);//if threshold_value has been reached, LED turns on as status indicator
}
else{
digitalWrite(Led_Pin, LOW);//if threshold not reached, LED remains off
}
}
