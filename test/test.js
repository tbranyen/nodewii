var wii = require( '../build/default/nodewii.node' );

var wiimote = new wii.WiiMote();

wiimote.connect( '00:17:AB:39:42:B1', function( err ) {
  wiimote.rumble( true );

  setTimeout(function() {
    wiimote.rumble( false );

    //wiimote.led(1, true); // turns 1 on
    //wiimote.led(2, true); // turns 2 on
    //wiimote.led(3, true); // turns 1 and 2 on 
    //wiimote.led(4, true); // turns 3 on
    //wiimote.led(5, true); // turns 1 and 3 on
    //wiimote.led(6, true); // turns 2 and 3 on
    //wiimote.led(7, true); // turns 1 and 2 and 3 on
    //wiimote.led(8, true); // turns 4 on

    wiimote.led(1, true);
    wiimote.led(3, true);
    

    setTimeout(function() {
      wiimote.led(1, false);
      wiimote.led(3, false);
      
      wiimote.led(2, true);
      wiimote.led(4, true);
     // console.log( wiimote.led(5, true) );
      wiimote.rumble( true );
    }, 1000);

  }, 1000);
});
