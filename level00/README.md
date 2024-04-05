# Walkthrough level00

First we have execute the program.  

```bash
level00@OverRide:~$ ./level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:123

Invalid Password!
```
With the disassembly code we have write c code. A comparaison with a number is make to execute a shell.   
So we have execute the program with this value :  

```bash
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami 
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
level00@OverRide:~$ (python -c 'print 0x149c';cat ) | ./level00
cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```