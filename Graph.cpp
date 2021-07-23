#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

//implementacao abaixo:
void Graph::insertNode(int id)
{
    Node *p = new Node(id);

    p->setNextNode(nullptr);
    if (first_node == nullptr)
    {
        first_node = p;
    }
    else
    {
        last_node->setNextNode(p);
    }
    last_node = p;
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    if(searchNode(id)){
        Node* p = getNode(id);
        p->insertEdge(target_id,weight);
    }
}

void Graph::removeNode(int id)
{
Node* p;
	if(last_node != nullptr)
	{
		if(first_node == last_node)
		{
			first_node = nullptr;
			p = nullptr;
		}
		else
		{
			p = first_node;
			while(p->getNextNode() != last_node)
				p = p->getNextNode();
			p->setNextNode(nullptr);
		}
		delete last_node;
		last_node = p;
		order--;
	}
	else
		cout << "ERRO: o grafo esta vazio!" << endl;
}

bool Graph::searchNode(int id)
{
    Node *p = first_node;
    int i = 0;
    while (i < id && p != NULL)
    {
        i++;
        p = p->getNextNode();
    }
    if (p != nullptr)
    {
        return true;
    }
    return false;
}

Node *Graph::getNode(int id)
{
    Node *p = first_node;
    int i = 0;
    if (searchNode(id))
    {
        while (i < id)
        {
            i++;
            p = p->getNextNode();
        }
        return p;
    }
}

//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file)
{
}

float Graph::floydMarshall(int idSource, int idTarget)
{
}

float Graph::dijkstra(int idSource, int idTarget)
{
}

//function that prints a topological sorting
void topologicalSorting()
{
}

void breadthFirstSearch(ofstream &output_file)
{
}
Graph *getVertexInduced(int *listIdNodes)
{
}

Graph *agmKuskal()
{
}
Graph *agmPrim()
{
}
