# Experiment #1: Forking processes

## The `fork` system call

Read the **forking_hell.c** source file and
have a go at guessing what output the program
will produce.

Compile and run forking_hell.c. Any surprises? 
Can you explain what is going on? What is
the value returned by `fork`?

## Getting there first

The conditional statement that takes up most of
the lines in **forking_hell.c** has three branches
which are guarded by the conditions `rc < 0`,
`rc == 0` and `rc > 0`.

As you have probably already seen, we usually enter
both the `rc == 0` and the `rc > 0` branch (??#!!?%!).
We see print statements coming from both of these branches.
Which of them comes first? Always? Can you modify the program
to change that?

Under what conditions do we enter the `rc < 0` branch?
