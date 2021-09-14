//
// Created by jakub on 13.12.2020.
//

#include "byWeight.h"
#include <iostream>

Product* byWeight::ProductCopy(){
    byWeight* ptr = new byWeight(*this);
    ptr->ProductName=new std::string;
    *ptr->ProductName=*this->ProductName;
    return ptr;
}

void byWeight::print_product() const {
    std::cout << getProductName() << " - " << getAmount() << " " << Unit  << std::endl;
}

void byWeight::setUnit(std::string newUnit){
    if(Unit=="kg"){
        if(newUnit=="g"){
            ProductAmount*=1000;
        }
        else {
            ProductAmount *= 100;
        }
    }

    else if(Unit=="dag"){
        if(newUnit=="kg"){
            if(ProductAmount%100==0)
                ProductAmount/=100;
            else{
                std::cout<<"Zamiana jednostki niemozliwa.";
                return;
            }
        }
        else{
            ProductAmount*=10;
        }
    }

    else if(Unit=="g"){
        if(newUnit=="kg"){
            if(ProductAmount%1000==0)
                ProductAmount/=1000;

            else{
                std::cout<<"Zamiana jednostki niemozliwa.";
                return;
            }
        }
        else{
            if(ProductAmount%10==0){
                ProductAmount/=10;
            }
            else{
                std::cout<<"Zamiana jednostki niemozliwa.";
                return;
            }
        }
    }

    Unit=newUnit;
}