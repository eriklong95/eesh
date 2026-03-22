# Issues

## Wrong command line when running `jobs`

When some background jobs are running and the user runs the built-in `jobs` command,
the correct JIDs and PIDs are listed, but the command lines are stated as `jobs` instead
of the correct command.

- How can an item be added to the jobs list?

when the error occurs, we don't hit a breakpoint in `register_job_in_list` after running `jobs`

we get a segmentation fault from `remove_job_from_list`