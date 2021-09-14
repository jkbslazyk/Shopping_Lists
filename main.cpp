#include <iostream>
#include <fstream>
//#include <vector>
#include "Vector.h"
#include "List.h"


//operacje na listach
int ChooseList(Vector<List *> &Listy);

void RemoveList(Vector<List *> &Listy);

void ClearList(Vector<List *> &Listy);

void AddList(Vector<List *> &Listy);

void PrintVector(Vector<List *> &Listy);

void CopyList(Vector<List *> &Listy);

void MergeList(Vector<List *> &Listy);

//edycja produktow listy
void EditList(Vector<List *> &Listy);

void ChangeUnit(Vector<List *> &Listy);// pozwala na zmiane wartosci

//operacje na produktach listy
void RemoveProduct(Vector<List *> &Listy);

void AddProduct(Vector<List *> &Listy);

void PrintList(Vector<List *> &Listy);

void MoveProduct(Vector<List *> &Listy);

//wczytywanie
int readInt();

std::string readString();

struct Error{
    std::string message;

    explicit Error(std::string msg) : message(std::move(msg)) {}

    friend std::ostream& operator<<(std::ostream & x, const Error & y) {
        x << y.message;
        return x;
    }
};
struct WrongBegin : public Error {

    explicit WrongBegin() : Error("Nazwa musi zaczynac sie od litery. Sprobuj jeszcze raz.") {};
};

struct NoList : public Error {
    explicit NoList() : Error("Nie mozesz wykonac wybranej akcji.") {} ;
};

struct OutOfRange : public Error {
    explicit OutOfRange() : Error(" Wybrano nieistniejacy indeks.") {};
};

struct TooBig : public Error{
    explicit TooBig() : Error("Powstala lista jest zbyt duza, aby ja stworzyc.") {};
};



int main(int argc, char *argv[]) {

    //std::vector<List *> Wektor_list;//tworze wektor obiektow
    Vector<List*> Wektor_list;


    std::ifstream in;
    std::streambuf *defaultCin = std::cin.rdbuf();

    if(argc > 1) {
        in.open(argv[1]);
        std::cin.rdbuf(in.rdbuf());
    }


    int choice = 0;
    do {

        if(choice != 997)
        std::cout << "\n**********Menu list**********\n\n"
                     "0: Zakoncz dzialanie programu\n"
                     "1: Dodaj liste\n" // dodaje liste do wektora
                     "2: Pokaz posiadane listy\n" //pokazuje nazwy list w wektorze
                     "3: Dodaj element do wybranej listy\n" //dodaje element do konkretnej listy
                     "4: Pokaz zawartosc wybranej listy\n" // wypisuje nazwy produktow z danej listy
                     "5: Edytuj zawartosc wybranej listy\n" // pozwala na edytowanie produktu z listy
                     "6: Zmien jednostke wybranego produktu\n" //pozwala na zmiane jednostek dla wybranych produktow
                     "7: Przenies element z listy na inna liste\n" //przenosi elementy miedzy listami
                     "8: Usun dany element z wybranej listy\n" //usuwa dany element z danej listy
                     "9: Wyczysc liste\n"// usuwa z wybranej listy wszystkie produkty
                     "10: Usun liste\n" // usuwa cala liste z wektora
                     "11: Kopiuj liste\n" //kopiuje liste
                     "12: Scal listy\n"   //umozliwia stworzenie listy wynikowej z dwoch innych list

                     "\nWybierz akcje:";

        choice = readInt();

        try{
            switch (choice) {
                case 0:
                    break;
                case 1:
                    AddList(Wektor_list);
                    break;
                case 2:
                    PrintVector(Wektor_list);
                    break;
                case 3:
                    AddProduct(Wektor_list);
                    break;
                case 4:
                    PrintList(Wektor_list);
                    break;
                case 5:
                    EditList(Wektor_list);
                    break;
                case 6:
                    ChangeUnit(Wektor_list);
                    break;
                case 7:
                    MoveProduct(Wektor_list);
                    break;
                case 8:
                    RemoveProduct(Wektor_list);
                    break;
                case 9:
                    ClearList(Wektor_list);
                    break;
                case 10:
                    RemoveList(Wektor_list);
                    break;
                case 11:
                    CopyList(Wektor_list);
                    break;
                case 12:
                    MergeList(Wektor_list);
                    break;
                case 997:
                    std::cin.rdbuf(defaultCin);
                    break;
                default:
                    std::cout << "Niepoprawny wybór(nalezy wybrac komende z przedzialu 0-12)." << std::endl;

            }
        }
        catch(TooBig & W){
            std::cout<<W;
        }
        catch(NoList & X){
            std::cout << X<<" Rozpoczeto procedure dodawania nowej listy.\n...\n";
            try {
                AddList(Wektor_list);
                std::cout<< "Lista zostala stworzona. Dodaj do niej produkty, aby stala sie uzyteczna.";
            }
            catch(WrongBegin & Y){
                std::cout<<Y;
            }

        }
        catch(WrongBegin & Y){
            std::cout<<Y;
        }
        catch(OutOfRange & Z){
            std::cout<<Z;
        }
    } while (choice != 0);

    return 0;
}

