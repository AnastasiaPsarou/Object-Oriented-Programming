#ifndef _GRAPH_HPP_ 
#define _GRAPH_HPP_

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <cstddef>
#include<limits>
#define VISITED 100

using namespace std;

template<typename T>
struct Edge {
  T from;
  T to;
  int dist;
  Edge(T f, T t, int d): from(f), to(t), dist(d) {
  }
  bool operator<(const Edge<T>& e) const;
  bool operator>(const Edge<T>& e) const;
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const Edge<U>& e);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Edge<T>& e) {
  out << e.from << " -- " << e.to << " (" << e.dist << ")";
  return out;
}

template <typename T>
class Graph {

  public:

    //list that contains neighbor nodes of a vertex
    struct List{
      T vertex; //node key
      int cost; //cost to go from vertex to node of the list
      struct List *next;
      struct List *prev;
      int ticket; //node priority
    };
    
    typedef struct Adjency{
      T value; //vertex key
      struct List *head; //list head
      struct List *tail; //list tail
      bool visited; //1 -> visited else 0 (dfs/bfs)
      int ticket; //node priority
      //~Adjency();
    }adjency;

    bool isDirected;
    std::vector<adjency> vectorArray;
    //o pinakas vector apo ton opoio 3ikanaei mia lista me tous geitonikous tou komvous
    
    Graph(bool isDirected);
    ~Graph();
    bool contains(const T& info);
    bool addVtx(const T& info);
    bool rmvVtx(const T& info);
    bool addEdg(const T& from, const T& to, int distance);
    bool rmvEdg(const T& from, const T& to);
    int findCost(const T& from, const T& to);
    std::list<T> dfs(const T& info);
    std::list<T> bfs(const T& info);
    std::list<Edge<T>> mst();
    std::list<Edge<T>> insertInList(std::list<Edge<T>> list,Edge<T> edge);
    bool isVisited(const T& info);
    void makeVisited(const T& info);
    int findTicket(const T& info);
    std::string printVector(void) const;
    void dfsPreFunction(const T& info);
    std::list<T> dfsRecursion(std::list<T> *dfsList, const T& info);
    bool print2DotFile(const char *filename) const;
    std::string printHelper(void) const;
    std::list<T> dijkstra(const T& from, const T& to);
    bool smallerTicket(const T& a, const T& b);
    void makeAllUnvisited();
};

template<typename T>
Graph<T>::Graph(bool isDirected){
    
    this->isDirected = isDirected;
}

template<typename T>
Graph<T>::~Graph(){
    unsigned long long int i;
    struct List *listHelper;
    struct List *nodeToDelete;

    for(i = 0; i < vectorArray.size(); i++){
        listHelper = vectorArray[i].head;

        while(listHelper !=  NULL){
            nodeToDelete = listHelper;
            listHelper = listHelper->next;
            delete(nodeToDelete->next);       
            delete(nodeToDelete->prev);
            delete(nodeToDelete);
        }
        delete(&vectorArray[i].head);
        delete(&vectorArray[i].tail);
        delete(&vectorArray[i]);
    }

    delete(&vectorArray);
}

template<typename T>
bool Graph<T>::addVtx(const T& info){

    //if node already exists
    if(contains(info) == true){
        return(false);
    }
    
    //new node is added to vertexArray
    struct Adjency adjencyNode;
    adjencyNode.value = info;
    adjencyNode.head = NULL;
    adjencyNode.tail = NULL;
    adjencyNode.visited = false;

    vectorArray.push_back(adjencyNode);
    vectorArray[vectorArray.size()-1].ticket = vectorArray.size()-1;
    return(true);
}

template<typename T>
bool Graph<T>::contains(const T& info){
    long long unsigned int i;

    for(i = 0; i < this->vectorArray.size(); i++){
        if(info == this->vectorArray[i].value){
            return(true);
        }
    }

    return(false);
}

