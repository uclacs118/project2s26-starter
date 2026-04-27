#pragma once

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Maximum payload size
#define MAX_PAYLOAD 1012

// NOTE: these are the values we put in for the reference code, which worked

// Retransmission time
#define TV_DIFF(end, start)                                                    \
    (end.tv_sec * 1000000) - (start.tv_sec * 1000000) + end.tv_usec -          \
        start.tv_usec
#define RTO 1000000
#define MIN(a, b) (a > b ? b : a)
#define MAX(c, d) (c > d ? c : d)

// Window size
#define MIN_WINDOW MAX_PAYLOAD
#define MAX_WINDOW MAX_PAYLOAD * 40
#define DUP_ACKS 3

// States
#define SERVER_AWAIT 0
#define CLIENT_START 1
#define SERVER_START 2
#define CLIENT_AWAIT 3
#define NORMAL 4

// Structs
// TODO: define your header for what's needed for reliable data transport
typedef struct {
    // uint16_t was used for all the reference code's fields
    uint8_t payload[0]; // we give this one to you
} packet;

// hint:
typedef struct buffer_node {
    struct buffer_node* next;
    packet pkt;
} buffer_node;

// Helpers
static inline void print(char* txt) { fprintf(stderr, "%s\n", txt); }

// TODO: we recommend having a diagnostic print helper like this, just make sure
// it's sending to stderr
static inline void print_diag(packet* pkt, int diag) {
    fprintf(stderr, "hello world\n");
}
