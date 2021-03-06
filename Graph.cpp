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
#include <bits/stdc++.h>

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
     this->conexGraph = false;
    this->first_node = NULL;
    this->last_node = NULL;
    this->number_edges = 0;

    insertAllNodes();
}

Graph::Graph(bool directed, bool weighted_edge, bool weighted_node)
{
    this->order = 0;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->conexGraph = false;
    this->first_node = NULL;
    this->last_node = NULL;
    this->number_edges = 0;
}

Graph::Graph(int node){
    this->num_arestas = 0;
    this->num_cores = 0;
    this->densidade = 0;
    this->generated = false;
    this->num_vertices = node;
    this->solucao_otima = NULL;
    MatrizAdjacente = new Edge *[node];
    for( int i=0 ; i<num_vertices ; i++ )
    {
        MatrizAdjacente[i] = new Edge [num_vertices];
    }
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
    for( int i=0 ; i<num_vertices ; i++ ){
        delete (MatrizAdjacente[i]);
    }
    delete MatrizAdjacente;
    if( solucao_otima!=NULL ){
        delete solucao_otima;
    }
}

void Graph::printGraph(ofstream &output_file)
{
    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();
    if (!directed)
    {
        output_file << "strict graph{"<<endl;
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
        output_file <<"}"<<endl;
    }
    else
    {
        output_file << "digraph{"<<endl;
        while (p != NULL)
        {

            aux = p->getFirstEdge();
            while (aux != NULL)
            {

                output_file << p->getId() << " -> " << aux->getTargetId() << endl;
                aux = aux->getNextEdge();
            }
            p = p->getNextNode();
        }
        output_file <<"}"<<endl;
    }
        output_file << endl;
    output_file << endl;
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
    // so cria o no e deixa ele no espa??o
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
    this->last_node->setNextNode(NULL);
    this->order++;
}
void Graph::insertAllNodes()
{
    for (int i = 0; i < this->order; i++)
    {
        Node *p = new Node(i + 1);
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
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    // junta os nos entre si
    if (searchNode(id)) //<-- ta sendo direcionado prestar aten????o nisso.
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
            int count_edges = 0;

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
            if (directed) // verifica se grafo e direcionado
            {
                aux = this->first_node;
                while (aux != NULL) //percorrendo todos os nos
                {
                    //conta  as arestas removidas e remove-as
                    count_edges += aux->removeEdge(id, this->directed, aux);
                    aux = aux->getNextNode();
                }
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

    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        if (p->getId() == id)
        {
            return true;
        }
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
    return p;
}

//Function that prints a set of edges belongs breadth tree

void Graph::floydMarshall(ofstream &output_file, int idSource, int idTarget)
{
    int tamanho = getOrder();
    Node* aux_node = first_node;
    int**distancia = new int*[this->order];
    distancia = constroiFloyd(tamanho, distancia);
    
    output_file << "O menor caminho entre o No[" << idSource << "] e o No[" << idTarget << "] e: [" << distancia[idSource-1][idTarget-1] << "]"<<endl;
    
    Node *aux_node2 = this->first_node;
    output_file<< " matriz das Dist??ncias mais curtas entre cada par de v??rtices:"<< endl;
    for (int i = 0; i < this->order + 1; i++) 
    {
        if (i == 0)
            output_file << setw(7) << " ";
        else {
            output_file << setw(7) << aux_node2->getId();
            aux_node2 = aux_node2->getNextNode();
        }
    }
    output_file<< endl;
    aux_node2= this->first_node;
    for (int i = 0; i < this->order; i++) 
    {
        for (int j = 0; j < this->order + 1; j++) {
            if (j == 0) 
            {
                output_file << setw(7) << " | "<< aux_node2->getId()<< " | ";;
                aux_node2 = aux_node2->getNextNode();
            }
            else {
                if (distancia[i][j - 1] == INT_MAX/2)
                    output_file << setw(7) << "INF" <<" | ";
                else
                    output_file << setw(7) << distancia[i][j - 1] << " | ";
            }
        }
        output_file << endl;
    }
}
int**Graph::constroiFloyd(int tamanho, int **distancia)
{
    // funcao para utilizar a lista de adjacencia e para usar o algoritmo de Floyd
    distancia = new int*[tamanho];
    for (int k = 0; k < tamanho; k++)
    {
        distancia[k] = new int[this->order];
    }
    Node* aux_node1 = this->first_node;
    Node* aux_node2;
    int peso_aresta = 1;

    //matriz  com os valores de cada aresta entre os nos
    for (int i = 0; aux_node1 != NULL; aux_node1 = aux_node1->getNextNode(), i++) {
        aux_node2 = this->first_node;

        for (int j = 0; aux_node2 != NULL; aux_node2 = aux_node2->getNextNode(), j++) 
        {
            Edge *aux = aux_node1->hasEdgeBetween(aux_node2->getId());

            if(this->weighted_edge && aux != NULL)
                peso_aresta  = aux->getWeight();

            if (aux_node1->getId() == aux_node2->getId())
                distancia[i][j] = 0;

            else if(aux!=NULL)

                distancia[i][j] = peso_aresta;

            else
                distancia[i][j] = INT_MAX/2;
        }
    }
    for (int c = 0; c < tamanho; c++)
    {
        // Escolhendo todos os v??rtices como fonte, um por um
        for (int i = 0; i < tamanho; i++)
        {
            if (i != c)
            {// Escolhendo todos os v??rtices como destino
                for (int j = 0; j < tamanho; j++)
                {
                    //Se o v??rtice c estiver no caminho mais curto de i para j, em seguida, atualize o valor de dist [i] [j]
                    if (distancia[i][j] > distancia[i][c] + distancia[c][j] && distancia[i][c] + distancia[i][j]>0)
                           distancia[i][j] = distancia[i][c] + distancia[c][j];
                }

            }
        }
    }
    return distancia;
}

void Graph::dijkstra(ofstream &output_file, int idSource, int idTarget)
{
    int distancia[this->order];           //vetor que faz uma analogia entre id e distancia
    int vertice_predecessor[this->order]; //vetor que faz uma analogia entre id e v??rtice predecessor do caminho minimo
    bool visitados[this->order];          //vetor que verifica se o v??rtice ja foi visitado

    //Fazer uma fila de prioridade minima.
    //a ideia ?? fazer uma fila onde o primeiro valor seja a distancia
    //e o segundo valor seja o id do v??rtice
    typedef pair<int, int> o;
    priority_queue<o, vector<o>, greater<o>> fila;

    //Iniciar todas as distancias como inifinito, todos vertices como n??o visitados e todos predecessores como inexistentes(-1)
    for (int i = 0; i < this->order; i++)
    {

        distancia[i] = 4203209;

        visitados[i] = false;
        vertice_predecessor[i] = -1;
    }

    distancia[idSource - 1] = 0;            //Distancia do vertice inicial at?? ele mesmo ?? 0
    vertice_predecessor[idSource - 1] = -2; //Predecessor do vertice inicial ?? tido como -2

    //inserir o vertice inicial na fila
    fila.push(make_pair(distancia[idSource - 1], idSource));
    //itera??ao
    while (!fila.empty())
    {
        pair<int, int> distancia_no = fila.top(); //copia par (id do vertice e distancia) do topo
        int idVertice = distancia_no.second;
        Node *verticeAnalisado = this->getNode(idVertice); //obtem o v??rtice a ser analisado a partir de seu id
        fila.pop();                                        //remove o par da fila

        //verifica se o v??rtice ja foi visitado
        if (visitados[verticeAnalisado->getId() - 1] == false)
        {
            //marca como visitado
            visitados[verticeAnalisado->getId() - 1] = true;
            for (Edge *it = verticeAnalisado->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                //obt??m o vertice adjancente e o custa da aresta
                int verticeAdjacente = it->getTargetId() - 1;
                int custo_aresta = it->getWeight();
                //verificar se a distancia v??rtices adjacente ?? maior que a distancia da distancia do vertice analisado + o custa da aresta
                if (distancia[verticeAdjacente] > (distancia[verticeAnalisado->getId() - 1] + custo_aresta))
                {
                    //atualiza a distancia do vertice Adjacente e insere na fila
                    distancia[verticeAdjacente] = distancia[verticeAnalisado->getId() - 1] + custo_aresta;
                    vertice_predecessor[verticeAdjacente] = verticeAnalisado->getId();
                    fila.push(make_pair(distancia[verticeAdjacente], verticeAdjacente + 1));
                }
            }
        }
    }

    if (vertice_predecessor[idTarget - 1] != -1 && vertice_predecessor[idTarget - 1] != -2)
    {

        if (vertice_predecessor[idTarget - 1] != -1 && vertice_predecessor[idTarget - 1] != -2)
        {
            if (this->directed)
            {
                list<int> caminho;
                int a = vertice_predecessor[idTarget - 1];
                while (vertice_predecessor[a - 1] != -2 && vertice_predecessor[a - 1] != -1)
                {
                    caminho.push_front(a);
                    a = vertice_predecessor[a - 1];
                }
                output_file << "Custo da Distancia de "<<idSource<< " at?? "<<idTarget<<" ??: "<<distancia[idTarget-1]<<endl;
                output_file << idSource;
                for (int i = 0; !(caminho.empty()); i++)
                {
                    output_file << " -> " << caminho.front();
                    caminho.pop_front();
                }
                output_file << " -> " << idTarget;
            }

            if (!(this->directed))
            {
                list<int> caminho;
                int a = vertice_predecessor[idTarget - 1];
                while (vertice_predecessor[a - 1] != -2 && vertice_predecessor[a - 1] != -1)
                {
                    caminho.push_front(a);
                    a = vertice_predecessor[a - 1];
                }
                output_file << "Custo da Distancia de "<<idSource<< " at?? "<<idTarget<<" ??: "<<distancia[idTarget-1]<<endl;
                output_file << idSource;
                for (int i = 0; !(caminho.empty()); i++)
                {
                    output_file << " -- " << caminho.front();
                    caminho.pop_front();
                }
                output_file << " -- " << idTarget;
            }
        }
        else if (vertice_predecessor[idTarget - 1] == -1)
        {
            output_file << "n??o existe caminho" << endl;
        }
        else if (vertice_predecessor[idTarget - 1] == -2)
        {
            output_file << "Id Sorurce ?? o mesmo que IdTarget" << endl;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////FECHO TRANSITIVO E BUSCAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::fechoTransitivoDireto(ofstream &output_file, int id)
{

    //com o id do v??rtice acha o vertice que deve ser analisado
    int idParametro = id - 1;
    //cria um vetor que marca quais v??rtices ja foram analisados
    bool visitados[this->order];
    //cria o vetor fecho transitivo direto
    bool FTD[this->order];
    //cria uma fila que diz quais vertices ainda precisam ser analisados
    list<int> fila;
    //adiciona o vertice inicial nele
    fila.push_front(id);

    for (int i = 0; i < this->order; i++)
    {
        visitados[i] = false;
        FTD[i] = false;
    }

    //come??a itera????o (enquanto a fila n??o estiver vazia repita)
    while (!(fila.empty()))
    {
        //pega um v??rtice a ser analisado da fila
        int aux = fila.front();
        int IdAnalisado = aux - 1;
        Node *V;
        V = getNode(fila.front());
        //exclui ele da fila
        fila.pop_front();
        //verifica se o v??rtice a ser analisado ja foi analisado. (se ele ja foi acaba essa itera????o)
        if (visitados[IdAnalisado] == false)
        {
            //marca o v??rtice como visitado;
            visitados[IdAnalisado] = true;
            //adiciona ele no vetor fecho transitivo direto
            FTD[IdAnalisado] = true;
            //adiciona todos os v??rtices adjacentes a ele na fila
            for (Edge *it = V->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                int verticeAdjacente = it->getTargetId();
                fila.push_front(verticeAdjacente);
            }
        }
    }

    //imprimir o FTD
    output_file << "O conjunto FTD do v??rtice " << id << " ??: {";
    int contador = 0;
    for (int i = 0; i < this->order; i++)
    {
        if (FTD[i] == true)
        {
            contador++;
        }
    }
    for (int i = 0; i < this->order; i++)
    {
        if (FTD[i] == true)
        {
            if (contador - 1 > 0)
            {
                output_file << i + 1 << ", ";
                contador--;
            }
            else if (contador - 1 == 0)
            {
                output_file << i + 1;
            }
        }
    }
    output_file << "}" << endl;
}

void Graph::fechoTransitivoIndireto(ofstream &output_file, int id)
{
    bool *fti = new bool[this->order];
    bool *verify = new bool[this->order];
    for (int i = 0; i < this->order; i++)
    {
        fti[i] = false;
        verify[i] = false;
    }

    int conta = 0;
    // diz sim ou nao para a existencia de um a caminho ate o id procurado, para todos os vertices do grafo
    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        if (!verify[p->getId() - 1])
        {
            verify[p->getId() - 1] = true;
            fti[p->getId() - 1] = deepthFirstSearch1(id, p->getId());
            if (fti[p->getId() - 1])
            {
                conta++;
            }
        }
    }

    // printando bonitinho
    output_file << "O fecho transitivo indireto de " << id << " eh:";
    output_file << "{";

    int aux = 0;
    for (int j = 0; j < this->order; j++)
    {
        if (fti[j])
        {
            if (aux == conta - 1)
            {
                output_file << (j + 1);
                aux++;
            }
            else
            {
                output_file << (j + 1) << ", ";
                aux++;
            }
        }
    }
    output_file << "}" << endl;
}

bool Graph::deepthFirstSearch1(int id, int start)
{

    //Cria vetor verificador e o vetor predecessor de profundidade
    bool *verify = new bool[this->order];
    int conta = 0;
    int idParametro;
    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
    }
    //cria o vetor auxiliar
    Node *p;
    
    //Para todo v em G
    p = getNode(start);
    idParametro = p->getId() - 1;
    //Se v n??o visitado entao

    
    //Se v n??o visitado entao
    if (id != p->getId())
    {
        //AUX-BuscaPorProfundidade (G,v)
        auxDeepthFirstSearch1(verify, p);
    }
    else
    {   

        return true;
    }

    //Se encontrou o que buscava
    if (verify[id - 1])
    {
        delete[] verify;
        return true;
    }
    delete[] verify;
    return false;
}

void Graph::auxDeepthFirstSearch1(bool verify[], Node *v)
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
        //Se w n??o visitado ent??o

        if (!verify[idParametro])
        {

            aux = getNode(p->getTargetId());
            //AUX-BuscaPorProfundidade (G,w)
            auxDeepthFirstSearch1(verify, aux);
        }
    }
}

////deepthFirstSearch realizar a busca por profundidade a partir de um ponto de referencia do grafo.
void Graph::deepthFirstSearch(Graph *novoGrafo, int start)
{

    //Cria vetor verificador e o vetor predecessor de profundidade
    bool *verify = new bool[this->order];

    int idParametro;
    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
    }
    //cria o vetor auxiliar
    Node *p;
    //verifica o no de entrada para come??ar a busca

    //Para todo v em G
    for (p = getNode(start); NULL != p; p = p->getNextNode())
    {

        idParametro = p->getId() - 1;
        //Se v n??o visitado entao
        if (!verify[idParametro])
        {
            novoGrafo->insertNode(p->getId());
            //AUX-BuscaPorProfundidade (G,v)
            auxDeepthFirstSearch(verify, novoGrafo, p);
            break;
        }
    }
}