template<typename T>
bool Graph<T>::print2DotFile(const char *filename) const{
    int i;

    while(filename[i] != '.'){
        i++;
    }
    if(!((filename[i+1] == 'd') || (filename[i+2] == 'o') || (filename[i+3] == 'o'))){
        return(false);
    }

    std::ofstream myFile;
    std::string graphSentence;
    myFile.open(filename);
    myFile<<"digraph G{\n";

    graphSentence= printHelper();

    myFile<<graphSentence;
    myFile<<"}";
    myFile.close();

    return(true);
}

template<typename T>
std::string Graph<T>::printHelper(void) const{
    std::string result = "\0";
    unsigned long long int i;
    struct List *listHelper = new List;

    for(i = 0; i < vectorArray.size(); i++){
        listHelper =  vectorArray[i].head;
        while(listHelper != NULL){   
            //result.append<T>(vectorArray[i].value, vectorArray[i].value);         
            //result = result + vectorArray[i].value + "->" + listHelper->vertex + ";\n";
            listHelper = listHelper->next;
        }
    }
    delete(listHelper);

    return(result);
}

//traverse vectorArray in order to find the ticket of a certain registration
template<typename T>
int Graph<T>::findTicket(const T& info){
    unsigned long long int i;

    for(i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == info){
            break;
        }
    }
    return(vectorArray[i].ticket);
}

