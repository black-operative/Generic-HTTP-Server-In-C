#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "Functions.h"

void handle_client(int client_socket) {
    // Define buffer to receive data from client
    char buffer[BUFFER_SIZE] = {0};                                             

    // How many bytes were sent from client + Error checking
    int byte_count = recv(client_socket, buffer, sizeof(buffer) - 1, 0);   
    if (byte_count < 0) {                                       
        perror("Client message read error");
        return;
    }

    // Terminate buffer
    buffer[byte_count] = '\0';   
    
    printf("\n--------------------------------\nClient Request :\n--------------------------------\n %s", buffer);

    // Extract important details for client handling and response
    char method[5];
    char file[256];
    char version[10];

    sscanf(buffer, "%s %s %s", method, file, version);

    // Check if http request is of GET type, if not reject
    if (strcmp(method, "GET") != 0) {                                           
        illegal_method_res(client_socket);
        return;
    }

    if (strcmp(file, "/") == 0) { strcpy(file, "/index.html"); }

    char full_path[512] = WEB_DIR;
    strcat(full_path, file);

    send_file_res(client_socket, full_path);
}

int send_response(int client_socket, const char *header, const char *content_type, const char *body, int body_length) {
    // Define buffer to store response back to client              
    char response_buffer[BUFFER_SIZE] = {0};                                   
    
    // Metadata for response buffer
    snprintf(                                                                            
        response_buffer, 
        sizeof(response_buffer), 
        "%sContent-Type: %s\r\nContent=Length: %d\r\n\r\n", 
        header, content_type, body_length
    );

    // Writing data to client 
    int byte_count_1 = send(
        client_socket, 
        response_buffer, 
        strlen(response_buffer), 
        0
    );         
    
    int byte_count_2 = send(
        client_socket, 
        body, 
        body_length, 
        0
    );

    if (byte_count_1 < 0 || byte_count_2 < 0) { return -1; } 
    else                                      { return 0;  }
}

int send_file_res(int client_socket, const char *path) {
    // Open file in read only mode
    FILE* file = fopen(path, "r");                                         

    if (file == NULL) {
        not_found_res(client_socket);
        return -1;
    }
    
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *file_content = malloc(file_size + 1);                                // Read file contents into a buffer
    if (file_content == NULL) {
        perror("malloc");
        fclose(file);
        return -1;
    }

    size_t bytes_read = fread(
        file_content, 
        1, 
        file_size, 
        file
    );
    if (bytes_read != file_size) {
        perror("fread");
        fclose(file);
        return -1;
    }

    file_content[file_size] = '\0';

    const char *content_type = CONTENT_HTML;
    const char *file_extension = strrchr(path, '.');

    if (file_extension != NULL) {
        if (strcmp(file_extension, ".css") == 0) { content_type = CONTENT_CSS; }
        if (strcmp(file_extension, ".js")  == 0) { content_type = CONTENT_JS; }    
    }

    int status_code = send_response(                                                                       // Send file content to client socket
        client_socket, 
        STATUS_200_OK, 
        content_type, 
        file_content, 
        file_size
    );

    if (status_code < 0) {
        perror("Response sending error");
        return -1;
    }

    fclose(file);
    free(file_content);

    return 0;
}

int not_found_res(int client_socket) {
    const char *body = "<!DOCTYPE html><html lang=\"en\"><head></head><body><h1>404 NOT FOUND</h1></body></html>";
    
    int status_code = send_response(
        client_socket,
        STATUS_404_ERR,
        "text/html",
        body,
        strlen(body)
    );

    if (status_code < 0) {
        perror("Response sending error");
        return -1;
    }

    return 0;
}

int illegal_method_res(int client_socket) {
    const char *body = "<!DOCTYPE html><html lang=\"en\"><head></head><body><h1>405 Method Not Allowed</h1></body></html>";
    
    int status_code = send_response(
        client_socket,
        STATUS_405_ERR,
        "text/html",
        body,
        strlen(body)
    );

    if (status_code < 0) {
        perror("Response sending error");
        return -1;
    }

    return 0;
}

void close_server(int server_socket, int client_socket) {
    close(client_socket);
    close(server_socket);
}