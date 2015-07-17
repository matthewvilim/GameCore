#ifndef SOCKET_H
#define SOCKET_H

#if _WIN32
# include <winsock2.h>
# include <Ws2tcpip.h>

#define SOCKET_HANDLE_INVALID(handle) (handle == INVALID_SOCKET)
#define SOCKET_FUNC_ERROR(val) (val == SOCKET_ERROR)

typedef SOCKET socket_handle_t;

#else
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>

#define SOCKET_HANDLE_INVALID(handle) (handle < 0)
#define SOCKET_FUNC_ERROR(val) (val != 0)

typedef int socket_handle_t;
#endif

#endif

typedef struct socket {
    socket_handle_t handle;
} socket_t;

socket_init(socket_t *socket);
socket_open(socket_t *socket);
socket_terminate(socket_t *socket);