template<typename T>
bool Graph<T>::addEdg(const T& from, const T& to, int cost){
    struct List *listHelper = new List;
    struct List *beforeTail = new List;
    struct List *newNode = new List;
    struct List *beforeNode = new List;
    struct List *afterNode = new List;
    long long unsigned int i;

    if((contains(from) == false) || (contains(to) == false)){
        return(false);
    }

    //does the vertex already exist
    for (i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == from){
            listHelper = vectorArray[i].head;
            while(listHelper!= NULL){
                if(listHelper->vertex == to){
                    return(false);
                }
                listHelper = listHelper->next;
            }
        }
    }
    if(this->isDirected == false){
        for (i = 0; i < vectorArray.size(); i++){
            if(vectorArray[i].value == to){
                listHelper = vectorArray[i].head;
                while(listHelper!= NULL){
                    if(listHelper->vertex == from){
                        return(false);
                    }
                    listHelper = listHelper->next;
                }
            }
        }
    }

    //Edge<T> newEdge(from, to, cost);
    int positionOfTicket = findTicket(to);

    //addition to the list -> from node
    for (i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == from){
            //if list is empty
            if(vectorArray[i].tail == NULL){ 
                vectorArray[i].head = new List; 
                vectorArray[i].tail = new List; 
                vectorArray[i].head = vectorArray[i].tail;
                vectorArray[i].head->vertex = to;
                vectorArray[i].head->ticket = positionOfTicket;
                vectorArray[i].head->cost = cost;

                vectorArray[i].head->next = NULL;
                vectorArray[i].head->prev = NULL;

            }  
            //list is not empty  
            else{
                listHelper = vectorArray[i].head;

                while(listHelper != NULL){
                    if(positionOfTicket < listHelper->ticket){
                        break;
                    }
                    listHelper = listHelper->next;
                }

                //addition does not happen at the end of the list
                if(listHelper != NULL){
                    newNode = new List;
                    newNode->vertex = to;
                    newNode->cost = cost;
                    newNode->ticket = positionOfTicket;
                    beforeNode = listHelper->prev;
                    afterNode = listHelper;

                    if(beforeNode != NULL){
                        beforeNode = listHelper->prev;
                        beforeNode->next = newNode;
                        newNode->prev = beforeNode;
                    }
                    else{
                        newNode->prev = beforeNode;
                        vectorArray[i].head = newNode;
                    }

                    if(afterNode != NULL){
                        afterNode->prev = newNode;
                        newNode->next = afterNode;
                    }
                    else{
                        newNode->next = afterNode;
                    }
                }
                //addition happend at the end of the list
                else{
                    beforeTail = new List;
                    beforeTail->vertex = to;
                    beforeTail->cost = cost;
                    beforeTail->ticket = positionOfTicket;
                    vectorArray[i].tail->next = beforeTail;
                    beforeTail->prev = vectorArray[i].tail;
                    beforeTail->next = NULL;
                    vectorArray[i].tail = beforeTail;
                }
            }
            break;
        }
    }
    //if directed addition to the vertex list
    if((this->isDirected == false) && (from != to)){
        positionOfTicket = findTicket(from);
        unsigned long long int i;

        for (i = 0; i < vectorArray.size(); i++){
            if(vectorArray[i].value == to){
                //list is empty
                if(vectorArray[i].tail == NULL){ 
                    vectorArray[i].head = new List; 
                    vectorArray[i].tail = new List; 
                    vectorArray[i].head = vectorArray[i].tail;
                    vectorArray[i].head->vertex = from;
                    vectorArray[i].head->ticket = positionOfTicket;
                    vectorArray[i].head->cost = cost;

                    vectorArray[i].head->next = NULL;
                    vectorArray[i].head->prev = NULL;
                }     
                //list is not empty      
                else{
                    listHelper = vectorArray[i].head;
                    int positionOfTicket = findTicket(from);

                    while(listHelper != NULL){
                        if(positionOfTicket < listHelper->ticket){
                            break;
                        }
                        listHelper = listHelper->next;
                    }
                    //addition does not happen at the end of the list
                    if(listHelper != NULL){
                        newNode = new List;
                        newNode->vertex = from;
                        newNode->cost = cost;
                        newNode->ticket = positionOfTicket;
                        beforeNode = listHelper->prev;
                        afterNode = listHelper;

                        if(beforeNode != NULL){
                            beforeNode->next = newNode;
                            newNode->prev = beforeNode;
                        }
                        else{
                            newNode->prev = beforeNode;
                            vectorArray[i].head = newNode;
                        }

                        if(afterNode != NULL){
                            afterNode->prev = newNode;
                            newNode->next = afterNode;
                        }
                        else{
                            newNode->next = afterNode;
                        }
                    }
                    //addition happens at the end of the list
                    else{
                        beforeTail = new List;
                        beforeTail->vertex = from;
                        beforeTail->cost = cost;
                        beforeTail->ticket = positionOfTicket;
                        vectorArray[i].tail->next = beforeTail;
                        beforeTail->prev = vectorArray[i].tail;
                        beforeTail->next = NULL;
                        vectorArray[i].tail = beforeTail;
                    }

                }
                break;
            }
        }
    }

    delete(listHelper);
    delete(beforeTail);
    delete(newNode);
    delete(beforeNode);
    delete(afterNode);
   
    return(true);
}


template<typename T>
bool Graph<T>::rmvVtx(const T& info){
    long long unsigned int i;
    long long unsigned int j;
    struct List rmvVertex;
    struct List *listHelper = new List;

    if(contains(info) == false){
        return(false);
    }

    //position of info at vectorArray
    for(i = 0; i < vectorArray.size(); i++){
        if(info == vectorArray[i].value){
            break;
        }
    }

    listHelper = vectorArray[i].head;
    while(listHelper != NULL){
        rmvEdg(info, listHelper->vertex);
        if(this->isDirected == false){
            rmvEdg(listHelper->vertex, info);
        }
        
        listHelper = listHelper->next;
    }

    //delete connections between vertexes that will be deleted
    for(j = 0; j < vectorArray.size(); j++){
        listHelper = vectorArray[j].head;
        while(listHelper != NULL){
            if(listHelper->vertex == info){
                rmvEdg(vectorArray[j].value, info);
            }
            listHelper = listHelper->next;
        }
    }

    vectorArray[i].head = NULL;
    vectorArray.erase(vectorArray.begin() + i);

    delete(listHelper);

    return(true);
}

