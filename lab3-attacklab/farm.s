
farm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <start_farm>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	b8 01 00 00 00       	mov    $0x1,%eax
   9:	5d                   	pop    %rbp
   a:	c3                   	retq   

000000000000000b <getval_142>:
   b:	55                   	push   %rbp
   c:	48 89 e5             	mov    %rsp,%rbp
   f:	b8 fb 78 90 90       	mov    $0x909078fb,%eax
  14:	5d                   	pop    %rbp
  15:	c3                   	retq   

0000000000000016 <addval_273>:
  16:	55                   	push   %rbp
  17:	48 89 e5             	mov    %rsp,%rbp
  1a:	89 7d fc             	mov    %edi,-0x4(%rbp)
  1d:	8b 45 fc             	mov    -0x4(%rbp),%eax
  20:	2d b8 76 38 3c       	sub    $0x3c3876b8,%eax
  25:	5d                   	pop    %rbp
  26:	c3                   	retq   

0000000000000027 <addval_219>:
  27:	55                   	push   %rbp
  28:	48 89 e5             	mov    %rsp,%rbp
  2b:	89 7d fc             	mov    %edi,-0x4(%rbp)
  2e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  31:	2d af 8c a7 6f       	sub    $0x6fa78caf,%eax
  36:	5d                   	pop    %rbp
  37:	c3                   	retq   

0000000000000038 <setval_237>:
  38:	55                   	push   %rbp
  39:	48 89 e5             	mov    %rsp,%rbp
  3c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  40:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  44:	c7 00 48 89 c7 c7    	movl   $0xc7c78948,(%rax)
  4a:	5d                   	pop    %rbp
  4b:	c3                   	retq   

000000000000004c <setval_424>:
  4c:	55                   	push   %rbp
  4d:	48 89 e5             	mov    %rsp,%rbp
  50:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  54:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  58:	c7 00 54 c2 58 92    	movl   $0x9258c254,(%rax)
  5e:	5d                   	pop    %rbp
  5f:	c3                   	retq   

0000000000000060 <setval_470>:
  60:	55                   	push   %rbp
  61:	48 89 e5             	mov    %rsp,%rbp
  64:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  68:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  6c:	c7 00 63 48 8d c7    	movl   $0xc78d4863,(%rax)
  72:	5d                   	pop    %rbp
  73:	c3                   	retq   

0000000000000074 <setval_426>:
  74:	55                   	push   %rbp
  75:	48 89 e5             	mov    %rsp,%rbp
  78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  7c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  80:	c7 00 48 89 c7 90    	movl   $0x90c78948,(%rax)
  86:	5d                   	pop    %rbp
  87:	c3                   	retq   

0000000000000088 <getval_280>:
  88:	55                   	push   %rbp
  89:	48 89 e5             	mov    %rsp,%rbp
  8c:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  91:	5d                   	pop    %rbp
  92:	c3                   	retq   

0000000000000093 <mid_farm>:
  93:	55                   	push   %rbp
  94:	48 89 e5             	mov    %rsp,%rbp
  97:	b8 01 00 00 00       	mov    $0x1,%eax
  9c:	5d                   	pop    %rbp
  9d:	c3                   	retq   

000000000000009e <add_xy>:
  9e:	55                   	push   %rbp
  9f:	48 89 e5             	mov    %rsp,%rbp
  a2:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  a6:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  aa:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  ae:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  b2:	48 01 d0             	add    %rdx,%rax
  b5:	5d                   	pop    %rbp
  b6:	c3                   	retq   

00000000000000b7 <getval_481>:
  b7:	55                   	push   %rbp
  b8:	48 89 e5             	mov    %rsp,%rbp
  bb:	b8 5c 89 c2 90       	mov    $0x90c2895c,%eax
  c0:	5d                   	pop    %rbp
  c1:	c3                   	retq   

