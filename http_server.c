#include "http_server.h"
#include "http_parser.h"

int main()
{
    int sockfd, new_fd, len_msg, bytes_sent;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    struct sigaction sa;
    http_request_line request_line;
    int sin_size;
    int yes = 1;
    char buf[MAXDATASIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 choose the correct protocol based on the type
    if (sockfd == -1)
    {
        perror("Socket");
        return -1;
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
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        {
            perror("accept");
            continue;
        }
        printf("Server: request from %s\n", inet_ntoa(their_addr.sin_addr));

        // data send by the client
        if (recv(new_fd, buf, MAXDATASIZE - 1, 0) == -1)
        {
            perror("recv");
        }
        request_line = parse_request_line(buf);
        if ((strncmp(request_line.method, "GET", 3) == 0) && (strncmp(request_line.uri, "/", 1) == 0))
        {
            http_request_line new_request_line;
            char *rep = "HTTP/1.1 200 OK\r\n\r\n";
            char *file_str = file_to_char("index.html");
            if (send(new_fd, rep, strlen(rep), 0) == -1)
            {
                perror("send");
            }
            free(file_str);
            // close the connection with the client
            close(new_fd);
        }
    }
    close(sockfd);
    return 0;
}