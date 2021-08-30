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
    this->colorida = false;
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
    colorida = false;
}
// relaciona uma cor na aresta
void Edge::addCor(int cor){
    if(cor_possivel!=NULL && cor<cores){
        cor_possivel[cor] = true;
        this->colorida = true;
    }
    else{
        cout << "Nao foi possivel colorir a aresta"<< endl;       
    }
}
//colore uma aresta 
void Edge::colorir(int cor){
    if(cor_ativa!=NULL && cor<cores && colorida && cor_possivel!=NULL && cor_possivel[cor] ){
        cor_ativa[cor] = true;
    }
    else{
        cout << "Nao foi possivel colorir a aresta"<< endl;         
    }
}
void Edge::colorir(int* cor){
    if(cor_ativa!=NULL && colorida && cor_possivel!=NULL ){
        for( int i =0 ; i<cores ; i++){
            if( cor[i]<0 && cor_possivel[i] ){
                cor_ativa[i] = true;
                return;
            }
        }
    }
    else{
        cout << "Nao foi possivel colorir a aresta"<< endl;  
        
    }
}
/**
Limpa todas as cores pintadas e associadas na aresta
**/
void Edge::removeCor(int cor){
    if(cor_ativa!=NULL && cor<cores){
        cor_ativa[cor] = false;
        cor_possivel[cor] = false;
        ativa = false;
        for( int i=0 ; i<cores ; i++ ){
            if( cor_ativa[t] ){
                ativa = true;
                return;
            }
        }
    }
    else{
        cout << "\n"<< cor_ativa << ", " << cor << ", " << cores << endl;
    }
}
