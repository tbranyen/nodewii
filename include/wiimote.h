/*
 * Copyright 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
 * Dual licensed under the MIT and GPL licenses.
 */

#ifndef CONNECT_H
#define CONNECT_H

#include <node.h>
#include <node_events.h>

#include <bluetooth/bluetooth.h>
#include "../vendor/cwiid/libcwiid/cwiid.h"

using namespace v8;
using namespace node;

/**
 * Class: WiiMote
 *   Wrapper for libcwiid connect.
 */
class WiiMote : public EventEmitter {
  public:
    /**
     * Variable: ir_event
     *   Used to dispatch infrared event.
     */
    static v8::Persistent<v8::String> ir_event;
    /**
     * Variable: acc_event
     *   Used to dispatch accelerometer event.
     */
    static v8::Persistent<v8::String> acc_event;
    /**
     * Variable: nunchuk_event
     *   Used to dispatch nunchuk extension event.
     */
    static v8::Persistent<v8::String> nunchuk_event;
    /**
     * Variable: buttondown_event
     *   Used to dispatch buttondown event.
     */
    static v8::Persistent<v8::String> buttondown_event;
    /**
     * Variable: buttonup_event
     *   Used to dispatch buttonup event.
     */
    static v8::Persistent<v8::String> buttonup_event;
    /**
     * Variable: error_event
     *   Used to dispatch error event.
     */
    static v8::Persistent<v8::String> error_event;
    /**
     * Variable: constructor_template
     *   Used to create Node.js constructor.
     */
    static v8::Persistent<v8::FunctionTemplate> constructor_template;
    /**
     * Function: Initialize
     *   Used to intialize the EventEmitter from Node.js
     *
     * Parameters:
     *   target - v8::Object the Node.js global module object
     */
    static void Initialize(v8::Handle<v8::Object> target);
    /**
     * Function: Connect
     *   Accepts an address and creates a connection.
     *
     * Returns:
     *   a string explaining the error code.
     */
    int Connect(const char* mac);
    int Rumble(bool on);
    int Led(int index, bool on);
    int IrReporting(bool on);
    int AccReporting(bool on);
    int ExtReporting(bool on);
    int ButtonReporting(bool on);
    int WatchMessages();

  protected:
    /**
     * Constructor: WiiMote
     */
    WiiMote() {};
    /**
     * Deconstructor: WiiMote
     */
    ~WiiMote() {};
    /**
     * Function: New
     *
     * Parameters:
     *   args v8::Arguments function call
     *
     * Returns:
     *   v8::Object args.This()
     */
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    /**
     * Function: Connect
     *
     * Parameters:
     *   args v8::Arguments function call
     *
     * Returns:
     *   v8::Object args.This()
     */
    static v8::Handle<v8::Value> Connect(const v8::Arguments& args);
    static int EIO_Connect(eio_req* req);
    static int EIO_AfterConnect(eio_req* req);

    static void TriggerMessages(EV_P_ ev_timer *watcher, int revents);

    static v8::Handle<v8::Value> Rumble(const v8::Arguments& args);
    static v8::Handle<v8::Value> Led(const v8::Arguments& args);
    static v8::Handle<v8::Value> IrReporting(const v8::Arguments& args);
    static v8::Handle<v8::Value> AccReporting(const v8::Arguments& args);
    static v8::Handle<v8::Value> ExtReporting(const v8::Arguments& args);
    static v8::Handle<v8::Value> ButtonReporting(const v8::Arguments& args);
  private:
    /**
     * Variable: wiimote
     *   Pointer to a wiimote handle
     */
    cwiid_wiimote_t* wiimote;
    /**
     * Variable: state
     *   struct representing a wiimote state
     */
    struct cwiid_state state;
    /**
     * Variable: address
     *   bluetooth address value
     */
    bdaddr_t mac;
    /**
     * Variable: msg_timer
     *   libev timer struct
     */
    ev_timer msg_timer;
    /**
     * Variable: button
     *   button identifier
     */
    int button;

    struct connect_request {
      WiiMote* wiimote;
      const char* mac;
      int err;
      v8::Persistent<v8::Function> callback;
    };
};

#endif
