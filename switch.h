
typedef enum __SWITCH_RESULT {
    SWITCH_RESULT_OK = 0,
    SWITCH_RESULT_ERROR
} SWITCH_RESULT;

typedef enum __SWITCH_TYPE {
	SWITCH_TYPE_WGET = 0
} SWITCH_TYPE;

typedef struct __SWITCHES {
	const char *name;
	int id;
	SWITCH_TYPE type;
	void *mySwitch;
	struct __SWITCHES *next;
} SWITCHES;

SWITCHES *switch_getByID(int id);
SWITCH_RESULT switch_addNew(const char *name, int id, SWITCH_TYPE type, void *mySwitch);
