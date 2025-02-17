#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_IP "10.12.110.57"
#define DEST_PORT 23

int main(){
    int sockfd;
    struct sockaddr_in dest_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    dest_addr.sin_port = htons(DEST_PORT);
    memset(&dest_addr.sin_zero, '\0', 8);

    connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr));

}