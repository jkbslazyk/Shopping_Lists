//
// Created by jakub on 13.12.2020.
//

#include "byUnit.h"
#include <iostream>

std::string byUnit::Unit="szt";

Product* byUnit::ProductCopy(){
    byUnit* ptr = new byUnit(*this);
    //delete Product_Name;
    ptr->ProductName=new std::string;
    *ptr->ProductName=*this->ProductName;
    return ptr;
}

void byUnit::print_product() const {
    std::cout << getProductName() << " - " << getAmount() << " " << Unit  << std::endl;
}