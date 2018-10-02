

typedef enum __REST_SERVER_RESULT {
    REST_SERVER_OK = 0,
    REST_SERVER_ERROR
} REST_SERVER_RESULT;

typedef REST_SERVER_RESULT (*REST_HANDLER_FN)(const char *params);

REST_SERVER_RESULT start_rest_server(unsigned short port);

REST_SERVER_RESULT stop_rest_server( void );

REST_SERVER_RESULT add_rest_server_handler( const char *tag, REST_HANDLER_FN handler_fn);

REST_SERVER_RESULT remove_rest_server_handlers( void );
