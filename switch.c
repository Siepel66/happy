
#include <malloc.h>
#include "happy.h"
#include "switch.h"

static SWITCHES *switches = NULL;

SWITCHES *switch_getByID(int id) {
	SWITCHES *mySwitch = switches;
	while ((mySwitch != NULL) && (mySwitch->id != id)) mySwitch = mySwitch->next;
	return mySwitch;
}

HAPPY_RESULT switch_addNew(const char *name, int id, SWITCH_TYPE type, void *mySwitch) {
	HAPPY_RESULT result = HAPPY_RESULT_ERROR;
  SWITCHES *newSwitch = calloc(1, sizeof(SWITCHES));

  if (newSwitch != NULL) {
		newSwitch->name = name;
		newSwitch->id = id;
	  newSwitch->type = type;
		newSwitch->mySwitch = mySwitch;
		newSwitch->next = switches;
		switches = newSwitch;
		result = HAPPY_RESULT_OK;
	}

	return result;
}

HAPPY_RESULT switch_setState(void *self, SWITCH_STATE newState) {
  SWITCHES *thisSwitch = (SWITCHES *) self;

  return thisSwitch->mySwitch->on(self);
}
