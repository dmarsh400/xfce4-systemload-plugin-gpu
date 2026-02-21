/*
 * GPU load reading for XFCE system load plugin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpu.h"

gulong read_gpu0load()
{
    /* Use the known working path for rocm-smi */
    const char *command = "/opt/rocm-6.0.0/bin/rocm-smi --showuse 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        char *pos = strstr(buffer, "GPU use (%): ");
        if (pos) {
            pos += strlen("GPU use (%): ");
            if (gpu_count == 0) {
                usage = atoi(pos);
            }
            gpu_count++;
        }
    }
    pclose(fp);
    return usage;
}

gulong read_gpu1load()
{
    /* Use the known working path for rocm-smi */
    const char *command = "/opt/rocm-6.0.0/bin/rocm-smi --showuse 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        char *pos = strstr(buffer, "GPU use (%): ");
        if (pos) {
            pos += strlen("GPU use (%): ");
            if (gpu_count == 1) {
                usage = atoi(pos);
            }
            gpu_count++;
        }
    }
    pclose(fp);
    return usage;
}