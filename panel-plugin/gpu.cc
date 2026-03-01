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
    const char *command = "/opt/rocm/bin/rocm-smi --showuse 2>/dev/null";
    
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
    const char *command = "/opt/rocm/bin/rocm-smi --showuse 2>/dev/null";
    
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
    const char *command = "/opt/rocm/bin/rocm-smi --showmeminfo vram 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        char *pos = strstr(buffer, "GPU ");
        if (pos) {
            // Look for VRAM usage pattern like "GPU 0: VRAM Total Used: 1024 MB, Total: 8192 MB"
            char *used_pos = strstr(buffer, "Used:");
            if (used_pos && gpu_count == 0) {
                used_pos += strlen("Used:");
                char *mb_pos = strstr(used_pos, " MB");
                if (mb_pos) {
                    *mb_pos = '\0';
                    gulong used_mb = atoi(used_pos);
                    
                    // Find total memory
                    char *total_pos = strstr(mb_pos + 3, "Total:");
                    if (total_pos) {
                        total_pos += strlen("Total:");
                        char *total_mb_pos = strstr(total_pos, " MB");
                        if (total_mb_pos) {
                            *total_mb_pos = '\0';
                            gulong total_mb = atoi(total_pos);
                            if (total_mb > 0) {
                                usage = (used_mb * 100) / total_mb;
                            }
                        }
                    }
                }
            }
            gpu_count++;
        }
    }
    pclose(fp);
    return usage;
}

gulong read_vram1usage()
{
    /* Use the known working path for rocm-smi */
    const char *command = "/opt/rocm/bin/rocm-smi --showmeminfo vram 2>/dev/null";
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return 0;
    }
    
    char buffer[256];
    gulong usage = 0;
    int gpu_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL && gpu_count < 2) {
        char *pos = strstr(buffer, "GPU ");
        if (pos) {
            // Look for VRAM usage pattern like "GPU 1: VRAM Total Used: 1024 MB, Total: 8192 MB"
            char *used_pos = strstr(buffer, "Used:");
            if (used_pos && gpu_count == 1) {
                used_pos += strlen("Used:");
                char *mb_pos = strstr(used_pos, " MB");
                if (mb_pos) {
                    *mb_pos = '\0';
                    gulong used_mb = atoi(used_pos);
                    
                    // Find total memory
                    char *total_pos = strstr(mb_pos + 3, "Total:");
                    if (total_pos) {
                        total_pos += strlen("Total:");
                        char *total_mb_pos = strstr(total_pos, " MB");
                        if (total_mb_pos) {
                            *total_mb_pos = '\0';
                            gulong total_mb = atoi(total_pos);
                            if (total_mb > 0) {
                                usage = (used_mb * 100) / total_mb;
                            }
                        }
                    }
                }
            }
            gpu_count++;
        }
    }
    pclose(fp);
    return usage;
}