//korzystam z funkcji wczytujacych, wykorzystanych w projekcie dotyczacym ksiazek

int readInt() {
    std::string line;
    std::getline(std::cin, line);

    while(line.empty()){
        std::cout<<"Nie podano zadnej wartosci. Sprobuj ponownie:";
        std::getline(std::cin, line);
    }

    bool checked=false;

    while(!checked) {
        for (char i : line) {
            if(isdigit(i) && i==*(line.end()-1))
                checked=true;
            else if (isdigit(i))
                    continue;
            else {
                std::cout << "Podane wyrazenie nie jest liczba. Sprobuj ponowanie.\n";
                std::getline(std::cin, line);
                break;
            }
        }
    }
    return atoi(line.c_str());
}

std::string readString() {
    std::string line;
    std::getline(std::cin, line);

    while(line.empty()){
        std::cout<<"Nie podano zadnej wartosci. Sprobuj jeszcze raz:";
        std::getline(std::cin, line);
    }
    return line;
}


int ChooseList(Vector<List *> &Listy) {

    PrintVector(Listy);
    if (Listy.empty()) {
        NoList Zero;
        throw Zero;
    }

    else if (Listy.size() == 1)
        std::cout << "\nAby ja wybrac wpisz 0.\n";
    else
        std::cout << "\nWybierz liste 0-" << Listy.size() - 1 << ": " << std::endl;

    int choice;

    std::cout << "Podaj indeks istniejacej listy:";
    choice = readInt();

    if (choice > Listy.size() - 1 || choice < 0) {
        std::cout<<"Zly wybor listy.";
        OutOfRange Out;
        throw Out;
    }

    return choice;

}

void AddList(Vector<List *> &Listy) {

    std::cout << "Podaj nazwe listy:";
    std::string listName = readString();

    if(!isalpha(listName.at(0))){
        WrongBegin Wrong;
        throw Wrong;
    }


    Listy.push_back(new List(listName));
}

void AddProduct(Vector<List *> &Listy) {

    int listChoice = ChooseList(Listy);

    std::cout << "Podaj nazwe produktu:";
    std::string productName = readString();

    if(!isalpha(productName.at(0))){
        WrongBegin Wrong;
        throw Wrong;
    }

    for(int i=0;i<Listy[listChoice]->getCurrSize();i++){
        if(productName==Listy[listChoice]->getProduct(i)->getProductName()){
            std::cout<<"Produkt o tej nazwie juz istnieje. Lepszym rozwiazaniem bedzie edycja ilosci produktu.\n";
            return;
        }
    }

    std::cout << "Podaj ilosc produktu:";
    int productAmount = readInt();
    while(productAmount<=0){
        std::cout<<"Bledna ilosc produktu. Podaj wartosc dodatnia.";
        productAmount = readInt();
    }

    std::cout <<"Wybierz typ jednostki: 1-na wage(kg/dag/g), 2-objetosciowo(l/ml), 3-ilosciowo(szt):";
    int productUnit=readInt();
    while (productUnit< 1 || productUnit > 3) {
        std::cout << "Bledny typ jednostki - wpisz jeszcze raz(1, 2 lub 3):";
        productUnit = readInt();
    }

    int unitType=0;

    if(productUnit==1){
        std::cout<<"Wybierz jednostke: 1-kg, 2-dag, 3-g:";
        unitType=readInt();
        while(unitType<1 || unitType>3){
            std::cout<<"Bledna jednostka - wpisz jeszcze raz(1, 2 lub 3):";
            unitType=readInt();
        }
    }

    else if(productUnit==2){
        std::cout<<"Wybierz jednostke: 4-l, 5-ml:";
        unitType=readInt();
        while(unitType<4 || unitType>5){
            std::cout<<"Bledna jednostka - wpisz jeszcze raz(4 lub 5):";
            unitType=readInt();
        }
    }

    else
        unitType=6;

    Listy[listChoice]->put(productName, productAmount, unitType);
}

