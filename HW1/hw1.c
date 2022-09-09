#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Used to hold original copy of all data from students_dataset.csv file.
typedef struct Students{
    char firstname[20];
    char lastname[20];
    char major[20];
    char degree[20];
    double gpa;
    int credithrs;
    char ta[20];
    char advisor[20];
}students;

void question1(size_t count, students *student){
    // Defining all variables.
    int i = 0, j = 0, k = 0, counter = 0;
    char temp[5];
    char *degrees[50];

    // Filling new array to modify data with out corrupting original.
    for(i=0; i<count; i++){
        degrees[i] = student[i].degree;  
    }

    // Reference used to help remove all duplicates from degrees array.
    // https://www.tutorialspoint.com/c-program-to-delete-the-duplicate-elements-in-an-array.
    for(i=0; i<count; i++){
        for(j=(i+1); j<count; j++){
            if(strcmp(degrees[i], degrees[j]) == 0){
                for(k=j; k<count; k++){
                    degrees[k] = degrees[k+1];
                }
            j--;
            count--;
            }
        }
    }

    // Print results.
    printf("---- QUESTION 1 ----\n");
    for(i=0; i<count; i++){
        printf("%s\n", degrees[i]);
    }
    printf("\n%ld Degrees total.\n\n", (sizeof(degrees)/100));
    return;
}

void question2(size_t count, students *student){
    // Defining all varaibles.
    int i = 0, j = 0; 
    double key1 = 0.0;
    char *key2 = " ", *key3 = " ";
    double topgpa[50];
    char *firstnames[50];
    char *lastnames[50];

    // Filling new arrays to modify the data without corrupting original.
    for(i=0; i<count; i++){
        topgpa[i] = student[i].gpa;
        firstnames[i] = student[i].firstname;
        lastnames[i] = student[i].lastname;  
    }

    // Implementing Insertion Sort from Lab02.
    for(i=1; i<count; i++){
        // Set key equal to the current index being evaluated.
        key1 = topgpa[i];
        key2 = firstnames[i];
        key3 = lastnames[i];
        j = i - 1;
        // Move each element that is greater than key ahead by 1.
        while(j>=0 && topgpa[j] > key1){
            topgpa[j+1] = topgpa[j];
            firstnames[j+1] = firstnames[j];
            lastnames[j+1] = lastnames[j];
            j--;
        }
        topgpa[j+1] = key1;
        firstnames[j+1] = key2;
        lastnames[j+1] = key3;
    }

    // Print results.
    printf("---- QUESTION 2 ----\n");
    printf("Top 3 students with the highest GPA:\n");
    for(i=(count-1); i>=(count-3); i--){
        printf("%s %s - ", firstnames[i], lastnames[i]);
        printf("%.2f\n", topgpa[i]);
    }
    return;
}

void question3(size_t count, students *student){
    int i = 0, tothrs = 0;
    // Loop through the list of students to get the sum of all credit hours.
    for (i=0; i<count; i++){
        tothrs = tothrs + student[i].credithrs;
    }
    // Get the average hours of the college.
    double avghrs = (double)tothrs / ((double)count);

    // Print results.
    printf("\n---- QUESTION 3 ----\n");
    printf("%.2f: Average credit hours of the University.\n\n", avghrs);
    return;
}

void question4(size_t count, students *student){
    // Defining all variables.
    int i = 0, totcss = 0;
    double totgpa = 0;
    char temp[] = "Computer Science";
    // Loop through the list of students to get the sum of GPA's hours for CS majors.
    for (i=0; i<count; i++){
        if(strcmp(student[i].major, temp) == 0){
            totgpa = totgpa + student[i].gpa;
            totcss++;
        }
    }
    // Get the average hours of all CS majors.
    double avghrs = totgpa / ((double)totcss);

    // Print results.
    printf("---- QUESTION 4 ----\n");
    printf("%.2f: Average GPA for CS majors.\n\n", avghrs);
    return;
}

