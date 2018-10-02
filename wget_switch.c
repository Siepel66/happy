#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "wget.h"
#include "wget_switch.h"

//#define DEBUG(a) printf a
#define DEBUG(a)


#define STATE_STRING  "\"state\":"

static WGET_SWITCH_RESULT wget_switch_get( struct __WGET_SWITCH *self, WGET_SWITCH_STATE *status ) {
  char *req = NULL;
  WGET_SWITCH_RESULT result = WGET_SWITCH_RESULT_ERROR;
  static const char pcIoTemplate[]="/control?cmd=Status,GPIO,%d";
  char buf[2048];
  char *state = NULL;

  req = calloc( 1, strlen( pcIoTemplate ) + 5);
  if (req != NULL) {
    sprintf( req, pcIoTemplate, self->io);
    memset(buf, 0, 2048);
    if (wget( self->server, self->port, req, 2048 , buf ) == WGET_OK ) {
      result = WGET_SWITCH_RESULT_OK;
      DEBUG(("Result : %s\n", buf));
      state = strstr(buf, STATE_STRING );
      if (state != NULL) {
        state += sizeof(STATE_STRING);
        DEBUG(("State: %c\n", *state));
        if (*state == '1') self->state = WGET_SWITCH_STATE_ON; else self->state = WGET_SWITCH_STATE_OFF;
      } else {
        self->state = WGET_SWITCH_STATE_UNKNOWN;
      }
      if (status != NULL)  *status = self->state;
    }
    free( req );
  }
  DEBUG(( "Result state: %d\n", self->state));
  return result;
}

static WGET_SWITCH_RESULT wget_switch_set( struct __WGET_SWITCH *self, WGET_SWITCH_REQUEST switch_req ) {
    char *req = NULL;
    WGET_SWITCH_RESULT result = WGET_SWITCH_RESULT_ERROR;
    static const char pcIoTemplate[]="/control?cmd=GPIO,%d,%d";

    req = calloc( 1, strlen( pcIoTemplate ) + 5);
    if (req != NULL) {
    	sprintf( req, pcIoTemplate, self->io, switch_req == WGET_SWITCH_REQUEST_OFF ? 0 : 1 );
      if (wget( self->server, self->port, req, 0 , NULL ) == WGET_OK ) {
        result = WGET_SWITCH_RESULT_OK;
        switch (switch_req) {
          case WGET_SWITCH_REQUEST_ON:
            self->state = WGET_SWITCH_STATE_ON;
            break;
          case WGET_SWITCH_REQUEST_OFF:
            self->state = WGET_SWITCH_STATE_OFF;
            break;
          default:
            self->state = WGET_SWITCH_STATE_UNKNOWN;
        }
      }
      free( req );
    }
    return result;
}

static WGET_SWITCH_RESULT wget_switch_on( struct __WGET_SWITCH *self ) {
	 return wget_switch_set( self, WGET_SWITCH_REQUEST_ON );
}

static WGET_SWITCH_RESULT wget_switch_off( struct __WGET_SWITCH *self ) {
	 return wget_switch_set( self, WGET_SWITCH_REQUEST_OFF );
}

WGET_SWITCH_RESULT wget_switch_init( struct __WGET_SWITCH *self, char *server, unsigned int port, unsigned int io ) {
	self->server = server;
	self->port = port;
	self->io = io;
  self->state = WGET_SWITCH_STATE_UNKNOWN;

	self->on = wget_switch_on;
	self->off = wget_switch_off;

	return wget_switch_get(self, NULL );
}
