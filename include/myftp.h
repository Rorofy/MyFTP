/*
** EPITECH PROJECT, 2021
** NWP
** File description:
** include
*/

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>

typedef struct user_s
{
    char *username;
    char *password;
    int login_status;
    char *curr_dir;
    int fd;
} user_t;

typedef struct server_s
{
    int control_socket;
    fd_set active_fd_set;
    fd_set read_fd_set;
    user_t user;
} server_t;

typedef struct command_s
{
    char *name;
    void (*cmd)(char **input, server_t *server);
} command_t;

void create_server(int port, char *path);
int init_socket(int port, unsigned int n);
void handle_accept(server_t *server, int i);
void handle_connections(server_t *server);
int read_from_client (int fd, server_t *server);
void handle_commands(int fd, char *buffer, server_t *server);
void error_print(const char *str, int exit_nb);
char **str_split(char *str);
int check_space_only(char *str);
void init_struct(server_t *server);

int check_nb_arg(char **input, server_t *server, int nb_param);
void user_cmd(char **input, server_t *server);
void pass_cmd(char **input, server_t *server);
void cwd_cmd(char **input, server_t *server);
void cdup_cmd(char **input, server_t *server);
void quit_cmd(char **input, server_t *server);
void dele_cmd(char **input, server_t *server);
void pwd_cmd(char **input, server_t *server);
void pasv_cmd(char **input, server_t *server);
void port_cmd(char **input, server_t *server);
void help_cmd(char **input, server_t *server);
void noop_cmd(char **input, server_t *server);
void retr_cmd(char **input, server_t *server);
void stor_cmd(char **input, server_t *server);
void list_cmd(char **input, server_t *server);

static const command_t commands[] = {
    {"USER", user_cmd},
    {"PASS", pass_cmd},
    {"CWD", cwd_cmd},
    {"CDUP", cdup_cmd},
    {"QUIT", quit_cmd},
    {"DELE", dele_cmd},
    {"PWD", pwd_cmd},
    {"PASV", pasv_cmd},
    {"PORT", port_cmd},
    {"HELP", help_cmd},
    {"NOOP", noop_cmd},
    {"RETR", retr_cmd},
    {"STOR", stor_cmd},
    {"LIST", list_cmd},
    {NULL, 0}
};

#endif /* !INCLUDE_H_ */