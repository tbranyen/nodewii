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

    static v8::Handle<v8::Value> Rumble(const v8::Arguments& args);
    static v8::Handle<v8::Value> Led(const v8::Arguments& args);
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

    struct connect_request {
      WiiMote* wiimote;
      const char* mac;
      int err;
      v8::Persistent<v8::Function> callback;
    };

};

#endif