template<typename T>
bool Graph<T>::rmvEdg(const T& from, const T& to){
    long long unsigned int i;
    struct List *listHelper = new List;
    struct List *beforeNode = new List;
    struct List *nextNode = new List;
    struct List *nextHead = new List;

    //does the vertex already exist
    if((contains(from) == false) || (contains(to) == false)){
        return(false);
    }

    for (i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == from){
           listHelper = vectorArray[i].head;
           while(listHelper != NULL){
               if(listHelper->vertex == to){
                    if((listHelper->vertex == vectorArray[i].head->vertex) && (vectorArray[i].head->next != NULL)){
                        nextHead = listHelper->next;
                        nextHead->prev = NULL;
                        vectorArray[i].head = nextHead;
                    }
                    else{
                        beforeNode = listHelper->prev;
                        nextNode = listHelper->next;

                        if(beforeNode != NULL){
                            beforeNode->next = nextNode;
                        }
                        else{
                            vectorArray[i].head = NULL;
                        }
                        
                        if(nextNode != NULL){
                            nextNode->prev = beforeNode;
                        }
                    }
                    break;
               }

               listHelper = listHelper->next;
           }
        }
    }
    if((this->isDirected == false) && (from != to)){        
        for (i = 0; i < vectorArray.size(); i++){
            if(vectorArray[i].value == to){
                listHelper = vectorArray[i].head;
                while(listHelper != NULL){
                    if(listHelper->vertex == from){
                        if((listHelper->vertex == vectorArray[i].head->vertex) && (vectorArray[i].head->next != NULL)){
                            nextHead = listHelper->next;
                            nextHead->prev = NULL;
                            vectorArray[i].head = nextHead;
                        }
                        else{
                            beforeNode = listHelper->prev;
                            nextNode = listHelper->next;

                            if(beforeNode != NULL){
                                beforeNode->next = nextNode;
                            }
                            else{
                                vectorArray[i].head = NULL;
                            }
                            
                            if(nextNode != NULL){
                                nextNode->prev = beforeNode;
                            }
                        }
                        break;
                    }

                    listHelper = listHelper->next;
                }
            }
        }
    }

    delete(listHelper);
    delete(beforeNode);
    delete(nextNode);
    delete(nextHead);

    return(true);
}

//dfs calls recursive dfs -> list must be clear before we start recusrion
template<typename T>
std::list<T> Graph<T>::dfs(const T& info){
    unsigned long long int i;
    std::list<T> dfsList;

    dfsList.clear();

    for (i = 0; i < vectorArray.size(); i++){
         vectorArray[i].visited = false;
    }

    dfsList = dfsRecursion(&dfsList, info);

    //case in which some vertexes are not connected with vertexes that are already visited
    for (i = 0; i < vectorArray.size(); i++){
         if(vectorArray[i].visited == false){
             dfs(vectorArray[i].value);
         }
    }

    return(dfsList);

}

template<typename T>
std::list<T> Graph<T>::dfsRecursion(std::list<T> *dfsList, const T& info){
    unsigned long long int i;
    struct List *listHelper = new List;

    for (i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == info)
            break;
    }

    vectorArray[i].visited = true;
    dfsList->push_back(info);
    listHelper = vectorArray[i].head;

    while(listHelper != NULL){
        if(isVisited(listHelper->vertex) == false){
            makeVisited(listHelper->vertex);
            dfsRecursion(dfsList, listHelper->vertex);
        }
        listHelper = listHelper->next;
    }

    delete(listHelper);
    return (*dfsList);
}

//checks if a vertex is visited
template<typename T>
bool Graph<T>::isVisited(const T& info){
    unsigned long long int i = 0;

    for(i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == info){
            return(vectorArray[i].visited);
        }
    }

    return(true);
}

//all vertexes visited 
template<typename T>
void Graph<T>::makeVisited(const T& info){
    unsigned long long int i = 0;

    for(i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == info){
            vectorArray[i].visited = true;
            return;
        }
    }
}

