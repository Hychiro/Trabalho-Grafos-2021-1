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

using namespace std;

int main()
{
    ofstream output_file;
    output_file.open("C://Users//Usuario//Documents//repositorio//Trabalho-Grafos-2021-1//testes.txt");

    Graph *grafo = new Graph(10, true, false, false);
    grafo->insertEdge(1,2,0);
    grafo->insertEdge(2,3,0);
    grafo->insertEdge(3,4,0);
    grafo->insertEdge(4,6,0);
    grafo->insertEdge(3,5,0);
    grafo->insertEdge(6,7,0);
    grafo->insertEdge(8,7,0);
    grafo->insertEdge(9,8,0);
    grafo->insertEdge(10,9,0);
    
    int order = grafo->getOrder();
    cout << "Ordem: "<< order << endl;
    int *vetPrev = new int[grafo->getOrder()];
    Node *p = grafo->getFirstNode();
    Edge *aux = p->getFirstEdge();
    grafo->printGraph(output_file);
    grafo->fechoTransitivoIndireto(7);
    grafo->deepthFirstSearch(output_file,8);
    output_file.close();

    return 0;
}