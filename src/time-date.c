#include <pebble.h>
#include "time-date.h"
#include "standby.h"
  
  TextLayer *timeLayer = NULL;
  TextLayer *dateLayer = NULL;
  TextLayer *dayLayer = NULL;

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  //check if should be in standby
  standby();
  
  //update the time
  if (standbyFlag==false){
    updateTime();
  }
}

void updateTime(){
  //get the time for local time zone
  time_t curTime = time(NULL);
  struct tm* curTimeLocal = localtime(&curTime);

  ///////////////Set up time////////////////////////
  //buffer to hold time
  static char timeBuffer[] = "00:00A";  
  //format the time if 24 hours style
  if (clock_is_24h_style()){
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", curTimeLocal);
  }else{
    //format time am or pm
    if (curTimeLocal->tm_hour<12){
      strftime(timeBuffer, sizeof(timeBuffer), "%I:%M", curTimeLocal);
    }else{
      strftime(timeBuffer, sizeof(timeBuffer), "%I:%M", curTimeLocal);      
    }
  }

  //print to screen
  text_layer_set_text(timeLayer, timeBuffer);
  ////////////Set up Date//////////////////////////////
  //buffer to hold date
  static char dateBuffer[] = "December 25";
  //format date
  strftime(dateBuffer, sizeof(dateBuffer), "%B %e", curTimeLocal);  
    
  //print to screen
  text_layer_set_text(dateLayer, dateBuffer);
  //////////Set up Day////////////////////////////////
  //buffer
  static char dayBuffer[] = "Wednesday";
  //format day
  strftime(dayBuffer, sizeof(dayBuffer), "%A", curTimeLocal);
  
  //print to screen
  text_layer_set_text(dayLayer, dayBuffer);    
}