template<typename T>
std::list<T> Graph<T>::bfs(const T& info){
    std::list<T> bfsList;
    unsigned long long int i;
    unsigned long long int j;
    struct List *helpVertex = new List;
    list<T> queue;

    //empty list
    bfsList.clear();

    //initiliasation of every vertex visited = false
    for(i = 0; i < vectorArray.size(); i++)
        vectorArray[i].visited = false;
    
    for(i = 0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == info)
            vectorArray[i].visited = true;
    }
    queue.push_back(info);
    
    
    while((!queue.empty())){
        bfsList.insert(bfsList.end(), queue.front());

        for(j = 0; j < vectorArray.size(); j++){
            if(vectorArray[j].value == queue.front()){
                break;
            }
        }
        queue.pop_front();

        helpVertex = vectorArray[j].head;

        //koitame ta paidia tou komvou pou itan stin arxi tis queue
        while(helpVertex != NULL){            
            if (isVisited(helpVertex->vertex) == false){
                makeVisited(helpVertex->vertex);
                queue.push_back(helpVertex->vertex);
            }
            helpVertex = helpVertex->next;
        }

        //periptosi pou kapoioi komvoi den einai paidia aftwn pou exoun ginei visited
        if((queue.empty() == true) && (this->isDirected == true) && (bfsList<T>.size() < vectorArray.size())){
            for(; k < vectorArray.size(); k++){
                if(vectorArray[k].visited == false){
                    vectorArray[k].visited = true;
                    queue.push_back(vectorArray[k].value);
                    k++;
                    break;
                }
            }
        }
    }

    delete(helpVertex);

    return bfsList;
}

template<typename T>
bool Graph<T>::smallerTicket(const T& a, const T& b){
    int ticketA = -1;
    int ticketB = -1;
    unsigned long long int i;
 
    for(i=0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == a){
            ticketA = vectorArray[i].ticket;
        }
        else if(vectorArray[i].value == b){
            ticketB = vectorArray[i].ticket;
        }
    }
    if(ticketA < ticketB){
        return(true);
    }
    return(false);
}

template<typename T>
std::list<Edge<T>> Graph<T>::mst(){
    list<Edge<T>> mstQueue;
    unsigned long long int nodesVisited;
    nodesVisited = 0;
    int min;
    struct List *currNode = new List;
    T from;
    T to;
    unsigned long long int i;
    
    if(this->isDirected){
        return(mstQueue);
    }
    vectorArray[0].visited = true;
    for(nodesVisited = 1; nodesVisited < vectorArray.size(); nodesVisited++){
        min = std::numeric_limits<int>::max();
        for(i = 0; i < vectorArray.size(); i++){
            if(vectorArray[i].visited){
                currNode = vectorArray[i].head;
                while(currNode != NULL){
                    if(!isVisited(currNode->vertex)){
                        if(min>currNode->cost){
                            min = currNode->cost;
                            from = vectorArray[i].value;
                            to = currNode->vertex;
                        }
                    }
                    currNode = currNode->next;
                }
            }
        }
        if(smallerTicket(from, to)){
            Edge<T> currEdge(from, to, min);
            mstQueue = insertInList(mstQueue, currEdge);
        }
        else{
            Edge<T> currEdge(to, from, min);
            mstQueue = insertInList(mstQueue, currEdge);
        }
        makeVisited(to);
    }
    delete(currNode);
    
    return(mstQueue);
}

template<typename T>
std::list<Edge<T>> Graph<T>::insertInList(std::list<Edge<T>> list, Edge<T> edge){
    std::list<Edge<T>> copyList;
 
    if(edge.dist < list.front().dist){
        list.push_front(edge);
    }
    else if(edge.dist > list.back().dist){
        list.push_back(edge);
    }
    else{    
        while(edge.dist > list.front().dist){
            copyList.push_front(list.front());
            list.pop_front();
        }
        list.push_front(edge);
        while(!copyList.empty()){
            list.push_front(copyList.front());
            copyList.pop_front();
        }
    }
    return(list);
}

 
template<typename T>
void Graph<T>::makeAllUnvisited(){
    unsigned long long int i;

    for(i=0; i < vectorArray.size(); i++){
        vectorArray[i].visited = false;
    }
}

