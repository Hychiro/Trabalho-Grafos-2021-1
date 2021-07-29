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
    //inserindo os nos
    for (int i = 1; i <= this->order; i++)
    {
        insertNode(i);
    }
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
    // so cria o no e deixa ele no espaço
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
    // junta os nos entre si
    if (searchNode(id))
    {
        Node *p = getNode(id);
        p->insertEdge(target_id, weight);
        this->number_edges += 1;
    }
    if (this->directed) //se pa da pa botar mais coisa
    {
        Node *p = getNode(id);
        p->incrementOutDegree();
        Edge *aux = p->getFirstEdge();
        while (target_id != aux->getTargetId())
        {
            aux->getNextEdge();
        }
        p = getNode(aux->getTargetId());
        p->incrementInDegree();
    }
}

void Graph::removeNode(int id) // pfv dps me ajudem a revisar esse removeNode
{
    Node *p;
    if (this->last_node != nullptr)
    {
        if (this->first_node == this->last_node)
        {
            this->first_node = nullptr;
            p = nullptr;
        }
        else
        {
            Node *previousN = this->first_node;
            Node *nextN;
            Node *aux;
            Edge *sup;

            p = getNode(id);

            while (p != previousN->getNextNode())
            {
                previousN->getNextNode();
            }
            nextN = p->getNextNode();

            previousN->setNextNode(nextN);
            if (previousN->getNextNode() == nullptr)
            {
                last_node = previousN;
            }
            // dps arrumar pra ser algo mais bonito, usando  remove edge, q eu n sei usar...
            if (directed)
            { /* sei implementa esse n...
                for (Node *i = first_node; i != nullptr; i->getNextNode())
                {
                    for (Edge *k = p->getFirstEdge(); k != nullptr; k->getNextEdge())
                    {
                        
                        
                    }
                }
            */
            }
            else
            {
                for (Node *i = first_node; i != nullptr; i->getNextNode())
                {
                    Edge *k = i->getFirstEdge();
                    while (k != nullptr)
                    {
                        sup = k;
                        k->getNextEdge();

                        if (k->getTargetId() == p->getId())
                        {
                            sup->setNextEdge(k->getNextEdge());
                            k = nullptr;
                            k = sup->getNextEdge();
                        }
                    }
                }
            }
            p->removeAllEdges();
            p = nullptr;
        }
        order--;
    }
    else
        cout << "ERRO: o grafo esta vazio!" << endl;
}

bool Graph::searchNode(int id)
{
    // so verifica se exste o no ali ou nao
    Node *p = first_node;
    while (p->getId() != id && p != nullptr)
    {
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
    //pega o no na lista de nos
    Node *p = first_node;
    if (searchNode(id))
    {
        while (p != nullptr && p->getId() != id)
        {
            p = p->getNextNode();
        }
        return p;
    }
}

//Function that prints a set of edges belongs breadth tree

float Graph::floydMarshall(int idSource, int idTarget)
{
}

void Graph::dijkstra(int idSource, int idTarget)
{
    int distancia[this->order]; 
    int vertice_predecessor[this->order];       
    bool visitados[this->order]; //vetor que verifica se o vértice ja foi visitado

    /*
    Fazer uma fila de prioridade. (priority_queue)????
    a ideia é fazer uma fila onde o primeiro valor seja a distancia (inteiro ou Edge????) 
    e o segundo valor seja o vetor (inteiro ou node???)
   */
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> fila;

    //Iniciar todas as distancias como inifinito
    for (int i = 0; i < this->order; i++)
    {
        distancia[this->order]=INFINITY;
        visitados[i] = false;
        vertice_predecessor[i]=-1;
    }

    distancia[idSource] = 0; //Distancia do vertice inicial até ele mesmo é 0
         vertice_predecessor[idSource]=-1;

    //inserir o vertice inicial na fila
    fila.push(make_pair(distancia[idSource], this->getNode(idSource)));

    //iteraçao
    while (!fila.empty())
    {
        pair<int, Node *> distancia_no = fila.top(); //copia par (vertice e distancia) do topo
        Node *verticeAnalisado = distancia_no.second;               //obtem o vértice copiado no passo anterior, (deveria ser do tipo Node???)
        fila.pop();                       //remove da fila

        //verifica se o vértice ja foi visitado
        if (visitados[verticeAnalisado->getId()] == false)
        {
            //marca como visitado
            visitados[verticeAnalisado->getId()] = true;

            // percorre os vértices adjacentes  do vertice analisado
            for (Edge *it = verticeAnalisado->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                //obtém o vertice adjancente e o custa da aresta
                int verticeAdjacente = it->getTargetId();
                int custo_aresta = it->getWeight();

                //verificar se a distancia vértices adjacente é maior que a distancia da distancia do vertice analisado + o custa da aresta
                if (distancia[verticeAdjacente] > (distancia[verticeAnalisado->getId()] + custo_aresta))
                {
                    //atualiza a distancia do vertice Adjacente e insere na fila
                    distancia[verticeAdjacente] = distancia[verticeAnalisado->getId()] + custo_aresta;
                    vertice_predecessor[verticeAdjacente] = verticeAnalisado->getId();
                    fila.push(make_pair(distancia[verticeAdjacente], getNode(verticeAdjacente)));
                }
            }
        }
    }
    
    

    std::list<int> caminho;
for(int i=idTarget;vertice_predecessor[i] != -1; i=vertice_predecessor[i])
{
    caminho.push_front(i);
}



}

//function that prints a topological sorting
void topologicalSorting()
{
}
void Graph::deepthFirstSearch(ofstream &output_file, int targetedId)
{
    int i = 0;

    bool *verify = new bool[getOrder()];
    for (int k = 0; k < getOrder(); k++)
    {
        verify[k] = false;
    }

    i = auxDeepthFirstSearch(output_file, first_node, verify, i, targetedId);
      output_file << first_node->getId() << endl;
}

int Graph::auxDeepthFirstSearch(ofstream &output_file, Node *p, bool verify[], int i, int targetedId)
{
    // retorna o valor de i, para quando achar o no,
    if (p->getId() == targetedId)
    {
        output_file << p->getId() << ", ";
        verify[first_node->getId() - 1] = true;
        return i;
    }
    // retorna o valor de i, para quando chegar em um ponto sem volta,
    else if (verify[p->getId() - 1])
    {
        return i;
    }
    //mantem a recursividade até tudo ser completado,
    else
    {
        Edge *aux = p->getFirstEdge();
        // fala q a procura passou por aqui
        if (!verify[p->getId() - 1])
        {
            verify[p->getId() - 1] = true;
        }
        // verifica as arestas disponiveis
        while (verify[aux->getTargetId() - 1])
        {
            aux = aux->getNextEdge();
        }

        //faz a leitura pra direita da lista de aresta,
        if (aux != nullptr)
        {
            Node *sup = p;
            p = getNode(aux->getTargetId());

            i = auxDeepthFirstSearch(output_file, p, verify, i + 1, targetedId); // se eu igualar a um i aqui eu tenho o numero de vertices visitados
            // verifica se ta voltano da recursividade apos ter achado, caso contrario, bota o algoritimo pra continuar a procurar do vertice anterior
            if (!verify[targetedId - 1])
            {
                verify[sup->getId() - 1] = false;
                i = auxDeepthFirstSearch(output_file, sup, verify, i + 1, targetedId); // faz a continuação da procura
            }
        }
        else
        {
            return i;
        }
        output_file << p->getId() << ", ";
        return i;
    }
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