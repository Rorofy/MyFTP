/*
** EPITECH PROJECT, 2021
** B-NWP-400-PAR-4-1-myftp-francois.zhao
** File description:
** commands2
*/

#include "../../include/myftp.h"

void dele_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0) {
        if (remove(input[1]) == 0) {
            dprintf(server->user.fd,
                "250 Requested file action okay, completed.\r\n");
        } else {
            dprintf(server->user.fd, "xxx Error (RFC compliant)\r\n");
        }
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void pwd_cmd(char **input, server_t *server)
{
    server->user.curr_dir = NULL;
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 1) == 0) {
        dprintf(server->user.fd, "257 \"%s\".\r\n",
            getcwd(server->user.curr_dir, 0));
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void pasv_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 1) == 0) {
        dprintf(server->user.fd,
            "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void port_cmd(char **input, server_t *server)
{
    if (server->user.login_status == 0) {
        dprintf(server->user.fd, "530 Not logged in\r\n");
        return;
    }
    if (check_nb_arg(input, server, 2) == 0) {
        dprintf(server->user.fd, "200 Command okay.\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}

void help_cmd(char **input, server_t *server)
{
    if (check_nb_arg(input, server, 1) == 0
        || check_nb_arg(input, server, 2) == 0) {
        dprintf(server->user.fd, "214 Help message\r\n");
        dprintf(server->user.fd, "USER PASS CWD CDUP QUIT DELE PWD"
        " PASV PORT HELP NOOP RETR STOR LIST\r\n");
    } else {
        dprintf(server->user.fd, "501 Error (RFC compliant)\r\n");
    }
}