void question5(size_t count, students *student){

    int i = 0, j = 0, k = 0, l = 0, n = 0, o = 0, p = 0, q = 0;
    size_t counter = count;
    char *cs[100], *h[100], *b[100], *m[100], *ece[100]; 
    char temp[] = "Computer Science";
    char temp2[] = "History";
    char temp3[] = "Biology";
    char temp4[] = "Math";
    char temp5[] = "ECE";

    for(i=0; i<count; i++){
        if(strcmp(student[i].major, temp) == 0){
            cs[l] = student[i].advisor;
            l++;
        }else if(strcmp(student[i].major, temp2) == 0){
            h[n] = student[i].advisor;
            n++;
        }else if(strcmp(student[i].major, temp3) == 0){
            b[o] = student[i].advisor;
            o++;
        }else if(strcmp(student[i].major, temp4) == 0){
            m[p] = student[i].advisor;
            p++;
        }else if(strcmp(student[i].major, temp5) == 0){
            ece[q] = student[i].advisor;
            q++;
        }
    }
    for(i=0; i<l; i++){
        for(j=(i+1); j<l; j++){
            if(strcmp(cs[i], cs[j]) == 0){
                for(k=j; k<l; k++){
                    cs[k] = cs[k+1];
                }
            j--;
            l--;
            }
        }
    }
    for(i=0; i<n; i++){
        for(j=(i+1); j<n; j++){
            if(strcmp(h[i], h[j]) == 0){
                for(k=j; k<n; k++){
                    h[k] = h[k+1];
                }
            j--;
            n--;
            }
        }
    }
    for(i=0; i<o; i++){
        for(j=(i+1); j<o; j++){
            if(strcmp(b[i], b[j]) == 0){
                for(k=j; k<o; k++){
                    b[k] = b[k+1];
                }
            j--;
            o--;
            }
        }
    }
    for(i=0; i<p; i++){
        for(j=(i+1); j<p; j++){
            if(strcmp(m[i], m[j]) == 0){
                for(k=j; k<p; k++){
                    m[k] = m[k+1];
                }
            j--;
            p--;
            }
        }
    }
    for(i=0; i<q; i++){
        for(j=(i+1); j<q; j++){
            if(strcmp(ece[i], ece[j]) == 0){
                for(k=j; k<q; k++){
                    ece[k] = ece[k+1];
                }
            j--;
            q--;
            }
        }
    }

    printf("---- QUESTION 5 ----\n");
    printf("Total number of advisors per department:\n\n");
    printf("%s: %d\n\n", temp, l);
    printf("%s: %d\n\n", temp2, n);
    printf("%s: %d\n\n", temp3, o);
    printf("%s: %d\n\n", temp4, p);
    printf("%s: %d\n\n", temp5, q);
    return;
}

int main(){
    // Incrementer variables.
    size_t rowcount = 0, i = 0;
    // To hold the header values in students_dataset.csv file because they are string and struct is set to hold double and int.
    char gpat[20];
    char credhrst[20];
    // List of students struct to hold all data.
    students student[50];

    // Open students_dataset.csv file.
    FILE *data = fopen("students_dataset.csv", "r");

    // Checks to see if file exists.
    if(data == NULL){
        perror("Unable to open file");
        exit(1);
    }
    // Read in the header because the GPA and Credit Hours columns contain strings in this row.
    fscanf(data, "%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %s", student[rowcount].firstname, student[rowcount].lastname, student[rowcount].major,
           student[rowcount].degree, gpat, credhrst, student[rowcount].ta, student[rowcount].advisor);

    // Increment the counter to skip the header before looping.
    //rowcount += 1;

    // Loop through the remaining rows to fill the students struct with all the data.
    while (fscanf(data, "%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %lf%*c %d%*c %[^,]%*c %[^\n]", student[rowcount].firstname, student[rowcount].lastname, student[rowcount].major,
                  student[rowcount].degree, &student[rowcount].gpa, &student[rowcount].credithrs, student[rowcount].ta, student[rowcount].advisor) == 8){
        rowcount++;
        if(rowcount == 51){
            continue;
        }
    }

    // Loop through structs and print all the data.
    for (i=0; i < rowcount; i++){
        printf("%s, %s, %s, %s, %.2lf, %d, %s, %s \n", student[i].firstname, student[i].lastname, student[i].major,
               student[i].degree, student[i].gpa, student[i].credithrs, student[i].ta, student[i].advisor);
    }

    // Print the total amount of records in the file.
    printf("%ld students.\n\n", rowcount);

    question1(rowcount, student);
    question2(rowcount, student);
    question3(rowcount, student);
    question4(rowcount, student);
    question5(rowcount, student);

    return 0;
}