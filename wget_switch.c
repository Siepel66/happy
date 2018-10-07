#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "happy.h"
#include "switch.h"
#include "wget.h"
#include "wget_switch.h"

#define STATE_STRING  "\"state\":"

static HAPPY_RESULT wget_switch_get( void *self, SWITCH_STATE *status ) {
  WGET_SWITCH *thisSwitch = (WGET_SWITCH *) self;
  char *req = NULL;
  HAPPY_RESULT result = HAPPY_RESULT_ERROR;
  static const char pcIoTemplate[]="/control?cmd=Status,GPIO,%d";
  char buf[2048];
  char *state = NULL;

  req = calloc( 1, strlen( pcIoTemplate ) + 5);
  if (req != NULL) {
    sprintf( req, pcIoTemplate, thisSwitch->io);
    memset(buf, 0, 2048);
    if (wget( thisSwitch->server, thisSwitch->port, req, 2048 , buf ) == HAPPY_RESULT_OK ) {
      result = HAPPY_RESULT_OK;
      DEBUG(("Result : %s\n", buf));
      state = strstr(buf, STATE_STRING );
      if (state != NULL) {
        state += sizeof(STATE_STRING);
        DEBUG(("State: %c\n", *state));
        if (*state == '1') thisSwitch->state = SWITCH_STATE_ON; else thisSwitch->state = SWITCH_STATE_OFF;
      } else {
        thisSwitch->state = SWITCH_STATE_UNKNOWN;
      }
      if (status != NULL)  *status = thisSwitch->state;
    }
    free( req );
  }
  DEBUG(( "Result state: %d\n", thisSwitch->state));
  return result;
}

static HAPPY_RESULT wget_switch_set( void *self, SWITCH_STATE switch_req ) {
    WGET_SWITCH *thisSwitch = (WGET_SWITCH *) self;
    char *req = NULL;
    HAPPY_RESULT result = HAPPY_RESULT_ERROR;
    static const char pcIoTemplate[]="/control?cmd=GPIO,%d,%d";

    req = calloc( 1, strlen( pcIoTemplate ) + 5);
    if (req != NULL) {
    	sprintf( req, pcIoTemplate, thisSwitch->io, switch_req == SWITCH_STATE_OFF ? 0 : 1 );
      if (wget( thisSwitch->server, thisSwitch->port, req, 0 , NULL ) == HAPPY_RESULT_OK ) {
        result = HAPPY_RESULT_OK;
        thisSwitch->state = switch_req;
      }
      free( req );
    }
    return result;
}

static HAPPY_RESULT wget_switch_on( void *self ) {
   WGET_SWITCH *thisSwitch = (WGET_SWITCH *) self;
	 return wget_switch_set( thisSwitch, SWITCH_STATE_ON );
}
static HAPPY_RESULT wget_switch_off( void *self ) {
   WGET_SWITCH *thisSwitch = (WGET_SWITCH *) self;
	 return wget_switch_set( thisSwitch, SWITCH_STATE_OFF );
}

HAPPY_RESULT wget_switch_init( void *self, char *server, unsigned int port, unsigned int io ) {
  WGET_SWITCH *thisSwitch = (WGET_SWITCH *) self;

	thisSwitch->server = server;
	thisSwitch->port = port;
	thisSwitch->io = io;
  thisSwitch->state = SWITCH_STATE_UNKNOWN;

	thisSwitch->on = wget_switch_on;
	thisSwitch->off = wget_switch_off;

	return wget_switch_get(self, NULL );
}
