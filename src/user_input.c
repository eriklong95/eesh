#include "include/user_input.h"
CommandLine *parse(char *input)
{
    CommandLine *cli;

    cli->executable = input;

    return cli;
}
