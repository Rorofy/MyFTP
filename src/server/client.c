/*
** EPITECH PROJECT, 2021
** NWP
** File description:
** client
*/

#include "../../include/myftp.h"

void handle_commands(int fd, char *buffer, server_t *server)
{
    char **input = str_split(buffer);
    int count = 0;

    if (input == NULL || input[0] == NULL)
        return;
    for (int j = 0; commands[j].name != NULL; j++) {
        if (strcmp(commands[j].name, input[0]) == 0) {
            commands[j].cmd(input, server);
            count = 1;
        }
    }
    if (count == 0) {
        dprintf(server->user.fd, "500 Command unrecognized 1\n");
    }
}

int read_from_client(int fd, server_t *server)
{
    char buf[512];
    int nbytes;

    memset(buf, '\0', 512);
    nbytes = read(fd, buf, 512);
    if (buf == NULL) {
        return 0;
    }
    if (nbytes < 0) {
        error_print("Read Error", 84);
    } else if (nbytes == 0) {
        return -1;
    } else {
        if (check_space_only(buf) == -1) {
            dprintf(server->user.fd, "500 Command unrecognized 2\r\n");
            return 0;
        }
        fprintf(stderr, "Server got message : %s", buf);
        handle_commands(fd, buf, server);
        return 0;
    }
}