template<typename T>
list<T> Graph<T>::dijkstra(const T& from,const T& to){
    list<T> dijkQueue;
    struct List *currNode = new List;
    
    unsigned long long int totalNodes;
    totalNodes = vectorArray.size();
    int dijkPathArrayIndex = 0;
    int maxCost = 100;
    //int thisRowWeight=0;
    unsigned long long int i;
    unsigned long long int j;
    unsigned long long int k;
 
    T dijkPathArray[totalNodes];
    int costsArray[totalNodes][totalNodes];
 
    makeAllUnvisited();
    for(i=0; i < totalNodes; i++){
        for(j=0; j < totalNodes; j++){
            costsArray[i][j] = maxCost;
        }
    }
    for(i=0; i < vectorArray.size(); i++){
        if(vectorArray[i].value == from){
            makeVisited(vectorArray[i].value);
            costsArray[0][vectorArray[i].ticket] = 0;
 
            dijkPathArray[dijkPathArrayIndex] = from;
            dijkPathArrayIndex++;
            
            currNode = vectorArray[i].head;
            while(currNode != NULL){
                int col = currNode->ticket;
                if(costsArray[0][col]>currNode->cost){
                    costsArray[0][col] = currNode->cost;
                }
                currNode = currNode->next;
            }
            break;
        }
    } // Mexri edw apla exei mpei to from ston pinaka
    // kai exei arxikopoiithei i prwti seira gia ta analoga kosth
    //xwris na exei ginei epilogi min klp klp
 
    
    //Diadikasia gia na vreis mono gia mia seira to elaxisto kai na kaneis o,ti xreiazetai
    for(i=0; i < (vectorArray.size()-1); i++){
        int min_cost = maxCost;
        int min_col = -1;
        
        for(j = 0; j < vectorArray.size(); j++){
            if((costsArray[i][j] < min_cost) && (!vectorArray[j].visited)){
                min_cost = costsArray[i][j];
                min_col = j;
            }
        }    
 
        for(k=0; k < vectorArray.size(); k++){
            costsArray[i+1][k] = costsArray[i][k];
        }//copying entire row to the next
        if(min_col == -1){
            break;
        }
        dijkPathArray[dijkPathArrayIndex] = vectorArray[min_col].value;
        dijkPathArrayIndex++;
 
        for(j=0; j < vectorArray.size(); j++){
            if(vectorArray[j].value == dijkPathArray[dijkPathArrayIndex-1]){
                makeVisited(vectorArray[j].value);
                currNode = vectorArray[j].head;
                while(currNode != NULL){
                    int col = currNode->ticket;
                    if(costsArray[dijkPathArrayIndex-1][col]>(currNode->cost+min_cost)){
                        costsArray[dijkPathArrayIndex-1][col] = currNode->cost+min_cost;
                    }
                    currNode = currNode->next;
                }
            }
        }
    }
    
    int currNodeTicket = findTicket(to);
    if(costsArray[vectorArray.size()-1][currNodeTicket] == maxCost){
        return(dijkQueue);
    }
    dijkQueue.push_front(to);
    for(j=0; ((j < vectorArray.size()) && (vectorArray[currNodeTicket].value != from)); j++){
        for(i=0; i < vectorArray.size(); i++){
            if((costsArray[i][currNodeTicket] == costsArray[vectorArray.size()-1][currNodeTicket]) && (i!= (vectorArray.size()-1))){
                currNodeTicket = findTicket(dijkPathArray[i]);
                dijkQueue.push_front(dijkPathArray[i]);
                break;
            }
        }
    }
 
    if(from != dijkQueue.front()){
        dijkQueue.clear();
    }

    delete(currNode);
 
    return(dijkQueue);
}




#endif
