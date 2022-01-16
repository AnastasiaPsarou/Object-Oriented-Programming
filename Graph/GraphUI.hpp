#ifndef _GRAPH_UI_
#define _GRAPH_UI_

#include <regex>
#include"Graph.hpp"

template <typename T>
int graphUI() {
  
  std::string option, line;
  //int distance;
  cin >> option;
  bool digraph = false;

  if(!option.compare("digraph"))
    digraph = true;

  Graph<T> g(digraph);
  
  while(true) {
    std::stringstream stream;
    cin >> option;

    //cout << option <<endl;
    
    if(!option.compare("av")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);

      if(g.addVtx(vtx))
        std::cout << "av " << vtx << " OK\n";
      else
        std::cout << "av " << vtx << " NOK\n";
    }
    else if(!option.compare("rv")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);

      if(g.rmvVtx(vtx))
        std::cout << "rv " << vtx << " OK\n";
      else
        std::cout << "rv " << vtx << " NOK\n";

    }
    else if(!option.compare("ae")) {
      getline(std::cin, line);
      stream << line;
      T vtx1(stream);
  
      stream << line;
      T vtx2(stream);
      
      int cost;
      stream >> cost;

      if(g.addEdg(vtx1, vtx2, cost))
        std::cout << "ae " << vtx1 << " " << vtx2 << " OK\n";
      else
        std::cout << "ae " << vtx1 << " " << vtx2 << " NOK\n";
      
    }
    else if(!option.compare("re")) {
      getline(std::cin, line);
      stream << line;
      T vtx1(stream);

      stream << line;
      T vtx2(stream);

      if(g.rmvEdg(vtx1, vtx2))
        std::cout << "ae " << vtx1 << " " << vtx2 << " OK\n";
      else
        std::cout << "ae " << vtx1 << " " << vtx2 << " NOK\n";

    }
    else if(!option.compare("dot")) {
      getline(std::cin, line);
      stream << line;
      const char* file;
      file = line.c_str();

      if(g.print2DotFile(file) == true){
        std::cout << "dot" << file << " OK\n";
      }
      else{
        std::cout << "dot" << file << " NOK\n";
      }
      
    }
    else if(!option.compare("bfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx1(stream);    

      std::cout << "\n----- BFS Traversal -----\n";

      std::list<T> bfsList = g.bfs(vtx1);
      int first = 0;
      auto l_front = bfsList.begin();

      while(l_front != bfsList.end()){
        if(first == 0){
          first = 1;
        }
        else{
          std::cout << " -> ";
        }
          std::cout << *l_front;
          std::advance(l_front, 1);
      }
    
      
      std::cout << "\n-------------------------\n";
    }
    else if(!option.compare("dfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      
      std::cout << "\n----- DFS Traversal -----\n";

      std::list<T> dfsList = g.dfs(vtx);
      int first = 0;
      auto l_front = dfsList.begin();

      while(l_front != dfsList.end()){
        if(first == 0){
          first = 1;
        }
        else{
          std::cout << " -> ";
        }
          std::cout << *l_front;
          std::advance(l_front, 1);
      }
      
      std::cout << "\n-------------------------\n";
    }
    else if(!option.compare("dijkstra")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);

      stream << line;
      T to(stream);

      int first = 0;

     // cout << "MPIKAA" << endl;

      list<T> dijkstraQueue = g.dijkstra(from, to);

      //cout << "meta tin klisi" << endl;

    //   int first = 0;
    //   auto l_front = Dijkstra.begin();

    cout << "Dijkstra (" << from << " - " << to <<"): ";
    while(!dijkstraQueue.empty()){
      if(first == 0){
        first = 1;
      }
      else{
        cout << ", ";
      }
      cout << dijkstraQueue.front();
      dijkstraQueue.pop_front();
    }
    cout << endl;      
      
    }
    else if(!option.compare("mst")){
      list<Edge<T>> mstQueue;
      // int i = 0;
      int totalCost = 0;

      std::cout << "\n--- Min Spanning Tree ---\n";

      mstQueue = g.mst();
      // cout << "Front is : " << mstQueue.front();
      while(!mstQueue.empty()){
        cout << mstQueue.front() << endl;
        totalCost += mstQueue.front().dist;
        mstQueue.pop_front();
      }

      cout << "MST Cost: " << totalCost << endl;
    }
    else if(!option.compare("q")) {
      std::cerr << "bye bye...\n";
      return 0;
    }
    else if(!option.compare("#")) {
      std::string line;
      getline(std::cin,line);
      std::cerr << "Skipping line: " << line << std::endl;
    }
    else {
      std::cout << "INPUT ERROR\n";
      return -1;
    }
  }
  return -1;  
}


#endif
