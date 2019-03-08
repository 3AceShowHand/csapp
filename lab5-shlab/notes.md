```
pid_t getpid() : 获取当前进程的pid
pid_t getppid(): 获取当前进程的父进程的pid

exit(int status): 进程以 status 为状态终止
pid_t fork()： 创建新的进程，新创建的进程为现运行进程的子进程，有相同的内存内容副本，不同的pid。子进程和父进程之间，是并发执行的。该函数向子进程返回0，向父进程返回子进程的pid。如果返回-1，则表示出错。

pid_t waitpid(pid_t pid, int* statusp, int options)：该函数可以用于回收僵死进程。在父进程中调用该函数，等待子进程完成所有的操作并退出。
pid用于指定调用函数的等待集合。
if pid > 0 ： 等待集合是指定的子进程
if pid = -1： 等待集合是所有该进程的子进程

options = 0：该参数为默认，父进程进入阻塞状态。一直等待等待集合中的一个子进程终止。
options = WNOHANG：设置该参数的时候，如果等待集合的所有子进程都没有终止，那么立即返回0。不会等待子进程终止
options = WUNTRACED：
options = WCONTINUED：挂起调用进程的执行，直到等待集中中一个正在运行的进程终止或等待集合中一个被停止的进程收到SIGCONT信号重新开始执行。

if statusp != NULL, 如果statusp不为空，那么子进程退出时候的状态会被传入到该参数里面。可以用于判断子进程是为何而亡

WIFEXITED(status)：如果子进程因为调用exit或return而正常终止，那么返回真。
WEXITSTATUS(status)：返回一个正常终止的子进程的退出状态

WIFSIGNALED(status)： 如果子进程因为一个未被捕获的信号终止，那么返回真。
WTERMSIG(status)： 返回导致子进程终止的那个信号的编号。

WIFSTOPPED(status)：如果引起返回的子进程当前是停止的，返回真。
WSTOPSIG(status)：返回导致子进程停止的那个信号的编号

WIFCONTINUED(status)： 如果子进程收到 SIGCONT信号重新启动，那么返回真。

wait(int* statusp): wait(&status) = waitpid(-1, &status, 0);

unsigned int sleep(unsigned int secs)：调用该函数的进程睡眠 指定的时长，如果被其他信号中断而过早地返回，那么返回剩余的时间数。
int pause()：调用函数的进程被暂停在此处，直到接收到一个信号。

int execve(const char* filename, const char* argv[], const char\* envp[])：在现有进程的内存空间中，调入指定的程序和相关参数及环境。该函数调用一次，正常情况下，从不返回。如果返回，必然是返回-1，表示出现了错误。

char* getenv(const char* name)：获取指定name对应的value， 如果name不在环境中，则返回NULL。
int setenv(const char* name, const char* newvalue, int overwrite)： 修改env中指定name的value为newvalue，仅当overwrite非0时。
void unsetenv(const char* name)： 从env中删除指定的name对应的value

pid_t getpgrp()： 获取当前进程的 组id
int setpgid(pid_t pid, pid_t pgid)： 设置指定 pid 的 组id

int kill(pid_t pid, int sig)： 向 指定pid的进程发送 信号sig
unsigned int alarm(unsigned int secs)： 调用该函数的进程在指定时间secs之后，向自己发送一个信号

typedef void (*sighandler_t)(int)
sighandler_t signal(int signum, sighandler_t handler)： 用于设置 signum对应的handler函数，可以用于修改signum默认的信号处理函数的行为。

handler = SIG_IGN： 忽略该信号
handler = SIG_DFL： 恢复到默认的行为

int sigprocmask(int how, const sigset_t* set, sigset_t* oldset)： 用于改变当前进程的阻塞信号集合的情况。
how = SIG_BLOCK：把set中的信号，添加到blocked当中。
how = SIG_UNBLOCK：从blocked中，删除set的信号
how = SIG_SETMASK：让blocked = set

int sigemptyset(sigset_t* set): 清空一个向量
int sigfillset(sigset_t* set)： 装满一个向量
int sigaddset(sigset_t* set, int signum)：在指定的set里面添加信号signum
int sigdelset(sigset_t* set, int signum)：在指定的set里面删除信号signum

int sigismember(const sigset_t* set, int signum)： 判断一个指定的signum是不是set中为真

G0. 处理程序尽可能简单。
G1. 在处理函数中只调用异步信号处理函数 （可重入的，不能被信号处理中断的）
G2. 保存和恢复 errno
G3. 阻塞所有的信号，保护对共享全局数据结构的访问。
G4. 用 volatile 声明全局变量。
G5. 用 sig_atomic_t 声明标志。

int sigsuspend(const sigset_t* mask)：暂时用mask替换当前的阻塞信号集合，然后将该进程挂起，直到收到了一个信号，要么是运行一个处理程序，要么是终止该进程。
```
