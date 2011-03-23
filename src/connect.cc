/*
 * Copyright 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
 * Dual licensed under the MIT and GPL licenses.
 */

#ifndef ERROR_H
#define ERROR_H

#include <node.h>
#include <node_events.h>

#include <bluetooth/bluetooth.h>
#include "../vendor/cwiid/libcwiid/cwiid.h"

using namespace node;

namespace {
  /**
   * Class: WiiConnect
   *   Wrapper for libcwiid connect.
   */
  class WiiConnect : public EventEmitter {
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
       * Function: StrError
       *   Get a read-only buffer with the raw content of a blob.
       *
       * Parameters:
       *   err - A signed int error code
       *
       * Returns:
       *   a string explaining the error code.
       */
      const char* StrError(int err);

    protected:
      /**
       * Constructor: GitBlob
       */
      GitError() {};
      /**
       * Deconstructor: GitBlob
       */
      ~GitError() {};
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
       * Function: StrError
       *
       * Parameters:
       *   args v8::Arguments function call
       *
       * Returns:
       *   v8::Object args.This()
       */
      static v8::Handle<v8::Value> StrError(const v8::Arguments& args);
  };
}

#endif
