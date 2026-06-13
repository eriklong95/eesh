# Issues

This file lists issues that have not yet been fixed.

## Restarted job appears twice in jobs list

The job list does not handle correctly the situation where a job is stopped, restarted and then stopped.
In fact, such a job ends up appearing twice in the job list.

### Steps to reproduce

- Run `make`, then run `./build/eesh` to start eesh.
- Enter `/usr/bin/sleep 60` into eesh's prompt and press enter to run `sleep` in the foreground.
- Enter ^Z to stop the `sleep` program.
- Run the built-in `jobs` command to display the job list. The `sleep` program appears as the job with JID 1.
- Run `fg 1` to restart the job, then enter ^Z to stop it again.
- Run `jobs`. We now see TWO ENTRIES for the `sleep` program, JIDs 1 and 2.

Expected behavior: The job only appears once with JID 1.