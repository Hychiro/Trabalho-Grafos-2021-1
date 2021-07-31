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
#include <string>

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
    this->first_node = NULL;
    this->last_node = NULL;
    this->number_edges = 0;

    insertAllNodes();
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != NULL)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

void Graph::printGraph(ofstream &output_file)
{
    output_file << "Printano o Grafo" << endl;
    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();

    while (p != NULL)
    {

        aux = p->getFirstEdge();
        while (aux != NULL)
        {

            output_file << p->getId() << " -- " << aux->getTargetId() << endl;
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{
    if (directed)
    {
        return this->number_edges;
    }
    else
    {
        return this->number_edges / 2;
    }
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
    if (this->first_node == NULL)
    {
        this->first_node = p;
    }
    else
    {
        this->last_node->setNextNode(p);
    }
    this->last_node = p;
}
void Graph::insertAllNodes()
{
    cout << " Escolha:" << endl;
    cout << " - 1 para colocar o id manualmente." << endl;
    cout << " - 2 para colocar de maneira automatica, porem pre-determinada." << endl;
    // int x;
    // cin >> x;
    for (int i = 0; i < this->order; i++)
    {
        /*
        if (x == 1)
        {
            int y;
            cin >> y;
            insertNode(y);
        }
        else if (x == 2)
        {
           */
        insertNode(i + 1); /*
        }
        else
        {
            cout << "Erro: selecione 1 ou 2 " << endl;
            cout << " - 1 para colocar o id manualmente." << endl;
            cout << " - 2 para colocar de maneira automatica, porem pre-determinada." << endl;
            i--;
            cin >> x;
        }*/
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    // junta os nos entre si
    if (searchNode(id)) //<-- ta sendo direcionado prestar atenção nisso.
    {
        if (this->directed) //se pa da pa botar mais coisa
        {
            Node *p = getNode(id);
            Node *sup = getNode(target_id);

            p->insertEdge(target_id, weight);
            p->incrementOutDegree();
            sup->incrementInDegree();
            this->number_edges += 1;
        }
        else
        {
            Node *p = getNode(id);
            Node *sup = getNode(target_id);
            p->insertEdge(target_id, weight);
            sup->insertEdge(id, weight);
            this->number_edges += 1;
        }
    }
}

void Graph::removeNode(int id) // pfv dps me ajudem a revisar esse removeNode
{
    Node *p;
    if (this->last_node != NULL)
    {
        if (this->first_node == this->last_node)
        {
            this->first_node = NULL;
            p = NULL;
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
            if (previousN->getNextNode() == NULL)
            {
                last_node = previousN;
            }
            // dps arrumar pra ser algo mais bonito, usando  remove edge, q eu n sei usar...
            if (directed)
            { /* sei implementa esse n...
                for (Node *i = first_node; i != NULL; i->getNextNode())
                {
                    for (Edge *k = p->getFirstEdge(); k != NULL; k->getNextEdge())
                    {
                        
                        
                    }
                }
            */
            }
            else
            {
                for (Node *i = first_node; i != NULL; i->getNextNode())
                {
                    Edge *k = i->getFirstEdge();
                    while (k != NULL)
                    {
                        sup = k;
                        k->getNextEdge();

                        if (k->getTargetId() == p->getId())
                        {
                            sup->setNextEdge(k->getNextEdge());
                            k = NULL;
                            k = sup->getNextEdge();
                        }
                    }
                }
            }
            p->removeAllEdges();
            p = NULL;
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
    while (p->getId() != id && p != NULL)
    {
        p = p->getNextNode();
    }
    if (p != NULL)
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
        while (p != NULL && p->getId() != id)
        {
            p = p->getNextNode();
        }
        return p;
    }
}

//Function that prints a set of edges belongs breadth tree

string Graph::floydMarshall(int idSource, int idTarget)
{
   int tamanho = getOrder();
    aux.str(string());
    Node* aux_node = first_node;
    int** distancia;
    distancia = constroiFloyd(tamanho, distancia);

    aux << "caminho minimo entre os pares" << idSource <<"e"<< idTarget << "=" << distancia[idTarget - 1][idTarget -1] << endl;

    for(int i=0; i< tamanho; i++){
        aux <<"[";
        for(int j=0; j< tamanho; j++){
            if(distancia[i][j] != INFINITY)
            {aux << distancia[i][j]<<".";}

            else{ aux<< distancia[i][j]<<".";}
            if(j == tamanho -1)
            aux<< "]\n";
        }
    }
    return aux.str();
}
int** Graph::constroiFloyd(int tamanho, int** distancia) {
    // funcao para utilizar a lista de adjacencia e para usar o algoritmo de Floyd
    //falta lista de adjacencia aqui
    for ( int c = 0; c < tamanho; c++ ) {
        for ( int i = 0; i < tamanho; i++ ) {
            if ( i != c ) {
                for ( int j = 0; j < tamanho; j++ ) {
                    if ( distancia[i][c] != INFINITY && distancia[c][j] != INFINITY ) {
                        if ( distancia[i][j] > distancia[i][c] + distancia[c][j] || distancia[i][j] == INFINITY )
                            distancia[i][j] = distancia[i][c] + distancia[c][j];
                    }
                }
            }
        }
    }
    return distancia;
}

void Graph::dijkstra(ofstream &output_file, int idSource, int idTarget)
{
    int distancia[this->order];
    int vertice_predecessor[this->order];
    bool visitados[this->order]; //vetor que verifica se o vértice ja foi visitado

    //Fazer uma fila de prioridade. (priority_queue)????
    //a ideia é fazer uma fila onde o primeiro valor seja a distancia (inteiro ou Edge????)
    //e o segundo valor seja o vetor (inteiro ou node???)

    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> fila;

    //Iniciar todas as distancias como inifinito, todos vertices como não visitados e todos predecessores como inexistentes(-1)
    for (int i = 0; i < this->order; i++)
    {

        distancia[this->order] = 99999999;

        visitados[i] = false;
        vertice_predecessor[i] = -1;
    }

    distancia[idSource - 1] = 0; //Distancia do vertice inicial até ele mesmo é 0
    vertice_predecessor[idSource - 1] = -1;

    //inserir o vertice inicial na fila
    fila.push(make_pair(distancia[idSource - 1], this->getNode(idSource)));
    //iteraçao
    while (!fila.empty())
    {

        pair<int, Node *> distancia_no = fila.top();  //copia par (vertice e distancia) do topo
        Node *verticeAnalisado = distancia_no.second; //obtem o vértice copiado no passo anterior
        fila.pop();                                   //remove da fila

        //verifica se o vértice ja foi visitado
        if (visitados[verticeAnalisado->getId() - 1] == false)
        {
            //marca como visitado
            visitados[verticeAnalisado->getId() - 1] = true;

            // percorre os vértices adjacentes  do vertice analisado
            for (Edge *it = verticeAnalisado->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                //obtém o vertice adjancente e o custa da aresta
                int verticeAdjacente = it->getTargetId() - 1;
                int custo_aresta = it->getWeight();

                //verificar se a distancia vértices adjacente é maior que a distancia da distancia do vertice analisado + o custa da aresta
                if (distancia[verticeAdjacente] > (distancia[verticeAnalisado->getId() - 1] + custo_aresta))
                {
                    //atualiza a distancia do vertice Adjacente e insere na fila
                    distancia[verticeAdjacente] = distancia[verticeAnalisado->getId() - 1] + custo_aresta;
                    vertice_predecessor[verticeAdjacente] = verticeAnalisado->getId();
                    fila.push(make_pair(distancia[verticeAdjacente], getNode(verticeAdjacente)));
                }
            }
        }
    }
    output_file << "teste de mesa 1" << endl;
    int contador = 0;
    int vetorId[this->order];
    for (int o = 0; o < this->order; o++)
    {
        output_file << vertice_predecessor[o] << " e ";
    }
    output_file << endl;
    for (int j = idTarget; vertice_predecessor[j - 1] != -1; j = vertice_predecessor[j - 1])
    {
        vetorId[contador] = vertice_predecessor[j - 1];
        contador++;
    }
    output_file << "valor contador: " << contador << endl;
    output_file << "teste de mesa 2" << endl;
    for (int k = 0; k < contador; k++)
    {
        output_file << vetorId[k] << " -- ";
    }
    output_file << "teste de mesa 3" << endl;
    output_file << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////FECHO TRANSITIVO E BUSCAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graph::fechoTransitivoDireto(int id)
{
    ofstream output_file;
    cout<<"Os procedimentos serao salvos em um arquivo avulso com o nome do metodo."<<endl;
    
    output_file.open("C://Users//Usuario//Documents//repositorio//Trabalho-Grafos-2021-1//fechoTransitivoIndireto.txt");


    int *preDeProfund = new int[this->order];
    //chama a busca para conseguir o preDeProfund;
    bool vemDaFecho = true;
    deepthFirstSearch(preDeProfund);
    //parametro para olhar o vetor;
    int i = id;
    //auxiliares
    int *vetAux = new int[this->order];
    for (int j = 0; j < this->order; j++)
    {
        vetAux[j] = 0;
    }
    int k = 0;
    //processo de salvar os dados;
    output_file << "Fecho Transitivo indireto:" << endl;
    output_file << " R-(" << id << ") = {";
    while (i != -2)
    {
        i = i - 1;
        vetAux[k] = preDeProfund[i];
        i = preDeProfund[i];
        k++;
        
    }   

    for (int p=k-1; p >= 0; p--)
    {
        if (vetAux[p] != -2)
        {
            output_file << " " << vetAux[p];
        }
    }
    output_file << "}" << endl;
}


////deepthFirstSearch 1 (do fecho transitivo indireto)
void Graph::deepthFirstSearch(ofstream &output_file, int x)
{
    //Cria vetor verificador e o vetor predecessor de profundidade
    bool *verify = new bool[this->order];
    int *preDeProfund = new int[this->order];

    int idParametro;
    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
        preDeProfund[i] = -1;
    }
    //cria o vetor auxiliar
    Node *aux;
    //verifica o no de entrada para começar a busca
    //Para todo v em G
    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        idParametro = p->getId() - 1;
        //Se v não visitado entao
        if (!verify[idParametro])
        {
            preDeProfund[idParametro] = -2;
            //AUX-BuscaPorProfundidade (G,v)
            auxDeepthFirstSearch(verify, preDeProfund, p);
        }
    }

    output_file << "Printando O vetor de profundidade" << endl;
    output_file << "< ";
    for (int k = 0; k < this->order; k++)
    {
        output_file << preDeProfund[k] << " ";
    }
    output_file << ">" << endl;
}
////deepthFirstSearch 2
void Graph::deepthFirstSearch(int preDeProfund[])
{
    //Cria vetor verificador e o vetor predecessor de profundidade
    bool *verify = new bool[this->order];

    int idParametro;
    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
        preDeProfund[i] = -1;
    }
    //cria o vetor auxiliar
    Node *aux;
    //verifica o no de entrada para começar a busca
    //Para todo v em G
    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        idParametro = p->getId() - 1;
        //Se v não visitado entao
        if (!verify[idParametro])
        {
            preDeProfund[idParametro] = -2;
            //AUX-BuscaPorProfundidade (G,v)
            auxDeepthFirstSearch(verify, preDeProfund, p);
        }
    }
}
void Graph::auxDeepthFirstSearch(bool verify[], int preDeProfund[], Node *v)
{
    //Protocolo inicial.
    int idParametro = v->getId() - 1;

    Node *aux;
    //Marca v como visitado
    verify[idParametro] = true;

    //Para todo w em Adj(v)
    for (Edge *p = v->getFirstEdge(); p != NULL; p = p->getNextEdge())
    {

        idParametro = p->getTargetId() - 1;
        //Se w não visitado então
        if (!verify[idParametro])
        {
            //Inserir aresta na arvore
            preDeProfund[idParametro] = v->getId();

            aux = getNode(p->getTargetId());
            //AUX-BuscaPorProfundidade (G,w)
            auxDeepthFirstSearch(verify, preDeProfund, aux);
        }
    }
}

//function that prints a topological sorting
void topologicalSorting()
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
