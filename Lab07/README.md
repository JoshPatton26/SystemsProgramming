This assignment asked us to open a file, read the contents(linux commands) line by line, and execute each of the linux commands that are contained within. This assignment wanted us to use the fork-exec method to operate the process seperately. After this it wanted us to open another file and write what commands were executed and how long it took the computer to execute these commands.

I compiled and ran my code on the Vulcan server and everything ran fine with no warnings or errors.

For some reason when I tried to use the ctime() function it would keep messing up my argument list and wouldn't execute the linux commands properly so I did not end up writing the times in my outputlog.txt file. The outputlog.txt file will only contain which linux commands were executed.

to compile my code you will need to be on the Vulcan server and you can use the command 'gcc -o lab07 lab07.c', and to run my code you need to use './lab07 (name of test file)' 

I tested mine using a text file which contained 'ls -l', 'ls', and 'echo "random stuff"' all of which ran fine until I tried to use fprintf() or fputs() to log down the times from ctime(). I could not figure out why it kept messing up so I just commented these parts out. However, I did print out the start and end time at the end of the code to show that I was using it correctly.