void EditList(Vector<List *> &Listy) {
    int listChoice = ChooseList(Listy);

    if (Listy[listChoice]->getCurrSize() == 0) {
        std::cout << "Wybrana lista jest pusta - nie ma mozliwosci edycji.";
        return;
    }

    std::cout
            << "Chcesz zamienic caly produkt czy tylko jego ilosc?\n"
               "Jesli zalezy Ci na edytowaniu calego produktu wcisnij 0, w przeciwnym wypadku dowolna cyfre.\n";
    int chose = readInt();

    Listy[listChoice]->PrintAll();

    std::cout << "Podaj istniejacy indeks elemntu listy:";
    int index = readInt();

    if (index < 0 || index > Listy[listChoice]->getCurrSize() - 1) {
        std::cout<<"Nie znaleziono produktu.";
        OutOfRange Out;
        throw Out;
    }

    if (chose == 0) {
        std::cout << "Podaj nowa nazwe:";
        std::string productName = readString();
        if(!isalpha(productName.at(0))){
            WrongBegin Wrong;
            throw Wrong;
        }
        std::cout << "Podaj nowa ilosc:";
        int productAmount = readInt();
        std::cout << "(Jednostka edytowanego produktu to: " << Listy[listChoice]->getProduct(index)->getUnit()<<")\n";
        Listy[listChoice]->getProduct(index)->edit(productName, productAmount);
    } else {
        std::cout << "\nPodaj nowa ilosc:";
        int productAmount = readInt();
        std::cout << "Jednostka edytowanego produktu to: " << Listy[listChoice]->getProduct(index)->getUnit();
        Listy[listChoice]->getProduct(index)->setAmount(productAmount);
    }

    std::cout << "Produkt: " << Listy[listChoice]->getProduct(index)->getProductName() << " zedytowano pomyslnie.";

}

void ChangeUnit(Vector<List *> &Listy){

    static int info=0;
    if((info++)==0){
        std::cout<<"Podpowiedz: Funkcja sluzy do zmiany jednostki, nie typu jednostki.\nJesli chcesz zmienic typ jednostki po prostu usun i produkt i dodaj ponownie z wlasciwa jednostka ;)"
                   "Funkcja ta powstala w razie sytuacji, gdy potrzebujesz czegos w bardzo duzych lub malych ilosciach w celu redukcji liczby zer na koncu-program nie obsluguje czesci dziesietnych, wiec zamiana jednostki nie zawsze jest mozliwa.\n";
    }


    int listChoice = ChooseList(Listy);

    if (Listy[listChoice]->getCurrSize() == 0) {
        std::cout << "Wybrana lista jest pusta - nie ma mozliwosci zmiany jednostki.";
        return;
    }

    Listy[listChoice]->PrintAll();

    std::cout << "Podaj istniejacy indeks elemntu listy:";
    int index = readInt();

    if (index < 0 || index > Listy[listChoice]->getCurrSize() - 1) {
        std::cout<<"Nie znaleziono produktu.";
        OutOfRange Out;
        throw Out;
    }

    std::string productUnit;

    if(typeid(*Listy[listChoice]->getProduct(Listy[listChoice]->getCurrSize()-1))==typeid(byUnit)){
        std::cout<<"Wybrany produkt jest na sztuki, w tym wypadku nie mozesz zmienic jednostki";
        return;
    }

    else if(typeid(*Listy[listChoice]->getProduct(Listy[listChoice]->getCurrSize()-1))==typeid(byWeight)){
        std::cout<<"Do wyboru 'kg', 'dag' oraz 'g', natomiast aktualna jednostka to: "<< Listy[listChoice]->getProduct(index)->getUnit()<<" (zamieniac mozesz tylko na inna jedsnotke):";
        productUnit=readString();
        if(productUnit!="kg" && productUnit!="dag" && productUnit!="g"){
            std::cout<<"Podales bledna jednostke. Sprobuj jeszcze raz.";
            productUnit=readString();
        }
        if(Listy[listChoice]->getProduct(index)->getUnit()==productUnit){
            std::cout<<"Wybrales jednostke, ktora juz jest przypisana twojemu produktowi.";
        }

        Listy[listChoice]->getProduct(index)->setUnit(productUnit);
    }

    else if(typeid(*Listy[listChoice]->getProduct(index))==typeid(byLiters)){
        if(Listy[listChoice]->getProduct(index)->getUnit()=="l"){
            std::cout<<"Aktualna jednostka to 'l', a wiec program moze zamienic jednostke na 'ml'.";
            productUnit="ml";
        }
        else{
            std::cout<<"Aktualna jednostka to 'ml', jesli ilosc produktu jest wlasciwa dokonam zamiany na 'l'";
            productUnit="l";
        }
        std::cout<<"Jesli o to chodzilo wprowadz dowolna wartosc rozna od 0, jesli nie nacisnij 0.";
        int temp=readInt();

        if(temp)
            Listy[listChoice]->getProduct(index)->setUnit(productUnit);
    }

}

