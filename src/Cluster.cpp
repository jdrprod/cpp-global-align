#include "Cluster.h"

using namespace std;

string Cluster::getNewickIntermediate() {
  string rep = "";

  if (subClusters.size() == 0) {
    rep += elements[0].to_string();
  } else {

    rep += "(";
    for (int i = 0; i < subClusters.size(); i++) {
      rep += subClusters[i].getNewickIntermediate();
      if (i < subClusters.size()-1)
        rep += ",";
    }
    rep += ")";
  }
  return rep;
}

string Cluster::getNewick() {
  return getNewickIntermediate() + ";";
}


Cluster::Cluster(Seq element) {
  elements.push_back(element);
}

Cluster::Cluster(vector<Seq> eltList) {
  for (Seq s : eltList) {
    subClusters.push_back( Cluster(s) );
  }
}

Cluster::Cluster(Cluster cluster1, Cluster cluster2) {
  subClusters.push_back(cluster1);
  subClusters.push_back(cluster2);
}

void Cluster::getElements() {
  for (Cluster c : subClusters) {
    if (c.elements.size() == 1) {
      elements.push_back(c.elements[0]);
    } else {
      c.getElements();
      for (Seq s : c.elements) {
        elements.push_back(s);
      }
    }
  }
}

void Cluster::printElements() {
  for (Seq s : elements) {
    cout << s.get_label() << endl;
  }
}

double Cluster::linkage(Cluster aCluster) {
  getElements();
  aCluster.getElements();
  Matrix mscore;
  
  int score = 0;
  int size1 = elements.size();
  int size2 = aCluster.elements.size();
  int size = size1*size2;

  for (Seq s1 : elements) {
    for (Seq s2 : aCluster.elements) {
      Seq::score_matrix(mscore, &s1, &s2);
      score += mscore[s1.len()][s2.len()];
    }
  }
  return  (double) score / size;
}

void Cluster::clusterize() {

  if (subClusters.size() >= 2) {
    int best_i = 0;
    int best_j = 0;
    int best = 0;
    double d = 0;

    vector<Cluster> new_subClusters;

    for (int i = 0; i < subClusters.size(); i++) {
      for (int j = i+1; j < subClusters.size(); j++) {
        d = subClusters[i].linkage(subClusters[j]);
        if (d > best) {
          best_i = i;
          best_j = j;
          best = d;
        }
      }
    }

    for (int i = 0; i < subClusters.size(); i++) {
      if (i != best_i && i != best_j) {
        new_subClusters.push_back(subClusters[i]);
      }
    }

    Cluster merged = Cluster(subClusters[best_i], subClusters[best_j]);
    new_subClusters.push_back(merged);
    
    subClusters.clear();

    for (int i = 0; i < new_subClusters.size(); i++) {
      subClusters.push_back(new_subClusters[i]);
    }

    clusterize();
  }
}


void Cluster::join() {

  Cluster top = Cluster(Seq("root", ""));
  
  vector<int> marked;

  int best_i = 0;
  int best_j = 0;
  int best = 0;
  double d = 0;

  for (int i = 0; i < subClusters.size(); i++) {
    for (int j = i+1; j < subClusters.size(); j++) {
      d = subClusters[i].linkage(subClusters[j]);
      if (d > best) {
        best_i = i;
        best_j = j;
        best = d;
      }
    }
  }

  top = Cluster(subClusters[best_i], subClusters[best_j]);

  marked.push_back(best_i);
  marked.push_back(best_j);

  int best_next = 0;
  int best_next_score = 0;

  while (marked.size() < subClusters.size()) {
    for (int i = 0; i < subClusters.size(); i++) {
      if (count(marked.begin(), marked.end(), i) == 0) {
        d = top.linkage(subClusters[i]);
        if (d >= best_next_score) {
          best_next = i;
          best_next_score = d;
        }
      }
    }

    marked.push_back(best_next);
    top = Cluster(top, subClusters[best_next]);
    best_next = 0;
    best_next_score = 0;
  }

  subClusters.clear();
  subClusters.push_back(top);
}