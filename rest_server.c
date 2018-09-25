#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <string.h>

#include "rest_server.h"

static struct MHD_Daemon * rest_server_daemon = NULL;

// ====
#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo</body></html>"

static int ahc_echo(void * cls,
		    struct MHD_Connection * connection,
		    const char * url,
		    const char * method,
                    const char * version,
		    const char * upload_data,
		    size_t * upload_data_size,
                    void ** ptr) {
  static int dummy;
  const char * page = cls;
  struct MHD_Response * response;
  int ret;

  if (0 != strcmp(method, "GET"))
    return MHD_NO; /* unexpected method */
  if (&dummy != *ptr)
    {
      /* The first time only the headers are valid,
         do not respond in the first round... */
      *ptr = &dummy;
      return MHD_YES;
    }
  if (0 != *upload_data_size)
    return MHD_NO; /* upload data in a GET!? */
  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_buffer (strlen(page),
                                              (void*) page,
  					      MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection,
			   MHD_HTTP_OK,
			   response);
  MHD_destroy_response(response);
  return ret;
}

REST_SERVER_RESULT start_rest_server(unsigned short port) {

  REST_SERVER_RESULT result = REST_SERVER_ERROR;

  if ( rest_server_daemon == NULL ) {
    rest_server_daemon =  MHD_start_daemon( 
        MHD_USE_THREAD_PER_CONNECTION,
        port,
        NULL,
        NULL,
        &ahc_echo,
        PAGE,
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
