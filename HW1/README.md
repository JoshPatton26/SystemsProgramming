
For this assignment I was asked to read a csv file containing students with all their information and the courses information that they are enrolled in.
All the code in the hw1.c file is very well documented and should explain to everyone how exactly my code works. I use the Vulcan server to compile and 
run my code, which on my computer runs fine with no issues. 

The main function is responisble for opening and parsing the file while storing the data to a struct called "Students". The main function also calls each 
function to answer individual questions for the assignment. 

All question functions take the count (amount of students in the csv file) and the struct Students
as arguments from the main. 

The question1 function creates a new array to hold all degrees and copies all the degree data from the csv file. After that I use 
an algorithm to delete duplicates from the array holding all degrees. It will then print all the results of the operations.

The question 2 function will create three new arrays to hold firstname, lastname, and gpa for all students in CS. I implemented Insertion Sort from Lab02 
to sort all the students in accending order of GPA while matching each students first and last name to their order of GPA. The function will finish up by printing 
off the last three elements of each array to get the results.

The question 3 function loops through the struct item "credithrs" while getting the summ of all the credit hours of the University. Take the average of this number by 
dividing the total sum of credit hours by the total number of students.

The question 4 function will loop through the struct item "major" and if the students major is "Computer Science" it will get add that students GPA to a variable that 
will contain the sum of all CS students GPA's, this loop also adds one to a new counter which will be used to help with averaging. Average this by dividing the total 
sum of CS majors GPA by the total number of students in CS.

The question 5 function creates a new array for each department in the college as well as a temp varaible used to test for comparrison. Then I will run through the 
struct while using nested if statements to determine which department the advisor are in and add each advisor to their respected array. I use the same algorithm from 
question 1 to delete all duplicate from each of these arrays and print off all departments with the number of unique advisors for that department.
