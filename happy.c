#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>       
#include <unistd.h>
#include <stdlib.h>


#include "wget_switch.h"
#include "rest_server.h"



int main(int argc, char **argv) {
	WGET_SWITCH mySwitch;


 	wget_switch_init(&mySwitch, "192.168.2.150", 80, 12);
  	mySwitch.off(&mySwitch);
  	usleep(1000000);
  	mySwitch.on(&mySwitch);

  	if ( start_rest_server( 8888 ) == REST_SERVER_OK ) {

        add_rest_server_handler( "/flierp" );
		add_rest_server_handler( "/TWEE" );

        (void) getc (stdin);
        remove_rest_server_handlers();
        stop_rest_server();		
  	}

}

