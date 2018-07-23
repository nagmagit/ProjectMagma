#include <sys/syscalls.h>
#include <sys/desctables.h>

#include <debug.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

// syscall.asm
extern void syscall_do();

void syscall_testcall(struct regs_t *r);

void* handlers[255];

void syscall_install(int int_no)
{
    idt_set_gate(int_no, (unsigned)syscall_do, 0x08, 0x8E);

    handlers[0] = (void*)syscall_testcall;
}

void syscall_handler(struct regs_t *r)
{
    #ifdef DEBUG
    char buffer[16];
    uint32_t r_ax = r->eax;

    kernel_lineString("\r\nSyscall!");

    kernel_putString("Syscall's function number: ");
    itoa(r_ax, buffer, 16);
    kernel_lineString(buffer);
    #endif
    
    void (*handler)(struct regs_t *r) = handlers[r->eax];
    if (handler == NULL) r->eax = (int)0;
    else handler(r);

    #ifdef DEBUG
    r_ax = r->eax;

    char* ax_r = (char*)r_ax;

    kernel_putString("Returned: ");
    kernel_lineString(ax_r);
    #endif
}

void syscall_testcall(struct regs_t *r)
{
    r->eax = (int)"OK!";
}