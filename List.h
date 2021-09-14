//
// Created by jakub on 21.11.2020.
//
#ifndef NOWY_FOLDER_LIST_H
#define NOWY_FOLDER_LIST_H

#include <string>
//#include <utility>
#include "Product.h"
#include "byLiters.h"
#include "byWeight.h"
#include "byUnit.h"

class List {
    Product* ProductList[10]{};
    int CurrentSizeList=0;
    std::string ListName;


public:
    explicit List(std::string name = "", int size = 0) : ListName{std::move( name )}, CurrentSizeList{ size } { };
    List& operator=(const List& wzor);
    List( List& wzor) { *this = wzor; }
    ~List();

    void put(std::string name, int amount, int jednostka);
    void take(int index);

    void PrintAll() const;

    Product* getProduct(int index) const { return ProductList[index]; };
    int getCurrSize() const { return CurrentSizeList; };
    std::string getName() const { return ListName; };

    void setProduct(Product* product, int index){ ProductList[index]=product; };
    void setCurrentSize(char x);

    void swap(int index1, int index2);
};

#endif //NOWY_FOLDER_LIST_H
