#ifndef COMMANDS_H
#define COMMANDS_H

typedef void (*command_handler_t)(void); //lets you store function addresses in a table
typedef struct 
{
    const char *name;
    command_handler_t handler;
} command_t; //lookup table entry

void process_command(char *cmd);

#endif