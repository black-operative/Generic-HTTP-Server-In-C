#include "../Headers/Header.h"

int main(int argc, char const *argv[]) {
    int skt = socket(AF_INET, SOCK_STREAM, 0);

    // Define buffer to receive data from client
    char buffer[256] = {0};

    struct sockaddr_in addr = {
        AF_INET,
        0x401f,                     //Port 8000 in hexadecimal backwards for small endian / little endian
        0   
    };

    bind(skt, &addr, sizeof(addr));

    printf("Server is now Running at port : %d", 8000);
    
    listen(skt, 10);

    int client = accept(skt, 0, 0);
    
    recv(client, buffer, 256, 0);

    //GET /file.html

    int start = 5;

    char* file_name = buffer + start; 
    
    *(strchr(file_name, ' ')) = 0; 

   char* final_name = malloc(strlen("../Demo-Files/") + strlen(file_name) + 1);
   strcpy(final_name, "../Demo-Files/");
   strcat(final_name, file_name);

    int open_file = open(final_name, O_RDONLY);

    sendfile(client, open_file, 0, 256);
    
    close(open_file);
    close(client);
    close(skt);

    return 0;
}