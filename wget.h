typedef enum __WGET_RESULT {
	WGET_OK = 0,
	WGET_TIMEOUT,
	WGET_ERROR
} WGET_RESULT;

WGET_RESULT wget(char *servername, unsigned short port, char *request, int responseLen, char *response);
