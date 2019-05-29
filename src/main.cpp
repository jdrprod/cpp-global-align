#include "Seq.h"
#include "Cluster.h"

int main(int argc, char const *argv[])
{
  vector<Seq> seqList;

  
  Seq seq1 = Seq("seq1", "where");
  Seq seq2 = Seq("seq2", "what");
  Seq seq3 = Seq("seq3", "why");
  Seq seq4 = Seq("seq4", "who");

  seqList.push_back( seq1 );
  seqList.push_back( seq2 );
  seqList.push_back( seq3 );
  seqList.push_back( seq4 );

  Cluster c = Cluster(seqList);

  c.join();
  cout << c.getNewick() << endl;

  return 0;
}