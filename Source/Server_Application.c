#include "../Headers/Header.h"

int main(int argc, char const *argv[]) {
    /*
        socket(int domain, int type, int protocol) creates a socket : 
        - Domain   : Communication domain type eg : AF_INET : IPV4 type Domain to use
        - Type     : Socket type to use        eg : TCP / UDP / RAW etc
        - Protocol : Protocol for socket ops   eg : 0 for default TCP/IP

        - Returns fle descriptor for new socket created
    */
    
    int skt = socket(AF_INET, SOCK_STREAM, 0);
    
    // Define PORT number to bind socket to 
    int PORT = 8000;

    // Define buffer to receive data from client
    char buffer[256] = {0};

    /*
        struct sockaddr_in {
            sin_family;
            sin_port;
            sin_addr;
        }

        - sin_family : Communications domain type eg : AF_INET : IPV4 type Domain to use
        // - sin_port   : Port number in Network byte order (BIG  ENDIAN i.e. First number stored first. Need to convert this to LITTLE ENDIAN i.e. Last number stored first, for CPU Execution)
        - sin_addr   : IP Address for socket, changes depending on connection type (WiFi / Ethernet), ---STRUCT DATATYPE--- 0.0.0.0 == INADDR_ANY 
    */
    struct sockaddr_in addr = {
        AF_INET,
        // htons(PORT),
        0x401f,
        0
    };

    //htons() (host to network) is a function used to perform big to little endian conversions depending on CPU for sin_port 

    /*
        bind(int socket, const struct sockaddr *address, socklen_t address_len)
        - socket      : Socket file descriptor value
        - *address    : Address of sockaddr struct type to interpret domain, protocol and address types (GPIO considerate measure)
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

        - Returns file descriptor for accepted socket
    */

    int client = accept(skt, 0, 0);

    /*
        recv(int socket, void buffer[len], size_t buffer_len, int flags) 
        - socket     : Socket file descriptor value
        - buffer     : Buffer to hold data sent from client
        - buffer_len : Length of buffer passed before hand
        - flags      : Used for recv operation mode and error handling

        - Returns total bytes received from connection
    */
    
    recv(client, buffer, 256, 0);

    //GET /file.html

    int start = 5;

    char* file_name = buffer + start; 
    
    *(strchr(file_name, ' ')) = 0; 

    /*
        open(const char *file, int flag)
        - file : File path to be opened
        - flag : Access mode to use for file (Read Only, Write Only, .. etc)

        - Returns file descriptor / index for target file in process's table of open files 
    */

    int open_file = open(file_name, O_RDONLY);

    /*
        sendfile(int target_file_descriptor, int source_file_descriptor, off_t *_Nullable offset, size_t count)
        - target_file_descriptor : Target / Destination File descriptor index (Client socket)
        - source_file_descriptor : Source File descriptor index (Open File)
        - offset                 : Position from start to send bytes from source_file_descriptor
        - count                  : Number of byte to send to target_file_descriptor / Client

        - Returns number of bytes sent to targe_file_descriptor / Client 
    */

    sendfile(client, open_file, 0, 256);
    
    /*
        close(int file_descriptor)
        - file_descriptor : Target / Process to close

        - Returns status (0 for successful, -1 for failure)
    */
    close(open_file);
    close(client);
    close(skt);

    return 0;
}
