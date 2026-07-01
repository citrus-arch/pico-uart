#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

void print_prompt(void);
void read_line(char *buf, size_t len);

#endif