

typedef HAPPY_RESULT (*REST_HANDLER_FN)(const char *params);

HAPPY_RESULT start_rest_server(unsigned short port);

HAPPY_RESULT stop_rest_server( void );

HAPPY_RESULT add_rest_server_handler( const char *tag, REST_HANDLER_FN handler_fn);

HAPPY_RESULT remove_rest_server_handlers( void );
