#pragma once

  //layers for displaying battery level
  extern Layer *batteryLevelTop;
  extern Layer *batteryLevelMiddle;
  extern Layer *batteryLevelBottom;

  //Functions for displaying battery level
  void updateBatteryLevelMiddle(Layer *layer, GContext *ctx);
  void updateBatteryLevelEdges(Layer *layer, GContext *ctx);