00000000000000c2 <setval_296>:
  c2:	55                   	push   %rbp
  c3:	48 89 e5             	mov    %rsp,%rbp
  c6:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  ca:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  ce:	c7 00 99 d1 90 90    	movl   $0x9090d199,(%rax)
  d4:	5d                   	pop    %rbp
  d5:	c3                   	retq   

00000000000000d6 <addval_113>:
  d6:	55                   	push   %rbp
  d7:	48 89 e5             	mov    %rsp,%rbp
  da:	89 7d fc             	mov    %edi,-0x4(%rbp)
  dd:	8b 45 fc             	mov    -0x4(%rbp),%eax
  e0:	2d 77 31 87 36       	sub    $0x36873177,%eax
  e5:	5d                   	pop    %rbp
  e6:	c3                   	retq   

00000000000000e7 <addval_490>:
  e7:	55                   	push   %rbp
  e8:	48 89 e5             	mov    %rsp,%rbp
  eb:	89 7d fc             	mov    %edi,-0x4(%rbp)
  ee:	8b 45 fc             	mov    -0x4(%rbp),%eax
  f1:	2d 73 2e df 24       	sub    $0x24df2e73,%eax
  f6:	5d                   	pop    %rbp
  f7:	c3                   	retq   

00000000000000f8 <getval_226>:
  f8:	55                   	push   %rbp
  f9:	48 89 e5             	mov    %rsp,%rbp
  fc:	b8 89 d1 48 c0       	mov    $0xc048d189,%eax
 101:	5d                   	pop    %rbp
 102:	c3                   	retq   

0000000000000103 <setval_384>:
 103:	55                   	push   %rbp
 104:	48 89 e5             	mov    %rsp,%rbp
 107:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 10b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 10f:	c7 00 81 d1 84 c0    	movl   $0xc084d181,(%rax)
 115:	5d                   	pop    %rbp
 116:	c3                   	retq   

0000000000000117 <addval_190>:
 117:	55                   	push   %rbp
 118:	48 89 e5             	mov    %rsp,%rbp
 11b:	89 7d fc             	mov    %edi,-0x4(%rbp)
 11e:	8b 45 fc             	mov    -0x4(%rbp),%eax
 121:	2d bf b7 76 1f       	sub    $0x1f76b7bf,%eax
 126:	5d                   	pop    %rbp
 127:	c3                   	retq   

0000000000000128 <setval_276>:
 128:	55                   	push   %rbp
 129:	48 89 e5             	mov    %rsp,%rbp
 12c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 130:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 134:	c7 00 88 c2 08 c9    	movl   $0xc908c288,(%rax)
 13a:	5d                   	pop    %rbp
 13b:	c3                   	retq   

000000000000013c <addval_436>:
 13c:	55                   	push   %rbp
 13d:	48 89 e5             	mov    %rsp,%rbp
 140:	89 7d fc             	mov    %edi,-0x4(%rbp)
 143:	8b 45 fc             	mov    -0x4(%rbp),%eax
 146:	2d 77 31 6f 6f       	sub    $0x6f6f3177,%eax
 14b:	5d                   	pop    %rbp
 14c:	c3                   	retq   

000000000000014d <getval_345>:
 14d:	55                   	push   %rbp
 14e:	48 89 e5             	mov    %rsp,%rbp
 151:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
 156:	5d                   	pop    %rbp
 157:	c3                   	retq   

0000000000000158 <addval_479>:
 158:	55                   	push   %rbp
 159:	48 89 e5             	mov    %rsp,%rbp
 15c:	89 7d fc             	mov    %edi,-0x4(%rbp)
 15f:	8b 45 fc             	mov    -0x4(%rbp),%eax
 162:	2d 77 3d ff 36       	sub    $0x36ff3d77,%eax
 167:	5d                   	pop    %rbp
 168:	c3                   	retq   

