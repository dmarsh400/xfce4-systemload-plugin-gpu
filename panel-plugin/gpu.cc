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

gulong read_vram0usage()
{
    /* Use the known working path for rocm-smi */
    const char *command = "/opt/rocm-6.0.0/bin/rocm-smi --showmeminfo vram 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong total_bytes = 0;
    gulong used_bytes = 0;
    int gpu_found = 0;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Look for GPU[0] lines
        if (strstr(buffer, "GPU[0]")) {
            if (strstr(buffer, "VRAM Total Memory (B):")) {
                char *pos = strstr(buffer, "VRAM Total Memory (B):");
                if (pos) {
                    pos += strlen("VRAM Total Memory (B):");
                    total_bytes = atoll(pos);
                }
            } else if (strstr(buffer, "VRAM Total Used Memory (B):")) {
                char *pos = strstr(buffer, "VRAM Total Used Memory (B):");
                if (pos) {
                    pos += strlen("VRAM Total Used Memory (B):");
                    used_bytes = atoll(pos);
                }
            }
            gpu_found = 1;
        }
    }
    pclose(fp);
    
    if (gpu_found && total_bytes > 0) {
        return (used_bytes * 100) / total_bytes;
    }
    return 0;
}

gulong read_vram1usage()
{
    /* Use the known working path for rocm-smi */
    const char *command = "/opt/rocm-6.0.0/bin/rocm-smi --showmeminfo vram 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong total_bytes = 0;
    gulong used_bytes = 0;
    int gpu_found = 0;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Look for GPU[1] lines
        if (strstr(buffer, "GPU[1]")) {
            if (strstr(buffer, "VRAM Total Memory (B):")) {
                char *pos = strstr(buffer, "VRAM Total Memory (B):");
                if (pos) {
                    pos += strlen("VRAM Total Memory (B):");
                    total_bytes = atoll(pos);
                }
            } else if (strstr(buffer, "VRAM Total Used Memory (B):")) {
                char *pos = strstr(buffer, "VRAM Total Used Memory (B):");
                if (pos) {
                    pos += strlen("VRAM Total Used Memory (B):");
                    used_bytes = atoll(pos);
                }
            }
            gpu_found = 1;
        }
    }
    pclose(fp);
    
    if (gpu_found && total_bytes > 0) {
        return (used_bytes * 100) / total_bytes;
    }
    return 0;
}