#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define BUFFER_SIZE (1024)
#define MESSAGE_SIZE (32)
#define NUMBER_RUNS (1000000)

static inline double microtime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1e6 * tv.tv_sec + tv.tv_usec;
}

static inline off_t min(off_t a, off_t b)
{
    return a < b ? a : b;
}

int main()
{
    uint8_t message[MESSAGE_SIZE];
    uint8_t buffer[2 * BUFFER_SIZE];
    size_t offset;

    double slow_start = microtime();
    offset = 0;
    for (int i = 0; i < NUMBER_RUNS; i++) {
        const size_t part1 = min(MESSAGE_SIZE, BUFFER_SIZE - offset);
        const size_t part2 = MESSAGE_SIZE - part1;
        memcpy(buffer + offset, message, part1);
        memcpy(buffer, message + part1, part2);
        offset = (offset + MESSAGE_SIZE) % BUFFER_SIZE;
    }
    double slow_stop = microtime();

    double fast_start = microtime();
    offset = 0;
    for (int i = 0; i < NUMBER_RUNS; i++) {
        memcpy(&buffer[offset], message, MESSAGE_SIZE);
        offset = (offset + MESSAGE_SIZE) % BUFFER_SIZE;
    }
    double fast_stop = microtime();

    printf("slow: %f microseconds per write\n",
           (slow_stop - slow_start) / NUMBER_RUNS);
    printf("fast: %f microseconds per write\n",
           (fast_stop - fast_start) / NUMBER_RUNS);

    return 0;
}