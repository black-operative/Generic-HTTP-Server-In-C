#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

enum req_name {
    GET,
    POST
};

typedef struct {
    enum req_name req_name;
    int req_name_len;
} get_req; 

#endif