#ifndef DEF_SEQ
#define DEF_SEQ

#include <iostream>

using namespace std;

/**
 * @brief      Alias defining matrix as 1000*1000 int arrays.
 */
typedef int Matrix [1000][1000];


/**
 * @brief      Structure describing an array of alignments.
 */
typedef struct Aligns
{
  int pos;
  string arr[1000][2];
} Aligns;


/**
 * @brief      Class describing a biological sequence.
 */
class Seq
{

public:
  Seq(string label, string seq);
  char  pos(int i);
  int   len();
  float linkage(Seq another_seq);
  string get_label();
  static void align_all(Matrix M, Seq * seq1, Seq * seq2, Aligns * all);
  static void score_matrix(Matrix M, Seq * seq1, Seq * seq2);
  static void print_score(Matrix M, Seq * seq1, Seq * seq2);
  static void align(Matrix M, Seq * seq1, Seq * seq2);

private:
  // custom attributes
  int m_len;
  const string m_label;
  const string m_seq;
  
  // static attributes
  static int gap;
  static int sub;
  static int match;
  static int subs(char a, char b);
  static void _align_all(
    Matrix M, int i, int j,
    Seq * seq1, Seq * seq2,
    string A, string B,
    Aligns * all);
  
};

#endif