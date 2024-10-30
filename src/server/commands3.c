/*
** EPITECH PROJECT, 2021
** B-NWP-400-PAR-4-1-myftp-francois.zhao
** File description:
** commands3
*/

#include "../../include/myftp.h"

void noop_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 1) == 0) {
        dprintf(server->user.fd, "200 Command okay.\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void retr_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0) {
        dprintf(server->user.fd,
            "150 File status okay; about to open data connection.\r\n");
        dprintf(server->user.fd, "226 Closing Data connection.\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }

}

void stor_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0) {
        dprintf(server->user.fd,
            "150 File status okay; about to open data connection.\r\n");
        dprintf(server->user.fd, "226 Closing Data connection.\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void list_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0
    || check_nb_arg(input, server, 1) == 0) {
        dprintf(server->user.fd,
            "150 File status okay; about to open data connection.\r\n");
        dprintf(server->user.fd, "226 Closing Data connection.\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

int check_nb_arg(char **input, server_t *server, int nb_param)
{
    int i = 0;

    for (i = 0; input[i] != NULL; i++);
    if (i != nb_param)
        return (-1);
    return (0);
}