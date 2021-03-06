Node.js libcwiid bindings
=======================

Created by Tim Branyen [@tbranyen](http://twitter.com/tbranyen)

Currently under active development (and seeking contributors), nodewii
provides asynchronous native bindings to the libcwiid C API.

Building and installing
-----------------------

### Dependencies ###
To run nodewii you need Node.js, bluez, and libcwiid installed. To run
unit tests you will need to have git installed and accessible from your
PATH to fetch any vendor/ addons. 

It is sufficient enough to rely on the system package manager to install
libcwiid and bluez.  Refer to your distros repository search to find the
correct module names and installation procedure.

### In action ###
nodewii was implemented at JSconf 2011 for Mary Rose Cook's game Pistol Slut.
You can see the pull request here for how it was implemented:

[https://github.com/maryrosecook/pistolslut/pull/1](https://github.com/maryrosecook/pistolslut/pull/1)

Video demo: [http://vimeo.com/23224874](http://vimeo.com/23224874)

### Linux/Unix ###

Install nodewii by cloning source from __GitHub__ and running the
configure, make, and make install commands:

Note: nodewii assumes your library path exists at ~/.node_libraries you
can change this by specifying a new path
    
``` bash
$ git clone git://github.com/tbranyen/nodewii.git
$ cd nodewii

$ ./configure
$ make
$ make install

$ make install NODE_LIB_PATH=/path/to/your/libraries
```

*Updating to a new version*

``` bash
$ make update

$ make update NODE_LIB_PATH=/path/to/your/libraries
```

### Apple OS X/Windows via Cygwin ###
nodewii currently does not run on either Mac OS X or Windows machines.  This
is a problem with `libcwiid`.  A future plan is to fork `libcwiid` and write
support for at least Apple OS X.


API Example Usage
-----------------

### Connecting and enabling features ###

#### Raw API ####

``` javascript
var wii = require("nodewii");
var wiimote = new wii.WiiMote();

// You need to specify a mac address to your wiimote, this is unique per wiimote
wiimote.connect("00:00:00:00:00", function(err) {
  // Enable rumble
  wiimote.rumble(true);

  // Turn on led"s 1 and 3
  wiimote.led(1, true);
  wiimote.led(3, true);

  // Turn off led 3
  wiimote.led(3, false);

  // Get IR Data
  wiimote.ir(true);
  wiimote.on("ir", function(data) {
    var x = data[0];
    var y = data[1];

    console.log("Position", x, y);
  });
});
```

Release information
-------------------

### v0.0.1: ###
* Some useful methods implemented
* Partial examples in example directory

Getting involved
----------------

If you find this project of interest, please document all issues and fork if
you feel you can provide a patch.  
