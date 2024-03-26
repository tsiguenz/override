# Walkthrough level03

First we have execute the program.  

```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:18

Invalid Password
```

With the disassembly code we have write c code. A substraction with 0x1337d00d is performed. We name this result `offset`. The offset must be above of 21 to run decrypt function with it.   
In decrypt funtion, we have a buffer in which we add the offset for each byte.  
We must convert our buffer to obtains "Congratulations!".

```
0x33617c7d | 0x7b66737e | 0x67667360 | 0x757c7d51 | 0x00
   g n o C |    u t a r |    i t a l |    ! s n o |
```

We can see that 'a' = '0x73'.  
'0x73' = 115
'a' = 97
`offset` = 115 - 97 = 18

So we want obtain 18 in parameter of decrytp.  
```python
>>> 0x1337d00d - 18
322424827
```

```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ id
uid=1003(level03) gid=1003(level03) euid=1004(level04) egid=100(users) groups=1004(level04),100(users),1003(level03)
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf

```