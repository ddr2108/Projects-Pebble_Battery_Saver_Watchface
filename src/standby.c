#include <pebble.h>
#include "standby.h"
#include "time-date.h"
  
  bool standbyFlag = false;

  /**************************************************
  * initStandby
  * checks if device needs to be put in standby initally
  *
  * Parameters:
  *   none
  * Returns:
  *   none
  ***************************************************/
  void initStandby(){
      //check if it should be in standby at inital turn on of face
      int a = 5;
  }
  
  
void standby(){
  //get the time for local time zone
  time_t curTime = time(NULL);
  struct tm* curTimeLocal = localtime(&curTime);
  //check if should put in standby mode
  if (curTimeLocal->tm_hour==23 && curTimeLocal->tm_min==00){
    standbyFlag = true;
    //reset text box
    text_layer_set_text(dayLayer,"");
    text_layer_set_text(timeLayer,"");
    text_layer_set_text(dateLayer,"");
  } else if (curTimeLocal->tm_hour==6 && curTimeLocal->tm_min==0){
    standbyFlag = false;
  }
}
  