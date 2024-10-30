/*
** EPITECH PROJECT, 2021
** B-NWP-400-PAR-4-1-myftp-francois.zhao
** File description:
** server
*/

#include "../../include/myftp.h"

void handle_accept(server_t *server, int i)
{
    struct sockaddr_in csin = { 0 };
    socklen_t csinsize = sizeof(csin);
    int new_sock = 0;

    server->user.fd = i;
    if (server->control_socket == i) {
        new_sock = accept(server->control_socket,
            (struct sockaddr *)&csin, &csinsize);
        if (new_sock < 0)
            error_print("Accept Failed", 84);
        dprintf(1, "Server: connect from host %s, port %d.\n",
            inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
        dprintf(new_sock, "220 Connected to server\r\n");
        FD_SET(new_sock, &server->active_fd_set);
    } else {
        if (read_from_client(i, server) < 0) {
            close(i);
            FD_CLR(i, &server->active_fd_set);
        }
    }
}

void handle_connections(server_t *server)
{
    struct sockaddr_in csin = { 0 };
    socklen_t csinsize = sizeof(csin);
    int accepted_sock = 0;
    int select_status = 0;

    FD_ZERO(&server->active_fd_set);
    FD_SET(server->control_socket, &server->active_fd_set);
    while (1) {
        server->read_fd_set = server->active_fd_set;
        select_status = select(FD_SETSIZE, &server->read_fd_set,
            NULL, NULL, NULL);
        if (select_status == -1) {
            error_print("Select Failed", 84);
        } else {
            for (int i = 0; i < FD_SETSIZE; ++i) {
                if (FD_ISSET(i, &server->read_fd_set))
                    handle_accept(server, i);
            }
        }
    }
}

int init_socket(int port, unsigned int n)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error_print("Can't create socket\n", 84);
    struct sockaddr_in sin = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(port)
    };
    if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
        error_print("Bind failed", 84);
    if (listen(sockfd, n) < 0)
        error_print("Listen failure", 84);
    return (sockfd);
}

void create_server(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));

    init_struct(server);
    if (chdir(path) == 0)
        server->user.curr_dir = path;
    else
        error_print("Bad path", 84);
    if (port <= 0 || port > 65535)
        error_print("Port must be between 1 and 65535", 84);
    server->control_socket = init_socket(port, FD_SETSIZE);
    printf("Starting server on port %d, waiting for connections...\n", port);
    while (1) {
        handle_connections(server);
    }
}
