#include "Arduino.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <base64.h>
#include <HTTPClient.h>

#define CAMERA_MODEL_AI_THINKER 

String payload;
//Array for payload
//String payload_arr[4];

//Define files used as a replacement to camer_pins.h libraray
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

const char* ssid = "SPECTRUMNET";
const char* password = "spectrum2021";

float first,second,third,fourth; //To store the response of the API for 4 images 

//char response[14] = ""; //To store response of API in each stage

void setup() {
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Serial.println();
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }


#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  }
void classifyImage() {
  
  // Capture picture
   camera_fb_t * fb = NULL;
   fb = esp_camera_fb_get();
   
   if(!fb) {
    Serial.println("Camera capture failed");
    return;
   }

  size_t size = fb->len;
  String buffer = base64::encode((uint8_t *) fb->buf, fb->len);
  payload = "{\"input\": \""+ buffer +"\"}";

  buffer = "";
  // Uncomment this if you want to show the payload
  //Serial.println(payload);

  esp_camera_fb_return(fb);
}
  
//Function to send image
String sendImage()
{
  HTTPClient http;
  //http.begin("https://api.clarifai.com/v2/models/" + model_id + "/outputs");
  http.begin("http://dstri26.pythonanywhere.com/scan");
  http.addHeader("Content-Type", "application/json");      
  int response_code = http.POST(payload);
  //Serial.println(payload_arr);
  //Serial.print(response_code);
  String response = http.getString();
  Serial.println(response);
  return response;
}

//Function to parse String returned by API to find float value
float str_parse(String r_value)
{
  char * char_r_value;
  r_value.toCharArray(char_r_value,15);
  //const char * char_r_value = r_value.c_str();
  char * part1;
  part1 = strtok (char_r_value," ");
  float aFloat = atof(strtok (NULL," "));  
  return aFloat;
}


void loop()
{
    classifyImage();
    //first = sendImage();
    first = str_parse(sendImage());
    //payload_arr[0]=payload;
    delay(3000);
    classifyImage();
    //second = sendImage();
    second = str_parse(sendImage());
    //payload_arr[1]=payload;
    delay(3000);
    classifyImage();
    //third = sendImage();
    third = str_parse(sendImage());
    //payload_arr[2]=payload;
    delay(3000);
    classifyImage();
    //fourth = sendImage();
    fourth = str_parse(sendImage());
    //payload_arr[3]=payload;
    delay(3000);
    
    Serial.println("Communication established"); //For debugging
    Serial.println(max(max(first,second),max(third,fourth))); //Send maximum value returned by API
    
    //payload=payload_arr[0] + "," + payload_arr[1] + "," + payload_arr[2] + "," + payload_arr[3];
    //Serial.pritln(payload);
    //sendImage();
    delay(10000);
}