0000000000000169 <addval_187>:
 169:	55                   	push   %rbp
 16a:	48 89 e5             	mov    %rsp,%rbp
 16d:	89 7d fc             	mov    %edi,-0x4(%rbp)
 170:	8b 45 fc             	mov    -0x4(%rbp),%eax
 173:	2d 77 31 c7 3f       	sub    $0x3fc73177,%eax
 178:	5d                   	pop    %rbp
 179:	c3                   	retq   

000000000000017a <setval_248>:
 17a:	55                   	push   %rbp
 17b:	48 89 e5             	mov    %rsp,%rbp
 17e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 182:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 186:	c7 00 81 ce 08 db    	movl   $0xdb08ce81,(%rax)
 18c:	5d                   	pop    %rbp
 18d:	c3                   	retq   

000000000000018e <getval_159>:
 18e:	55                   	push   %rbp
 18f:	48 89 e5             	mov    %rsp,%rbp
 192:	b8 89 d1 38 c9       	mov    $0xc938d189,%eax
 197:	5d                   	pop    %rbp
 198:	c3                   	retq   

0000000000000199 <addval_110>:
 199:	55                   	push   %rbp
 19a:	48 89 e5             	mov    %rsp,%rbp
 19d:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1a0:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1a3:	2d 38 76 1f 3c       	sub    $0x3c1f7638,%eax
 1a8:	5d                   	pop    %rbp
 1a9:	c3                   	retq   

00000000000001aa <addval_487>:
 1aa:	55                   	push   %rbp
 1ab:	48 89 e5             	mov    %rsp,%rbp
 1ae:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1b1:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1b4:	2d 77 3d 7b 3f       	sub    $0x3f7b3d77,%eax
 1b9:	5d                   	pop    %rbp
 1ba:	c3                   	retq   

00000000000001bb <addval_201>:
 1bb:	55                   	push   %rbp
 1bc:	48 89 e5             	mov    %rsp,%rbp
 1bf:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1c2:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1c5:	2d b8 76 1f 38       	sub    $0x381f76b8,%eax
 1ca:	5d                   	pop    %rbp
 1cb:	c3                   	retq   

00000000000001cc <getval_272>:
 1cc:	55                   	push   %rbp
 1cd:	48 89 e5             	mov    %rsp,%rbp
 1d0:	b8 99 d1 08 d2       	mov    $0xd208d199,%eax
 1d5:	5d                   	pop    %rbp
 1d6:	c3                   	retq   

00000000000001d7 <getval_155>:
 1d7:	55                   	push   %rbp
 1d8:	48 89 e5             	mov    %rsp,%rbp
 1db:	b8 89 c2 c4 c9       	mov    $0xc9c4c289,%eax
 1e0:	5d                   	pop    %rbp
 1e1:	c3                   	retq   

00000000000001e2 <setval_299>:
 1e2:	55                   	push   %rbp
 1e3:	48 89 e5             	mov    %rsp,%rbp
 1e6:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1ea:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 1ee:	c7 00 48 89 e0 91    	movl   $0x91e08948,(%rax)
 1f4:	5d                   	pop    %rbp
 1f5:	c3                   	retq   

00000000000001f6 <addval_404>:
 1f6:	55                   	push   %rbp
 1f7:	48 89 e5             	mov    %rsp,%rbp
 1fa:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1fd:	8b 45 fc             	mov    -0x4(%rbp),%eax
 200:	2d 77 31 6d 3c       	sub    $0x3c6d3177,%eax
 205:	5d                   	pop    %rbp
 206:	c3                   	retq   

0000000000000207 <getval_311>:
 207:	55                   	push   %rbp
 208:	48 89 e5             	mov    %rsp,%rbp
 20b:	b8 89 d1 08 db       	mov    $0xdb08d189,%eax
 210:	5d                   	pop    %rbp
 211:	c3                   	retq   

