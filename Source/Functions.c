#include "../Headers/Header.h"
#include "../Headers/Functions.h"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};                                             // Define buffer to receive data from client

    int byte_count = read(client_socket, buffer, sizeof(buffer) - 1);           // How many bytes were sent from client

    if (byte_count < 0) {                                       
        perror("Client message read error");
        return;
    }

    buffer[byte_count] = '\0';                                                  // Terminate buffer

    // Extract important details for client handling and response
    char method[5];
    char file[256];
    char version[10];

    sscanf(buffer, "%s %s %s", method, file, version);

    if (strcmp(method, "GET") != 0) {                                           // Check if http request is of GET type, if not reject
        not_found_res(client_socket);
        return;
    }

    if (strcmp(file, "/") == 0) { strcpy(file, "/index.html"); }

    char full_path[512] = "./Demo-Files";
    strcat(full_path, file);

    send_file_res(client_socket, full_path);
}

void send_response(int client_socket, const char *header, const char *content_type, const char *body, int body_length) {
    char response_buffer[BUFFER_SIZE] = {0};                                    // Define buffer to store response back to client              
    
    snprintf(                                                                   // Metadata for response buffer
        response_buffer, 
        sizeof(response_buffer), 
        "%sContent-Type: %s\r\nContent=Length: %z\r\n\r\n", 
        header, content_type, body_length
    );

    write(client_socket, response_buffer, strlen(response_buffer));             // Writing data to client 
    write(client_socket, body, body_length);
}

void send_file_res(int client_socket, const char *path) {
    int file = open(path, O_RDONLY);                                            // Open file in read only mode

    if (file < 0) {
        not_found_res(client_socket);
        return;
    }
    
    // File state structure to store metadata
    struct stat file_state;                                                     

    if (fstat(file, &file_state) < 0) {
        close(file);
        not_found_res(client_socket);
        return;
    }

    char *file_content = malloc(file_state.st_size);                            // Read file contents into a buffer
    read(file, file_content, file_state.st_size);

    const char *content_type = "text/html";
    const char *file_extension = strrchr(path, '.');

    if (strcmp(file_extension, ".css") == 0) { content_type = "text/css"; }
    if (strcmp(file_extension, ".js")  == 0) { content_type = "text/javascript"; }

    send_response(                                                              // Send file content to client socket
        client_socket, 
        STATUS_OK, 
        content_type, 
        file_content, 
        file_state.st_size
    );

    close(file);
    free(file_content);
}

void not_found_res(int client_socket) {
    const char *body = "<!DOCTYPE html><html lang=\"en\"><head></head><body><h1>404 NOT FOUND</h1></body></html>";
    send_response(
        client_socket,
        STATUS_ERR,
        "text/html",
        body,
        strlen(body)
    );
}