#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5648

int main() {
    int sockfd; 
    struct sockaddr_in my_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 choose the correct protocol based on the type

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");
    my_addr.sin_port = htons(PORT);
    memset(&(my_addr.sin_zero), '\0', 8);

    // Assign an address to the sockfd
    // The cast is necessary because bind does not accept the struct sockaddr_in 
    bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));
    // Listen for incoming connection 
    listen(sockfd, 5);
    
    return 0;
}