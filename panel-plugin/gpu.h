/*
 * GPU load header for XFCE system load plugin
 */

#ifndef _XFCE_SYSTEMLOAD_GPU_H_
#define _XFCE_SYSTEMLOAD_GPU_H_

#include <glib.h>

gulong read_gpu0load();
gulong read_gpu1load();

#endif /* _XFCE_SYSTEMLOAD_GPU_H_ */