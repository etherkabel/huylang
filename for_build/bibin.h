#ifndef _BIBIN_H
#define _BIBIN_H

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

// Я бы сделал const char * но execve принимает без варнингов только char *const
typedef char *const program_t[];
struct child_t {
  pid_t pid;
  int pipefd;
};

#define READ 0
#define WRITE 1

#ifndef COMPILER
#define COMPILER "clang"
#endif

#ifndef LINKER
#define LINKER "clang"
#endif

#ifndef COMPILER_FLAGS
#define COMPILER_FLAGS "-Wall", "-Wextra", "-Wall", "--std=c99", "-c"
#endif

#ifndef LINKER_FLAGS
#define LINKER_FLAGS "-fuse-ld=lld"
#endif

#define PROG(...) (program_t){__VA_ARGS__, NULL}
#define LEN(var) (sizeof(var) / sizeof var[0])
#define RUN(...) run(PROG(__VA_ARGS__))
#define SPAWN(...) spawn(PROG(__VA_ARGS__))
#define CC(output, ...) RUN(COMPILER, COMPILER_FLAGS, __VA_ARGS__, "-o", output)
#define CC_SPAWN(output, ...) SPAWN(COMPILER, COMPILER_FLAGS, __VA_ARGS__, "-o", output)
#define LD(output, ...) RUN(LINKER, LINKER_FLAGS, __VA_ARGS__, "-o", output)
#define LD_SPAWN(output, ...) SPAWN(LINKER, LINKER_FLAGS, __VA_ARGS__, "-o", output)
#define RM(...) RUN("rm", "-rf", __VA_ARGS__)
#define ETERNAL_LOOP for(;;);

static inline struct child_t spawn(const program_t argv) {

  int pipefd[2];
  if(pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t cpid = fork();
  switch(cpid) {

    case -1: {
      perror ("fork");
    }

    case 0: {
      close(pipefd[READ]);

      if (fcntl(pipefd[WRITE], F_SETFD, fcntl(pipefd[1], F_GETFD) | FD_CLOEXEC) == -1) {
        perror("fcntl");
        close(pipefd[READ]);
        close(pipefd[WRITE]);
        exit(EXIT_FAILURE);
      }

      dup2(pipefd[WRITE], STDOUT_FILENO);
      dup2(pipefd[WRITE], STDERR_FILENO);

      execvp(argv[0], argv);

      if(errno == ENOENT) {
        printf("Executable not found!\n");
        close(pipefd[WRITE]);
        exit(EXIT_FAILURE);
      }

      perror("execvp");
      close(pipefd[WRITE]);
      exit(EXIT_FAILURE);
    }

    default: {
      close(pipefd[WRITE]);
      return (struct child_t) {
        .pid = cpid,
        .pipefd = pipefd[READ]
      };
    }
  }
}

// static inline char *get_signal_name(int sig) {
//   switch(sig) {
//     case SIGINT: return "TERMINAL INTERRUPT SIGNAL (SIGINT)";
//     case SIGTERM: return "POLITE QUIT REQUEST SIGNAL (SIGTERM)";
//     case SIGKILL: return "ULTRAKILL SIGNAL (SIGKILL)";
//     case SIGABRT: return "ABORT SIGNAL (SIGABRT)";
//     case SIGHUP: return "HANGUP SIGNAL (SIGHUP)";
//     case SIGALRM: return "MEMORY ACCESS ERROR SIGNAL (SIGBUS)";
//     case SIGFPE: return "FLOATING POINT EXCEPTION SIGNAL (SIGFPE)";
//     case SIGILL: return "ILLEGAL INSTRUCTION SIGNAL (SIGILL)";
//     case SIGIO: return "I/O EVENT SIGNAL (SIGIO/SIGPOLL)";
//     case SIGPIPE: return "BROKEN PIPE SIGNAL (SIGPIPE)";
//     case SIGPROF: return "PROFILING TIMER SIGNAL (SIGPROF)";
//     case SIGPWR: return "POWER FAILURE SIGNAL (SIGPWR)";
//     case SIGQUIT: return "QUIT SIGNAL (SIGQUIT)";
//     case SIGSEGV: return "SEGMENTATION FAULT SIGNAL (SIGSEGV)";
//     case SIGSTOP: return "STOP SIGNAL (SIGSTOP)";
//     case SIGSYS: return "INVALID SYSTEM CALL SIGNAL (SIGSYS)";
//   }
// }

static inline void run(const program_t argv) {
  struct child_t c = spawn(argv);

  int retval = 0;
  waitpid(c.pid, &retval, 0);

  if(WEXITSTATUS(retval)) {
    int bytes_read = 0;
    char buffer[512];
    printf("\x1b[31m");
    while((bytes_read = read(c.pipefd, buffer, LEN(buffer) - 1))) {
      buffer[bytes_read] = 0;
      printf("%s", buffer);
    }
    printf("\x1b[0m");
  }

  close(c.pipefd);
}

#undef READ
#undef WRITE

#endif
