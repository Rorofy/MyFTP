/*
** EPITECH PROJECT, 2021
** B-NWP-400-PAR-4-1-myftp-francois.zhao
** File description:
** utils
*/

#include "../../include/myftp.h"

void error_print(const char *str, int exit_nb)
{
    fprintf(stderr, "%s\n", str);
    exit(exit_nb);
}

char **str_split(char *str)
{
    char **tab = NULL;
    char *s = strtok(str, " \t\r\n");
    int sp_nb = 0;

    while (s) {
        tab = realloc(tab, sizeof(char *) * ++sp_nb);
        if (tab == NULL)
            return NULL;
        tab[sp_nb - 1] = s;
        s = strtok(NULL, " \t\r\n");
    }
    tab = realloc(tab, sizeof(char *) * (sp_nb + 1));
    tab[sp_nb] = NULL;
    return (tab);
}

int check_space_only(char *str)
{
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r') {
            return 0;
        } 
    }
    return -1;
}

void init_struct(server_t *server)
{
    server->control_socket = 0;
    server->user.username = NULL;
    server->user.password = NULL;
    server->user.login_status = 0;
    server->user.curr_dir = NULL;
    server->user.fd = 0;
}