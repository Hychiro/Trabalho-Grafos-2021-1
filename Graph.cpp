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
    if (!directed)
    {
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
    else{
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
    return p;
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

    for (int i = 0; i < tamanho; i++)
    {
        aux << "[";
        for (int j = 0; j < tamanho; j++)
        {
            if (distancia[i][j] != INFINITY)
            {
                aux << distancia[i][j] << ".";
            }

            else
            {
                aux << distancia[i][j] << ".";
            }
            if (j == tamanho - 1)
                aux << "]\n";
        }
    }
    return aux.str();
}
int** Graph::constroiFloyd(int tamanho, int** distancia)
 {
    // funcao para utilizar a lista de adjacencia e para usar o algoritmo de Floyd
    //falta lista de adjacencia aqui
    
    distancia = new int* [tamanho];
    for ( int k = 0; k < tamanho; k++ ) {
        distancia[k] = new int [tamanho];
    }
    for ( int c = 0; c < tamanho; c++ ) 
    {
        // Escolhendo todos os vértices como fonte, um por um
        for ( int i = 0; i < tamanho; i++ ) 
        {
            // Escolhendo todos os vértices como destino
            if ( i != c ) 
            {
                for ( int j = 0; j < tamanho; j++ ) 
                {
                    // Se o vértice k estiver no caminho mais curto de i para j, em seguida, atualize o valor de dist [i] [j]
                    if ( distancia[i][c] != INFINITY && distancia[c][j] != INFINITY ) 
                    {
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
    int distancia[this->order];//vetor que faz uma analogia entre id e distancia
    int vertice_predecessor[this->order];//vetor que faz uma analogia entre id e vértice predecessor do caminho minimo
    bool visitados[this->order]; //vetor que verifica se o vértice ja foi visitado

    //Fazer uma fila de prioridade minima.
    //a ideia é fazer uma fila onde o primeiro valor seja a distancia 
    //e o segundo valor seja o id do vértice
    typedef pair<int, int> pi;
    priority_queue<pi, vector<pi>, greater<pi> > fila;

    //Iniciar todas as distancias como inifinito, todos vertices como não visitados e todos predecessores como inexistentes(-1)
    for (int i = 0; i < this->order; i++)
    {

        distancia[i] = 4203209;

        visitados[i] = false;
        vertice_predecessor[i] = -1;
    }

    distancia[idSource - 1] = 0; //Distancia do vertice inicial até ele mesmo é 0
    vertice_predecessor[idSource - 1] = -2;//Predecessor do vertice inicial é tido como -2

    //inserir o vertice inicial na fila
    fila.push(make_pair(distancia[idSource - 1], idSource));
    //iteraçao
    while (!fila.empty())
    {
        pair<int, int> distancia_no = fila.top();//copia par (id do vertice e distancia) do topo
        int idVertice = distancia_no.second;
        Node *verticeAnalisado = this->getNode(idVertice); //obtem o vértice a ser analisado a partir de seu id
        fila.pop();//remove o par da fila

        //verifica se o vértice ja foi visitado
        if (visitados[verticeAnalisado->getId() - 1] == false)
        {
            //marca como visitado
            visitados[verticeAnalisado->getId() - 1] = true;
            for (Edge *it = verticeAnalisado->getFirstEdge(); it != NULL; it=it->getNextEdge())
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
                    fila.push(make_pair(distancia[verticeAdjacente],verticeAdjacente+1));
                }
            }
        }
    }



    if(vertice_predecessor[idTarget-1]!=-1 && vertice_predecessor[idTarget-1]!=-2)
    {
        if (this->directed)
        {
            list<int> caminho;
            int a=vertice_predecessor[idTarget-1];
            while (vertice_predecessor[a-1]!=-2 && vertice_predecessor[a-1]!=-1)
                {
                    caminho.push_front(a);
                    a=vertice_predecessor[a-1];
                }
            output_file << idSource ;
            for(int i=0;!(caminho.empty());i++)
                {
                    output_file << " -> " << caminho.front();
                    caminho.pop_front();
                }
            output_file <<" -> " << idTarget; 
        }

        if(!(this->directed))
        {
            list<int> caminho;
            int a=vertice_predecessor[idTarget-1];
            while (vertice_predecessor[a-1]!=-2 && vertice_predecessor[a-1]!=-1)
                {
                    caminho.push_front(a);
                    a=vertice_predecessor[a-1];
                }
            output_file << idSource ;
                for(int i=0;!(caminho.empty());i++)
                {
                    output_file << " -- " << caminho.front();
                    caminho.pop_front();
                }
                output_file <<" -- " << idTarget;
        }

    }else if (vertice_predecessor[idTarget-1]==-1)
    {
        output_file<<"não existe caminho"<<endl;
    }else if (vertice_predecessor[idTarget-1]==-2)
    {
        output_file<<"Id Sorurce é o mesmo que IdTarget"<<endl;
    }
    
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////FECHO TRANSITIVO E BUSCAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::fechoTransitivoDireto(ofstream &output_file, int id)
{

    //com o id do vértice acha o vertice que deve ser analisado
    int idParametro = id - 1;
    //cria um vetor que marca quais vértices ja foram analisados
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

    //começa iteração (enquanto a fila não estiver vazia repita)
    while (!(fila.empty()))
    {
        //pega um vértice a ser analisado da fila
        int aux = fila.front();
        int IdAnalisado = aux - 1;
        Node *V;
        V = getNode(fila.front());
        //exclui ele da fila
        fila.pop_front();
        //verifica se o vértice a ser analisado ja foi analisado. (se ele ja foi acaba essa iteração)
        if (visitados[IdAnalisado] == false)
        {
            //marca o vértice como visitado;
            visitados[IdAnalisado] = true;
            //adiciona ele no vetor fecho transitivo direto
            FTD[IdAnalisado] = true;
            //adiciona todos os vértices adjacentes a ele na fila
            for (Edge *it = V->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                int verticeAdjacente = it->getTargetId();
                fila.push_front(verticeAdjacente);
            }
        }
    }

    //imprimir o FTD
    output_file << "O conjunto FTD do vértice " << id << " é: {";
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
    Graph *novoGrafo = new Graph(this->directed, this->weighted_edge, this->weighted_node);

    //chama a busca para conseguir o preDeProfund;

    cout << "Como acho que eh possivel do fecho variar de acordo com a direcao de onde se comeca a busca," << endl;
    cout << "ja que ele, o fecho transitivo indireto, representa os antescedente de vertice em um grafo." << endl;
    cout << "se faz necessario um ponto de referencia inicial por onde comecar a busca." << endl;
    cout << "Por isso, escolha um vertice indo de 1 a " << this->order << " e que seja diferente de " << id;
    cout << ", ja que queremos os antecessores desse vertice e nao ele mesmo." << endl;
    cout << "Digite um dos vertices apresentados Acima: ";
    int start;
    cin >> start;
    cout << " O resultado aparecera em um arquivo .txt" << endl;
    deepthFirstSearch(novoGrafo, start, id);
    output_file << endl;
    output_file << "Novamente, Como acho que eh possivel do fecho variar de acordo com a direcao de onde se comeca a busca," << endl;
    output_file << "ja que ele, o fecho transitivo indireto, representa os antescedente de vertice em um grafo." << endl;
    output_file << "se faz necessario um ponto de referencia inicial por onde comecar a busca." << endl;
    //processo de salvar os dados;
    output_file << "Fecho Transitivo indireto em relação ao vertice " << start << " eh:" << endl;
    //parametro para olhar o vetor;*/
    //auxiliares
    int *vetAux = new int[this->order];
    bool *verify = new bool[this->order];
    for (int j = 0; j < this->order; j++)
    {
        vetAux[j] = -1;
        verify[j] = false;
    }

    Node *p = novoGrafo->getFirstNode();
    Edge *aux = p->getFirstEdge();

    while (p != NULL)
    {

        aux = p->getFirstEdge();

        verify[p->getId() - 1] = true;

        while (aux != NULL)
        {
            if (!verify[aux->getTargetId() - 1])
            {
                verify[aux->getTargetId() - 1] = true;
                vetAux[aux->getTargetId() - 1] = p->getId();
            }
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
    for (int i = 0; i < this->order; i++)
    {
        output_file << vetAux[i] << " ";
    }

    int k = vetAux[id - 1];
    output_file << " R-(" << id << ") = {";

    while (k != -1)
    {

        output_file << k;
        k = vetAux[k - 1];
        if (k != -1)
        {
            output_file << " ";
        }
    }

    //processo para uma impressao bonitinha ... soh isso mesmo ...

    output_file << "}" << endl;
}

////deepthFirstSearch 2 realizar a busca por profundidade a partir de um ponto de referencia do grafo.
void Graph::deepthFirstSearch(Graph *novoGrafo, int start, int id)
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
    //verifica o no de entrada para começar a busca
    //Para todo v em G
    for (p = getNode(start); NULL != p; p = p->getNextNode())
    {

        idParametro = p->getId() - 1;
        //Se v não visitado entao
        if (verify[id - 1])
        {
            break;
        }
        if (!verify[idParametro])
        {
            novoGrafo->insertNode(p->getId());
            //AUX-BuscaPorProfundidade (G,v)
            auxDeepthFirstSearch(verify, novoGrafo, p);
        }
    }
}
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
    //verifica o no de entrada para começar a busca

    //Para todo v em G
    for (p = getNode(start); NULL != p; p = p->getNextNode())
    {

        idParametro = p->getId() - 1;
        //Se v não visitado entao
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
        //Se w não visitado então

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

// função que imprime uma classificação topológica
int *Graph::topologicalSorting()
{   
    int *vetor = new int(this->order);//alocando o vetor para ordenaçao topologica
    if (this->graphtemCiclo())
    // verifica se o grafo tem circuito ou nao
    return NULL;
    else{
            int i =0;
            Edge *auxAres;
            Node *auxNo;
            queue<Node *> filaTopologica; //fila auxiliar para os nos de origem
            //procurando nos com enttrada =0
            for (auxNo=this->first_node;auxNo!=NULL;auxNo = auxNo->getNextNode())
            {   if (auxNo->getInDegree()==0)// se entrada  = 0
                {
                    filaTopologica.push(auxNo); //coloca os nos corretos na fila
                }
            }
            while (!filaTopologica.empty())// enquanto fila e vazia
            {
                vetor[i] = filaTopologica.front()->getId(); //coloca o id do no a ser removido da fila
                auxAres = filaTopologica.front()->getFirstEdge(); // obtendo a primeiro no 
                filaTopologica.pop(); //remve da fila
                while (auxAres != NULL){
                    auxNo = this->getNode(auxAres->getTargetId());//pega o no vizinho
                    auxNo->decrementInDegree(); //decrementa a entrada
                    if(auxNo->getInDegree()==0){ //se a entrada = 0
                    filaTopologica.push(auxNo);
                }
            } i++;
        }
        return vetor;  //retorna a classificação topologica em um vetor
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
    }// Então a lista é classificada
    auxC.sort();

    for (list<int>::iterator i = auxC.begin(); i !=  auxC.end();){
     int prev = *i;
        i++;
        // Se houver componentes iguais, o gráfo é cíclico,
         // entao o grafo tem um circuito
        if (prev == *i)
            return true;
    }
        // Se  forem diferentes entre eles, o grafo nao tem circuito
    return false;
}

/*
Graph *getVertexInduced(int *listIdNodes)
{
}

Graph *agmKuskal()
{
}
Graph *agmPrim()
{
}*/
