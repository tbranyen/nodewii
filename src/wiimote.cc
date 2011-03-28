/*
 * Copyright 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
 * Dual licensed under the MIT and GPL licenses.
 */

#include <v8.h>
#include <node.h>
#include <node_events.h>

#include <node.h>
#include <node_events.h>

#include <bluetooth/bluetooth.h>
#include "../vendor/cwiid/libcwiid/cwiid.h"

#include "../include/wiimote.h"

using namespace v8;
using namespace node;

void WiiMote::Initialize (Handle<v8::Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("WiiMote"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "connect", Connect);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "rumble", Rumble);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "led", Led);

  target->Set(String::NewSymbol("WiiMote"), constructor_template->GetFunction());
}

int WiiMote::Connect(const char* mac) {
  str2ba(mac, &this->mac);

  if(!(this->wiimote = cwiid_open(&this->mac, 0))) {
    return -1;
  }

  return 0;
}

int WiiMote::Rumble(bool on) {
  unsigned char rumble = on ? 1 : 0;

  if(cwiid_set_rumble(this->wiimote, rumble)) {
    return -1;
  }
  
  return 0;
}

int WiiMote::Led(int index, bool on) {
  int indexes[] = { 1, 2, 4, 8 };

  cwiid_get_state(this->wiimote, &this->state);

  int led = this->state.led;

  led = on ? led | indexes[index-1] : led & indexes[index-1];

  if(cwiid_set_led(this->wiimote, led)) {
    return -1;
  }

  return 0;
}

Handle<Value> WiiMote::New(const Arguments& args) {
  HandleScope scope;

  WiiMote* wiimote = new WiiMote();
  wiimote->Wrap(args.This());

  return args.This();
}

Handle<Value> WiiMote::Connect(const Arguments& args) {
  WiiMote* wiimote = ObjectWrap::Unwrap<WiiMote>(args.This());
  Local<Function> callback;

  HandleScope scope;

  if(args.Length() == 0 || !args[0]->IsString()) {
    return ThrowException(Exception::Error(String::New("MAC address is required and must be a String.")));
  }

  if(args.Length() == 1 || !args[1]->IsFunction()) {
    return ThrowException(Exception::Error(String::New("Callback is required and must be a Function.")));
  }

  callback = Local<Function>::Cast(args[1]);

  connect_request* ar = new connect_request();
  ar->wiimote = wiimote;

  String::Utf8Value mac(args[0]);
  ar->mac = *mac;
  ar->callback = Persistent<Function>::New(callback);

  wiimote->Ref();

  eio_custom(EIO_Connect, EIO_PRI_DEFAULT, EIO_AfterConnect, ar);
  ev_ref(EV_DEFAULT_UC);

  return Undefined();
}

int WiiMote::EIO_Connect(eio_req* req) {
  connect_request* ar = static_cast<connect_request* >(req->data);

  ar->err = ar->wiimote->Connect(ar->mac);

  return 0;
}

int WiiMote::EIO_AfterConnect(eio_req* req) {
  HandleScope scope;

  connect_request* ar = static_cast<connect_request* >(req->data);
  ev_unref(EV_DEFAULT_UC);
  ar->wiimote->Unref();

  Local<Value> argv[1];
  argv[0] = Integer::New(ar->err);

  TryCatch try_catch;

  ar->callback->Call(Context::GetCurrent()->Global(), 1, argv);

  if(try_catch.HasCaught())
    FatalException(try_catch);
    
  ar->callback.Dispose();

  delete ar;

  return 0;
}

Handle<Value> WiiMote::Rumble(const Arguments& args) {
  HandleScope scope;

  WiiMote* wiimote = ObjectWrap::Unwrap<WiiMote>(args.This());

  if(args.Length() == 0 || !args[0]->IsBoolean()) {
    return ThrowException(Exception::Error(String::New("On state is required and must be a Boolean.")));
  }

  bool on = args[0]->ToBoolean()->Value();

  return Integer::New(wiimote->Rumble(on));
}

Handle<Value> WiiMote::Led(const Arguments& args) {
  HandleScope scope;

  WiiMote* wiimote = ObjectWrap::Unwrap<WiiMote>(args.This());

  if(args.Length() == 0 || !args[0]->IsNumber()) {
    return ThrowException(Exception::Error(String::New("Index is required and must be a Number.")));
  }

  if(args.Length() == 1 || !args[1]->IsBoolean()) {
    return ThrowException(Exception::Error(String::New("On state is required and must be a Boolean.")));
  }

  int index = args[0]->ToInteger()->Value();
  bool on = args[1]->ToBoolean()->Value();

  return Integer::New(wiimote->Led(index, on));
}

Persistent<FunctionTemplate> WiiMote::constructor_template;
