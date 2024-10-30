/*
** EPITECH PROJECT, 2021
** B-NWP-400-PAR-4-1-myftp-francois.zhao
** File description:
** commands
*/

#include "../../include/myftp.h"

void user_cmd(char **input, server_t *server)
{
    if (check_nb_arg(input, server, 2) == 0) {
        if (server->user.username != NULL && server->user.password != NULL) {
            dprintf(server->user.fd, "230 User logged in, proceed\r\n");
            server->user.login_status = 1;
        } else {
            server->user.username = input[1];
            if (server->user.password == NULL) {
                dprintf(server->user.fd,
                    "331 User name okay, need password.\r\n");
            } else {
                dprintf(server->user.fd, "230 User logged in, proceed\r\n");
                server->user.login_status = 1;
            }
        }
    } else {
        dprintf(server->user.fd, "530 Not logged in\r\n");
    }
}

void pass_cmd(char **input, server_t *server)
{
    if (check_nb_arg(input, server, 1) == 0) {
        if (strcmp(server->user.username, "Anonymous") == 0
            && input[1] != NULL) {
                dprintf(server->user.fd, "530 Not logged in\r\n");
                return;
        }
        if (server->user.username != NULL && server->user.password != NULL) {
            dprintf(server->user.fd, "230 User logged in, proceed\r\n");
            server->user.login_status = 1;
        } else {
            server->user.password = " ";
            if (server->user.username == NULL) {
                dprintf(server->user.fd, "332 Need account for login.\r\n");
            } else {
                dprintf(server->user.fd, "230 User logged in, proceed\r\n");
                server->user.login_status = 1;
            }
        }
    } else {
        dprintf(server->user.fd, "530 Not logged in\r\n");
    }
}

void cwd_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0) {
        if (chdir(input[1]) == -1) {
            dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
        } else {
            dprintf(server->user.fd,
                "250 Requested file action okay, completed.\r\n");
        }
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void cdup_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 1) == 0) {
        if (chdir("../") == -1) {
            dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
        } else {
            dprintf(server->user.fd, "200 Command okay.\r\n");
        }
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void quit_cmd(char **input, server_t *server)
{
    if (check_nb_arg(input, server, 1) == 0) {
        dprintf(server->user.fd, "%s %s\r\n",
            "221 Service closing control connection.",
            "Logged out if appropriate.");
        FD_CLR(server->user.fd, &server->read_fd_set);
        shutdown(server->user.fd, SHUT_RDWR);
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}