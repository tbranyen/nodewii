/*
Copyright (c) 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
*/

#include <v8.h>
#include <node.h>
#include <node_events.h>

#include "../vendor/libgit2/include/git2.h"

#include "../include/connect.h"

extern "C" void init(Handle<v8::Object> target) {
  HandleScope scope;

  Connect::Initialize(target);
}
