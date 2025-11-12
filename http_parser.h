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

#define MAXDATASIZE 1024
#define GET "GET"

typedef struct
{
    char method[16];
    char uri[128];
    char http_version[16];
} http_request_line;

typedef struct
{
    char server_name[16];

} http_response_header;

typedef struct
{
    char content_type[16];
} http_representation_header;

typedef struct
{
    char status_line[16];
    http_response_header response_header;
    http_representation_header reprensentation_header;
    char response_body[MAXDATASIZE];
} http_response;

/*
 * Parse the request line of a HTTP request
 */
http_request_line parse_request_line(char *string_request);

/*
 * Read all bytes in the file and put them into a buffer
 */
char *file_to_char(char *file_string);