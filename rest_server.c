#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "rest_server.h"

typedef struct __REST_HANDLER {
  char *tag;
  //REST_HANDLER_FN *fn;
  struct __REST_HANDLER *next;
} REST_HANDLER;

static struct MHD_Daemon * rest_server_daemon = NULL;

static REST_HANDLER *handlers = NULL;

static int rest_parse( const char *url ) {
  REST_HANDLER *h = handlers;
  while (( h != NULL ) && ( strncmp( h->tag, url, strlen( h->tag ) ) != 0 )) { 
     h = h->next;
  }
  if ( h != NULL ) {
    printf("Detected: %s\n", h->tag);
    return 0;
  } else {
    return 1;
  }
}

static int rest_handler(void * cls,
        struct MHD_Connection * connection,
        const char * url,
        const char * method,
        const char * version,
        const char * upload_data,
        size_t * upload_data_size,
        void ** ptr) {
  static int dummy;

  struct MHD_Response * response;
  int ret;
  if (0 != strcmp(method, "GET"))
    return MHD_NO; /* unexpected method */
  if (0 != *upload_data_size)
    return MHD_NO; /* upload data in a GET!? */
  if (&dummy != *ptr) {
      /* The first time only the headers are valid,
         do not respond in the first round... */
      *ptr = &dummy;
      return MHD_YES;
  }

  if ( rest_parse( url ) == 0 ) {

  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_buffer (strlen("HOI"),
                                              (void*) "HOI",
                  MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection,
         MHD_HTTP_OK,
         response);
  MHD_destroy_response(response);
  } else {
    ret = MHD_NO;
  }
  return ret;
}

REST_SERVER_RESULT add_rest_server_handler( const char *tag ) {
  REST_SERVER_RESULT result = REST_SERVER_ERROR;
  REST_HANDLER *handler = malloc(sizeof( REST_HANDLER ));

  if ( handler != NULL ) {

    printf("Add handler for %s\n", tag);
    handler->tag = malloc(strlen(tag) + 2);
    if ( handler->tag != NULL ) {
      strcpy( handler->tag, tag );
      strcat( handler->tag, "/");
      handler->next = handlers;
      handlers = handler;
      printf("Handlers = %p\n", handlers);
      result = REST_SERVER_OK;
    } else {
      free( handler );
    }
  }

  return result;
}


REST_SERVER_RESULT remove_rest_server_handlers( void ) {
  REST_HANDLER *handler = handlers;
  while ( handler != NULL ) {
    handlers = handlers->next;
    free( handler->tag );
    free( handler );
    handler = handlers;
  }
  return REST_SERVER_OK;
}

REST_SERVER_RESULT start_rest_server(unsigned short port) {
  REST_SERVER_RESULT result = REST_SERVER_ERROR;
  if ( rest_server_daemon == NULL ) {
    rest_server_daemon =  MHD_start_daemon( 
        MHD_USE_THREAD_PER_CONNECTION,
        port,
        NULL,
        NULL,
        &rest_handler,
        NULL,
        MHD_OPTION_END);
    if ( rest_server_daemon != NULL ) result = REST_SERVER_OK;
  }
  return result;
}

REST_SERVER_RESULT stop_rest_server( void ) {
  REST_SERVER_RESULT result = REST_SERVER_ERROR;
  if ( rest_server_daemon != NULL ) {
    MHD_stop_daemon( rest_server_daemon );
    rest_server_daemon = NULL;
    result = REST_SERVER_OK;
  }
  return result;
}
