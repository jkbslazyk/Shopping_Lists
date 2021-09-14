//
// Created by jakub on 21.11.2020.
//
#include "Product.h"

#include <iostream>
#include <string>

void Product::print_product() const {
    std::cout << *ProductName << " - " << ProductAmount <</* ' ' << *unit << */std::endl;
}

void Product::edit(std::string Name, int Amount) {
    *ProductName = std::move(Name);
    setAmount(Amount);
}


