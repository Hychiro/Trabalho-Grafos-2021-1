/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include<string>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void insertAllNodes();

        void topologicalSorting();
        void deepthFirstSearch(ofstream& output_file, int id);
        int auxDeepthFirstSearch(ofstream &output_file, Node* p, bool verify[], int i, int targetId);
        Graph* getVertexInduced(int* listIdNodes);
        Graph* agmKuskal();
        Graph* agmPrim();
        string floydMarshall(int idSource, int idTarget);
        int ** constroiFloyd ( int tamanho, int ** distancia);
        void dijkstra(ofstream &output_file,int idSource, int idTarget);
        void printGraph(ofstream &output_file);
        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
    private:
        //Auxiliar methods
        stringstream aux;

};

#endif // GRAPH_H_INCLUDED
