#include "Seq.h"
#include "Cluster.h"

int main(int argc, char const *argv[])
{
  // Initializing sequences

  vector<Seq> seqList;
  
  Seq seq1 = Seq("seq1", "where");
  Seq seq2 = Seq("seq2", "what");
  Seq seq3 = Seq("seq3", "why");
  Seq seq4 = Seq("seq4", "who");

  seqList.push_back( seq1 );
  seqList.push_back( seq2 );
  seqList.push_back( seq3 );
  seqList.push_back( seq4 );

  // Clustering
  
  Cluster C1 = Cluster(seqList);
  
  cout << endl << "Hierachical Clustering : " << endl;
  C1.clusterize();
  cout << C1.getNewick() << endl;

  Cluster C2 = Cluster(seqList);

  cout << endl << "Simple ordering : " << endl;
  C2.order();
  cout << C1.getNewick() << endl;


  cout << endl << "Global alignement : " << endl;

  Matrix score;
  Aligns all;
  
  Seq::score_matrix(score, &seq1, &seq2);
  Seq::align_all(score, &seq1, &seq2, &all);

  Seq::print_score(score, &seq1, &seq2);

  for(int i = 0; i < all.pos; i++) {
    cout << all.arr[i][0] << endl;
    cout << all.arr[i][1] << endl;
    cout << endl;
  }


  return 0;
}