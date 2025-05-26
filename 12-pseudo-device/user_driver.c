// file: user_driver.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *dev = "/dev/mydevice";
    char buffer[128];

    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Writing to device...\n");
    write(fd, "Hello from userspace!\n", 23);

    lseek(fd, 0, SEEK_SET);  // rewind before reading

    printf("Reading from device...\n");
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received: %s", buffer);
    }

    close(fd);
    return 0;
}

