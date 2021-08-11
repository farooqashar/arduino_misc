#include <WiFi.h>
#include<math.h>
#include<string.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  

int state1 = -1;
String locationArea;
int timeLapse = 0;
bool responseData;

#define BUTTON_PIN 16
HardwareSerial gps_serial(2);

class Button {
  public:
    int pin;
    int flag;
    bool held;
    int state; 
    unsigned long timeInState;
    unsigned long timeButton;
    unsigned long debounce;
    unsigned long holdTime;
    
    Button(int pinn) {
      flag = 0;
      state = 0;
      pin = pinn;
      timeInState = millis(); 
      timeButton = millis(); 
      debounce = 10;
      holdTime = 1000;
      held = 0;
    }
};

void update() {
      int buttonStatus = digitalRead(pin);
      held = !buttonStatus;
      flag = 0;
      if (state == 0) { 
        if (held) {
          state = 1;
          timeButton = millis();
        }
      } else if (state == 1) { 
        if (!held) {
          state = 0;
          timeButton = millis();
        } else if (millis() - timeButton >= debounce) {
          state = 2;
          timeInState = millis();
        }
      } else if (state == 2) {
        if (!held) {
          state = 4;
          timeButton = millis();
        } else if (millis() - timeInState >= holdTime) {
          state = 3;
        }
      } else if (state == 3) { 
        if (!held) {
          state = 4;
          timeButton = millis();
        }
      } else if (state == 4) { 
        if (held && millis() - timeInState < holdTime) {
          state = 2; 
          timeButton = millis();
        } else if (held && millis() - timeInState >= holdTime) {
          state = 3; 
          timeButton = millis();
        } else if (millis() - timeButton >= debounce) { 
          state = 0;
          if (millis() - timeInState < holdTime) { 
            flag = 1;
          } else {  
            flag = 2;
          }
        }
      }
   }

Button button(BUTTON_PIN);


void setup() {
  Serial.begin(115200); 
  tft.init();
  tft.setRotation(2);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  gps_serial.begin(9600, SERIAL_8N1, 32, 33);
  wifi();
  timeLapse = millis() - 15000;
}

TinyGPSPlus gps;

void loop() {
  button_status = button.update();

  if (button_status == 2) { 
    state1 = 0;
  }
    if (gps_serial.available()) {
      while (gps_serial.available())
        gps.encode(gps_serial.read());
    }
    if (gps.location.isValid()) { 
      if (responseData == false) { 
        state1 = 0;
      }
      responseData = true;
    }

    if (millis() - timeLapse > 1300 && responseData == true) { 
      locationArea = do_GET(gps.location.lat(), gps.location.lng());
      timeLapse = millis();
    }

    switch (state1) {
      case -1:
      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
      tft.println(""); //long line that wraps!
      tft.println("Invalid GPS");
        break;
      case 0:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea);        
        if (locationArea == "Infinite Corridor/Killian") { 
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Infinite Corridor/Killian");   
          while (button.update() != 1) { 
            state1 = 1;
          }
        }
        break;
      case 1:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea);   
        
        if (locationArea == "Dorm Row") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Dorm Row");           
          while (button.update() != 1) {
            state1 = 2;
          }
        }
        break;
      case 2:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea);  
        if ((button_status == 1) && (locationArea == "Student Center")) {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Student Center");    
          while (button.update() != 1) {
            state1 = 3;
          }
        }
        break;
      case 3:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Vassar Academic Buildings") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Vassar Academic Buildings");  
          while (button.update() != 1) {
            state1 = 4;
          }
        }
        break;
      case 4:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Stata/North Court") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Stata/North Court");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
         case 5:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Stata/North Court") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Stata/North Court");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
         case 6:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Simmons/Briggs") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Simmons/Briggs");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
         case 7:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Boston FSILG (West)") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Boston FSILG (West)");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
         case 8:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "East Campus") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in East Campus");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
          case 9:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Sloan/Media Lab") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Sloan/Media Lab");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
          case 10:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "North Campus") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in North Campus");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
            case 11:
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("Proceed to" + locationArea); 
        if (locationArea == "Technology Square") {
        tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
        tft.println(""); //long line that wraps!
        tft.println("You are in Technology Square");  
          while (button.update() != 2) { 
            state1 = 0;
          }
        }
        break;
    }
}
