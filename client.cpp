#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int PORT = 8888;
using namespace std;

int main(int argc, char **argv) {
    if(argc > 1) {
        PORT = atoi(argv[1]);
    }
    int sock, new_socket;
    long valread;
    struct sockaddr_in serv_address;
    int addrlen = sizeof(sockaddr_in);
    char *hello = "henlo bacc";
    char buffer[1024] = {0};

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Cannot open socket");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr) <= 0) {
        cout << "Invalid address" << endl;
        return -1;
    }
    if(connect(sock, (struct sockaddr*) &serv_address, sizeof(serv_address)) < 0) {
        cout << "Connection failed" << endl;
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    cout << "Hello World sent" << endl;
    read(sock, buffer, 1024);
    cout << "Message recieved: " << buffer << endl;

    return 0;
}