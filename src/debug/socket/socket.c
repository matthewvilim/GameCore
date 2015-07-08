#include "socket.h"

gc_error_t
socket_open(socket_t *socket) {
    int error;

    struct addrinfo hints;
    memzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result;
    error = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result)
    if (SOCKET_FUNC_ERROR(error)) {
        goto error_return;
    }

    socket->handle = socket(result->ai_family,
                            result->ai_socktype,
                            result->ai_protocol);
    if (SOCKET_HANDLE_INVALID(socket->handle)) {
        goto error_free_addr;
    }

    error = bind(socket->handle, result->ai_addr, (int)result->ai_addrlen);
    if (SOCKET_FUNC_ERROR(error))
        goto error_close;
    }
    return GC_NO_ERROR;

    error_close:
    socket_close(socket);
    error_free_addr:
    freeaddrinfo(result);
    error_return:
    return GC_SOCKET_ERROR;
}

gc_error_t
socket_terminate(const socket_t *socket) {
    return socket_terminate_platform();
}
