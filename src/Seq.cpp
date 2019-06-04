#include "Seq.h"

using namespace std;

int Seq::sub = -1;
int Seq::gap = -2;
int Seq::match = 3;

Seq::Seq(string label, string seq) :
  m_label(label),
  m_seq(seq),
  m_len(seq.length())
{}


char Seq::pos(int i) {
  return m_seq.at(i);
}

int Seq::len() {
  return m_len;
}

string Seq::get_label() {
  return m_label;
}

string Seq::to_string() {
  return m_label + " " + m_seq;
}


int Seq::subs(char a, char b) {
  return a == b ? Seq::match : Seq::sub;
}


void Seq::align_all(Matrix M, Seq * seq1, Seq * seq2, Aligns * all) {
  Seq::_align_all(
    M,
    seq1->len(), seq2->len(),
    seq1, seq2, "", "", all
  );
}


/**
 * @brief      Find all equivalent alignments using traceback method
 * from position (i,j) in a score matrix.
 *
 * @param[in]  M     Score Matrix (obtained with Seq::score_matrix)
 * @param[in]  i     starting row
 * @param[in]  j     starting column
 * @param[in]  seq1  The sequence 1
 * @param[in]  seq2  The sequence 2
 * @param[in]  A     already aligned version of seq1 (traced until i)
 * We generally want to set A to ""
 * @param[in]  B     already aligned version for seq2 (traced until j)
 * We generally want to set B to ""
 * @param      all   all alignements
 */
void Seq::_align_all(
  Matrix M, int i, int j, 
  Seq * seq1, Seq * seq2,
  std::string A, std::string B,
  Aligns * all) {

  Aligns options;
  options.pos = 0;

  // recursive case
  if (i > 0 && j > 0) {
    
    // Testing if it can be an indel
    if (M[i][j] == M[i-1][j] + Seq::gap) {
      string B1 = '-' + B;
      string A1 = seq1->pos(i - 1) + A;
      Seq::_align_all(M, i-1, j, seq1, seq2, A1, B1, &options);
    }
    
    // Testing if it can be an indel (2)
    if (M[i][j] == M[i][j-1] + Seq::gap) {
      string B2 = seq2->pos(j - 1) + B;
      string A2 = '-' + A;
      Seq::_align_all(M, i, j-1, seq1, seq2, A2, B2, &options);
    }

    // Testing if it can be a match or sub (2)
    if (M[i][j] == M[i-1][j-1] + Seq::subs(seq1->pos(i - 1), seq2->pos(j - 1))) {
      string B3 = seq2->pos(j - 1) + B;
      string A3 = seq1->pos(i - 1) + A;
      Seq::_align_all(M, i-1, j-1, seq1, seq2, A3, B3, &options);
    }

    // saving all optionnal alignments from Mi,j
    for (int i = 0; i < options.pos; i++) {
      all->arr[all->pos][0] = options.arr[i][0];
      all->arr[all->pos][1] = options.arr[i][1];
      all->pos += 1;
    }

  } else {
    // base case

    // process trailing chars
    while ( i > 0 ) {
      A = seq1->pos(i - 1) + A;
      B = '-' + B;
      i -= 1;
    }

    while ( j > 0 ) {
      A = '-' + A;
      B = seq2->pos(j - 1) + B;
      j -= 1;
    }

    // save the alignment (A, B)
    all->arr[all->pos][0] = A;
    all->arr[all->pos][1] = B;
    all->pos += 1;
  }
}


void Seq::align(Matrix M, Seq * seq1, Seq * seq2) {
  
  string A = "";
  string B = "";

  int i = seq1->m_len;
  int j = seq2->m_len;

  while ( i > 0 && j > 0 ) {
    if (M[i][j] == M[i-1][j] - 2) {
      B = '-' + B;
      A = seq1->pos(i - 1) + A;
      i -= 1;
    } else if (M[i][j] == M[i][j-1] - 2) {
      B = seq2->pos(j - 1) + B;
      A = '-' + A;
      j -= 1;
    } else {
      B = seq2->pos(j - 1) + B;
      A = seq1->pos(i - 1) + A;
      i -= 1;
      j -= 1;
    }
  }

  while ( i > 0 ) {
    A = seq1->pos(i - 1) + A;
    B = '-' + B;
    i -= 1;
  }

  while ( j > 0 ) {
    A = '-' + A;
    B = seq2->pos(j - 1) + B;
    j -= 1;
  }

  cout << A << endl;
  cout << B << endl;
}


void Seq::score_matrix(Matrix M, Seq * seq1, Seq * seq2) {

  int score_del = 0;
  int score_ins = 0;
  int score_sub = 0;

  // INITIALIZING SCORE MATRIX
  
  for (int j = 0; j <= seq2->m_len; j++)
    M[0][j] = -j;

  for (int j = 0; j <= seq1->m_len; j++)
    M[j][0] = -j;

  // FILL THE SCORE MATRIX

  for (int i = 1; i <= seq1->m_len; i++) {
    for (int j = 1; j <= seq2->m_len; j++) {
      
      score_del = M[i-1][j] + Seq::gap;
      score_ins = M[i][j-1] + Seq::gap;
      score_sub = M[i-1][j-1] + Seq::subs(seq1->pos(i-1), seq2->pos(j-1));

      M[i][j] = max(score_sub, max(score_del, score_ins));

    }
  }
}


void Seq::print_score(Matrix M, Seq * seq1, Seq * seq2) {
  for (int i = 0; i <= seq1->m_len; i++) {
    for (int j = 0; j <= seq2->m_len; j++) {
      char c = i > 0 ? seq1->pos(i-1) : '.';
      printf("%4d ", M[i][j]);
    }
    printf("\n");
  }
}