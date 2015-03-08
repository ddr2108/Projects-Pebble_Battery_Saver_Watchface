  #pragma once
    
  //layers for displaying date and time
  extern TextLayer *timeLayer;
  extern TextLayer *dateLayer;
  extern TextLayer *dayLayer;
  
  //Functions for updating time
  void updateTime();
  void tick_handler(struct tm *tick_time, TimeUnits units_changed);