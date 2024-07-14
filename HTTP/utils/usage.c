#include <stdio.h>
#include "../includes/usage.h"

void print_usage(const char *prog_name) {
    fprintf(stderr,
        "*******************************************************\n"
        "*                                                     *\n"
        "*                   USAGE GUIDE                       *\n"
        "*                                                     *\n"
        "*  Welcome to the Client Application!                 *\n"
        "*                                                     *\n"
        "*  Usage:                                             *\n"
        "*                                                     *\n"
        "     %s <hostname> <filename> <method>                 \n"
        "*                                                     *\n"
        "*  Example:                                           *\n"
        "*                                                     *\n"
        "     %s localhost index.html GET                       \n"
        "*                                                     *\n"
        "*******************************************************\n"
        , prog_name, prog_name);
}
