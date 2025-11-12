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

// HTTP first line
typedef struct
{
    char method[16];
    char uri[128];
    char http_version[16];
} http_request_line;

// HTTP Header
typedef struct
{
    char host[16];
} http_request_header;

// Full HTTP request
typedef struct
{
    http_request_line request_line;
    http_request_header request_header;
    char body[1024];
} http_request;

/*
 * Find the header in a string
 */
size_t find_header(const char *string_request, const char *header_name, char *output);
/*
 * Parse full request into a http_request struct
 */
void parse_request(http_request *request, const char *string_request);
/*
 * Parse the header of a HTTP request
 */
void parse_request_header(http_request_header *rh, const char *string_request);
/*
 * Parse the request line of a HTTP request
 */
void parse_request_line(http_request_line *rl, const char *string_request);
/*
 * Read all bytes in the file and put them into a buffer
 */
void file_to_char(const char *file_string, char *output);