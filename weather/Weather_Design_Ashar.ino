#include <WiFi.h> //Connect to WiFi Network
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h> //Used in support of TFT Display
#include <string.h>  //used for some string handling and processing.
#define IDLE 0  //example definition
#define DOWN 1  //example definition
#define UP 2
#define RESPONSE 3
//add more if you want!!!
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
const int RESPONSE_TIMEOUT = 6000; //ms to wait for response from host
const int GETTING_PERIOD = 2000; //periodicity of getting a number fact.
const int BUTTON_TIMEOUT = 1000; //button timeout in milliseconds
const uint16_t IN_BUFFER_SIZE = 1000; //size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 1000; //size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE]; //char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE]; //char array buffer to hold HTTP response
char request_buffer2[1000];
char response_buffer2[1000];
char network[] = "Help";  //SSID for 6.08 Lab
char password[] = "passwordhereiguess"; //Password for 6.08 Lab
char city[] = "Cambridge";
char state_geo[] = "Massachusetts";
char appid[] = "b53b437dfdf36c11d865ccb771a8833e";
char request_link[250];
char* beginDivide;
char delimeter[]="{";
char* intermediate;
char delimeter2[]=",";
char* temp;
char* pressure;
char* visibility;
char* humidity;
char* temp2;
char* pressure2;
char* visibility2;
char* humidity2;
char* pch3;
char * pch4;
char* time_local;
char* date_local;
char* temporary;
int counter = 0;
char temperature_reading[50];
char visibility_reading[50];
char humidity_reading[50];
char pressure_reading[50];
char date_reading[50];
char time_reading[50];
float temp2float;
const int input_pin = 19; //pin connected to button (CHANGED from 19!!)
uint8_t state;  //system state (feel free to use)
uint8_t num_count; //variable for storing the number of times the button has been pressed before timeout
unsigned long timer;  //used for storing millis() readings.
void setup(){
  tft.init();  //init screen
  tft.setRotation(2); //adjust rotation
  tft.setTextSize(1); //default font size
  tft.fillScreen(TFT_BLACK); //fill background
  tft.setTextColor(TFT_GREEN, TFT_BLACK); //set color of font to green foreground, black background
  Serial.begin(115200); //begin serial comms
  delay(100); //wait a bit (100 ms)
  WiFi.begin(network); //attempt to connect to wifi
  uint8_t count = 0; //count used for Wifi check times
  num_count = 0;
  Serial.print("Attempting to connect to ");
  Serial.println(network);
  while (WiFi.status() != WL_CONNECTED && count<6) {
    delay(500);
    Serial.print(".");
    count++;
  }
  delay(2000);
  if (WiFi.isConnected()) { //if we connected then print our IP, Mac, and SSID we're on
    Serial.println("CONNECTED!");
    Serial.printf("%d:%d:%d:%d (%s) (%s)\n",WiFi.localIP()[3],WiFi.localIP()[2],WiFi.localIP()[1],WiFi.localIP()[0], WiFi.macAddress().c_str() ,WiFi.SSID().c_str());
    delay(500);
  } else { 
    Serial.println("Failed to Connect :/  Going to restart");
    Serial.println(WiFi.status());
    ESP.restart(); // restart the ESP (proper way)
  }
  pinMode(input_pin, INPUT_PULLUP); //set input pin as an input!
  state = IDLE; //start system in IDLE state!
}
void loop(){
  userInputNumbers(digitalRead(input_pin)); 
  //Serial.println(num_count);
}

