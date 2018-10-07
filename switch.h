
typedef enum __SWITCH_TYPE {
	SWITCH_TYPE_WGET = 0
} SWITCH_TYPE;

typedef enum __SWITCH_STATE {
  SWITCH_STATE_OFF = 0,
  SWITCH_STATE_ON = 1,
  SWITCH_STATE_UNKNOWN
} SWITCH_STATE;

typedef struct __SWITCHES {
	const char *name;
	int id;
	SWITCH_TYPE type;
	void *mySwitch;
	struct __SWITCHES *next;
} SWITCHES;

SWITCHES *switch_getByID(int id);
HAPPY_RESULT switch_addNew(const char *name, int id, SWITCH_TYPE type, void *mySwitch);
