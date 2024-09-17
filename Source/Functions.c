#include "../Headers/Header.h"
#include "../Headers/Functions.h"

/**
* @brief Handles client connections and processes HTTP requests.
*
* This function reads data from the client socket, extracts the HTTP method, file required and HTTP version, 
* and then processes the request accordingly. If the method is not GET, it sends a 404 NOT FOUND response. 
* Otherwise, it sends the requested file to the client.
*
* @param client_socket Socket descriptor of the client to handle.
*
* @return void
*/

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

    char full_path[512] = "./Demo-Files";
    strcat(full_path, file);

    send_file_res(client_socket, full_path);
}

/**
* @brief Sends an HTTP response to the client.
*
* This function constructs and sends an HTTP response to the client. 
* The response includes a header, content type, and body. 
* The header, content type and body are provided as parameters to the function.
*
* @param client_socket  Socket descriptor of the client to send the response to.
* @param header         The HTTP header for the response.
* @param content_type   The content type of the response body.
* @param body           The response body.
* @param body_length    The length of the response body.
*
* @return int
* @retval -1           If there was an error sending the response to the client.
* @retval 0            If the response was successfully sent to the client.
*/

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
    int byte_count_1 = write(client_socket, response_buffer, strlen(response_buffer));         
    int byte_count_2 = write(client_socket, body, body_length);

    if (byte_count_1 < 0 || byte_count_2 < 0) {
        return -1;
    } else {
        return 0;
    }
}

/**
* @brief Sends a file as an HTTP response to the client.
*
* This function opens the specified file, reads its contents, and sends an HTTP response to the client.
* The function determines the content type based on the file extension and sends the file content along 
* with the appropriate HTTP headers. If the file cannot be opened or read, it sends a 404 NOT FOUND response.
*
* @param client_socket  Socket descriptor of the client to send the response to.
* @param path           The path to the file to be sent.
*
* @return               int
* @retval -1            If an error occurred while sending the response or opening/reading the file.
* @retval 0             If the file was successfully sent as HTTP response
*/

int send_file_res(int client_socket, const char *path) {
    // Open file in read only mode
    int file = open(path, O_RDONLY);                                         

    if (file < 0) {
        not_found_res(client_socket);
        return -1;
    }
    
    // File state structure to store metadata
    struct stat file_state;                                                     

    if (fstat(file, &file_state) < 0) {
        close(file);
        not_found_res(client_socket);
        return -1;
    }

    char *file_content = malloc(file_state.st_size);                                // Read file contents into a buffer
    recv(file, file_content, file_state.st_size, 0);

    const char *content_type = "text/html";
    const char *file_extension = strrchr(path, '.');

    if (strcmp(file_extension, ".css") == 0) { content_type = "text/css"; }
    if (strcmp(file_extension, ".js")  == 0) { content_type = "text/javascript"; }

    int status_code = send_response(                                                                       // Send file content to client socket
        client_socket, 
        STATUS_200_OK, 
        content_type, 
        file_content, 
        file_state.st_size
    );

    if (status_code < 0) {
        perror("Response sending error");
        return -1;
    }

    close(file);
    free(file_content);

    return 0;
}

/**
* @brief Sends a 404 NOT FOUND HTTP response to the client.
*
* This function constructs and sends a 404 NOT FOUND HTTP response to the client
*
* @param client_socket Socket descriptor of the client to send the response to.
*
* @return int
* @retval -1           If there was an error sending the response to the client.
* @retval 0            If the response was successfully sent to the client.
*/

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