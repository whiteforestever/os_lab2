#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048


int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Incorrect number of parameters. Run in the format: ./<exec_file> pid=<pid> vendor_id=<vendor_id> device_id=<device_id>\n");
        exit(1);
    }

    char *buffer[BUFFER_SIZE];
    unsigned short pid, vendor_id, device_id;
    sscanf(argv[1], "pid=%hu", &pid);
    sscanf(argv[2], "vid=%hu", &vendor_id);
    sscanf(argv[3], "devid=%hu", &device_id);

    FILE *file = fopen("/sys/kernel/debug/lab2/structs", "r+");
    if(file == NULL) {
        printf("Can not open file\n");
        exit(1);
    }

    if(pid) {
        fprintf(file, "pid: %hu,", pid);
    }
    if(vendor_id && device_id) {
        fprintf(file, "vid: %hu, devid: %hu", vendor_id, device_id);
    }

    while(1) {
        char *msg = fgets(buffer, BUFFER_SIZE, file);
        if (msg == NULL) {
            if (!feof(file)) {
                fprintf(stderr, "struct reading failed with errno code: %d\n", errno);
            }
            break;
        }
        printf(msg);
    }

    fclose(file);
    return 0;
}