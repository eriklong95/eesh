try running forking_hell.c
Can you guess what is going on?
Do you get the same output every time?
What do you think the numbers mean?

Try to delete `#include <unistd.h>` and compile (and maybe run) the program. Any errors?
What's an "implicit declaration? 
If you are on Linux, open the file /usr/include/unistd.h
Find the declaration of getpid()
Why does this file exist on your system?
What does it do?

Modify the program by putting in `sleep(5);` in `else` branch
Modify the program by putting in `sleep(5);` in the `else if (rc == 0)` branch
What's the difference between doing these two thing?
Try to find sleep in unistd.h
