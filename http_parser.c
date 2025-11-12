/*

http_parser.c : function for parsing and validating HTTP requests

*/

#include "http_parser.h"

http_request_line parse_request_line(char *string_request)
{
    http_request_line request_line;
    strncpy(request_line.method, strtok(string_request, " "), sizeof(request_line.method));
    //  NULL because strtok keep a static pointer to our string
    strncpy(request_line.uri, strtok(NULL, " "), sizeof(request_line.uri));
    strncpy(request_line.http_version, strtok(NULL, " "), sizeof(request_line.http_version));
    return request_line;
}

char *file_to_char(char *file_string)
{
    size_t size = 0;
    int c;
    char *res = malloc(MAXDATASIZE);
    char *ptr = res;
    FILE *fptr;
    if ((fptr = fopen(file_string, "rb")) == NULL)
    {
        perror("fopen");
        exit(0);
    }
    // When reaching
    while ((c = fgetc(fptr)) != EOF)
    {
        *res++ = c;
        if (res == &res[MAXDATASIZE - 1])
            break;
    }
    // null terminate
    *res = '\0';
    fclose(fptr);
    return ptr;
}