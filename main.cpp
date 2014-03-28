#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

#ifdef _TEST
#ifndef COUNT
#define COUNT 25
#endif
#ifndef NUM_OF_TRIALS
#define NUM_OF_TRIALS 3
#endif
#else
#ifndef COUNT
#define COUNT 1000
#endif
#ifndef NUM_OF_TRIALS
#define NUM_OF_TRIALS 10
#endif
#endif

int get_random_number();
void make_heap( int *& A, int size );
int push_up( int *& A, int i );
int push_down( int *&A, int i, int size );
void print_heap( int * A, int count );
int sort1( int *& A, int size );
int sort2( int *& A, int size );

int main( int argc, char **argv ) {
  int * heap = new int[ COUNT + 1 ];
  int * heap2 = new int[ COUNT + 1 ];

  /*
   * Seed random number generator
   */
#ifdef USE_RANDOM_NUMBERS
  srand( 1 );
#else
  srand( time( NULL ) );  
#endif

  for( int trial = 1; trial <= NUM_OF_TRIALS; ++trial ) {
    for( int i = 0; i < COUNT; ++i ) {
#ifdef _TEST
      heap[i+1] = heap2[i+1] = get_random_number();
#else
      heap[i+1] = get_random_number();
      heap2[i+1] = get_random_number();
#endif
    }

    cout << "Trial #" << trial << endl;

#ifndef _TEST
    cout << "Comparisons with push_down:\t" << sort1( heap, COUNT ) << endl; 
    cout << "Comparisons with push_up:\t" << sort2( heap2, COUNT )<< endl;
    cout << endl;
#endif
    
#ifdef _TEST
    print_heap( heap, COUNT );
    print_heap( heap2, COUNT );
    bool error = false;
    int inversions = 0;
    for( int i = 1; i <= COUNT; ++i )
      {
	if(heap[i] != heap[i]) {
	  ++inversions;
	  error = true;
	}
      }

    if(!error)
      cout << "Test status: Passed\n\n" << endl;
    else
      cout << "Test status: Failed (" << inversions << " inversions)\n\n" << endl;
#endif
  }

  delete [] heap;
  delete [] heap2;
  return 0;
}

/*
 * Returns a random number between -1000 and 1000
 * Before this function is called, srand() must have been called
 * to seed the random number generator.
 */
int get_random_number() {
  return rand() % 2000 - 1000;
}

/*
 * Given an array of length size, make_heap reorders
 * the array to have min-heap order properities
 */
void make_heap( int *& A, int size ) {
  for( int i = size / 2; i >= 1; --i ) {
    push_down( A, i, size );
  }
}

/*
 * Pushes element i in A up until heap order properties are
 * re-established
 */
int push_up( int *& A, int i ) {
  if( i < 0 ) {
    throw std::out_of_range("Attempt to push up element outside bounds of heap.");
  }

  int retVal = 0;
  
  const int val = A[i];
  int position = i;
  while( val < A[position / 2] && position > 1 ) {
    /*
     * 1 comparison: val < A[position / 2]
     */
    ++retVal;

    /*
     * Normally would include this condition in the while loop,
     * but I broke it out here so that I can count all of the
     * list item comparisons that happen in the while loop.
     * Otherwise, I might miss the last comparison that is made
     * when the code breaks out of the while loop.
     */
    if( position <= 1 ) break;

    A[position] = A[position/2];
    position = position / 2;
  }
  A[position] = val;
  
  return retVal;
}

/*
 * Pushes element i in A down until heap order properties are
 * re-established
 */
int push_down( int *& A, int i, int size ) {
  if( i > size ) {
    throw std::out_of_range("Attempt to push down element outside bounds of heap.");
  }

  int retVal = 0;

  const int val = A[i];
  int position = i;

  while( ( position * 2 ) <= size ) {
    const int child1 = position * 2;
    const int child2 = child1 + 1;
    const int k = (child1 != size && A[child2] < A[child1]) ? child2 : child1;
    /*
     * 1 comparison: A[child2] < A[child1]
     */
    ++retVal;

    /*
     * 1 comparision: A[k] < val
     */
    ++retVal;
    if( A[k] < val ) {
      A[position] = A[k];
      position = k;
    } else {
      break;
    }
    A[position] = val;
  }

  return retVal;
}

/*
 * HeapSort method #1: uses push_down()
 */
int sort1( int *& A, int size ) {
  int retVal = 0;

  make_heap( A, size );

  for( int j = size; j > 1; j-- ) {
    /*
     * Move the first element (minimum element in heap)
     * to the end of the array, decrease the "size" of the
     * heap, and push the first element down until the heap
     * properties are re-established
     */
    int tmp = A[1];
    A[1] = A[j];
    A[j] = tmp;
    retVal += push_down( A, 1, j - 1 );
  }

  return retVal;
}

/*
 * HeapSort method #2: uses push_up()
 */
int sort2( int *& A, int size ) {
  int retVal = 0;

  make_heap( A, size );

  for( int j = size; j > 1; j-- ) {
    /*
     * Swap first and last elements of heap
     */
    int tmp = A[1];
    A[1] = A[j];
    A[j] = tmp;
    
    /*
     * Move the first element down to the leaf 
     * level by switching at each level with its
     * smallest child node
     */
    const int val = A[1];
    int position = 1;
    while( ( position * 2 ) <= (j - 1) ) {
      const int child = position * 2;
      const int k = (child != (j - 1) && A[child+1] < A[child]) ? child + 1 : child;
      /*
       * 1 comparison: A[child+1] < A[child]
       */
      ++retVal;

      A[position] = A[k];
      position = k;
    }
    A[position] = val;
    retVal += push_up( A, position );
  }
  return retVal;
}

/*
 * Print the values in heap A of size count
 */
void print_heap( int * A, int count ) {
  for( int i = 1; i <= count; ++i ) {
    cout << A[i] << " ";
  }
  cout << endl;
}
