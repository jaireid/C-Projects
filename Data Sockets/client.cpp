#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int sockfd, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t serverAddr_size, addr_size;
    int i = 1;

    // Socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    // Settings
    serverAddr.sin_family = AF_INET;

    // Host
    std::string host;
    std::cout << "Enter the server host name: " << std::endl;
    std::cin >> host;
    struct hostent *h;
    if((h = gethostbyname(host.c_str())) == NULL){
        perror("Could not get host name");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_addr = *(struct in_addr *)h -> h_addr;
    
    // Ask user for PORT number
    int port;
    do {
        std::cout << "Enter the server port number: " << std::endl;
        std::cin >> port;
    } while(port <= 1024);
    
    serverAddr.sin_port = htons(port);

    // More Settings
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;
    while(i) {
        // Ask user for license plate
        std::cout << "Enter license plate number: ";
        std::cin >> buffer;
        std::cout << buffer << std::endl;

        nBytes = strlen(buffer) + 1;

        // Sent license plate to server
        sendto(sockfd, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

        if(strcmp(buffer, "killsvc") == 0) {
            std::cout << "Sent killsvc command to server. Client is terminating." << std::endl;
            break;
        }

        // Recieve answer from server
        nBytes = recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);

        // Print message
        printf("Received from server: %s\n", buffer);

        i = 0;
    }

    // Terminate
    close(sockfd);

    return 0;
}
