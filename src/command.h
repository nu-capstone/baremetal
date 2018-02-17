#ifndef COMMAND_H
#define COMMAND_H

#define COMMAND_QUEUE_SIZE 256

uint8_t commandq_buf[COMMAND_QUEUE_SIZE];

typedef struct _command_queue_t {
    uint8_t *queue_buf;
} command_queue_t;

#endif
