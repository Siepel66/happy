typedef enum __WGET_SWITCH_RESULT {
  WGET_SWITCH_RESULT_OK = 0,
	WGET_SWITCH_RESULT_ERROR
} WGET_SWITCH_RESULT;

typedef enum __WGET_SWITCH_REQUEST {
	WGET_SWITCH_REQUEST_OFF = 0,
	WGET_SWITCH_REQUEST_ON  = 1
} WGET_SWITCH_REQUEST;

typedef enum __WGET_SWITCH_STATE {
	WGET_SWITCH_STATE_OFF = 0,
	WGET_SWITCH_STATE_ON = 1,
	WGET_SWITCH_STATE_UNKNOWN
} WGET_SWITCH_STATE;

typedef struct __WGET_SWITCH {
    char *server;
    unsigned int port;
    unsigned int io;
		WGET_SWITCH_STATE state;

    WGET_SWITCH_RESULT (*on) (struct __WGET_SWITCH *self);
    WGET_SWITCH_RESULT (*off) (struct __WGET_SWITCH *self);
} WGET_SWITCH;

WGET_SWITCH_RESULT wget_switch_init(struct __WGET_SWITCH *self, char *server, unsigned int port, unsigned int io);
