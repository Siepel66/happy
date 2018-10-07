typedef struct __WGET_SWITCH {
    char *server;
    unsigned int port;
    unsigned int io;
		SWITCH_STATE state;

    HAPPY_RESULT (*on) (void *self);
    HAPPY_RESULT (*off) (void *self);
} WGET_SWITCH;

HAPPY_RESULT wget_switch_init(void *self, char *server, unsigned int port, unsigned int io);
