#include <stdio.h>
#include <string.h>
#include <malloc.h>       

#include "wget.h"
#include "wget_switch.h"


static SWITCH_RESULT wget_switch_set( struct __WGET_SWITCH *self, SWITCH_REQUEST switch_req ) {
    char *req = NULL;
    SWITCH_RESULT result = SWITCH_ERROR;
    static const char pcIoTemplate[]="/control?cmd=GPIO,%d,%d";

    req = calloc( 1, strlen( pcIoTemplate ) + 5);
    if (req != NULL) {
    	sprintf( req, pcIoTemplate, self->io, switch_req == SWITCH_OFF ? 0 : 1 );
        if (wget( self->server, self->port, req, 0 , NULL ) == WGET_OK ) result = SWITCH_OK;
        free( req );
    } 
    return result;
}

static SWITCH_RESULT wget_switch_on( struct __WGET_SWITCH *self ) {
	 return wget_switch_set( self, SWITCH_ON );
}

static SWITCH_RESULT wget_switch_off( struct __WGET_SWITCH *self ) {
	 return wget_switch_set( self, SWITCH_OFF );
}

SWITCH_RESULT wget_switch_init( struct __WGET_SWITCH *self, char *server, unsigned int port, unsigned int io ) {
	self->server = server;
	self->port = port;
	self->io = io;
	
	self->on = wget_switch_on;
	self->off = wget_switch_off;

	return SWITCH_OK;
}