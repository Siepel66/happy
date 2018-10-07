#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>

#include "happy.h"
#include "switch.h"


#include "wget_switch.h"
#include "rest_server.h"



char *getItem(const char *items, char **next) {
	char *p = strchr(items, '/');
	char *item = NULL;

	if (p != NULL) {
		 printf("P: %s, %ld\n", p,  (p - items + 1) );
     item = calloc(1, (p - items + 1));
		 if ( item != NULL) memcpy(item, items, (p - items));
		 if (next != NULL) *next = p + 1;
	} else {
		if (strlen(items) > 0) {
			item = strdup(items);
		}
	}
	return item;
}


HAPPY_RESULT *flierp_handler(char *params) {
  char *id = params;
	char *command = NULL;
	SWITCHES *mySwitch;
	WGET_SWITCH *sw;

	printf("Hello world ! : %s\n", params);
	id = getItem(params, &command);
	if (id != NULL) {
		printf ("Item: %s \n", id);
		mySwitch = switch_getByID(atoi(id));
		printf ("P: %p, name: %s\n ", mySwitch, mySwitch != NULL ? mySwitch->name : "NULL");
			printf ("command: %s \n", command);
		command = getItem(command, NULL);
		if (command != NULL) {
			printf ("command: %s \n", command);
			sw = (WGET_SWITCH *) mySwitch->mySwitch;
			if (strcmp("on", command) == 0 ) {
				sw->on(sw);
			} else {
				sw->off(sw);
			}
			free(command);
		}
		free(id);
	}
}

int main(int argc, char **argv) {
	WGET_SWITCH myWgetSwitch;
	SWITCHES *mySwitch;

 	wget_switch_init(&myWgetSwitch, "192.168.2.150", 80, 12);
  switch_addNew("Lampie", 0, SWITCH_TYPE_WGET, (void *) &myWgetSwitch);

  mySwitch = switch_getByID(0);
	printf ("P: %p, name: %s\n ", mySwitch, mySwitch != NULL ? mySwitch->name : "NULL");
	mySwitch = switch_getByID(120);
	printf ("P: %p, name: %s\n ", mySwitch, mySwitch != NULL ? mySwitch->name : "NULL");


  //mySwitch.off(&mySwitch);
  //usleep(1000000);
  //mySwitch.on(&mySwitch);

  	if ( start_rest_server( 8888 ) == HAPPY_RESULT_OK ) {

        add_rest_server_handler( "/flierp", (REST_HANDLER_FN) flierp_handler);
		    add_rest_server_handler( "/TWEE", NULL );

        (void) getc (stdin);
        remove_rest_server_handlers();
        stop_rest_server();
  	}

}
