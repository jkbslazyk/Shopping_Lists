//
// Created by jakub on 21.11.2020.
//
#ifndef NOWY_FOLDER_PRODUCT_H
#define NOWY_FOLDER_PRODUCT_H

#include <string>
#include <utility>
#include <vector>

class Product {
protected:
    std::string* ProductName;
    int ProductAmount;

public:
    Product(std::string name, int Amount ) : ProductName{new std::string( name )}, ProductAmount{ Amount } {};
    virtual ~Product()=default;

    virtual Product* ProductCopy()=0;

    virtual void print_product() const=0;
    virtual void edit(std::string Name, int Amount/*, std::string jednostka*/);

    std::string getProductName() const  { return *ProductName; };
    int getAmount() const { return ProductAmount; };

    void setAmount(int newAmount) { ProductAmount = newAmount; };
    void increaseAmount(int newAmount){ProductAmount+=newAmount;};


    virtual std::string getUnit() const=0;
    virtual void setUnit(std::string newUnit){};

};
#endif //NOWY_FOLDER_PRODUCT_H

