# 42HN_get_next_line

The goal of this project is to introduce the student to the concept of static variables. The student will write a function, that returns a line read from a file descriptor.

## Description
 * repeated calls to the function should read the source pointed to by the file descriptor one line at a time
 * if there is nothing to read, or an error occurs, return value should be NULL
 * the function should work on a file and on the standard input
 * the line should include the terminating '/n'
 * the compiler call can contain '-D BUFFER_SIZE=n'

The only external functions allowed are 'read', 'malloc' and 'free'.

## Learnings
I tried to solve this project without relying on any of the string manipulation functions from our libft. I thus utilized a **ring buffer** and processed the read line **char by char**. All of this was a very good learning, that accompanied me in the parsing parts of the following 42 projects.

### Resources
[Static variables](https://www.geeksforgeeks.org/static-variables-in-c/)  
[Fixed size ring buffer](https://www.embedded.com/ring-buffer-basics/)
