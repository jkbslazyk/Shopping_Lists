//
// Created by jakub on 13.12.2020.
//

#ifndef SLAZYKJAKUB_ETAP1_BYWEIGHT_H
#define SLAZYKJAKUB_ETAP1_BYWEIGHT_H
//#include <utility>

#include "Product.h"

class byWeight : public Product {
     std::string Unit;

public:
    byWeight( std::string name, int Amount, std::string jednostka): Product(std::move(name),Amount),Unit(std::move(jednostka)) {};
    ~byWeight()override { delete ProductName; };

    Product* ProductCopy() override;

    void print_product() const override;
    std::string getUnit() const override { return Unit; };
    void setUnit(std::string newUnit) override;
};


#endif //SLAZYKJAKUB_ETAP1_BYWEIGHT_H
