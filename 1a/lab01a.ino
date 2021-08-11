#include<string.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
//#include <SPI.h>
#include "dome_image.h"
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
#define IDLE 0  //example definition
#define DOWN 1  //example definition
#define UP 2
#define Med 3
#define med1 4
#define more1 5
const uint32_t PAUSE = 1000;
uint32_t timer;
uint8_t draw_state;
const uint8_t NUM_DRAW_STATES = 5;

const int input_pin = 16; //pin connected to button (CHANGED from 19!!)
uint8_t state;  //system state (feel free to use)
uint8_t num_count; //variable for storing the number of times the button has been pressed before timeout
void setup(void) {
  tft.init();
  tft.setRotation(2);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  Serial.begin(115200);
}

void loop() {              
  //draw_stuff();
   number_fsm(digitalRead(input_pin));
}

void draw_stuff(){
    timer = millis(); //store time of switch for future comparison
    draw_state +=1; //increment draw state
    draw_state %= NUM_DRAW_STATES;  //mod state (keep within 0 to NUM_DRAW_STATES -1
    if (draw_state==0){
      tft.drawString("Grinding All Night",0,0,1);
    }else if(draw_state==1){
      tft.drawString("ASHAR FAROOQ", 40, 0, 2); //viewable on Screen 
    }else if (draw_state==2){
      tft.drawString("ASHAR FAROOQ", 40, 0, 2); //viewable on Screen 
    }else if (draw_state==3){
      tft.drawString("ASHAR FAROOQ", 40, 0, 2); //viewable on Screen 
    }else if (draw_state==4){
      tft.drawString("ASHAR FAROOQ", 40, 0, 2); //viewable on Screen 
      }
}

void number_fsm(uint8_t input){
  //your logic here!

  switch(state){
    case IDLE:
      //example state
      //do logic here
      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1

      tft.println("Proceed to Simmons/Briggs" ); //long line that wraps!
      tft.println("" ); //long line that wraps!
       if (input == 0){
       tft.fillScreen(TFT_BLACK);
       tft.println("                                                             " ); //long line that wraps!
       state = DOWN;

      }
      
      break; //don't forget break statements
    case DOWN:
      //another state...etc...
      //do logic here 
      num_count+=1;
       tft.fillScreen(TFT_BLACK);
       tft.println("                                                                                                   " ); //long line that wraps!
    // tft.println("RESET COMPLETE" ); //long line that wraps!

      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
 
      tft.println("Proceed to Kendall Square" ); //long line that wraps!
    
      if(input == 1){
        state = UP;
      }
      break;
    case UP:
      //another state!
      //do logic here
      //add more states if you want! 
      //etc....keep adding states if needed
      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
      tft.println("" ); //long line that wraps!

       tft.println("                                                             " ); //long line that wraps!
      if(input == 0){
      tft.fillScreen(TFT_BLACK);
           tft.println("                                                                                                   " ); //long line that wraps!

      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1

      tft.println("Proceed to Technology Square" ); //long line that wraps!
      delay(1000);

            state = Med;

      }

       tft.println("                                                                                                                                                     " ); //long line that wraps!
      break;
    case Med:
      delay(1000);
      tft.println("                                                                                                                                                                                                           ");

      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1

      tft.println("Proceed to Boston FSILG (East)" ); //long line that wraps!
      tft.println(""); //long line that wraps!

      tft.println("                                                                                                                                                                                                           ");

      if(input == 0){

        tft.println("RESET COMPLETE" ); //long line that wraps!    

        state = med1;
      }
      break;
     case med1:

      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1
                tft.fillScreen(TFT_BLACK);

      tft.println("                                                                                                                                                                  " ); //long line that wraps!
      tft.setCursor(0,0,1); //set cursor at top left of screen, and set font size to 1

      tft.println("Proceed to East Campus"); //long line that wraps!
      delay(100000);
      if(input == 0){
        state = more1;
      }
      tft.println("                                                                                                                                            " ); //long line that wraps!

     break;
    case more1:
        tft.println("Proceed to Student Center"); //long line that wraps!
        delay(1000000000);
  }}
