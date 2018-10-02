typedef enum __SWITCH_RESULT {
	SWITCH_RESULT_OK = 0,
	SWITCH_RESULT_ERROR
} SWITCH_RESULT;

typedef enum __SWITCH_REQUEST {
	SWITCH_REQUEST_OFF = 0,
	SWITCH_REQUEST_ON  = 1
} SWITCH_REQUEST;

typedef enum __SWITCH_STATE {
	SWITCH_STATE_OFF = 0,
	SWITCH_STATE_ON = 1,
	SWITCH_STATE_UNKNOWN
} SWITCH_STATE;

typedef struct __WGET_SWITCH {
    char *server;
    unsigned int port;
    unsigned int io;
		SWITCH_STATE state;

    SWITCH_RESULT (*on) (struct __WGET_SWITCH *self);
    SWITCH_RESULT (*off) (struct __WGET_SWITCH *self);
} WGET_SWITCH;

SWITCH_RESULT wget_switch_init(struct __WGET_SWITCH *self, char *server, unsigned int port, unsigned int io);
