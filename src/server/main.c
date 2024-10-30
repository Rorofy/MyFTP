/*
** EPITECH PROJECT, 2021
** NWP
** File description:
** main
*/

#include "../../include/myftp.h"

static void print_h(void)
{
    printf("USAGE:\t./myftp port path\n");
    printf("port\tis the port number on which the server socket listens\n");
    printf("path\tis the path to the home directory for the Anonymous user\n");
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        print_h();
        return 0;
    }
    if (ac == 3) {
        create_server(atoi(av[1]), av[2]);
    } else {
        error_print("Wrong number of arguments", 84);
    }
    return 0;
}
