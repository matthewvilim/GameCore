#include "socket.h"

gc_error_t
socket_init_platform(socket_t *socket) {
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
}

gc_error_t
socket_terminate_platform(const socket_t *socket) {
    WSACleanup();

    return WSACleanup() == 0 ? GC_NO_ERROR : ;
}