void PrintVector(Vector<List *> &Listy) {

    if (Listy.empty()) {
        std::cout<<"Brak posiadanych list. ";
        NoList Zero;
        throw Zero;
    }

    else if(Listy.size()==1){
        std::cout<<"Posiadasz jedna liste:";
    }

    else
        std::cout << "\nObecnie posiadasz nastepujace listy:";

    std::cout<<"\n\n##########"<<std::endl;

    for (int i = 0; i < (int) Listy.size(); i++)
        std::cout << i << ". " << Listy[i]->getName() << std::endl;

    std::cout<<"##########"<<std::endl;

}

void PrintList(Vector<List *> &Listy) {
    int listChoice = ChooseList(Listy);

    Listy[listChoice]->PrintAll();

}

void RemoveProduct(Vector<List *> &Listy) {
    int listChoice = ChooseList(Listy);

    std::cout << "Ktory element usunac?";
    int index=readInt();

    if(index<0 ||index>=Listy[listChoice]->getCurrSize()){
        std::cout<<"Nie znaleziono produktu.";
        OutOfRange Out;
        throw Out;
    }

    Listy[listChoice]->take(index);

}

void ClearList(Vector<List *> &Listy) {
    int listChoice = ChooseList(Listy);

    int listSize = Listy[listChoice]->getCurrSize();

    for (int i = listSize - 1; i >= 0; i--)
        Listy[listChoice]->take(i);

    std::cout << "Lista " << Listy[listChoice]->getName()
              << " zostala wyczyszczona i jest gotowa do ponownego wykorzystania.\n";

}

void RemoveList(Vector<List *> &Listy) {
    int listChoice = ChooseList(Listy);

    delete Listy[listChoice];
     Listy.erase(listChoice);

}

void CopyList(Vector<List *> &Listy) {

    int listChoice = ChooseList(Listy);

    List *listCopy = new List(
            *Listy[listChoice]); //moznaby zrobic to w jednej linijce, ale wydaje mi sie ze nadmierna komplikacja kodu w takich sytuacjach jest niewskazana
    Listy.push_back(listCopy);

}

void MoveProduct(Vector<List *> &Listy) {
    if (Listy.size() < 2) {
        std::cout << "Aby przenosic produkty miedzy listami, musisz posiadac chcoiaz 2 listy ;)";
        return;
    }

    std::cout << "Wybierz numer list z ktorej przenosimy produkt. ";
    int from = ChooseList(Listy);

    std::cout << "Podaj istniejacy indeks elemntu listy:";
    int indexFrom = readInt();

    if(indexFrom < 0 || indexFrom > Listy[from]->getCurrSize() - 1) {
        std::cout<<"Nie znaleziono produktu.";
        OutOfRange Out;
        throw Out;
    }

    std::cout << "Wybierz numer listy do ktorej przenosimy produkt. ";
    int to = ChooseList(Listy);

    if (to == from) {
        std::cout
                << "Nie rob sobie ze mnie zartow, nie ma sensu przenoszenia produktu na siebie sama. Wroc kiedy naprawde bedziesz potrzebowal tej funkcji :)";
        return;
    }
    for(int i=0; i<Listy[to]->getCurrSize();i++) {
        if (Listy[to]->getProduct(i)->getProductName()==Listy[from]->getProduct(indexFrom)->getProductName()){
            std::cout<<"Produkt o tej nazwie juz istnieje na tej liscie.";
            return;
        }
    }

    Listy[to]->setProduct(Listy[from]->getProduct(indexFrom),
                          Listy[to]->getCurrSize());//przenosze produkt na druga liste
    Listy[from]->swap(indexFrom, Listy[from]->getCurrSize() - 1);//
    Listy[from]->setProduct(nullptr, Listy[from]->getCurrSize() - 1);

    Listy[to]->setCurrentSize('+');
    Listy[from]->setCurrentSize('-');

}

