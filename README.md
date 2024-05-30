# Chapter 11 - Files -> Fundamentals of Programming in C 

## Introduction

Files are data structures changed outside an program environment. It's Considered an program environment in the main memory (RAM)
Files are stored in secondary device memory, like hard drives.

For example, a database is composed of one or many files.


### Working Files in C/C++

Files are supported for <stdio.h> lib -> This library can provides many changes of file.

### Files Declaration

> FILE *file, *doc;

In C, data can be recored in binary files or text.


### Opening Files

To open a file we use the  **fopen()** function, returning the pointer associated for this file.

> FILE *file;
> file = (filename, opening_mode);

- **file** it's a variable that will store the initial address memory busy for a file
- **filename** represents the name of the file that you like to open, this file could be the path
- **opening_mode** represents how the file will be opened.

                           ##    Table of opening Mode    ##

            r   Opens a text file where only readings can be performed.
            w   Creates a text file where only writing operations can be performed.
            a   Appends new data to a text file.
            rb  Opens a binary file where only readings can be performed.
            wb  Creates a binary file where only write operations can be performed.
            ab  Appends new data to a binary file.
            r+  Opens a text file where reading and writing operations can be performed.
            w+  Creates a text file where reading and writing operations can be performed.
            a+  Appends new data or creates a text file for read and write operations.
            rb+ Opens a binary file where reading and writing operations can be performed.
            wb+ Creates a binary file where reading and writing operations can be performed.
            ab+ Appends new data to a binary file for read and write operations.


Example 01:

> FILE *file;
> file = fopen("file.dat", "w");


### Closing Files

Function **fclose()**

> int fclose(file);

- You'll always needs to close a file. 

### Catching errors while using files.

> int ferror(file);

### Writing characters to a file.

> fputc(char ch, FILE *file);

- **ch** it's the character will be writed on the file.

### Reading characters 

> fgetc(file);

### Writing a string to a file

> fputs(char *string, FILE *file);

### Reading a string to a file

> string[30];
> fgets(char *string, int size, *file);

### Writing any type of data to a file

> int fwrite(&var, sizeof(struct name), 1, var);

### Reading any type of data from a file

> int fread(&c, sizeof(struct c), 1, c);

### Finding the end of file

> int feof(file);

This function find the end of file, it return a integer number. When this number is 0 it means that the end of file has not yet been reached. Any other value means the end of file was found.

### Returning the cursor to the beginning of the file

> void rewind(file);

### Removing a file

> int remove(char *file_name);

### Renaming a file

> int rename(char *actual_name, char *new_name);


## Solved Exercises

