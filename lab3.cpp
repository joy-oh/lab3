// -------------------------------------------------lab3.cpp-------------------------------------------------------

// Programmer Name Course Section Number : Joy hyunjung Oh, Sahithi Chimakurthi, CSS-503 A

// Creation Date : 05/09/2024

// Date of Last Modification : 05/09/2024

// Purpose : Implementing a program that reads a given file using Linux read() system call as well as 
//           C/C++ fgetc()/fread() functions.
//
// ---------------------------------------------------------------------------------------------------------------

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
using namespace std;

struct timeval start, end2; //maintain starting and finishing wall time.

// startTimer()
// Summary - Starts the timer to measure elapsed time.
// Pre-conditions - None.
// Post-conditions - The timer is started.
void startTimer()
{
    gettimeofday(&start, NULL);
}

// stopTimer(const char *str)
// Summary - Stops the timer and prints the elapsed time.
// Pre-conditions - The timer should have been started previously.
// Post-conditions - The elapsed time is printed.
void stopTimer(const char *str)
{
    gettimeofday(&end2, NULL);
    
    cout << str << "'s elapsed time\t= " << ((end2.tv_sec - start.tv_sec) * 1000000 + (end2.tv_usec - start.tv_usec)) << endl;
}

// main(int argc, char *argv[])
// Summary - Reads a file using both Linux I/O and C standard I/O functions and measures the elapsed time.
// Pre-conditions - Command line arguments should include both the filename and the number of bytes to read.
// Post-conditions - The file is read using both methods, and the elapsed time for each method is printed.
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "usage: lab3 filename bytes" << endl;
        return -1;
    }

    int bytes = atoi(argv[2]);
    
    if (bytes < 1)
    {
        cerr << "usage: lab3 filename bytes" << endl;
        cerr << "where bytes > 0" << endl;
        return -1;
    }

    char *filename = argv[1];
    char *buf = new char[bytes];

    // linux i/o
    // Reading a file using Linux I/O functions.
    // The entire file is read using the read system call, and the elapsed time is measured.
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1)
    {
        cerr << filename << " not found" << endl;
        return -1;
    }
    
    startTimer();
    while (read(fd, buf, bytes) > 0);
    stopTimer("Unix read");
    
    close(fd);

    // write the same functionality as in linux i/o
    // but use fopen(), fgetc(), fread(), and fclose( )
    // standard i/o
    // Reading a file using C standard I/O functions.
    // The entire file is read using either fgetc or fread, depending on the value of bytes, 
    // and the elapsed time is measured.
    FILE *fp;
    int c;

    fp = fopen(filename, "r");

    if (fp == NULL) 
    {
        cerr << "error opening " << filename << endl;
        return -1;
    }

    // use fgetc() if bytes == 1
    if (bytes == 1) 
    {
        startTimer();
        while(true) 
        {
            c = fgetc(fp);
            if(c == EOF) 
            {
                break;
            }
        } 
        stopTimer("standard fgetc's elapsed time");
    }
    else 
    {
        startTimer();
        while(fread(buf,1, bytes, fp) > 0);
        stopTimer("standard fread");
    }
    fclose(fp);

    delete[] buf;
    return 0;
}
