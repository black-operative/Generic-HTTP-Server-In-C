// #include "../Headers/Header.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "Functions.h"

int server_socket = 0;
int client_socket = 0;

const int enable = 1;

void exit_signal_handle(int signal) {
    if (signal == SIGINT) {
        printf("\nServer shutting down...\n");
        close_server(server_socket, client_socket);
        printf("Server shutdown complete.\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {

    signal(SIGINT, exit_signal_handle);

    // Define port numbers to use
    int PORT = 3000;

    // Initialize the server socket + Error checks
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket initialization error");
        exit(EXIT_FAILURE);
    }

    // Apply Address and Port resuse options
    if (setsockopt(
            server_socket, 
            SOL_SOCKET, 
            SO_REUSEADDR | SO_REUSEPORT, 
            &enable, 
            sizeof(enable)
        ) < 0) {
        perror("setsockopt(SO_REUSEADDR)");
        exit(EXIT_FAILURE);
    }

    // Define socket address struture
    struct sockaddr_in server_address;
    
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;                     
    server_address.sin_port        = htons(PORT);               //Port in hexadecimal. 
    
    // Bind + Error checks
    if (bind(
            server_socket, 
            (struct sockaddr*) &server_address, 
            sizeof(server_address)
        ) < 0) {
        perror("Bind");
        exit(EXIT_FAILURE);
    }

    // Set socket to listen for incoming connections + Error checks
    if (listen(server_socket, 10) < 0) {
        perror("Server listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is now Running at port : %d\n", PORT);
    printf("Website available at : localhost:%d\n", PORT);
    
    while (1) {
        client_socket = accept(server_socket, 0, 0);

        if (client_socket < 0) {
            perror("Client Accept error");
            continue;
        }

        // Close client connection once done handling the connection
        handle_client(client_socket);
        close(client_socket);
    }

    // Close server socket when done serving requests
    close(server_socket);
    return 0;
}

