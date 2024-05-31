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
- 2 Basic API calls
    - GET
    - POST

## Code Organization

The Project is divided into 2 Parts :

- ### Server
- ### Client

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
- **sin_addr   :** IP Address for socket, changes depending on connection type (WiFi / Ethernet), ---STRUCT DATATYPE--- 0.0.0.0 == INADDR_ANY 

### 3. bind()

```c
bind(int socket, const struct sockaddr *address, socklen_t address_len)
```
Allots network port to a socket for communication :
- **socket**      : Socket file descriptor value
- **address**   : Address of sockaddr struct type to interpret domain, protocol and address types (GPIO considerate measure)
- **address_len** : Length of address struct before hand

### 4. listen()

```c
listen(int socket, int backlog)
```
Opens socket at network port alloted to certain number of connections

- **socket  :** Socket file descriptor value
- **backlog :** Max number of connections the socket can accept

### 5. accept()
Allows connection from client to socket listening at alloted network port :
```c
accept(int socket, struct sockaddr *_Nullable restrict address, socklen *_Nullable restrict address_len)
```
- **socket      :** Socket file descriptor value
- **address     :** Address of sockaddr struct type from client with limited access
- **address_len :** Length of address struct passed before hand

- Returns file descriptor for accepted socket

### 6. recv()
Reads data sent from client over web using http protocol :
```c
recv(int socket, void buffer[len], size_t buffer_len, int flags) 
```
- **socket     :** Socket file descriptor value
- **buffer     :** Buffer to hold data sent from client
- **buffer_len :** Length of buffer passed before hand
- **flags      :** Used for recv operation mode and error handling

- Returns total bytes received from connection

### 7. open()
Opens files / directories which are required and are preset on the system : 
```c
open(const char *file, int flag)
```
- **file :** File path to be opened
- **flag :** Access mode to use for file (Read Only, Write Only, .. etc)

- Returns file descriptor / index for target file in process's table of open files 

### 8. sendfile()
Used to send files from source directory / process to destination directory / process :
```c
sendfile(int target_file_descriptor, int source_file_descriptor, off_t *_Nullable offset, size_t count)
```
- **target_file_descriptor :** Target / Destination File descriptor index (Client socket)
- **source_file_descriptor :** Source File descriptor index (Open File)
- **offset                 :** Position from start to send bytes from source_file_descriptor
- **count                  :** Number of byte to send to target_file_descriptor / Client

- Returns number of bytes sent to targe_file_descriptor / Client 

### 9. close()
Closes any required and open process / file / directory :
```c
close(int file_descriptor)
```
- **file_descriptor :** Target / Process to close

- Returns status (0 for successful, -1 for failure)