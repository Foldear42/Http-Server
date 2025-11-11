#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXSIZE 1024

typedef struct
{
    char method[16];
    char uri[128];
    char http_version[16];
} http_request_line;

http_request_line parse_request_line(char *string_request);

char *file_to_char(char *file_string);