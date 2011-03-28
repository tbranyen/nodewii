Node.js libcwiid bindings
=======================

Created by Tim Branyen [@tbranyen](http://twitter.com/tbranyen)

Currently under active development (and seeking contributors), `nodewii` provides asynchronous native bindings to the `libcwiid` C API.

Building and installing
-----------------------

### Dependancies ###
To run `nodewii` you need `Node.js`, `bluez`, and `libcwiid` installed. To run unit tests you will need to have `git` installed and accessible from your `PATH` to fetch any `vendor/` addons. 

### Easy install (Recommended) ###
This will install and configure everything you need to use `nodewii`.

    $ sudo npm install nodewii

### Mac OS X/Linux/Unix ###

#### Install `nodewii` by cloning source from __GitHub__ and running the `configure`, `make`, and `make install` commands: ####
\*Note: `nodewii` assumes your library path exists at `~/.node_libraries` you can change this by specifying a new path\*
    
    $ git clone git://github.com/tbranyen/nodewii.git
    $ cd nodewii

    $ ./configure
    $ make
    $ make install
    
    $ make install NODE_LIB_PATH=/path/to/your/libraries

\*Updating to a new version\*

    $ make update

    $ make update NODE_LIB_PATH=/path/to/your/libraries

### Windows via Cygwin ###

#### `nodewii` installs cleanly using the same build process as above, assuming you followed the `Node.js` Windows instructions. ####

Instructions on compiling `Node.js` on a Windows platform can be found here:
[https://github.com/ry/node/wiki/Building-node.js-on-Cygwin-(Windows)](https://github.com/ry/node/wiki/Building-node.js-on-Cygwin-(Windows\))

API Example Usage
-----------------

### Connecting and enabling features ###

#### Convenience API ####

    var wii = require( 'nodewii' );

    wii.mote( '00:00:00:00:00', function( err, wiimote ) {

      this.rumble( true );

      this.led( 1, true );
      this.led( 3, true );

      this.led( 3, false );

    });

#### Raw API ####

    var wii = require( 'nodewii' ).raw;

    var wiimote = new wii.WiiMote();

    wiimote.connect( '00:00:00:00:00', function( err ) {

      wiimote.rumble( true );

      wiimote.led( 1, true );
      wiimote.led( 3, true );

      wiimote.led( 3, false );

    });
    


Running tests
-------------

__ `nodewii` library code is written adhering to a modified `JSHint`. Run these checks with `make lint` in the project root. __

__ To run unit tests ensure the submodules `nodeunit` and `rimraf` are located in the `vendor/` subdirectory. __

If they are not, `cd` into the `nodewii` dir and run the following `git` commands to automatically fetch them:
    $ cd nodewii
    $ git submodule init vendor/
    $ git submodule update vendor/

Then simply run `make unittest` in the project root.

Release information
-------------------

### v0.0.1: ###
    * Some useful methods implemented

Getting involved
----------------

If you find this project of interest, please document all issues and fork if you feel you can provide a patch.  Testing is of huge importance; by simply running the unit tests on your system and reporting issues you can contribute!

__ Before submitting a pull request, please ensure both unit tests and lint checks pass. __