void Graph::auxDeepthFirstSearch(bool verify[], Graph *novoGrafo, Node *v)
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
        //Se w n??o visitado ent??o

        if (!verify[idParametro])
        {
            novoGrafo->insertNode(p->getTargetId());
            //Inserir aresta na arvore
            novoGrafo->insertEdge(v->getId(), p->getTargetId(), p->getWeight());

            aux = getNode(p->getTargetId());
            //AUX-BuscaPorProfundidade (G,w)
            auxDeepthFirstSearch(verify, novoGrafo, aux);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CAMINHAMENTO,ALGORITMOS E ORDENACAO TOPOLOGICA///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Graph *Graph::caminhamentoDeProfundidade(int x)
{

    Graph *novoGrafo = new Graph(this->directed, this->weighted_edge, this->weighted_node);
    deepthFirstSearch(novoGrafo, x);
    return novoGrafo;
}
// fun????o que imprime uma classifica????o topol??gica

void Graph::topologicalSorting(ofstream &output_file)
{   list<Node*> listaNos; 
    list<int> listaTopologica;
    if (this->graphtemCiclo())// verifica se o grafo e aciclico ou nao
    {
        output_file <<" Se Grafo possui ciclos, nao possui ordena????o topologica"<<endl;
    }
    else{ // adaptando algoritimo kahn's
            Edge *auxAres;
            Node *auxNo;
            //procurando nos com enttrada =0
            for (auxNo=this->first_node;auxNo!=NULL;auxNo = auxNo->getNextNode())
            {   if (auxNo->getInDegree()==0)// se entrada  = 0
                {
                    listaNos.push_back(auxNo); //coloca os nos corretos na fila
                }
            }
            while (!listaNos.empty())// enquanto lista e vazia 
            {
                Node *aux = listaNos.front();
                listaNos.pop_front(); //remove da lista
                listaTopologica.push_back(aux->getId()); //coloca na lista auxiliar
                for(auxAres =aux->getFirstEdge(); auxAres!=NULL;auxAres=auxAres->getNextEdge())
                {
                    auxNo = this->getNode(auxAres->getTargetId()); //pega o no vizinho
                    auxNo->decrementInDegree(); //decrementa o grau de entrada
                    if (auxNo->getInDegree()==0) //se a entrada = 0
                    {    
                        listaNos.push_back(auxNo);
                    }
                    
                }
            }
            //imprimindo ordena??ao a classifica????o topologica 
            output_file << "Ordena????o Topologica :" << endl;
            for(list<int>::iterator i = listaTopologica.begin(); i != listaTopologica.end(); i++)
            {
                    if(listaTopologica.size() == this->getOrder())
                    output_file << (*i) << endl;
            }
           
        }
}
//verifica se grafo tem ciclo
bool Graph::graphtemCiclo()
{
    list<int> auxC;
    // coloca os components em uma lista
    for (int i = 0; i < this->order; i++)
    {
        auxC.push_back(i);
    }// Ent??o a lista ?? classificada
    auxC.sort();

    for (list<int>::iterator i = auxC.begin(); i !=  auxC.end();){
     int prev = *i;
        i++;
        // Se houver componentes iguais, o gr??fo ?? c??clico,
         // entao o grafo tem um circuito
        if (prev == *i)
            return true;
    }
        // Se  forem diferentes entre eles, o grafo nao tem circuito
    return false;
}
Graph *Graph::getVertexInduced(int *listIdNodes, int tam)
{
    Graph *subGrafo = new Graph(this->directed, this->weighted_edge, this->weighted_node);
    //para todo noh da lista fa??a

    for (int i = 0; i < tam; i++)
    {

        //incluir noh no subgrafo
        if (this->searchNode(listIdNodes[i]))
        {
            subGrafo->insertNode(listIdNodes[i]);
        }
    }
    Node *p;
    Node *orig;
    Edge *aux;
    bool verificaSeTem = false;
    //para todo noh do subgrafo,
    for (p = subGrafo->getFirstNode(); p != NULL; p = p->getNextNode())
    {
        orig = getNode(p->getId());

        //verificar as arestas no grafo original.
        for (aux = orig->getFirstEdge(); aux != NULL; aux = aux->getNextEdge())
        {

            // se a aresta do vertice pra onde ela aponta existir

            verificaSeTem = subGrafo->searchNode(aux->getTargetId());
            if (verificaSeTem)
            {
                // incluir a aresta no noh do subgrafo;
                subGrafo->insertEdge(p->getId(), aux->getTargetId(), aux->getWeight());
            }
        }
    }
    // retorna subgrafo
    return subGrafo;
}

Graph *Graph::agmKuskal(ofstream &output_file)
{
    //transformar o abaixo em codigo e usar o vetor listaNos como parametro
    int tamanho, x;
    cout << "Digite o numero de v??rtices de '1' a " << this->order << " que ser??o adicionados no subgrafo v??rtice induzido" << endl;
    cin >> tamanho;
    int *listaNos = new int[this->order];
    for (int i = 0; i < this->order; i++)
    {
        listaNos[i] = -1;
    }
    for (int i = 0; i < tamanho; i++)
    {
        cout << "Digite o v??rtice numero " << i + 1 << ": " << endl;
        cin >> x;
        listaNos[i] = x;
    }
    //pre-requisitos pra fazer a ordenacao
    Graph *grafoVI;
    grafoVI = this->getVertexInduced(listaNos, tamanho);

    Graph *grafoAux = new Graph(this->directed, this->weighted_edge, this->weighted_node); //vai vira o grafoVI

    int *nohArestas = new int[3];
    int totalArestas;

    totalArestas = grafoVI->getNumberEdges();

    list<pair<int, int>> lista;

    Node *sup;
    Node *p;
    Edge *aux;

    for (sup = grafoVI->getFirstNode(); sup != NULL; sup = sup->getNextNode())
    {
        grafoAux->insertNode(sup->getId());
    }

    //Criar uma lista L com as arestas ordenadas em
    //ordem crescente de pesos.
    for (int i = 0; i < totalArestas; i++)
    {
        // acha a aresta de menor peso
        grafoVI->getWeithlessEdge(nohArestas);
        //insere a aresta de menor peso
        lista.push_back(make_pair(nohArestas[0], nohArestas[1]));
        //retira a aresta do grafo pra evitar repetir a mesma aresta;
        sup = grafoVI->getNode(nohArestas[0]);
        p = grafoVI->getNode(nohArestas[1]);
        if (!this->directed)
        {
            sup->removeEdge(p->getId(), this->directed, p);
            p->removeEdge(sup->getId(), this->directed, sup);
            sup->removeEdge(p->getId(), this->directed, p);
            p->removeEdge(sup->getId(), this->directed, sup);
            cout << sup->getId() << " -- " << p->getId() << endl;
        }
        else
        {
            sup->removeEdge(p->getId(), this->directed, p);
        }
        //adiciona a a resta num grafo auxiliar.
        grafoAux->insertEdge(nohArestas[0], nohArestas[1], nohArestas[2]);
    }

    //Organizar a lista;

    //Criar |V| sub??rvores contendo cada uma um n??
    //isolado.
    Graph *arvoreGerMin = new Graph(this->directed, this->weighted_edge, this->weighted_node);
    for (sup = grafoAux->getFirstNode(); sup != NULL; sup = sup->getNextNode())
    {
        arvoreGerMin->insertNode(sup->getId());
    }
    
    //F ?? ??
    //Cria lista vazia
    list<pair<int, int>> listaAux;

    //contador ?? 0
    int conta = 0;
    int numMaxAresta = arvoreGerMin->getOrder() - 1;
    bool verify[this->order];

    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
    }

    //Enquanto contador < |V|-1 e L 1 ?? fa??a
    while (conta < numMaxAresta && !lista.empty())
    {
        //Seja (u,v) a pr??xima aresta de L.
        pair<int, int> distancia_no = lista.front(); //copia par (id do vertice e distancia) do topo
        int v1 = distancia_no.first;
        int v2 = distancia_no.second;

        lista.pop_front();
        //Se u e v n??o est??o na mesma sub??rvore ent??o
        if (!verificaSubarvore(v1, v2, arvoreGerMin))
        {
             //F ?? F ?? {(u,v)}
            //preenche a lista;
            listaAux.push_back(make_pair(v1, v2));
            //busca o peso da aresta
            int peso = getWeightFromEdgeNodeCombo(v1, v2, grafoAux);

            //Unir as sub??rvores que cont??m u e v.
            arvoreGerMin->insertEdge(v1, v2, peso);
            //contador ?? contador + 1
            conta++;
            //fim-se
        }
    }

    int pesoTotal = 0;
    while (!listaAux.empty())
    {
        pair<int, int> distancia_no = listaAux.front(); //copia par (id do vertice e distancia) do topo
        int v1 = distancia_no.first;
        int v2 = distancia_no.second;
        pesoTotal = pesoTotal + getWeightFromEdgeNodeCombo(v1, v2, arvoreGerMin);
        listaAux.pop_front();
    }
    output_file << "Peso da Arvore Geradora Minima: " << pesoTotal << endl;
    return arvoreGerMin;
}

