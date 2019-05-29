#include "Seq.h"
#include "Cluster.h"

int main(int argc, char const *argv[])
{
  // Seq * a = new Seq("seq a", "what");
  // Seq * b = new Seq("seq b", "why");

  // Matrix score;
  // Aligns all;


  // Seq::score_matrix(score, a, b);
  // Seq::align_all(score, a, b, &all);
  // Seq::print_score(score, a, b);

  // for (int i = 0; i < all.pos; i++) {
  //   std::cout << all.arr[i][0] << std::endl;
  //   std::cout << all.arr[i][1] << std::endl;
  // }

  vector<Seq> seqList;

  seqList.push_back( Seq("seqD", "where") );
  seqList.push_back( Seq("seqA", "what") );
  seqList.push_back( Seq("seqB", "why") );
  seqList.push_back( Seq("seqC", "who") );

  Cluster c = Cluster(seqList);

  Cluster c2 = Cluster(
    Cluster(Seq("seqa", "where")),
    Cluster(Seq("seqb", "who"))
  );

  Cluster c3 = Cluster(
    Cluster(Seq("seqc", "where")),
    Cluster(Seq("seqd", "who"))
  );

  Cluster c4 = Cluster(c3, c2);

  Cluster c1 = Cluster(
    Cluster(Seq("seqe", "where")),  
    c4
  );

  c1.getElements();
  c1.printElements();
  
  c.clusterize();
  cout << c.getNewick() << endl;

  return 0;
}