void userInputNumbers(uint8_t input){
  switch(state){
    case IDLE:
      //example state
      //do logic here
      if (input==0){
        Serial.println("pushed");
        state = DOWN;
      }
      // if (some condition){
      // state = next_state_you_wanna_go_to;
      //}
      break; //don't forget break statements
    case DOWN:
      //another state...etc...
      //do logic here 
      if (input==1){
        Serial.println("unpushed");
        timer = millis();
        num_count += 1;
        state = UP;
      }
      break;
    case UP:
      //another state!
      if (input==0){
        state = DOWN;
      }
      if (millis()-timer >BUTTON_TIMEOUT){
        state = RESPONSE;
      }
      break;
    case RESPONSE:
      Serial.print("num_count =");
      Serial.println(num_count);
      sprintf(request_link, "https://api.openweathermap.org/data/2.5/weather?q=%s,state=%s&appid=%s HTTP/1.1\r\n", city, state_geo, appid); 
      sprintf(request_buffer, "GET %s", request_link);
      strcat(request_buffer,"Host: api.openweathermap.org\r\n"); 
      strcat(request_buffer,"\r\n"); 
      sprintf(request_buffer2, "GET %s", "http://iesc-s3.mit.edu/esp32test/currenttime HTTP/1.1\r\n");
      strcat(request_buffer2, "Host: iesc-s3.mit.edu\r\n");
      strcat(request_buffer2,"\r\n"); 
      do_http_GET("api.openweathermap.org", request_buffer, response_buffer, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT,true);
      do_http_GET("iesc-s3.mit.edu", request_buffer2, response_buffer2, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT,true);
      pch4=strtok(response_buffer2, " ");
      date_local=pch4;
      pch4=strtok(NULL, ".");
      time_local=pch4;
      sprintf(time_reading, "Time: %s\n", time_local);
      sprintf(date_reading, "Date: %s\n", date_local);    
      
      beginDivide=strtok(response_buffer,delimeter);
      for (int i=0; i<3;i++){
        beginDivide=strtok(NULL, delimeter);
      }
      intermediate=strtok(beginDivide, delimeter2);
      temp = intermediate;
      
      while (counter<7){
        intermediate=strtok(NULL, delimeter2);
        if (counter==3){
          pressure=intermediate;
        }
        if (counter==4){
          humidity=intermediate;
        }
        if (counter==5){
          visibility=intermediate;
        }
        counter+=1;          
      }
      pressure2=strtok(pressure, ":");
      pressure2=strtok(NULL, ":");
      sprintf(pressure_reading, "Pressure: %s MB\n", pressure2);
      temp2=strtok(temp, ":");
      temp2=strtok(NULL, ":");
      temp2float=(((atof(temp2)-273.15)*(9.0/5.0)) + 32);
      sprintf(temperature_reading, "Temperature: %f deg F\n", temp2float);
      
    
      
      visibility2=strtok(visibility, ":");
      visibility2=strtok(NULL, ":");
      sprintf(visibility_reading, "Visibility: %f km\n", atof(visibility2)/1000.0);
      tft.fillScreen(TFT_BLACK); 

      humidity2=strtok(humidity, ":");
      humidity2=strtok(NULL, "}");
      sprintf(humidity_reading, "Humidity: %d \n", atoi(humidity2));

      
      if(num_count=1){
        tft.setCursor(0,0,1);
        tft.print(temperature_reading);
      }
      if (num_count==2){
        tft.setCursor(20,0,1);
        tft.print(humidity_reading);
      }
      if (num_count==3){
        tft.setCursor(40,0,1);
        tft.print(visibility_reading);
      }
      if (num_count==4){
        tft.setCursor(60,0,1);
        tft.print(pressure_reading);
      }
      if(num_count==5){
        tft.setCursor(80,0,1);
        tft.print(time_reading);
      }
      if(num_count==6){
        tft.setCursor(100,0,1);
        tft.print(date_reading);
      }
      Serial.println(temperature_reading);
      Serial.println(pressure_reading);
      Serial.println(humidity_reading);
      state = IDLE;
      num_count=0;
  }
  
}
uint8_t char_append(char* buff, char c, uint16_t buff_size) {
        int len = strlen(buff);
        if (len>buff_size) return false;
        buff[len] = c;
        buff[len+1] = '\0';
        return true;
}
void do_http_GET(char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial){
  WiFiClient client; //instantiate a client object
  if (client.connect(host, 80)) { //try to connect to host on port 80
    if (serial) Serial.print(request);//Can do one-line if statements in C without curly braces
    client.print(request);
    memset(response, 0, response_size); //Null out (0 is the value of the null terminator '\0') entire buffer
    uint32_t count = millis();
    while (client.connected()) { //while we remain connected read out data coming back
      client.readBytesUntil('\n',response,response_size);
      if (serial) Serial.println(response);
      if (strcmp(response,"\r")==0) { //found a blank line!
        break;
      }
      memset(response, 0, response_size);
      if (millis()-count>response_timeout) break;
    }
    memset(response, 0, response_size);  
    count = millis();
    while (client.available()) { //read out remaining text (body of response)
      char_append(response,client.read(),OUT_BUFFER_SIZE);
    }
    if (serial) Serial.println(response);
    client.stop();
    if (serial) Serial.println("-----------");  
  }else{
    if (serial) Serial.println("connection failed :/");
    if (serial) Serial.println("wait 0.5 sec...");
    client.stop();
  }
}
