#pragma once
#ifndef FUNCTIONS
#define FUNCTIONS

void handle_client(int client_socket);
int  send_response(int client_socket, const char *header, const char *content_type, const char *body, int body_length);
int  send_file_res(int client_socket, const char *path);
int  not_found_res(int client_socket);

#define STATUS_OK  "HTTP/1.1 200 OK\r\n"
#define STATUS_ERR "HTTP/1.1 404 NOT FOUND\r\n"

#endif