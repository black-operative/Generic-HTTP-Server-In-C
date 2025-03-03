#pragma once

#ifndef FUNCTIONS
#define FUNCTIONS

#define STATUS_200_OK  "HTTP/1.1 200 OK\r\n"
#define STATUS_404_ERR "HTTP/1.1 404 NOT FOUND\r\n"
#define STATUS_405_ERR "HTTP/1.1 405 METHOD NOT ALLOWED\r\n"

#define CONTENT_HTML "text/html"
#define CONTENT_CSS  "text/css"
#define CONTENT_JS   "application/javascript"

#define WEB_DIR "./web"

#define BUFFER_SIZE 65536

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
void handle_client(int client_socket);

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
int send_response(int client_socket, const char *header, const char *content_type, const char *body, int body_length);

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
int send_file_res(int client_socket, const char *path);

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
int not_found_res(int client_socket);

/**
* @brief Sends a 405 ILLEGAL METHOD HTTP response to the client.
*
* This function constructs and sends a 405 ILLEGAL METHOD HTTP response to the client
*
* @param client_socket Socket descriptor of the client to send the response to.
*
* @return int
* @retval -1           If there was an error sending the response to the client.
* @retval 0            If the response was successfully sent to the client.
*/
int illegal_method_res(int client_socket);

/**
 * @brief Closes incoming and outgoing connections.
 * 
 * @param server_socket 
 * @param client_socket 
 */
void close_server(int server_socket, int client_socket);

#endif