// usa os mecanismos da busca em profundidade para indicar a alcansabilidade de um vertice a outro
bool Graph::verificaSubarvore(int v1, int v2, Graph *subGrafo)
{
    //vetor de alcansabilidade -- se tem caminho ou nao
    bool *fti = new bool[this->order];

    for (int i = 0; i < this->order; i++)
    {
        fti[i] = false;
    }
    // verifica para todos os nohs se tem caminho ou nao
    for (Node *p = subGrafo->getFirstNode(); p != NULL; p = p->getNextNode())
    {

        fti[p->getId() - 1] = subGrafo->deepthFirstSearch1(v2, p->getId());
    }

    return fti[v1 - 1];
}

//pega o peso da aresta atravez do int idNoh, int idAresta, Graph *subGrafo
int Graph::getWeightFromEdgeNodeCombo(int idNoh, int idAresta, Graph *subGrafo)
{
    Node *p = subGrafo->getNode(idNoh);
    Edge *aux;
    for (aux = p->getFirstEdge(); aux != NULL; aux = aux->getNextEdge())
    {
        if (aux->getTargetId() == idAresta)
        {
            break;
        }
    }
    return aux->getWeight();
}

//procura a aresta de menor peso e adiciona os dados dos vertices de entrada, saida e o seu proprio peso no vetor
void Graph::getWeithlessEdge(int *nohAresta)
{

    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();
    int menor = 9999999;
    while (p != NULL)
    {

        aux = p->getFirstEdge();
        while (aux != NULL)
        {
            if (aux->getWeight() < menor)
            {
                nohAresta[0] = p->getId();
                nohAresta[1] = aux->getTargetId();
                nohAresta[2] = aux->getWeight();
                menor = aux->getWeight();
            }
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
}

Graph *Graph::agmPrim(ofstream &output_file)
{
    int tamanho, x;
    cout << "Digite o numero de v??rtices de 1 a " << this->order << " que ser??o adicionados no subgrafo v??rtice induzido" << endl;
    cin >> tamanho;
    int *listaNos = new int[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        cout << "Digite o v??rtice numero " << i + 1 << ": " << endl;
        cin >> x;
        listaNos[i] = x;
    }

    Graph *grafoVI;
    grafoVI = this->getVertexInduced(listaNos, tamanho);

    Graph *grafoX = new Graph(this->directed, this->weighted_edge, this->weighted_node);
    Node *p;
    //para todo noh da lista fa??a
    for (p = grafoVI->getFirstNode(); p != NULL; p = p->getNextNode())
    {
        grafoX->insertNode(p->getId());
    }

    bool adicionados[this->order]; //marca quais v??rtices ja possuem um caminho
    for (int i = 0; i < this->order; i++)
    {
        adicionados[i] = false;
    }
    adicionados[x] = true;

    std::list<int> vertices; //marca quais v??rtices ja possuem um caminho
    std::list<int>::iterator k;
    vertices.push_front(x); //adiciona o primeiro v??rtice na lista

    bool todosVerticesAdicionados = false;

    int custoTotal=0;


    while (todosVerticesAdicionados == false) //repetir at?? ter um caminho para todos os v??rtices
    {
        int vertice1; //n?? que vai armazenar o v??rtice de onde vai sair a aresta
        int vertice2; //n?? que vai armazenar o v??rtice que a aresta vai chegar
        int menorCusto = 999999999;
        for (k = vertices.begin(); k != vertices.end(); k++) //percorre todos v??rtices da lista
        {
            Node *verticeAnalisado = grafoVI->getNode(*k);
            for (Edge *it = verticeAnalisado->getFirstEdge(); it != NULL; it = it->getNextEdge()) //percorre todas arestas de grafoVI
            {
                int verticeAdjacente = it->getTargetId(); //pega o v??rtice alvo dessa aresta
                int custo_aresta = it->getWeight();       //pega o custo dessa aresta

                if (adicionados[verticeAdjacente - 1] == false) //se o v??rtice alvo n??o foi adicionado
                {
                    if (menorCusto > custo_aresta) //se o custo dessa aresta for menor de todas que ja forram analisados
                    {
                        vertice1 = verticeAnalisado->getId();                   //lembra do n?? que esta saindo essa aresta
                        vertice2 = verticeAdjacente; //lembra do n?? onde esta chegando essa arresta
                        menorCusto = custo_aresta;                     //lembra do custo dessa aresta
                    }
                }
            }
        }

        //adiciona uma aresta entre o v??rtice 1 e 2 que possui custo = menorCusto
        grafoX->insertEdge(vertice1, vertice2, menorCusto);

        custoTotal=custoTotal+menorCusto;

        vertices.push_front(vertice2);    //adiciona o vertice 2 na lista vertices
        adicionados[vertice2 - 1] = true; //marcar o vertice 2 como adicionado
        int contador = 0;
        for (int i = 0; i < (this->order); i++) //verificar se todos v??rtices ja foram adicionados se sim todosVerticesAdicionados=true
        {
            if (adicionados[i] == true)
            {
                contador++;
            }
        }
        if (contador == (grafoX->order))
        {
            todosVerticesAdicionados = true;
        }
    }
    delete[] listaNos;

    output_file<<"Peso da Arvore Geradora Minima: "<<custoTotal<<endl;

    return grafoX;
}

///// Inicia Arvore Geradora Rota????o Minima

void Graph::geraArvRotMin( int cores, float densidade ){
    this->clearArestas(); //limpa todas as arestas no grafo com cores 
    num_cores= cores;
    densidade = densidade;

    //inicializa as arestas
    for( int i=0 ; i<num_vertices ; i++ ){
        for( int j=0 ; j<num_vertices ; j++ ){
            MatrizAdjacente[i][j].setNumCores(num_cores);
        }
    }
}

//remove as cores associadas a aresta, e as cores que foram pintadas na aresta)
void Graph::clearArestas(){
    for( int i=0 ; i<num_vertices ; i++ ){
        for( int j=0 ; j<num_vertices ; j++ ){
            for( int k=0 ; k<num_cores ; k++ ){
                MatrizAdjacente[i][j].removeCor(k);//
            }
        }
    }
}
