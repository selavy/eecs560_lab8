#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

#define COUNT 25
#define TEST

int get_random_number();

void make_heap( int *& A, int size );
void push_up( int *& A, int i );
void push_down( int *&A, int i, int size );
void print_heap( int * A, int count );
void sort1 ( int *& A, int size );

int main( int argc, char **argv ) {
  int * heap = new int( COUNT + 1 );

  /*
   * Seed random number generator
   */
#ifdef TEST
  srand( 1 );
#else
  srand( time( NULL ) );  
#endif

  for( int i = 0; i < COUNT; ++i ) {
    heap[i+1] = ( get_random_number() );
  }
  
  print_heap( heap, COUNT );
  sort1( heap, COUNT );
  print_heap( heap, COUNT );
  return 0;
}

int get_random_number() {
  return rand() % 2000 - 1000;
}

void make_heap( int *& A, int size ) {
  for( int i = size / 2; i >= 1; --i ) {
    push_down( A, i, size );
  }
}

void push_up( int *& A, int i ) {
  if( i < 0 ) {
    throw std::out_of_range("Attempt to push up element outside bounds of heap.");
  }
  
  int position = i;
  
  while( (position / 2) >= 1 ) {
    const int parent = position / 2;
    if( A[position] < A[parent] ) {
      /*
       * Swap elements
       */
      int tmp = A[position];
      A[position] = A[parent];
      A[parent] = tmp;
      position = parent;
    } else {
      break;
    }
  }
}

void push_down( int *& A, int i, int size ) {
  if( i > size ) {
    throw std::out_of_range("Attempt to push down element outside bounds of heap.");
  }

  const int val = A[i];
  int position = i;

  while( ( position * 2 ) <= size ) {
    const int child1 = position * 2;
    const int child2 = child1 + 1;
    const int k = (child1 != size && A[child2] < A[child1]) ? child2 : child1;

    if( A[k] < val ) {
      A[position] = A[k];
      position = k;
    } else {
      break;
    }
    A[position] = val;
  }
}

void sort1 ( int *& A, int size ) {
  make_heap( A, size );
  for( int j = size; j > 1; j-- ) {
    int tmp = A[1];
    A[1] = A[j];
    A[j] = tmp;
    push_down( A, 1, j - 1 );
  }
}

void print_heap( int * A, int count ) {
  for( int i = 1; i <= count; ++i ) {
    cout << A[i] << " ";
  }
  cout << endl;
}
