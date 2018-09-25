typedef enum __SWITCH_RESULT {
	SWITCH_OK = 0,
	SWITCH_ERROR
} SWITCH_RESULT;

typedef enum __SWITCH_REQUEST {
	SWITCH_OFF = 0,
	SWITCH_ON  = 1
} SWITCH_REQUEST;

typedef struct __WGET_SWITCH {
    char *server;
    unsigned int port;
    unsigned int io;

    SWITCH_RESULT (*on) (struct __WGET_SWITCH *self);
    SWITCH_RESULT (*off) (struct __WGET_SWITCH *self);
} WGET_SWITCH;

SWITCH_RESULT wget_switch_init(struct __WGET_SWITCH *self, char *server, unsigned int port, unsigned int io);

