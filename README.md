Node.js libcwiid bindings
=======================

Created by Tim Branyen [@tbranyen](http://twitter.com/tbranyen)

Currently under active development (and seeking contributors), `nodewii` provides asynchronous native bindings to the `libcwiid` C API.

Building and installing
-----------------------

### Dependancies ###
To run `nodewii` you need `Node.js`, `bluez`, and `libcwiid` installed. To run unit tests you will need to have `git` installed and accessible from your `PATH` to fetch any `vendor/` addons. 

It is sufficient enough to rely on the system package manager to install libcwiid and bluez.  Refer to your distros repository search
to find the correct module names and installation procedure.

### Easy install (Recommended) ###
This will install and configure everything you need to use `nodewii`.

    $ sudo npm install nodewii

### Linux/Unix ###

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

### Apple OS X/Windows via Cygwin ###
`nodewii` currently does not run on either Mac OS X or Windows machines.  This is a problem with `libcwiid`.  A future plan is to
fork `libcwiid` and write support for at least Apple OS X.


API Example Usage
-----------------

### Connecting and enabling features ###

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

__`nodewii` library code is written adhering to a modified `JSHint`. Run these checks with `make lint` in the project root.__

Release information
-------------------

### v0.0.1: ###
    * Some useful methods implemented
    * Partial examples in example directory

Getting involved
----------------

If you find this project of interest, please document all issues and fork if you feel you can provide a patch.  Testing is of huge importance; by simply running the unit tests on your system and reporting issues you can contribute!

__Before submitting a pull request, please ensure lint checks pass.__
