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
    int dist[this.order];//vetor que diz a distancia de um vértice até todos os outos.
	bool visitados[this.order];//vetor que verifica se o vértice ja foi visitado


   /*
    Fazer uma fila de prioridade. (priority_queue)????
    a ideia é fazer uma fila onde o primeiro valor seja a distancia (inteiro ou Edge????) 
    e o segundo valor seja o vetor (inteiro ou node???)
   */
    priority_queue < pair<int, Node>, vector<pair<int,Node> >,greater<pair<int,Node> > > fila;

    //Iniciar todas as distancias como inifinito
    for (int i=0; i < this.order;i++)
    {
        dist[i] = INFINITY;   
        visitados[i] = false;
    }


    dist[idSource] = 0;//Distancia do vertice inicial até ele mesmo é 0

    //inserir o vertice inicial na fila
    fila.push(make_pair(dist[idSource],this->getNode(idSource)));

    //iteraçao
    while(!fila.empty())
    {
        pair<int, Node> p=fila.top();//copia par (vertice e distancia) do topo
        Node u = p.second;//obtem o vértice copiado no passo anterior, (deveria ser do tipo Node???)
        fila.pop(); //remove da fila

        //verifica se o vértice ja foi visitado
        if(visitados[u->getid()] == false)
        {
            //marca como visitado
            visitados[u->getid()] = true;


            ----// percorre os vértices "v" adjacentes de "u"
            for(Edge* it = u->getFirstEdge();it!=nullptr;it = it->next_edge)
            {
                -----//obtém o vertice adjancente e o custa da aresta
                int v = it->getTargetId();
                int custo_aresta = it->getWeight();

                -----//verificar se a dist[v] é maior que a distancia de dist[u] + o custa da aresta
                if(dist[v] > (dist[u] + custo_aresta))
                {
                    //atualiza a distancia de "v" e insere na fila
                    dist[v] = dist[u] + custo_aresta;
                    fila.push(make_pair(dist[v], getNode(v)));

                }
            }
        }
    }

    return dist[idSource];
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
