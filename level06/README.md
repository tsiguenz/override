# Walkthrough level06

First, we have tried the program:


```bash
explevel06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: AAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42
```

We have write the code to understand what happen. We have found a `magic number`. We have found a page who explain [this](https://reverseengineering.stackexchange.com/questions/1397/how-can-i-reverse-optimized-integer-division-modulo-by-constant-operations)
Secondly we have use gdb to obtains the value.  

```bash
(gdb) b *0x080487ba
Breakpoint 8 at 0x80487ba
(gdb) b *0x08048866
Breakpoint 9 at 0x8048866
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: AAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 1
Breakpoint 8, 0x080487ba in auth ()
```

We must set eax register to enter in our condition. Because of in gdb ptrace function return -1.    

```bash
(gdb) i r $eax
eax            0xffffffff	-1
(gdb) set $eax=0
(gdb) ni
0x080487bd in auth ()
(gdb) n
Single stepping until exit from function auth,
which has no line number information.

Breakpoint 2, 0x08048866 in auth ()
```
Now we are after the while. We can check the value of the condition to exploit the program.

```bash
=> 0x08048866 <+286>:	cmp    eax,DWORD PTR [ebp-0x10]

(gdb) i r eax
eax            0x1	1
(gdb) x/w $ebp-0x10
0xffffd6a8:	6229050
```

eax register is our serial and $ebp-0x10 is the value searched.  
We can now try with the value obtains in gdb.   

```bash
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: AAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6229050
Authenticated!
$ whoami 
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

We can obtain the value with a printf in the code, after the while.

```c
	printf("Value: %u\n", modulo);
```

