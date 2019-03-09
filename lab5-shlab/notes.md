父进程和子进程是并发执行的
signal handler 和 其他的进程也是并发执行的
那么就不能保证每个进程的执行进度，也不能保证某一个进程A一定会比其他的进程先执行。这种情况下，会出现对某些资源的竞争。


1. eval

该函数接收用户传入的命令和相应的参数。在parseline函数中对其进行解析，并放入argv当中。如果argv[0]为空，那么就表示用户并没有传入有效的参数，那么就直接返回。

如果argv[0]不为空，那么就判断这个命令是不是内置的命令。内置的命令包括 quit, fg, bg, jobs。其余的命令可能是linux平台自己带的命令，比如 ls，ps 之类的，这类命令不是我们的tsh自带的，那么就开一个子进程，让其运行。

父进程在 Fork 一个子进程之后，会把子进程作为要给 job 添加到一个全局的 jobs 链表当中。

在使用子进程运行某一个命令的时候，会出现这个命令是不存在的情况，这时候 execve 会返回 -1。那么就应该输出相应的提醒，然后直接返回。

在 Fork 要给子进程之前，需要屏蔽 SIGCHLD 信号。想象一下，在 Fork 了子进程之后，内核可能会直接调度子进程，子进程死亡，相应的 job 也已经结束，然后发送要给 SIGCHLD 到父进程。大多数时候，这是没有什么问题的。但是因为存在一个全局的 jobs 数据结构，如果父进程在被内核调度执行之前，发现了还存在一个 SIGCHLD，那么他会直接先去调用相应的 handler 程序，很可能会在 handler 程序中 删除 已经结束的 job。问题是，这个时候父进程还并未将 job 加入到 jobs。这就会出现 handler 和父进程对全局的 jobs 的竞争。所以，应该先屏蔽掉 SIGCHLD 信号，然后将 job 加入到 jobs， 之后解除这个屏蔽，就可以正常地解决 handler 和 父进程之间的竞争关系。为了保证全局数据结构的安全性，甚至应该在操作的时候，屏蔽掉所有的信号，然后在执行了对全局数据结构的操作之后再解除。注意，屏蔽信号的操作发生在 Fork 之前，Fork 之后的子进程这个时候是继承了对信号的屏蔽。而子进程可能还会生成子进程，这时候就应该解除子进程当中对相应信号的屏蔽，不然的话，子进程无法接收到二级子进程的相应信号。

job 分为两种，前台 和 后台。对于前台信号，需要等待其结束。对于后台信号，可以直接返回到命令运行之前的状态。

2. void waitfg(pid_t pid)
该函数接收的pid参数指的是才生成的前台 job 的进程号。前台进程只有一个，当前台进程结束的时候，该进程会被收割，然后就和 fgpid 返回的前台进程号不一样，在此过程中，使用 Sigsuspend，将当前进程挂起。

3. sigint_handler(int sig), sigtstp_handler(int)
这两个方法分别用于修改默认的 SIGINT 和 SIGTSTP 的行为。找到唯一的前台 job 的进程号，发送 SIGINT 或 SIGTSTP 信号。

4. sigchld_handler(int sig)
该方法用于处理 SIGCHLD 信号的行为。SIGCHLD 信号触发的原因可能是 1.一个子进程终止，正常的或不正常的。2. 子进程收到了 SIGCONT 信号。3. 收到了 SIGSTOP 或 SIGTSTP信号。

在该 handler 当中，如果触发的原因是有子进程退出，出现了僵死进程，那么就收割该进程。通过 WIFEXITED(status)判断是不是因为 exit 或 返回而正常终止的，如果是，那么就在此修改 jobs 链表，在操作前，需要锁住该链表。如果是因为信号被终止的，那么就获取终止该进程的信号，修改jobs链表，打印出信号的相关信息。

5. do_bgfg

使用该方法处理 fg 和 bg 这两个内置的命令。bg <job> 将一个停止的后台job变成运行的。 fg <job> 将一个停止的或正在运行的后台 job 变成在前台运行。

第一步就应该是判断是否给出了 pid 或者 jid。如果没有，直接报告相关提示然后返回。

根据 pid 或者 jid 从 jobs 列表中找相应的job，如果没找到，或者找到了但是状态是 UNDEF， 报告相关提示，然后返回。

找到了合法的 job。如果运行的命令是 bg， 那么就判断 job 的状态，如果正好是BG， 那么什么都不做。如果是ST， 则改变状态为BG。如果运行的命令是 fg，先判断 job 的状态，如果是ST, 那么就发送 SIGCONT 到这个 job， 让其从新开始执行， 并且在前台等待其运行完成。如果是一个 BG ，那么直接在前台等待运行完成。


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
