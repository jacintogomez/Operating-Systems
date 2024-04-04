# Operating Systems Content

## XV6 Command Shell Implementation

  This is an adaptation of the command shell in XV6 that I edited as part of a project for my operating systems class at NYU. It \
was edited to handle command execution, IO redirection (with < and >), and piping the output of one command to the input of another with the `|` operator.

## Using Threads in Parallel with Spinlock and Mutex

  `parallelhashtable.c` contains a hashtable that is meant to be accessed by multiple threads at the same time. The code shows errors with \
parallelism where when a thread writes to a spot in the table, is interrupted for another thread to write to that same spot, then regains control and \
finishes its write. This gives rise to a mistake where not all the slots in the table are full. 

  Our task was to correct this problem using locks around critical sections of the code. In `mutex.c`, I used the C mutex API to place a mutex around each "bucket" that the threads would work with. This ensures that thread inserts will not result in missing key values, and that insert operations could be performed in parallel. I recreated this same functionality in `spinlock.c`, using the C spinlock API to place a spinlock around critical sections.


## Uniq Command in Linux

  This is a simple remake of the Linux "uniq" command. When uniq is called on afile here, it will print out the file omitting repeated \
lines. If uniq is called without a file, it will read from standard input in the terminal using pipes. This implementation can \
also use the -c (count the number of occurrences of a line), -d (only print duplicate lines), and -i (ignore case differences in \
lines) flags that would work with a real Linux machine.
