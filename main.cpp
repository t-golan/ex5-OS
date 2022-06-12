#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK 8192

static char child_stack[STACK];

static int child_fn() {
    printf("PID: %ld\n", (long)getpid());
    chroot(NULL);
    sethostname(hostname, strlen(hostname));
    mkdir('/sys/fs/cgroup/pids');
    return 0;
}

int main() {
    pid_t child_pid = clone(child_fn, child_stack+STACK, CLONE_NEWPID | SIGCHLD | CLONE_NEWUTS, NULL);
    printf("clone() = %ld\n", (long)child_pid);

    waitpid(child_pid, NULL, 0);
    return 0;
}