#include <stdio.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	pid_t pid		 = fork();
	int	  syscall_nb = 0;
	int	  a			 = 0;
	int	  b			 = 0;
	int	  status1	 = 0;
	char  buffer[128];
	int	  status2 = 0;
	if (pid == 0) {
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PTRACE_TRACEME);
		puts("Give me some shellcode, k");
		gets(buffer);
		return 1;
	} else {
		while (1) {
			wait(&status2);
			status1 = status2;
			if ((status2 & 127) == 0) {
				break;
			}
			b = status2;
			b = ((b & 128) + 1) >> 1;
			if (b <= 0) {
				syscall_nb = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
				if (syscall_nb == 11) {
					puts("no exec() for you");
					kill(pid, 9);
					return 0;
				}
			} else {
				break;
			}
		}
	}
	puts("child is exiting...");
	return 0;
}
