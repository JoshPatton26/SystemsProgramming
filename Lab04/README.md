CS332: Lab04

This assignment asked us to write code that will take two text file in the command arguments and append the contents of one folder into the other
with out overwriting the content in the destination file. 

I was informed on 9/16/22 by the TA's that we were allowed to use the source code for this assignment and make the necessary changes to this file to complete the assignment. 

I used the source code for my submission and changed the writeFileDescriptor open flag from truncate to append. 

I ran this on the Vulcan server and the code ran fine on my computer with no warnings or errors. 

Following the instructions in the Lab04.pdf I used the 'cat' command to display all the contents in each text file before runninng the code.
Then, I compiled my code by using 'gcc -o lab04 lab04.c' and ran the code using './lab04 file2.txt file1.txt' 
Finally, I did the 'cat' command for each file once more, when it showed the file1.txt containing the content from both files.