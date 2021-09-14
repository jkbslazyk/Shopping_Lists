//
// Created by jakub on 13.12.2020.
//

#ifndef SLAZYKJAKUB_ETAP1_BYLITERS_H
#define SLAZYKJAKUB_ETAP1_BYLITERS_H
//#include <utility>

#include "Product.h"

class byLiters : public Product {
    std::string Unit;

public:
    byLiters( std::string name, int Amount, std::string Jednostka): Product(std::move(name),Amount), Unit(std::move(Jednostka)) {};
    ~byLiters() override{delete ProductName;};

    Product* ProductCopy() override;

    void print_product() const override;
    std::string getUnit() const override {return Unit;};
    void setUnit(std::string newUnit)override;

};


#endif //SLAZYKJAKUB_ETAP1_BYLITERS_H
