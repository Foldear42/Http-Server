/*

http_parser.c : function for parsing and validating HTTP requests 

*/

#include "http_parser.h"

http_request_line parse_request_line(char *string_request){
    http_request_line request_line;
    memcpy(request_line.method, strtok(string_request, " "), sizeof(request_line.method));
    // NULL because strtok keep a static pointer to our string 
    memcpy(request_line.uri, strtok(NULL, " "), sizeof(request_line.uri));
    memcpy(request_line.http_version, strtok(NULL, " "), sizeof(request_line.http_version));
    return request_line;
}