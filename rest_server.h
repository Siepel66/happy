

typedef enum __REST_SERVER_RESULT {
    REST_SERVER_OK = 0,
    REST_SERVER_ERROR
} REST_SERVER_RESULT;

REST_SERVER_RESULT start_rest_server(unsigned short port);

REST_SERVER_RESULT stop_rest_server( void );