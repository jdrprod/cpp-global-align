#include "Seq.h"

int main(int argc, char const *argv[])
{
  Seq * a = new Seq("seq a", "what");
  Seq * b = new Seq("seq b", "why");

  Matrix score;
  Aligns all;

  Seq::score_matrix(score, a, b);
  Seq::align_all(score, a, b, &all);
  Seq::print_score(score, a, b);

  for (int i = 0; i < all.pos; i++) {
    std::cout << all.arr[i][0] << std::endl;
    std::cout << all.arr[i][1] << std::endl;
  }

  return 0;
}