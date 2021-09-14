//
// Created by jakub on 13.12.2020.
//
#include "byLiters.h"
#include <iostream>

void byLiters::print_product() const {
    std::cout << getProductName() << " - " << ProductAmount << " " << Unit  << std::endl;
}

Product* byLiters::ProductCopy(){
    byLiters* ptr = new byLiters(*this);
    ptr->ProductName=new std::string;
    *ptr->ProductName=*this->ProductName;
    return ptr;
}

void byLiters::setUnit(std::string newUnit){
    if(Unit=="l"){
        ProductAmount*=1000;
    }

    else{
        if(ProductAmount%1000==0)
            ProductAmount/=1000;
        else {
            std::cout << "Zamiana jednostki niemozliwa.";
            return;
        }
    }

    Unit=newUnit;
}