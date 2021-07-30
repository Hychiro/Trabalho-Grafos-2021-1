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

    Graph *grafo = new Graph(4, false, false, false);

    int order = grafo->getOrder();
    cout << order << endl;

    Node *p = grafo->getFirstNode();
    int i = 0;
    int order = grafo->getOrder();
    Edge *aux = p->getFirstEdge();
    while (p != NULL && i != order)
    {
        
        p = p->getNextNode();
        aux = p->getFirstEdge();
        while (aux != NULL)
        {
            cout << p->getId() << " -- "<< aux->getTargetId()<<endl;
            aux = aux->getNextEdge();
        }
        i++;
    }

    grafo->deepthFirstSearch(output_file, 2);
    output_file.close();
    return 0;
}