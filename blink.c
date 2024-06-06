#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_PINS 10  // Số lượng chân GPIO tối đa bạn muốn hỗ trợ

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pin1> <pin2> ... <pinN>\n", argv[0]);
        return 1;
    }

    int f = open("/proc/gpio", O_RDWR);

    if (f < 0) {
        perror("Failed to open /proc/gpio");
        return 1;
    }

    while (1) {
        for (int i = 1; i < argc; i++) {
            int pin = atoi(argv[i]);
            char buffer[20];  // Tăng kích thước buffer để chứa dữ liệu
            snprintf(buffer, sizeof(buffer), "%d,1", pin);
            write(f, buffer, strlen(buffer));
            usleep(500000);
            snprintf(buffer, sizeof(buffer), "%d,0", pin);
            write(f, buffer, strlen(buffer));
            usleep(500000);
        }
    }

    close(f);
    return 0;
}
