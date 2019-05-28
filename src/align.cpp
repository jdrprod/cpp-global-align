#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
  int M[200][200];
  string seq1 = "ATCGCC";
  string seq2 = "ATCUUUGCC";

  int score_del = 0;
  int score_ins = 0;
  int score_sub = 0;

  // INITIALIZING SCORE MATRIX
  
  for (int j = 0; j < 200; j++)
    M[0][j] = -j;

  for (int j = 0; j < 200; j++)
    M[j][0] = -j;

  // FILL THE SCORE MATRIX

  for (int i = 0; i < seq1.length(); i++) {
    for (int j = 0; j < seq2.length(); j++) {
      score_del = M[i][j+1] - 2;
      score_ins = M[i+1][j] - 2;
      score_sub = M[i][j] - 1;

      if (seq1.at(i) == seq2.at(j)) {
        M[i+1][j+1] = M[i][j] + 3;
      } else {
        M[i+1][j+1] = max(score_sub, max(score_del, score_ins));
      }

    }
  }

  // PRINT THE SCORE MATRIX

  for (int i = 0; i <= seq1.length(); i++) {
    for (int j = 0; j <= seq2.length(); j++) {
      printf("%3d", M[i][j]);
    }
    printf("\n");
  }

  // EXTRACT ALIGNMENT

  string A = "";
  string B = "";

  int i = seq1.length();
  int j = seq2.length();

  while ( i > 0 && j > 0 ) {
    if (M[i][j] == M[i-1][j] - 2) {
      A = seq2.at(j - 1) + A;
      B = '-' + B;
      i -= 1;
    } else if (M[i][j] == M[i][j-1] - 2) {
      A = '-' + A;
      B = seq1.at(i - 1) + B; 
      j -= 1;
    } else {
      A = seq2.at(j - 1) + A;
      B = seq1.at(i - 1) + B;
      i -= 1;
      j -= 1;
    }
  }

  while ( i > 0 )
    B = seq1.at(i - 1) + B;

  while ( j > 0 )
    A = seq2.at(j - 1) + A;


  // DISPLAY ALIGNMENT
  
  cout << A << endl;
  cout << B << endl;

  return 0;
}