#include "http_server.h"
#include "http_parser.h"

int main()
{
    int sockfd;
    struct sockaddr_in my_addr;
    int yes = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 choose the correct protocol based on the type
    // fcntl(sockfd, F_SETFL, O_NONBLOCK);
    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Allow the program to reuse the port
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connection
    if (listen(sockfd, 5) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
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
    int client_fd, len_msg, bytes_sent;
    int sin_size = sizeof(struct sockaddr_in);
    char client_data[MAXDATASIZE];
    struct sockaddr_in their_addr;
    http_request client_request;

    if ((client_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
    {
        perror("accept");
    }
    printf("[Server] request from %s\n", inet_ntoa(their_addr.sin_addr));
    // data send by the client
    if (recv(client_fd, client_data, MAXDATASIZE - 1, 0) == -1)
    {
        perror("recv");
    }

    parse_request(&client_request, client_data);
    if ((strncmp(client_request.request_line.method, "GET", 3) == 0) && (strncmp(client_request.request_line.uri, "/", 1) == 0))
    {
        char *response_line = "HTTP/1.1 200 OK\r\n";
        char *response_header = "Content-Type: text/html\r\n\r\n";
        char file_data[512];
        file_to_char("index.html", file_data);
        char response[1024];
        snprintf(response, MAXDATASIZE - 1, "%s%s%s", response_line, response_header, file_data);
        if (send(client_fd, response, strlen(response), 0) == -1)
        {
            perror("send");
        }
    }

    // close the connection with the client
    close(client_fd);
}