# Generic HTTP Web server in C

This a small and simple project that aims to create a working minimalist and a Generic HTTP server using the C programming language.

## Installation

You can use the following methods to clone this repo to your local machine :

1. HTTP Clone

    ```bash
    git clone https://github.com/black-operative/Generic-HTTP-Server-In-C.git
    ```

2. GitHub Desktop
    - File
        - `Alt + f`
    - Clone Repository  
        - `Alt + f` + `n`
        - `Ctrl + Shift + O`
    - URL Tab
    - Repo URL ***or*** Username + Repo name :  
        - `https://github.com/black-operative/Generic-HTTP-Server-In-C.git`
        - `black-operative/Generic-HTTP-Server-In-C`
    - Local Path, pick any location that you want

3. GitHub CLI

    ```bash
    gh repo clone black-operative/Generic-HTTP-Server-In-C
    ```

## Features

- [**POSIX / UNIX**](https://en.wikipedia.org/wiki/Unix_domain_socket) Socket architecture
- [**IPV4**](https://en.wikipedia.org/wiki/IPv4) Protocol
- [**GNU/Linux**](https://en.wikipedia.org/wiki/Linux) Runtime Environment
- Static Website hosting

## Code Organization

### Functions / System Calls / Data Structures used

#### 1. socket()

```c
int socket(int domain, int type, int protocol)
```

Creates a socket :

- **Domain   :** Communication domain type eg : AF_INET : IPV4 type Domain to use
- **Type     :** Socket type to use        eg : TCP / UDP / RAW etc
- **Protocol :** Protocol for socket ops   eg : 0 for default TCP/IP
- Returns fle descriptor for new socket created

#### 2. sockaddr_in

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

#### 3. bind()

```c
int bind(int socket, const struct sockaddr *address, socklen_t address_len)
```

Allots network port to a socket for communication :

- **socket**      : Socket file descriptor value
- **address**   : Address of sockaddr struct type to interpret domain, protocol and address types (GPIO considerate measure)
- **address_len** : Length of address struct before hand
- Returns status (0 for successful, -1 for failure)

#### 4. listen()

```c
int listen(int socket, int backlog)
```

Opens socket at network port alloted to certain number of connections

- **socket  :** Socket file descriptor value
- **backlog :** Max number of connections the socket can accept
- Returns status (0 for successful, -1 for failure)

#### 5. accept()

Allows connection from client to socket listening at alloted network port :

```c
int accept(int socket, struct sockaddr *_Nullable restrict address, socklen_t *_Nullable restrict address_len)
```

- **socket      :** Socket file descriptor value
- **address     :** Address of sockaddr struct type from client with limited access
- **address_len :** Length of address struct passed before hand
- Returns file descriptor for accepted socket

#### 6. open()

Opens a file and associates a stream with it :

```c
FILE* fopen(const char *restrict file, const char *restrict mode)
```

- **file :** File path to be opened
- **mode :** Access mode to use for file (Read Only, Write Only, .. etc)
- Returns FILE pointer to said file

#### 7. fread()

Reads data from file into a buffer :

```c
size_t fread(void *restrict buffer, size_t token_size, size_t buffer_len, FILE *restrict file) 
```

- **buffer     :** Buffer to hold data being read from file stream
- **token_size :** Chunk of byte(s) to read, one at a time
- **buffer_len :** Length of buffer passed before hand / number of tokens to read
- **file       :** FILE stream to read from
- Returns number of tokens read from file

#### 8. send()

Send data to another socket :

```c
ssize_t send(int socket, const void buffer[], size_t buffer_len, int flags)
```

- **socket     :** Socket file descriptor value
- **buffer     :** Buffer to hold data which is to be written to client
- **buffer_len :** Length of buffer passed before hand
- **flags      :** Options for message transmission and formatting
- Returns number of bytes sent to target socket

#### 9. sscanf()

Parses and scans formatted input according to desired format :

```c
int sscanf(const char *target, const char *restrictor_format, char *destination1, char *destination2,......)
```

- **target :** Buffer to scan
- **restrictor_format :** Required format to scan and match required segments
- **destination1, destination2, destination3, ..... :** Series of buffers, where the results must be stored
- Returns number of items successfully matched from **buffer** and stored in **destination buffers**

#### 10. close()

Closes any required and open process / file / directory :

```c
int close(int file_descriptor)
```

- **file_descriptor :** Target / Process to close
- Returns status (0 for successful, -1 for failure)

### Functions defined for HTTP servicing

#### 1. handle_client()

Handles client connections and process HTTP requests from clients

```c
void handle_client(int client_socket)
```

- **client_socket :** Client file descriptor to handle / process
- Does NOT return any status code

#### 2. send_response()

Constructs and sends HTTP responses to client socket. Responses consist of HTTP header, content and body

```c
int send_response(int client_socket, const char *header, const char *content_type, const char *body, int body_length)
```

- **client_socket :** Client file descriptor to handle / process
- **header :** The HTTP header for the response.
- **content_type :** The MIME (content) type of the response body.
- **body :** The response body.
- **body_length :** The length of the response body.
- Returns status (0 for successful, -1 for failure)

#### 3. send_file_res()

Opens, reads and sends and content according to it's type in the form of an HTTP response to client with appropriate HTTP headers. Sends 404 if file does not exist or cannot be opened

```c
int send_file_res(int client_socket, const char *path)
```

- **client_socket :** Client file descriptor to handle / process
- **path :** The path to the file to be sent.
- Returns status (0 for successful, -1 for failure)
- **NOTE :** Uses helper function : [`send_response()`](#2-send_response)

#### 4. not_found_res()

Constructs and sends a 404 Error HTTP response to client socket.

```c
int not_found_res(int client_socket)
```

- **client_socket :** Client file descriptor to handle / process
- Returns status (0 for successful, -1 for failure)

#### 5. illegal_method_res()

Constructs and sends a 405 Error HTTP response to client socket.

```c
int illegal_method_res(int client_socket) 
```

- **client_socket :** Client file descriptor to handle / process
- Returns status (0 for successful, -1 for failure)

#### 6. close_server()

Shuts down all incoming and outgoing socket connections upon request.

```c
void close_server(int server_socket, int client_socket)
```

- **server_socket :** Server file description to close
- **client_socket :** Client file descriptor to handle / process
- Does NOT return any status code

#### 7. exit_signal_handle()

Detects `Ctrl + C` / `⌘ + C` and handles server shutdown.

```c
void exit_signal_handle(int signal)
```

- **signal :** Kernel signal to handle
- Does NOT return any status code
- **NOTE** :
  - Only [`SIGINT`](https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html) is handled
  - Uses function [`close_server()`](#6-close_server)
