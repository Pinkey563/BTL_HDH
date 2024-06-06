#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pin_number>\n", argv[0]);
        return 1;
    }

    char buffer[10];
    int pin = atoi(argv[1]);
    int f = open("/proc/gpio", O_RDWR);

    if (f < 0) {
        perror("Failed to open /proc/gpio");
        return 1;
    }

    while (1) {
        snprintf(buffer, sizeof(buffer), "%d,1", pin);
        write(f, buffer, strlen(buffer));
        usleep(500000);
        snprintf(buffer, sizeof(buffer), "%d,0", pin);
        write(f, buffer, strlen(buffer));
        usleep(500000);
    }

    close(f);
    return 0;
}
