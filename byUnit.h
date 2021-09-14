//
// Created by jakub on 13.12.2020.
//

#ifndef SLAZYKJAKUB_ETAP1_BYUNIT_H
#define SLAZYKJAKUB_ETAP1_BYUNIT_H
#include "Product.h"

class byUnit: public Product {
    static std::string Unit;

public:
    byUnit( std::string name, int Amount): Product(name,Amount) {};
    ~byUnit()override= default;

    Product* ProductCopy() override;

    void print_product() const override;
    std::string getUnit() const override {return Unit;};

};


#endif //SLAZYKJAKUB_ETAP1_BYUNIT_H
