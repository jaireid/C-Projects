#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdlib.h>

int main() {
    int sockfd, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t serverAddr_size, addr_size;
    int i = 1;

    // Ask user for Database name
    std::string db_filename;
    std::cout << "Enter the name of the database file: " << std::endl;
    std::cin >> db_filename;

    // Open database file
    std::ifstream db(db_filename);

    if (!db) {
        std::cerr << "Error: Unable to open database file." << std::endl;
        return 1;
    }

    // Socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    // Settings
    serverAddr.sin_family = AF_INET;
    
    // Ask user for PORT number
    int port;
    std::cout << "Enter the server port number: " << std::endl;
    std::cin >> port;
    serverAddr.sin_port = htons(port);
  
    // Address
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    // Bind
    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // Wait for incoming messages
    std::cout << "Waiting for messages." << std::endl;

    addr_size = sizeof serverStorage;
    while(i) {
        // Receive message
        nBytes = recvfrom (sockfd, buffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);

        // Print message
        std::string response(buffer);
        std::cout << "License plate recieved from client: " << response << std::endl;

        // Request = KILLSVC
        if(response == "killsvc") {
            std::cout << "Killing server..." << std::endl;
            exit(0);
            // break;
        }

        // Consult database
        std::string plate;
        bool found = false;
        while (getline(db, plate)) {
            std::cout << "License plate in Database: " << plate << std::endl;

            if(plate == response) {
                found = true;
                break;
            }
        }

        db.clear();
        db.seekg(0, std::ios::beg);

        // Send reply
        std::string reply_msg;
        if (found) {
            std::cout << response << ": Reported as stolen" << std::endl;
            reply_msg = response + ": Yes, license plate reported as stolen.";
        } else {
            std::cout << response << ": Not in the database" << std::endl;
            reply_msg = response + ": No, license plate not reported as stolen.";
        }

        nBytes = reply_msg.copy(buffer, reply_msg.size(), 0);
        buffer[nBytes] = '\0';
        sendto(sockfd, buffer, nBytes+1, 0, (struct sockaddr *)&serverStorage, addr_size);

      
        nBytes = reply_msg.size();
        const char* reply_buf = reply_msg.c_str();
        int reply = sendto(sockfd, reply_buf, nBytes, 0, (struct sockaddr *)&serverStorage, addr_size);

        // Wait for next client message
    }

    db.close();

    return 0;
}
