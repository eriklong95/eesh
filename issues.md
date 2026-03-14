# Issues

## Wrong command line when running `jobs`

When some background jobs are running and the user runs the built-in `jobs` command,
the correct JIDs and PIDs are listed, but the command lines are stated as `jobs` instead
of the correct command.