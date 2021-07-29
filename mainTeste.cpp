#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.cpp"
#include "Node.cpp"
#include "Edge.cpp"

int main(){
    ofstream output_file;
    output_file.open("C://Users//Usuario//Documents//Ufjf//Grafos//testes.txt");
    
    Graph* grafo = new Graph(4,false,false,false);
    grafo->insertEdge(1,2,0);
    grafo->insertEdge(2,1,0);
    grafo->insertEdge(1,4,0);
    grafo->insertEdge(4,1,0);
    grafo->insertEdge(3,2,0);
    grafo->insertEdge(2,3,0);
    grafo->insertEdge(3,4,0);
    grafo->insertEdge(4,3,0);
    
    grafo->deepthFirstSearch( output_file,4);
    output_file.close();
    return 0;
}