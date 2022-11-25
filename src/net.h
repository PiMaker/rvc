#ifndef NET_H
#define NET_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "types.h"

static int net_fd = -1;
static int net_fd_conn = -1;
static bool g_server;

static struct {
    union {
        int32_t i32;
        uint8_t buf[4];
    } len;
    uint32_t i;

    uint8_t *buf;
    uint32_t buf_pos;

    bool valid;
    int reads;
} recv_info;

bool is_server() {
    return g_server;
}

void net_init(char *path, bool server)
{
    struct sockaddr_un addr;
    int flags;

    recv_info.len.i32 = -1;
    recv_info.valid = false;
    g_server = server;

    if (strlen(path) > sizeof(addr.sun_path) - 1) {
        perror("path too long");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    if (server) {
        net_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (net_fd < 0) {
            perror("socket");
            exit(1);
        }

        if (unlink(path) == -1 && errno != ENOENT) {
            perror("unlink");
        }

        if (bind(net_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("bind");
            exit(1);
        }

        if (listen(net_fd, 1) < 0) {
            perror("listen");
            exit(1);
        }

        printf("waiting for net client on %s\n", path);
        net_fd_conn = accept(net_fd, NULL, NULL);
        printf("net client connected\n");
    } else {
        net_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (net_fd < 0) {
            perror("socket");
            exit(1);
        }

        printf("connecting to net server on %s\n", path);

        if (connect(net_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("connect");
            exit(1);
        }

        printf("net client connected\n");
        net_fd_conn = net_fd;
    }

    flags = fcntl(net_fd_conn, F_GETFL, 0);
    fcntl(net_fd_conn, F_SETFL, flags | O_NONBLOCK);
}

#define min(a, b) ((a) < (b) ? (a) : (b))
static void pkt_hex_dump(uint8_t *data, size_t len)
{
    int rowsize = 16;
    int i, l, linelen, remaining;
    int li = 0;
    uint8_t ch;

    remaining = len;
    for (i = 0; i < len; i += rowsize) {
        printf("%06d\t", li);

        linelen = min(remaining, rowsize);
        remaining -= rowsize;

        for (l = 0; l < linelen; l++) {
            ch = data[l];
            printf("%02X ", (uint32_t) ch);
        }

        data += linelen;
        li += 10;

        printf("\n");
    }
}

void net_send(uint8_t *data, uint32_t len)
{
    if (VERBOSE >= 1)
        printf("net_send: %d\n", len);
    if (net_fd_conn != -1) {
        for (uint32_t i = 0; i < 4; i++) {
            uint8_t data = (len >> (i * 8)) & 0xFF;
            if (write(net_fd_conn, &data, 1) < 0) {
                fprintf(stderr, "net_send: write error (length %d): %s\n", i, strerror(errno));
                exit(1);
            }
        }
        if (VERBOSE >= 3)
            pkt_hex_dump(data, len);
        if (write(net_fd_conn, data, len) != len) {
            fprintf(stderr, "net_send: write error (data): %s\n", strerror(errno));
            exit(1);
        }
    }
}

bool net_recv(uint8_t **data_out, uint32_t *len_out) {
    int data_read;

    if (net_fd_conn == -1) {
        return false;
    }

    if (!recv_info.valid) {
        // read length
        for (; recv_info.i < 4; recv_info.i++) {
            uint8_t data;
            if ((data_read = read(net_fd_conn, &data, 1)) <= 0) {
                if (data_read == 0 && recv_info.i == 0) {
                    // no data waiting
                    return false;
                }
                // we're in the middle of reading the length, the rest should
                // arrive shortly
                if (data_read != 0 && errno != EAGAIN) {
                    fprintf(stderr, "net_recv: read error (at byte %d): %s\n", recv_info.i, strerror(errno));
                    exit(1);
                }
                // next emulation loop will retry
                return false;
            }
            recv_info.len.buf[recv_info.i] = data;
        }
        // length received, prime for receiving data
        if (VERBOSE >= 1)
            printf("net_recv: awaiting %d\n", recv_info.len.i32);
        recv_info.i = 0;
        recv_info.buf = malloc(recv_info.len.i32);
        if (recv_info.buf == NULL) {
            fprintf(stderr, "net_recv: malloc error\n");
            exit(1);
        }
        recv_info.valid = true;
    }

    // read data
    if ((data_read = read(net_fd_conn, recv_info.buf + recv_info.buf_pos, recv_info.len.i32 - recv_info.buf_pos)) < 0) {
        if (errno != EAGAIN) {
            fprintf(stderr, "net_recv: read error (data): %s\n", strerror(errno));
            exit(1);
        }
        // next emulation loop will retry
        return false;
    }

    recv_info.reads++;

    recv_info.buf_pos += data_read;
    if (recv_info.buf_pos == recv_info.len.i32) {
        // full data packet received, return it
        if (VERBOSE >= 1)
            printf("net_recv: got %d in %d\n", recv_info.len.i32, recv_info.reads);
        if (VERBOSE >= 3)
            pkt_hex_dump(recv_info.buf, recv_info.len.i32);
        *data_out = recv_info.buf;
        *len_out = (uint32_t)recv_info.len.i32;
        recv_info.reads = 0;
        recv_info.buf_pos = 0;
        recv_info.len.i32 = 0;
        recv_info.valid = false;
        return true;
    }

    // still some data left
    return false;
}

#endif