0000000000000212 <setval_167>:
 212:	55                   	push   %rbp
 213:	48 89 e5             	mov    %rsp,%rbp
 216:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 21a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 21e:	c7 00 89 d1 91 c3    	movl   $0xc391d189,(%rax)
 224:	5d                   	pop    %rbp
 225:	c3                   	retq   

0000000000000226 <setval_328>:
 226:	55                   	push   %rbp
 227:	48 89 e5             	mov    %rsp,%rbp
 22a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 22e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 232:	c7 00 81 c2 38 d2    	movl   $0xd238c281,(%rax)
 238:	5d                   	pop    %rbp
 239:	c3                   	retq   

000000000000023a <setval_450>:
 23a:	55                   	push   %rbp
 23b:	48 89 e5             	mov    %rsp,%rbp
 23e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 242:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 246:	c7 00 09 ce 08 c9    	movl   $0xc908ce09,(%rax)
 24c:	5d                   	pop    %rbp
 24d:	c3                   	retq   

000000000000024e <addval_358>:
 24e:	55                   	push   %rbp
 24f:	48 89 e5             	mov    %rsp,%rbp
 252:	89 7d fc             	mov    %edi,-0x4(%rbp)
 255:	8b 45 fc             	mov    -0x4(%rbp),%eax
 258:	2d f8 76 1f 6f       	sub    $0x6f1f76f8,%eax
 25d:	5d                   	pop    %rbp
 25e:	c3                   	retq   

000000000000025f <addval_124>:
 25f:	55                   	push   %rbp
 260:	48 89 e5             	mov    %rsp,%rbp
 263:	89 7d fc             	mov    %edi,-0x4(%rbp)
 266:	8b 45 fc             	mov    -0x4(%rbp),%eax
 269:	05 89 c2 c7 3c       	add    $0x3cc7c289,%eax
 26e:	5d                   	pop    %rbp
 26f:	c3                   	retq   

0000000000000270 <getval_169>:
 270:	55                   	push   %rbp
 271:	48 89 e5             	mov    %rsp,%rbp
 274:	b8 88 ce 20 c0       	mov    $0xc020ce88,%eax
 279:	5d                   	pop    %rbp
 27a:	c3                   	retq   

000000000000027b <setval_181>:
 27b:	55                   	push   %rbp
 27c:	48 89 e5             	mov    %rsp,%rbp
 27f:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 283:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 287:	c7 00 48 89 e0 c2    	movl   $0xc2e08948,(%rax)
 28d:	5d                   	pop    %rbp
 28e:	c3                   	retq   

000000000000028f <addval_184>:
 28f:	55                   	push   %rbp
 290:	48 89 e5             	mov    %rsp,%rbp
 293:	89 7d fc             	mov    %edi,-0x4(%rbp)
 296:	8b 45 fc             	mov    -0x4(%rbp),%eax
 299:	2d 77 3d 9f 2d       	sub    $0x2d9f3d77,%eax
 29e:	5d                   	pop    %rbp
 29f:	c3                   	retq   

00000000000002a0 <getval_472>:
 2a0:	55                   	push   %rbp
 2a1:	48 89 e5             	mov    %rsp,%rbp
 2a4:	b8 8d ce 20 d2       	mov    $0xd220ce8d,%eax
 2a9:	5d                   	pop    %rbp
 2aa:	c3                   	retq   

00000000000002ab <setval_350>:
 2ab:	55                   	push   %rbp
 2ac:	48 89 e5             	mov    %rsp,%rbp
 2af:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 2b3:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2b7:	c7 00 48 89 e0 90    	movl   $0x90e08948,(%rax)
 2bd:	5d                   	pop    %rbp
 2be:	c3                   	retq   

00000000000002bf <end_farm>:
 2bf:	55                   	push   %rbp
 2c0:	48 89 e5             	mov    %rsp,%rbp
 2c3:	b8 01 00 00 00       	mov    $0x1,%eax
 2c8:	5d                   	pop    %rbp
 2c9:	c3                   	retq   
