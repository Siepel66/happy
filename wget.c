#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "wget.h"

//#define DEBUG(a) printf a
#define DEBUG(a)

#define OK_HEADER "HTTP/1.1 200 OK"



WGET_RESULT wget(char *servername, unsigned short port, char *request, int responseLen, char *response) {

  int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
  struct hostent *server;
  unsigned int j = 0;
  struct sockaddr_in serveraddr;
  char *req = NULL;
  WGET_RESULT result = WGET_ERROR;
  int bytes_read = 0;

  static const char pcRequest[]="Get %s HTTP/1.1\r\n Host: %s\r\n \r\n \r\n";

  if (tcpSocket >= 0) {
     server = gethostbyname(servername);
     if (server != NULL) {
            DEBUG(("%s ", inet_ntoa(*(struct in_addr*)(server -> h_addr_list[j]))));
        DEBUG(("\n%s = ", server->h_name));
        while (server -> h_addr_list[j] != NULL) {
            DEBUG(("%s ", inet_ntoa(*(struct in_addr*)(server -> h_addr_list[j]))));
            j++;
        }
        DEBUG(("\n"));
        bzero((char *) &serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
        serveraddr.sin_port = htons(port);
        if (connect(tcpSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) >= 0) {
            req = calloc(1, strlen(pcRequest) + strlen((char *) servername) + strlen(request));
            if (req != NULL) {
                sprintf(req, "Get %s HTTP/1.1\r\n Host: %s\r\n \r\n \r\n", request, (char *)servername);
                DEBUG(("wget Request: \n%s", req));
                if (send(tcpSocket, req, strlen(req), 0) >= 0) {
                    if (responseLen > 0) {
                      bzero(response, responseLen);
                      responseLen--;
                      do {
                         bytes_read = recv(tcpSocket, response + bytes_read, responseLen - bytes_read, 0);
                      } while (( bytes_read > 0 ) && ( bytes_read < responseLen ));

                      DEBUG(("wget Response: \n%s", response));
                      if (strncmp(OK_HEADER, response, sizeof(OK_HEADER) - 1 ) == 0) result = WGET_OK;
                    } else {
                      result = WGET_OK;
                    }

                    close(tcpSocket);
                }
                free(req);
            }
        }
      }
    }
    return result;
}
