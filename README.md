[We are winning that chocolate bar.]

CS3014 Lab 1: Parallel matrix multiplication

13th February 2014

Dense matrix times matrix multiplication is one of the most important
and commonly-performed operations in computational science. The
purpose of this labs is to better understand modern multicore
architectures by writing an efficient matrix multiplication routine.

The machine is stoker.scss.tcd.ie. This machine has four processors.
Each processor has eight out-of-order pipelined, superscalar cores.
And each core has two-way simultaneous multithreading.

To write an efficient matrix multiplication routine you will need an
efficient basic algorithm, but it is also important that you take
account of issues such as locality of data access and multiple
available processor cores.

Your routine should be written in C/C++, and multiply arrays of
double-precision numbers. You may consult books, papers and online
sources, but all sources should be acknowledged in your
submission. All the submitted code should be your own, however.

Your routine should have the following prototype:
void matmul(double ** A, double ** B, double ** C, int size);

Where A, B and C are two dimensional arrays with dimensions that
make them compatible for multiplication.

The work for this lab should be carried out in pairs, and each pair of
students will make a joint submission. The submission should take the
form of a working, well-written, commented piece of code, and a 1-2
page docuement decscirbing the efforts made to make the code
efficient. Both members of the team should be able to fully explain
all the code, and should be prepared to stand up in front of the class
and speak about their solution.

I will shortly provide a test harness program to test and time your
routine. Your routine should be capable of operating efficiently on a
range of matrix sizes and shapes.

The marks you get for this lab will depend on two things. First, the
mark will depend on the code itself --- its correctness, quality and
the optimization ideas it contains. Secondly your make will depend on
the running time of the code. The faster your code compared to that of
other teams, the higher the mark you will get.

We will discuss the deadline in class, but the most likely candidate
is the first week back after reading week.
