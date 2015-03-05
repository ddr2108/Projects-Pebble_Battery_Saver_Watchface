#include <pebble.h>
 
//Layers
static Window *mainWindow;
static TextLayer *timeLayer;
static TextLayer *dateLayer;
static TextLayer *dayLayer;
static TextLayer *weatherLayer;

static Layer *batteryLevelTop;
static Layer *batteryLevelMiddle;
static Layer *batteryLevelBottom;

static Layer *s_canvas_layer;

static void updateBatteryLevelEdges(Layer *layer, GContext *ctx) {
  //get the size
  GRect bounds = layer_get_bounds(layer);

  // Draw the line
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void updateBatteryLevelMiddle(Layer *layer, GContext *ctx) {
  //get the size
  GRect bounds = layer_get_bounds(layer);

  // Draw the line
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

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

static void updateTime(){
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

static void initStandby(){
  
  //check if it should be in standby at inital turn on of face
  
}

bool standbyFlag = false;
static void standby(){
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

static void showWeather(){
  
  
}

static void hideWeather(){
  
  
}

static void battery_handler(BatteryChargeState charge_state) {
  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  //check if should be in standby
  standby();
  
  //update the time
  if (standbyFlag==false){
    updateTime();
  }
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