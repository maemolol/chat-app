#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

int PORT = 8888;

int main(int argc, char **argv) {
    if(argc > 1) {
        PORT = atoi(argv[1]);
    }
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(sockaddr_in);
    char *hello = "henlo worl :3";

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Cannot open socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof(address.sin_zero));

    if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("Cannot bind to socket");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 10) < 0) {
        perror("Can't listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening on port " << PORT << "..." << std::endl;

    while(true) {
        std::cout << "Waiting for new connection..." << std::endl;
        if(!new_socket)
        if((new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
            perror("Accepted connection");
            continue;
        }
        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        std::cout << "Number of bytes recieved: " << valread << std::endl;
        if(valread > 0) {
            std::cout << "Recieved message: " << buffer << std::endl;
        }
        write(new_socket, hello, strlen(hello));
        std::cout << "Hello message sent.\n";
        if(buffer[0] == 'e') {
            close(new_socket);
            new_socket = 0;
        }
    }

    return 0;
}