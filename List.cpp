//
// Created by jakub on 21.11.2020.
//
#include <iostream>
#include "List.h"

std::string readString();

List::~List() {

    for (int i = 0; i < CurrentSizeList; i++) { //dealokuje obiekty ze wskazanych indeksow
        delete ProductList[i];
    }
}

List & List::operator=(const List& wzor) {

    if (&wzor != this) {
        for (int i = 0; i < wzor.CurrentSizeList; i++) {
            delete ProductList[i];
        }


        for(int i=0; i<wzor.CurrentSizeList;i++){
            ProductList[i]= wzor.getProduct(i)->ProductCopy();
        }

        CurrentSizeList = wzor.CurrentSizeList;

        std::cout << "Podaj nazwe nowej(skopiowanej) listy: "; //umozliwia uzytkownikowi zmiane nazwy skopiowanej listy(dla rozroznienia)
        ListName = readString();

    }

    return *this;
}

void List::put(std::string name, int amount, int jednostka) {

    if (CurrentSizeList >= 10) {
        std::cerr << "Lista jest pelna - nie moge dodac elementu" << std::endl;
        return;
    }

    switch(jednostka){
        case 1:
            ProductList[CurrentSizeList] = new byWeight( name, amount, "kg" );
            break;
        case 2:
            ProductList[CurrentSizeList] = new byWeight( name, amount, "dag" );
            break;
        case 3:
            ProductList[CurrentSizeList] = new byWeight( name, amount, "g" );
            break;
        case 4:
            ProductList[CurrentSizeList] = new byLiters( name, amount, "l" );
            break;
        case 5:
            ProductList[CurrentSizeList] = new byLiters( name, amount, "ml" );
            break;
        case 6:
            ProductList[CurrentSizeList] = new byUnit( name, amount );
            break;
        default: break;
    }


    std::cout << "Do listy dodano produkt ktorego nazwa to: " << ProductList[CurrentSizeList++]->getProductName() << std::endl;
    if (CurrentSizeList == 10)//ostrzezenie dla uzytkownika, ze dodal ostatni mozliwy element do listy
        std::cout << "Dodano dziesiaty element. Lista jest pelna.\n";
}

void List::take(int index) {

    if(CurrentSizeList>1)
        swap(index,CurrentSizeList-1);

    delete ProductList[--CurrentSizeList];//i usuwam ostatni element
    ProductList[CurrentSizeList] = nullptr;

}

void List::PrintAll() const {

    std::cout<<"\n<><><><><><><><><><>\n";

    std::cout << "Lista o nazwie: " << ListName << std::endl<<std::endl;

    if(CurrentSizeList==0)
        std::cout<<"Lista jest pusta\n";

    for (int i = 0; i < CurrentSizeList; i++) {
        std::cout << i  << ". ";
        ProductList[i]->print_product();
    }

    std::cout<<"<><><><><><><><><><>\n";

    /*for (int i = CurrentSizeList; i < 10; i++) {
        std::cout << i << ". ..." << std::endl;
    }*/

}

void List::setCurrentSize(char x){
    if( x=='+' )
        CurrentSizeList++;
    else
        CurrentSizeList--;
}

void List::swap(int index1, int index2){
    Product* temp=ProductList[index1];
    ProductList[index1]=ProductList[index2];
    ProductList[index2]=temp;
}
