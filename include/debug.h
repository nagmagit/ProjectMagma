#ifndef __DEBUG_H
#define __DEBUG_H

extern void kernel_putString(char* str);
extern void kernel_lineString(char* str);

extern void kernel_putStacktrace(int max);

#endif