#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
**************************************************************************************************/

// Constructor
Edge::Edge(int target_id){

    this->target_id = target_id;
    this->next_edge = NULL;
    this->weight = 1;
}
Edge::Edge(){
    this->ativa = false;
    this->cor_possivel = NULL;
    this->cor_ativa = NULL;
}
// Destructor
Edge::~Edge(){
    if (this->next_edge != NULL){
        delete this->next_edge;
        this->next_edge = NULL;
    }
    if( cor_possivel!=NULL ){
        delete[] cor_possivel;
    }
    if( cor_ativa!=NULL ){
        delete[] cor_ativa;
    }

}

// Getters
int Edge::getTargetId(){

    return this->target_id;

}

Edge* Edge::getNextEdge(){

    return this->next_edge;

}

float Edge::getWeight(){

    return this->weight;

}

// Setters
void Edge::setNextEdge(Edge* edge){

    this->next_edge = edge;

}

void Edge::setWeight(float weight){

    this->weight = weight;

}

void Edge::setNumCores(int num){
    cores = num;
    if(cor_possivel!=NULL)
    {
        delete  cor_possivel;
    }
    if(cor_ativa!=NULL)
    {
        delete cor_ativa;
    }
    cor_possivel = new bool [num];
    cor_ativa = new bool [num];
    for( int i=0 ; i<num ; i++ )
    {
        cor_possivel[i] = false;
        cor_ativa[i] = false;
    }
    ativa = false;
}
// adiciona uma cor na aresta
void Edge::addCor(int cor){
    if(cor_possivel!=NULL && cor<cores){
        cor_possivel[cor] = true;
        this->ativa = true;
    }
    else{
        cout << "Nao foi possivel colorir a aresta"<< endl;       
    }
}
