#include <pebble.h>
#include "main.h"
#include "time-date.h"
#include "battery.h"


static void mainWindowInit(Window *window){

  ////////////////Set up window///////////////////////
  //window color
  window_set_background_color(mainWindow, GColorBlack);
  
  ///////////////Set up Time//////////////////////////
  //set text layer
  timeLayer = text_layer_create(GRect(2,34, 130, 44));
  //set colors
  text_layer_set_background_color(timeLayer, GColorClear);
  text_layer_set_text_color(timeLayer, GColorWhite);
  //set fonts
  text_layer_set_font(timeLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(timeLayer, GTextAlignmentLeft);
  
  //add to screen
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(timeLayer));

  /////////////Set up Date/////////////////////////////////
  //create the text layer
  dateLayer = text_layer_create(GRect(2, 78, 130, 32));
  //set colors
  text_layer_set_background_color(dateLayer, GColorClear);
  text_layer_set_text_color(dateLayer, GColorWhite);
  //set fonts
  text_layer_set_font(dateLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(dateLayer, GTextAlignmentLeft);
  
  //add to screen
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(dateLayer));
  
  /////////////Set up Day/////////////////////////////////////
  //create text layer
  dayLayer = text_layer_create(GRect(2,2, 130,32));
  //set colors
  text_layer_set_background_color(dayLayer, GColorClear);
  text_layer_set_text_color(dayLayer, GColorWhite);
  //set fonts
  text_layer_set_font(dayLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(dayLayer, GTextAlignmentLeft);
  
  //add to screen
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(dayLayer));
  
  ///////////Battery Levels//////////////////////////////////////
  //create lines
  batteryLevelTop = layer_create(GRect(2, 115, 144, 5));
  batteryLevelMiddle = layer_create(GRect(2, 120, 144, 8));
  batteryLevelBottom = layer_create(GRect(2, 128, 144, 5));

  //add to window
  layer_add_child(window_get_root_layer(mainWindow), batteryLevelTop);
  layer_add_child(window_get_root_layer(mainWindow), batteryLevelMiddle);
  layer_add_child(window_get_root_layer(mainWindow), batteryLevelBottom);
  
  //functions that will do the drawing
  layer_set_update_proc(batteryLevelTop, updateBatteryLevelEdges);
  layer_set_update_proc(batteryLevelMiddle, updateBatteryLevelMiddle);
  layer_set_update_proc(batteryLevelBottom, updateBatteryLevelEdges);

}

static void mainWindowDeinit(Window *window){
  //deallocate layers 
  text_layer_destroy(timeLayer);
  text_layer_destroy(dateLayer);
  text_layer_destroy(dayLayer);
}







static void battery_handler(BatteryChargeState charge_state) {
  
}



static void init(){
  ///////////////Set up window//////////////////////////////
  //Create the window
  mainWindow = window_create();
  
  //set handlers
  window_set_window_handlers(mainWindow, (WindowHandlers){
    .load = mainWindowInit,
    .unload = mainWindowDeinit
  });
  
  //set to show
  window_stack_push(mainWindow, true);

  //////////////Set up time///////////////////////////////
  //set up time service
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Set to show time
  updateTime();
}

static void deinit(){
  //destorys window
  window_destroy(mainWindow);
}

int main(void){
  init();
  app_event_loop();
  deinit();
}