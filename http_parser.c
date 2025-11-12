/*
 * http_parser.c : function for parsing and validating HTTP requests
 */

#include "http_parser.h"

size_t find_header(const char *string_request, const char *header_name, char *output)
{
    char *p_header_string;
    char *starting_p = output;
    int c;
    size_t size;
    // Find where the header name is and point to the start of the string
    if ((p_header_string = strstr(string_request, header_name)) != NULL)
    {
        strtok(p_header_string, ":");
        char *token = strtok(NULL, "");
        // Get every character till the \r
        while ((c = *token++) != '\r')
        {
            *output++ = c;
            size++;
        }
        *output = '\0';
    }
    return size;
}

void parse_request(http_request *request, const char *string_request)
{
    char *copy_string_request = strndup(string_request, MAXDATASIZE);

    parse_request_line(&request->request_line, copy_string_request);

    free(copy_string_request);
}

void parse_request_header(http_request_header *rh, const char *string_request)
{
    char *copy = strndup(string_request, MAXDATASIZE);
    // Host header
    char *host_header_string;
    size_t host_header_size = find_header(string_request, "Host", host_header_string);
    strncpy(rh->host, host_header_string, host_header_size);
}

void parse_request_line(http_request_line *rl, const char *string_request)
{
    // TODO: Find a solution to avoid copy
    char *copy = strndup(string_request, MAXDATASIZE);
    strncpy(rl->method, strtok(copy, " "), sizeof(rl->method));
    //  NULL because strtok keep a static pointer to our string
    strncpy(rl->uri, strtok(NULL, " "), sizeof(rl->uri));
    strncpy(rl->http_version, strtok(NULL, " "), sizeof(rl->http_version));
    free(copy);
}

void file_to_char(const char *file_string, char *output)
{
    size_t size = 0;
    FILE *fptr;
    int c;
    if ((fptr = fopen(file_string, "rb")) == NULL)
    {
        perror("fopen");
        exit(0);
    }
    while ((c = fgetc(fptr)) != EOF)
    {
        *output++ = c;
        if (output == &output[MAXDATASIZE - 1])
            break;
    }
    // null terminate
    *output = '\0';
    fclose(fptr);
}