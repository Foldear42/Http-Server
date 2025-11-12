#include "http_server.h"
#include "http_parser.h"

int main()
{
    int sockfd;
    struct sockaddr_in my_addr;
    int yes = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 choose the correct protocol based on the type
    if (sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    // Allow the program to reuse the port
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(PORT);
    memset(&(my_addr.sin_zero), '\0', 8);

    // Assign an address to the sockfd
    // The cast is necessary because bind does not accept the struct sockaddr_in
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connection
    if (listen(sockfd, 5) == -1)
    {
        perror("listen");
        exit(1);
    }

    // Main loop : handling connections
    while (1)
    {
        handle_connection(sockfd);
    }
    close(sockfd);
    return 0;
}

void handle_connection(int sockfd)
{
    int new_fd, len_msg, bytes_sent;
    int sin_size = sizeof(struct sockaddr_in);
    char client_data[MAXDATASIZE];
    struct sockaddr_in their_addr;
    http_request_line request_line;

    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
    {
        perror("accept");
    }
    printf("[Server] request from %s\n", inet_ntoa(their_addr.sin_addr));
    // data send by the client
    if (recv(new_fd, client_data, MAXDATASIZE - 1, 0) == -1)
    {
        perror("recv");
    }

    request_line = parse_request_line(client_data);

    if ((strncmp(request_line.method, "GET", 3) == 0) && (strncmp(request_line.uri, "/", 1) == 0))
    {
        char *response_line = "HTTP/1.1 200 OK\r\n";
        char *response_header = "Content-Type: text/html\r\n\r\n";
        char *file_str = file_to_char("index.html");
        char response[1024];
        snprintf(response, MAXDATASIZE - 1, "%s%s%s", response_line, response_header, file_str);
        if (send(new_fd, response, strlen(response), 0) == -1)
        {
            perror("send");
        }
        free(file_str);
        // close the connection with the client
        close(new_fd);
    }
}