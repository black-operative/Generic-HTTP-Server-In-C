# Minimalist HTTP Web server in C

This a small and simple project that aims to create a working minimalist HTTP server, using the C programming language. 

## Installation

You can use the following methods to clone this repo to your local machine : 

1. HTTP Clone 
    ```bash
    git clone https://github.com/rudrakshm64/Generic-HTTP-Server-In-C.git
    ```

2. GitHub Desktop
    - File              
        - `Alt + f`
    - Clone Repository  
        - `Alt + f` + `n` 
        - `Ctrl + Shift + O`
    - URL Tab
    - Repo URL ***or*** Username + Repo name :  
        - `https://github.com/rudrakshm64/Generic-HTTP-Server-In-C.git`
        - `rudrakshm64/Generic-HTTP-Server-In-C`
    - Local Path, pick any location that you want

3. GitHub CLI
    ```bash
    gh repo clone rudrakshm64/Generic-HTTP-Server-In-C
    ```

## Features

- [**POSIX / UNIX**](https://en.wikipedia.org/wiki/Unix_domain_socket) Socket architecture
- [**IPV4**](https://en.wikipedia.org/wiki/IPv4) Protocol
- [**GNU/Linux**](https://en.wikipedia.org/wiki/Linux) Runtime Environment
- Static Website hosting

## Code Organization

The Project is divided into 4 Parts :

- ### Header Files
- ### Source Files
- ### Build Files
- ### Static Website Files

## Functions / System Calls / Data Structures used

### 1. socket()

```c
socket(int domain, int type, int protocol)
```
Creates a socket : 
- **Domain   :** Communication domain type eg : AF_INET : IPV4 type Domain to use
- **Type     :** Socket type to use        eg : TCP / UDP / RAW etc
- **Protocol :** Protocol for socket ops   eg : 0 for default TCP/IP

- Returns fle descriptor for new socket created

### 2. sockaddr_in

```c
struct sockaddr_in {
    sin_family;
    sin_port;
    sin_addr;
}
```
Contains information about protocol types, address usage and requested subnet : 
- **sin_family :** Communications domain type eg : AF_INET : IPV4 type Domain to use
- **sin_port   :** Port number in Network byte order (BIG  ENDIAN i.e. First number stored first. Need to convert this to LITTLE ENDIAN i.e. Last number stored first, for CPU Execution)
- **sin_addr   :** IP Address for socket, changes depending on connection type (WiFi / Ethernet) 

### 3. bind()

```c
bind(int socket, const struct sockaddr *address, socklen_t address_len)
```
Allots network port to a socket for communication :
- **socket**      : Socket file descriptor value
- **address**   : Address of sockaddr struct type to interpret domain, protocol and address types (GPIO considerate measure)
- **address_len** : Length of address struct before hand

- Returns status (0 for successful, -1 for failure)

### 4. listen()

```c
listen(int socket, int backlog)
```
Opens socket at network port alloted to certain number of connections

- **socket  :** Socket file descriptor value
- **backlog :** Max number of connections the socket can accept

- Returns status (0 for successful, -1 for failure)

### 5. accept()
Allows connection from client to socket listening at alloted network port :
```c
accept(int socket, struct sockaddr *_Nullable restrict address, socklen *_Nullable restrict address_len)
```
- **socket      :** Socket file descriptor value
- **address     :** Address of sockaddr struct type from client with limited access
- **address_len :** Length of address struct passed before hand

- Returns file descriptor for accepted socket

### 6. open()
Opens files / directories which are required and are preset on the system : 
```c
open(const char *file, int flag)
```
- **file :** File path to be opened
- **flag :** Access mode to use for file (Read Only, Write Only, .. etc)

- Returns file descriptor / index for target file in process's table of open files 

### 7. read()
Reads data sent from client over web using http protocol :
```c
read(int socket, void buffer[buffer_len], size_t buffer_len) 
```
- **socket     :** Socket file descriptor value
- **buffer     :** Buffer to hold data sent from client
- **buffer_len :** Length of buffer passed before hand

- Returns total bytes received from connection

### 8. write()
Writes data to target file descriptor / buffer : 
```c
write(int socket, void buffer[buffer_len], size_t buffer_len)
```
- **socket     :** Socket file descriptor value
- **buffer     :** Buffer to hold data which is to be written to client
- **buffer_len :** Length of buffer passed before hand

- Returns number of bytes return to target file descriptor 

### 9. sscanf()
Parses and scans formatted input according to desired format : 
```c
sscanf(const char *target, const char *restrictor_format, char *destination1, char *destination2, char *destination3, ......)
```
- **target :** Buffer to scan
- **restrictor_format :** Required format to scan and match required segments
- **destination1, destination2, destination3, ..... :** Series of buffers, where the results must be stored

- Returns number of items successfully matched from **buffer** and stored in **destination buffers**

### 10. close()
Closes any required and open process / file / directory :
```c
close(int file_descriptor)
```
- **file_descriptor :** Target / Process to close

- Returns status (0 for successful, -1 for failure)
