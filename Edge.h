/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int target_id;
        Edge* next_edge;
        float weight;
        bool * cor_possivel;
        bool * cor_ativa;
        bool colorida;
        int cores;

    public:
        // Constructor
        Edge(int target_id);
        Edge();
        // Destructor
        ~Edge();
        // Getters
        int getTargetId();
        Edge* getNextEdge();
        float getWeight();
        // Setters
        void setNextEdge(Edge* edge);
        void setWeight(float weight); 
        void setNumCores(int num);
        void addCor(int cor);
        void colorir(int cor);
        void colorir(int* cor);
        void removeCor(int cor);

        bool colorida;

}; 

#endif // EDGE_H_INCLUDED