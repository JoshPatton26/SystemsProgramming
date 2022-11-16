CS332: Lab12

This lab asked us to modify some source code and implement a multi-thread process to compute the sum of an array of elements. It asked us to implement a struct to hold all the values of the computation and to pass the struct as an argument to the pthread_create() function. When you run the code it will ask you for 3 arguments, the executable, the number of elements in the arrray, and the number of threads you want to use. Then I created an array of structs so you have one thread per pthread_create() function which will compute the partial sum for the determined amount of elements. At the end it will print the value of the total sum while comparing it to the value that it should be. 

I ran all of my code on the Vulcan server which all ran fine with no errors or warnings on my local machine. 

To test my code you can compile it by "gcc -o lab12 lab012.c -lpthread" and to run it use "./lab10 (number of elements) (number of threads)". I tested mine using values "100 4", "75 3", "6 6", "5 5", "4 4" all of which executed properly.