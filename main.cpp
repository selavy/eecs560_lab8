#include <iostream>
#include <cstdlib>

using namespace std;

void push_up( int *& A, int n ) {
  int val = A[n];
  int position = n;

  while( ( val < A[position/2] ) && ( position > 1 ) ) {
    A[position] = A[position/2];
    position = position / 2;
  }
  A[position] = val;
}

void push_down( int *& A, int i ) {
  int val = A[i];
  int position = i;
  const int pos1 = 2*position;
  const int pos2 = 2*position + 1;
  int k = (A[pos1] < A[pos2]) ? pos1 : pos2;
  if( val > A[k] ) {
    A[position] = A[k];
    position = k;
  } else {
    A[position] = val;
  }
}

int main( int argc, char **argv ) {
  
  return 0;
}
