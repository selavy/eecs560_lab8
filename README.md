eecs560_lab8
============

To build just the program:
   "make"

To build the program AND the tests:
   "make test"

If you want to run more tests then uncomment line #3 ("#NUMBER_OF_TESTS ..."), and change
the number (where it currently says "20") to whatever number of tests you would like to have.
(N.B. Do not give a value less than 1)

1. Testing to verify buildheap and heapsort:
   Test file can be generated with "make test", and is in lab8_test.out

2. All data collected:
   Data file generated with "make test", and is in lab8.out

3. Which method is better?
   All of my tests have shown that the modified method for heapsort uses around half as many
comparisons for a 1000 element array.  With only 1000 elements, that isn't very significant,
but it could become very significant as the number of elements increases.  It appears that quite
often the element that is pushed down to a leaf node doesn't have to come very far back up
to re-establish the heap properties.
