/*
 * http_parser.c : functions for parsing and validating HTTP requests
 */

#include "http_parser.h"

size_t find_header(const char *string_request, const char *header_name, char *output)
{
    char *p_header_string;
    char *starting_p = output;
    int c;
    size_t size = 0;
    // Find where the header name is and point to the start of the string
    if ((p_header_string = strstr(string_request, header_name)) != NULL)
    {
        strtok(p_header_string, ":");
        char *token = strtok(NULL, " ");
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
    char *copy_string_request = strndup(string_request, MAX_RESPONSE_SIZE);

    parse_request_line(&request->request_line, copy_string_request);
    parse_request_header(&request->request_header, copy_string_request);

    free(copy_string_request);
}

void parse_request_header(http_request_header *rh, const char *string_request)
{
    char *copy = strndup(string_request, MAX_RESPONSE_SIZE);
    // Host header
    char host_header_string[16];
    size_t host_header_size = find_header(string_request, "Host", host_header_string);
    strncpy(rh->host, host_header_string, host_header_size);
}

void parse_request_line(http_request_line *rl, const char *string_request)
{
    // TODO: Find a solution to avoid copy
    char *copy = strndup(string_request, MAX_RESPONSE_SIZE);
    strncpy(rl->method, strtok(copy, " "), sizeof(rl->method));
    //  NULL because strtok keep a static pointer to our string
    strncpy(rl->uri, strtok(NULL, " "), sizeof(rl->uri));
    strncpy(rl->http_version, strtok(NULL, " "), sizeof(rl->http_version));
    free(copy);
}

int is_request_valid(http_request *request)
{
    return 0;
}

int file_to_char(const char *file_string, char *output)
{
    size_t size = 0;
    FILE *fptr;
    int c;
    if ((fptr = fopen(file_string, "rb")) == NULL)
    {
        perror("fopen");
        return -1;
    }
    while ((c = fgetc(fptr)) != EOF)
    {
        *output++ = c;
        if (output == &output[MAX_FILE_DATA_SIZE - 1])
            break;
    }
    // null terminate
    *output = '\0';
    fclose(fptr);
}