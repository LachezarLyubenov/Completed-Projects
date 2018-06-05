

file _pq.c

BASIC INSTRUCTIONS:

  Place the file _pq.c in a directory with your implementation of pq.c and
  also copy over the makefile in this directory (or simply incorporate
  the target 'tester' in this makefile into a makefile you have already
  developed.


SUMMARY:

  contains a 'framework' for testing your priority queue implementation 
  for behavioral correctness (not runtime).

  It is a 'framework' because it lets you add new test functions and
  just by adding them to an array (as function pointers), the driver
  program (and user) can easily select the newly written function for
  executiion.

  Two basic testers named test0 and test1 are given.  But you should write
  more!!!

  There are also numerous functions for initialization, checking and
  doing small tests.  From these functions (and similar ones you may
  add), you can build new test functions.

  The tests are based on the premise of a functionally correct implementation
  already existing (realized by the type _PQ and functions _pq_XXXX)).

  A test has this structure:

      create an empty priority queue (your 'fast' version)
      create an another empty priority queue:  a slow but correct version.

      perform exactly the same sequence of operations on each (in "lock step").
      These two queues should always represent the same set of <id,priority>
      pairs.  Perform various tests during this process and afterward to
      check this property.


UNDERSTANDING THE APPROACH:

  The file _pq.c Contains a "mirror" implementation of the priority queue 
  ADT sprcified in pq.h

  Every type and function in pq.h has a matching counterpart with one change

      the counterpart is prefixed with an underscore "_"

  For example:

      in pq.h we have the type PQ
 
      in _pq.c, we have a type _PQ

      pq_insert --> _pq_insert


  IDEA:

      the _pq_XXXX functions are NOT efficient, but are (believed to be)
      functionally correct.

      The slow priority queue implementation is very simple and does
      lots of scanning.

      So... if we are convinced the slow priority queue is correct, we
      can use it to do tests on an implementation of the fast version:

          create a slow priority queue
          create a fast priority queue

          Perform a sequence of identical operations on both and
          perform checks along the way and at the end to see if they
          contain the same data.

  
  DRIVER PROGRAM:

      _pq.c does have a main inside of it.  From main one or more 
      test functions are launched.

      The test functions are self-contained and take just a single 
      integer n as a parameter (and have void return type).

      The test functions are also "registered" in an array/table 
      called TestFunctions for the following reasons:

          To launch a test, we just need its index in the array.
          Initially, given test functions test0 and test1 are registered.

          To add a new test, you just write a function with the
          correct signature (return type void, single int parameter) and
          make an entry for it in the function table.


      Usage:  after you type make tester, you will have a program
      (called tester) which results from the _pq.c source file.

      The program has several optional switches/command line args:

           -n <N>     to specify a problem size/queue capacity
                      Default:  10

           -t <TEST_NUM>  to select a specific test to run.
                          Tests are numbered from 0 and follow their
                          assignment into TestFunctions[]

                          Default: 0 (corresponding to the test0 function)

          -all            this option will just run all of the tests
                          one-by-one.

          -s <SEED>       The provided tests are randomized.  (Tests
                          that you add may or may not be randomized).
                          By default, the random number generator is
                          seeded with time(NULL) as is tradition.  However,
                          as part of the output, the seed used will be
                          reported.

                          One issue with randomization is that when you have
                          a bug, you'd like the program to run the same
                          way every time until you fix the bug.  This 
                          switch lets you reproduce results by specifying
                          the seed to use (and using the same seed each
                          subsequent test).

    Example:  to run the tester with n=100, a seed of 111 and applying
              test 1 you would do this:

        ./tester -n 100 -t 1 -s 111

      The output will be a hopefully reasonably readable sequence of
      diagnostics with failure messages traceable back to the code
      segments where the failure is flagged (i.e., to help get at least
      a reasonable start on finding the bug.)
    

MAKEFILE:

    Pretty basic.  Just remember that the executable is called 'tester'
    even though there is no file tester.c

    (tester is produced by typing

           make tester
    )


DISCLAIMER:

    The _pq_XXXX implementation is strongly believed to be bug free, 
    but ...

    The idea is that the implementation is so trivial (though slow) that 
    we have high levels of confidence in its correctness without TONS
    of testing...


MISC DETAILS:


    Remember, the basic model:  two priority queues (one slow, one fast)
    being operated on in "parallel"  At any point in time, we expect them
    to contain exactly the same data (set of <id, priority> pairs).

    To ensure that each will behave exactly the same (if correctly 
    implemented), some effort has been made to ensure that priorities 
    are themselves distinct.

    This is not a requirement of the ADT itself, but it does make it
    so that, for example, there is only one correct result to a 
    delete_top operation -- nice for testing.

