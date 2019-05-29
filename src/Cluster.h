#include "Seq.h"
#include <vector>

using namespace std;

class Cluster
{
  private:
    std::vector<Cluster> subClusters;
    std::vector<Seq> elements;
    string getNewickIntermediate();

  public:
    Cluster(Seq element);
    Cluster(vector<Seq> eltList);
    Cluster(Cluster cluster1, Cluster cluster2);
    double linkage(Cluster aCluster);
    void clusterize();
    void join();
    void printElements();
    void getElements();
    string getNewick();

};