#include "consts.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

// TODO: put all your instance variables here
// hint: you will likely need some buffers
int state = 0;           // Current state for handshake
packet* base_pkt = NULL; // Minimum packet to be sent out
bool force_ack = false;

ssize_t (*input)(uint8_t*, size_t); // Get data from layer
void (*output)(uint8_t*, size_t);   // Output data from layer

struct timeval start; // Last packet sent at this time
struct timeval now;   // Temp for current time

// TODO: Get data from standard input buffer / make handshake packets
packet* get_data() {
    switch (state) {
    case SERVER_AWAIT:
    case CLIENT_AWAIT:
    case CLIENT_START:
    case SERVER_START:
    default: {
    }
    }
}

// TODO: Process data received from socket
void recv_data(packet* pkt) {
    switch (state) {
    case CLIENT_START:
    case SERVER_START:
    case SERVER_AWAIT:
    case CLIENT_AWAIT:
    default: {
    }
    }
}

// Main function of transport layer; never quits
void listen_loop(int sockfd, struct sockaddr_in* addr, int initial_state,
                 ssize_t (*input_p)(uint8_t*, size_t),
                 void (*output_p)(uint8_t*, size_t)) {

    // Set initial state (whether client or server)
    state = initial_state;

    // Set input and output function pointers
    input = input_p;
    output = output_p;

    // Set socket for nonblocking
    int flags = fcntl(sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &(int) {1}, sizeof(int));

    // Setting timers
    gettimeofday(&now, NULL);
    gettimeofday(&start, NULL);

    // TODO: Set initial values

    // Create buffer for incoming data
    char buffer[sizeof(packet) + MAX_PAYLOAD] = {0};
    packet* pkt = (packet*) &buffer;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    // Start listen loop
    while (true) {
        memset(buffer, 0, sizeof(packet) + MAX_PAYLOAD);
        // Get data from socket
        int bytes_recvd = recvfrom(sockfd, &buffer, sizeof(buffer), 0,
                                   (struct sockaddr*) addr, &addr_size);
        // If data, process it
        if (bytes_recvd > 0) {
            recv_data(pkt);
        }

        packet* tosend = get_data();
        // TODO: you need to write the logic for what to send here. you can use
        // sendto() to send a packet once you've determined what its header
        // should look like. the code below is here so you can copy/paste it
        // any time you want to send a packet.
        //
        // Data available to send
        if (tosend != NULL) {
            sendto(sockfd, tosend, sizeof(packet) + ntohs(tosend->length), 0,
                   (struct sockaddr*) addr, sizeof(struct sockaddr_in));
        }
    }
}