void MergeList(Vector<List *> &Listy) {

    if (Listy.size() < 2) {
        std::cout << "Aby scalac listy, musisz posiadac chcoiaz 2 listy ;)";
        return;
    }

    std::cout << "Wybierz numer listy 1: ";
    int from = ChooseList(Listy);

    std::cout << "Wybierz numer listy 2: ";
    int from2 = ChooseList(Listy);

    if(from==from2){
        std::cout<<"Musisz wybrac 2 rozne listy.";
        return;
    }

    AddList(Listy);

    int counter = 0;

    for (int i = 0; i < Listy[from]->getCurrSize(); i++) {
        for (int j = 0; j < Listy[from2]->getCurrSize(); j++) {
            if (Listy[from]->getProduct(i)->getProductName() == Listy[from2]->getProduct(j)->getProductName() &&
                typeid(*Listy[from]->getProduct(i)) == typeid(*Listy[from2]->getProduct(j))) {
                counter++;
                break;
            }
        }
    }

    if (Listy[from]->getCurrSize() + Listy[from2]->getCurrSize() - counter > 10) {
        TooBig Size;
        throw Size;
    }

    std::vector<int> counter2;

    if(counter<1)
        counter2.push_back(-1);


    for (int i = 0; i < Listy[from]->getCurrSize(); i++) {
        bool temp=false;
        for (int j = 0; j < Listy[from2]->getCurrSize(); j++) {
            if (Listy[from]->getProduct(i)->getProductName() == Listy[from2]->getProduct(j)->getProductName() &&
                typeid(*Listy[from]->getProduct(i)) == typeid(*Listy[from2]->getProduct(j))) {
                if(Listy[from]->getProduct(i)->getUnit()!=Listy[from2]->getProduct(j)->getUnit()){
                    if(typeid(*Listy[from]->getProduct(i))==typeid(byWeight)){
                        if(Listy[from]->getProduct(i)->getUnit()!="g")
                            Listy[from]->getProduct(i)->setUnit("g");
                        if(Listy[from2]->getProduct(j)->getUnit()!="g")
                            Listy[from2]->getProduct(j)->setUnit("g");
                    }
                    else if(typeid(*Listy[from]->getProduct(i))==typeid(byLiters)){
                        if(Listy[from]->getProduct(i)->getUnit()!="ml")
                            Listy[from]->getProduct(i)->setUnit("ml");
                        if(Listy[from2]->getProduct(j)->getUnit()!="ml")
                            Listy[from2]->getProduct(j)->setUnit("ml");
                    }
                }
                temp = true;

                Listy[Listy.size()-1]->setProduct(Listy[from]->getProduct(i)->ProductCopy (), Listy[Listy.size() - 1]->getCurrSize());
                Listy[Listy.size()-1]->getProduct(Listy[Listy.size()-1]->getCurrSize())->increaseAmount(Listy[from2]->getProduct(j)->getAmount());
                Listy[Listy.size()-1]->setCurrentSize('+');

                counter2.push_back(j);

                break;
            }
            }


        if (!temp) {

            Listy[Listy.size()-1]->setProduct(Listy[from]->getProduct(i)->ProductCopy(), Listy[Listy.size() - 1]->getCurrSize());
            Listy[Listy.size()-1]->setCurrentSize('+');

        }
    }

    int counter3=0;

    for (int i = 0; i < Listy[from2]->getCurrSize(); i++) {

        if(counter3<counter2.size())
            if(i==counter2[counter3]) {
            counter3++;
            continue;
        }

        Listy[Listy.size()-1]->setProduct(Listy[from2]->getProduct(i)->ProductCopy(), Listy[Listy.size() - 1]->getCurrSize());
        Listy[Listy.size()-1]->setCurrentSize('+');

    }

    std::cout<<"Scalona lista zostala utworzona. Jesli listy, z ktorych zostala scalona wynikowa lista sa Ci juz niepotrzebne, po prostu je usun - to w sumie tylko 4 interakcje z programem.";
}
