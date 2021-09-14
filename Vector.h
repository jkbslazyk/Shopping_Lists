//
// Created by jakub on 08.01.2021.
//

#ifndef SLAZYKJAKUB_ETAP2_VECTOR_H
#define SLAZYKJAKUB_ETAP2_VECTOR_H

template<typename X>
class Vector{
    X* Lista=nullptr;
    int Size=0;
    int Capacity=0;

    void ReAllocation(int newCapacity){
         X* NewVector=new X[newCapacity];

         for(int i=0; i<Size;i++){
             NewVector[i]=std::move(Lista[i]);
         }

         delete []Lista;
         Lista=NewVector;
         Capacity=newCapacity;

    }
public:
    Vector(){
        ReAllocation(2);
    }

    ~Vector(){
        for (int i=0; i<Size; i++)
            delete Lista[i];
        delete[] Lista;
    }

    void push_back(X Value){

        if(Size>=Capacity){
           ReAllocation(2*Size);
        }

        Lista[Size++]=Value;

    }

    X& operator[](int index){
        return Lista[index];
    }

    int size(){ return Size;};

    int empty() {if(Size==0) return 1; return 0;};

    void erase(int index){

        if(Size*2<Capacity){
            ReAllocation(Size);
        }

        for(int i=index;i<Size-1;i++){
            Lista[i]=Lista[i+1];
        }
        Size--;
    }
};

#endif //SLAZYKJAKUB_ETAP2_VECTOR_H