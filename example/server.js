var wii = require( '../build/default/nodewii.node' ),
    app = require( 'express' ).createServer(),
    io = require( 'socket.io' ),
    wiimote = new wii.WiiMote();

var clients = {
  lookup: function( key ) {
    var key;
    Object.keys( clients ).forEach( function( e ) {
      if( clients[e] === key ) {
        key = e;
        return false;
      }
    });

    return key;
  },
  all: function() {
    var _ = [];
    Object.keys( clients ).forEach( function( e ) {
      if( typeof clients[e] !== 'function' ) {
        _.push( e );
      }
    });

    return _;
  }
};

function sendAll( name, args ) {
  args.method = name;

  clients.all().forEach(function( e ) {
    clients[e].socket.send( args );
  });
}

var socket = io.listen( app );


console.log( 'Put wiimote in discoverable mode...' );
wiimote.connect( '00:17:AB:39:42:B1', function( err ) {
  if( err ) { console.log( 'Could not establish connection'); return; }
  console.log('connected');

  //wiimote.rumble( true );

  //setTimeout(function() {
  //  wiimote.rumble( false );

  //  wiimote.led(1, true);
  //  wiimote.led(3, true);

  //  setTimeout(function() {
  //    wiimote.led(1, false);
  //    wiimote.led(3, false);
  //    
  //    wiimote.led(2, true);
  //    wiimote.led(4, true);
  //  }, 50);

  //}, 50);


  wiimote.ir( true );
  
  // Wait for infrared data
  var bit = 0, prev = [];
  wiimote.on( 'ir', function( err, data ) {

    if(data[0] !== 0 && data[1] !== 0 && bit < 1) {
      bit += 1;
      prev = data;
      //data[0] = ( data[0] * -1 ) + 500;
    }
    else if(data[0] !== 0 && data[1] !== 0 && bit === 1) {
      //data[0] = (data[0]+prev[0]) / 2;
      //data[0] = ( data[0] * -1 ) + 500;

      //data[1] = (data[1]+prev[1]) / 2;
      console.log( data );
      sendAll( 'ir', { data: data } );
      bit += 1;
    }
    else {
      bit = 0;
    }
  });

  //wiimote.ext( true );
  //wiimote.on( 'nunchuk', function( err, data ) {
  //  if( err ) { return; }

  //  sendAll( 'nunchuk', { data: data } );
  //});

  wiimote.on( 'accelerometer', function( err, data ) {
    console.log( data );
  });

  socket.on( 'connection', function( socket ) {
    wiimote.rumble( true );
    wiimote.led( 1, true );

    setTimeout(function() {
      wiimote.rumble( false );
    }, 500);

    var uuid = socket.sessionId;

    var client = clients[ uuid ] = { socket: socket };

    function send( name, args ) {
      args.method = name;
      socket.send( args );
    }

    send( 'uuid', { uuid: uuid } );

    socket.on( 'message', function( e ) {
      var actions = {
        // Some action
      };

      return function( e ) {
        e.method && e.method in actions && actions[ e.method ]( e );
      };
    }());

    socket.on( 'disconnect', function( socket ) {
      delete clients[ clients.lookup( socket ) ];
    });
  });

  app.listen( 8888 );

});
