#include "./Header.h"

int main(int argc, char const *argv[]) {
    /*
        socket(int domain, int type, int protocol) creates a socket : 
        - Domain   : Communication domain type eg : AF_INET : IPV4 type Domain to use
        - Type     : Socket type to use        eg : TCP / UDP / RAW etc
        - Protocol : Protocol for socket ops   eg : 0 for default TCP/IP
    */
    
    int skt = socket(AF_INET, SOCK_STREAM, 0);
    
    // Define PORT number to bind socket to 
    int PORT = 8000;

    // Define buffer to recieve data from client
    char buffer[256] = {0};

    /*
        struct sockaddr_in {
            sin_family;
            sin_port;
            sin_addr;
        }

        - sin_family : Communications domain type eg : AF_INET : IPV4 type Domain to use
        - sin_port   : Port number in Network byte order (BIG  ENDIAN i.e. First number stored first. Need to convert this to LITTLE ENDIAN i.e. Last number sotred first, for CPU Execution)
        - sin_addr   : IP Address for socket, changes depending on connection type (WiFi / Ethernet), ---STRUCT DATATYPE--- 0.0.0.0 == INADDR_ANY 
    */
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    //htons() (host to network) is a function used to perform big to little endian conversions depending on CPU for sin_port 

    /*
        bind(int socket, const struct sockaddr *address, socklen_t address_len)
        - socket      : Socket file descriptor value
        - *address    : Address of sockaddr struct type to interpret domain, protocl and address types (GPIO considerate measure)
        - address_len : Length of address struct before hand
    */

    bind(skt, &addr, sizeof(addr));

    /*
        listen(int socket, int backlog)
        - socket  : Socket file descriptor value
        - backlog : Max number of connections the socket can accept
    */

    listen(skt, 10);

    /*
        accept(int socket, struct sockaddr *_Nullable restrict address, socklen *_Nullable restrict address_len)
        - socket      : Socket file descriptor value
        - address     : Address of sockaddr struct type from client with limited access
        - address_len : Length of address struct passed before hand
    */

    int client = accept(skt, 0, 0);

    /*
        recv(int socket, void buffer[len], size_t buffer_len, int flags) 
        - socket     : Socket file descriptor value
        - buffer     : Buffer to hold data sent from client
        - buffer_len : Length of buffer passed before hand
        - flags      : Used for recv operation mode and error handling
    */
    
    int bytes_received_count = recv(client, buffer, 256, 0);

    if (bytes_received_count > 0) { buffer[bytes_received_count] = '\0'; }

    //0 /file.html

    enum req_name client_req_type = (int)buffer[0];
    char file_name[256] = {0}; 
    
    if (client_req_type == 0) {
        int start = 3;
        int len = bytes_received_count - start;

        if (len > 0) {
            strncpy(file_name, buffer + start, len);
            file_name[len] = '\0';
        }

        

    }

    return 0;
}
