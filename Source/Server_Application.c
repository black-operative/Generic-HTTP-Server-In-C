#include "../Headers/Header.h"
#include "../Headers/Functions.h"

int main(int argc, char const *argv[]) {
    // Define port numbers to use
    int PORT1 = 3000;
    int PORT2 = 8888;
    int CURRENT_PORT = 0;

    // Create and initialize socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Check for socket creation errors
    if (server_socket < 0) {
        perror("Socket initialization error");
        exit(EXIT_FAILURE);
    }

    // Define socket address struture
    struct sockaddr_in server_address;
    
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;                     
    server_address.sin_port        = htons(PORT1);               //Port in hexadecimal. 
    
    // Try binding to PORT1 first, then PORT2 if PORT1 fails to bind + Error checks
    if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        perror("Server socket binding error, trying another address");
        
        server_address.sin_family      = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;                     
        server_address.sin_port        = htons(PORT2);           //Port in hexadecimal.

        // Error checks if PORT2 fails
        if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
            perror("Server socket binding error");
            close(server_socket);
            exit(EXIT_FAILURE);
        }  
        else { CURRENT_PORT = PORT2; }
    } 
    else { CURRENT_PORT = PORT1; }

    // Set socket to listen for incoming connections + Error checks
    if (listen(server_socket, 10) < 0) {
        perror("Server listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is now Running at port : %d\n", CURRENT_PORT);
    printf("Website available at : localhost:%d\n", CURRENT_PORT);
    
    while (TRUE) {
        int client_socket = accept(server_socket, 0, 0);

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

