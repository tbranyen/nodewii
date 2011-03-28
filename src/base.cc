/*
Copyright (c) 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
*/

#include <v8.h>
#include <node.h>
#include <node_events.h>

#include "../include/wiimote.h"

extern "C" void init(Handle<v8::Object> target) {
  HandleScope scope;

  WiiMote::Initialize(target);
}
