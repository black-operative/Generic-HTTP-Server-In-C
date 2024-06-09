#include "../Headers/Header.h"
#include "../Headers/Functions.h"

int main(int argc, char const *argv[]) {
    int PORT = 8080;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        perror("Socket initialization error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;                     
    server_address.sin_port        = htons(PORT);           //Port in hexadecimal. HTONS for small endian / little endian compatibility
    
    if (bind(server_socket, &server_address, sizeof(server_address)) < 0) {
        perror("Server socket binding error");
        close(server_socket);
        exit(EXIT_FAILURE);
    } 

    if (listen(server_socket, 10) < 0) {
        perror("Server listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }


    printf("Server is now Running at port : %d\n", PORT);
    printf("Website available at : localhost:%d\n", PORT);
    
    while (TRUE) {
        int client_socket = accept(server_socket, 0, 0);

        if (client_socket < 0) {
            perror("Client Accept error");
            continue;
        }

        handle_client(client_socket);
        close(client_socket);
    }

    close(server_socket);

    return 0;
}