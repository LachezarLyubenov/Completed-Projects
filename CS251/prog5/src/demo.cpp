
#include <iostream>
#include "Graph.h"


int main(){
  graph g;

  g._add_edge("a b 2");
  g._add_edge("b c 2");
  g._add_edge("c d 2");
  g._add_edge("c e 1");
  g._add_edge("d e 2");
  g._add_edge("a f 2");
  g._add_edge("f c 2");


  /*
  g.add_edge("a", "b");
  g.add_edge("b", "a");

  g.add_edge("b", "c");
  g.add_edge("d", "a");
  g.add_edge("b", "d");
  g.add_edge("a", "b");
  */
  std::vector<graph::vertex_label> vtest;

  g.bfs(0, vtest);

  for(int i = 0; i < vtest.size(); i++)
  {
    printf("numbers: %d\n", vtest[i].npaths);
  }
  printf("\n\n");

  g.display();

  return 0;
}

