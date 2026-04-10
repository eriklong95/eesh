# Issues

## [RESOLVED] Wrong command line when running `jobs`

When some background jobs are running and the user runs the built-in `jobs` command,
the correct JIDs and PIDs are listed, but the command lines are stated as `jobs` instead
of the correct command.

- How can an item be added to the jobs list?

when the error occurs, we don't hit a breakpoint in `register_job_in_list` after running `jobs`

we get a segmentation fault from `remove_job_from_list`

## [RESOLVED] Are we sure we reap child processes?

If the PID of a process is returned by `waitpid, it has been reaped.

Idea: comment out reaper code and check what happens

What does a `Z` value in the `S` column of the output of `ps -l` mean? It is a zombie

it works

## ^C and ^Z not handled correctly

if user sends a SIGINT to eesh by typing ^C while writing a command -> new prompt

### Step 1: Handle SIGINT from empty command line [DONE]

eesh must have the following behaviour:

1. User starts eesh. eesh prints a `>`
2. User sends SIGINT by typing ^C
3. eesh prints a new `>`

### Step 2: Handle SIGTSTP to foreground job

Desired behaviour

1. User types `/usr/bin/sleep 30` in the eesh prompt and hits Enter.
2. Program starts as foreground job
3. User sends SIGTSTP to eesh by typing `^Z`
4. eesh sends SIGTSTP to foreground job
5. `Stopped ...` is printed
6. User presented with new prompt
7. User types `quit` and hits Enter
8. eesh terminates

How can we verify that a process has received a SIGTSTP? Use `ps -al`, state is `T`

Actually, when the foreground job receives SIGTSTP it should be transformed into a background job!

When you `kill -9` the child process manually, you return to a healthy state.
`kill -20` (SIGTSTP) does not work

counter program is actually stopped with `kill -20 <pid>` from other terminal. Can we continue? Yes

It seems that we don't enter the signal handler installed in the child process. Is it not installed
correctly? `execve` changes process

### Step 3: Handle SIGTSTP while writing cmd

1. User starts eesh. eesh prints a `>`
2. User sends SIGTSTP by typing ^Z
3. eesh ignores the signal, ^Z is not even printed

### Step 4: Make process appear in job list after it has been stopped
