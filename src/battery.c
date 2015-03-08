  #include <pebble.h>
  #include "battery.h"
  
  Layer *batteryLevelTop = NULL;
  Layer *batteryLevelMiddle = NULL;
  Layer *batteryLevelBottom = NULL;

  /**************************************************
  * updateBatteryLevelEdges
  * updates the battery level line on top and bottom
  *
  * Parameters:
  *   Layer *layer - layer holding the line
  *   GContext *ctx - context holding line
  * Returns:
  *   none
  ***************************************************/
  void updateBatteryLevelEdges(Layer *layer, GContext *ctx) {
    //get the size
    GRect bounds = layer_get_bounds(layer);
  
    // Draw the line
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  }
  
  /**************************************************
  * updateBatteryLevelMiddle
  * updates the battery level line on middle
  *
  * Parameters:
  *   Layer *layer - layer holding the line
  *   GContext *ctx - context holding line
  * Returns:
  *   none
  ***************************************************/
  void updateBatteryLevelMiddle(Layer *layer, GContext *ctx) {
    //get the size
    GRect bounds = layer_get_bounds(layer);
  
    // Draw the line
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  }

  /**************************************************
  * battery_handler
  * handle changes in battery life
  *
  * Parameters:
  *   BatteryChargeState charge_state - charge state
  * Returns:
  *   none
  ***************************************************/
  void battery_handler(BatteryChargeState charge_state) {
    
  }