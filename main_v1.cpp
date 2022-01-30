/***********************************************************************
przedmiot: podstawy programowania obiektowego
zadanie: tresc jak ponizej, obiektowo
wersja: 2022-01-30
środowisko: #CL-213.6461.75

Tresc zadania:
Napisz program w C++ który  (działając na typie strukturalnym,
 poleceniu switch.. case, tablicach dynamicznych)  będzie
 umożliwiał wprowadzanie i wyświetlanie informacji o zadaniach
 do wykonania na dany dzień

Menu programu
1) Dodaj zadanie na dany dzień
  1.1 Wybierz dzień
  1.2 Opisz zadanie
2) Pokaz zadania zdefiniowane na dany dzień
  2.1 Wybierz dzień -> Wyświetl wszystkie zadania zdefiniowane na ten dzień
3) Usuń zadanie
  2.1 Wybierz dzień -> Wybierz zadanie - > usuń
4) Usuń zadania
  2.1 Wybierz dzień -> usuń wszystkie zadania z danego dnia
5) wyjście z programu

Program zmodyfikowalem o dodatkowe funkcje:
 - zapis i odczyt danych do/z pliku;
 - wyswietl wszystkie zadania;
 - wyswietlanie zadana w sposob posortowany;
 + obiektowość.
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Zadanie{
public:
    int dzien;
    int nr_zadania;
    string notatka;
    Zadanie *nastepny;
};

class Lista_zadan {
    Zadanie *glowa;
    int liczba_zadan = 0;

public:
    Lista_zadan() {
        glowa = NULL;
        liczba_zadan = 0;
    }
    ~Lista_zadan() {
        Zadanie *zadanie_tmp;
        while (glowa) {
            zadanie_tmp = glowa;
            glowa = glowa->nastepny;
            delete zadanie_tmp;
        }
    }

    void dodaj_zadanie(){
        cout<<"#=============================================================================#"<<endl;
        cout<<"#   Dodawanie notatki na wybrany dzien:"<<endl;
        Zadanie * nowe_zadanie = new Zadanie;
        liczba_zadan++;
        nowe_zadanie->nr_zadania=liczba_zadan;
        cout<<"Wprowadz numer dnia: ";
        cin>>nowe_zadanie->dzien;
        cout<<"Podaj tresc notatki: ";
        cin>>nowe_zadanie->notatka;
        cout<<endl;
        nowe_zadanie->nastepny=NULL;

        if(glowa){
            Zadanie *zadanie_tmp=glowa;
            while (zadanie_tmp->nastepny) zadanie_tmp=zadanie_tmp->nastepny;
            zadanie_tmp->nastepny=nowe_zadanie;
        }
        else glowa=nowe_zadanie;
    }

    void usun_zadanie_o_numerze(int numer_zadania){
        if(czy_zadanie_istnieje(numer_zadania)){
            Zadanie *tmp=glowa;
            Zadanie *tmp_do_skasowania=glowa;
            while(tmp){
                if(tmp->nr_zadania==numer_zadania) tmp_do_skasowania=tmp;
                tmp=tmp->nastepny;
            }//tmp_do_skas wskazuje ten, ktory chce usunac

            if(tmp_do_skasowania->nastepny == NULL){//ostatni element
                if(tmp_do_skasowania==glowa){//przypadek kiedy usuwamy pierwszy i zarazem ostatni
                    cout<<"debug: (1) przypadek kiedy usuwamy pierwszy i zarazem ostatni"<<endl;
                    glowa=NULL;
                    delete tmp_do_skasowania;
                } else {//przypadek kiedy usuwany ostatni ale jest cos wczesniej
                    cout<<"debug: (2) przypadek kiedy usuwany ostatni ale jest cos wczesniej"<<endl;
                    tmp=glowa;
                    //Zadanie * tmp3=glowa;
                    while(tmp->nastepny != tmp_do_skasowania){ //dociagnij do jednego wczesniej
                        tmp=tmp->nastepny;
                    }//w tmp jest adres jednego wczesniej
                    //tmp3=tmp->nastepny;//w tmp3 zostal zapamietany adres tego do usuniecia
                    tmp->nastepny=NULL;//wskaznik na nastepny w przedostatnim null
                    delete tmp_do_skasowania;//kasowanie ostatniego
                }
            } else {//nie ostatni element
                if(tmp_do_skasowania==glowa){//przypadek kiedy usuwa sie pierwszy ale cos jest dalej
                    cout<<"debug: (3) przypadek kiedy usuwa sie pierwszy ale cos jest dalej"<<endl;
                    Zadanie *tmp2=glowa;
                    glowa=glowa->nastepny;
                    delete tmp2;
                } else{ //przypadek kiedy jest cos wczesniej i cos dalej
                    cout<<"debug: (4) przypadek kiedy jest cos wczesniej i cos dalej"<<endl;
                    Zadanie * tmp2=glowa;
                    while(tmp2->nastepny != tmp_do_skasowania){ //dociagnij do jednego wczesniej
                        tmp2=tmp2->nastepny;
                    }//w tmp2 jest adres jednego wczesniej
                    //tmp3=tmp2->nastepny;//w tmp3 zostal zapamietany adres tego do usuniecia
                    tmp2->nastepny=tmp_do_skasowania->nastepny;//wskaznik na nastepny w przedostatnim null
                    delete tmp_do_skasowania;//kasowanie ostatniego
                }
            }
        }
    }

    void usun_zadania_z_dnia(int numer_dnia){
        if(czy_dzien_istnieje(numer_dnia)){
            Zadanie *tmp=glowa;
            while(tmp){
                if(tmp->dzien == numer_dnia){
                    usun_zadanie_o_numerze(tmp->nr_zadania);
                }
                tmp = tmp->nastepny;
            }
        }
    }
    void wyswietl_zadania_dnia(int numer_dnia){
        Zadanie *tmp=glowa;
        while (tmp) {
            if (tmp->dzien == numer_dnia) {
                cout << "# Nr dnia: " << tmp->dzien << " Zadanie nr: " << tmp->nr_zadania << " Zadanie: "
                     << tmp->notatka << endl;
            }
            tmp = tmp->nastepny;
        }
    }
    bool czy_zadanie_istnieje(int numer_zadania){
        Zadanie *tmp=glowa;
        bool zadanie_istnieje=false;
        while(tmp){
            if(tmp->nr_zadania==numer_zadania) zadanie_istnieje=true;
            tmp=tmp->nastepny;
        }
        return zadanie_istnieje;
    }
    bool czy_dzien_istnieje(int numer_dnia){
        Zadanie *tmp=glowa;
        bool dzien_istnieje=false;
        while(tmp){
            if(tmp->dzien==numer_dnia) dzien_istnieje=true;
            tmp=tmp->nastepny;
        }
        return dzien_istnieje;
    }
    void wyswietl_naglowek(){
        cout<<"#=============================================================================#"<<endl;
        cout<<"#               Kalendarz zadan"<<endl<<"#"<<endl;
    }
    void wyswietl_zadania(){
        Zadanie *tmp=glowa;
        if(tmp){
            cout<<"#=============================================================================#"<<endl;
            cout<<"#   Wyswietlanie wszystkich zadzan:"<<endl;
            while (tmp){
                cout<<"# Nr dnia: "<<tmp->dzien<<" Zadanie nr: "<<tmp->nr_zadania<<" Zadanie: "<<tmp->notatka<<endl;
                tmp=tmp->nastepny;
            }
        }
    }
    void wyswietl_zadania_sort(){
        Zadanie *tmp=glowa;
        Zadanie *tmp2=glowa;
        if(tmp){
            int maks_numer_dnia=0;
            while(tmp2){//przelicz wpisy, znajdz maks nr dnia;
                if(tmp2->dzien > maks_numer_dnia) maks_numer_dnia=tmp2->dzien;
                tmp2=tmp2->nastepny;
            }
            if(maks_numer_dnia>0){
                cout<<"#=============================================================================#"<<endl;
                cout<<"#   Zadania posortowane w kolejnych dniach"<<endl;
            }
            //cout<<"debug maks numer dnia:"<<maks_numer_dnia;
            tmp=glowa;
            for(int i=0; i<=maks_numer_dnia; i++) {
                //cout<<"i="<<i<<endl;
                if(czy_dzien_istnieje(i)){
                    cout<<"#==============Zadania na dzien: "<<i<<"=============="<<endl;
                    wyswietl_zadania_dnia(i);
                }
            }
        }
    }

    void wyswietl_zadanie(int numer_zadania){
        if(czy_zadanie_istnieje(numer_zadania)){
            Zadanie *tmp=glowa;
            while(tmp->nr_zadania!=numer_zadania) {
                tmp = tmp->nastepny;
            }
            cout<<"# Nr dnia: "<<tmp->dzien<<" Zadanie nr: "<<tmp->nr_zadania<<" Zadanie: "<<tmp->notatka<<endl;
        }
    }
    void zapisz_backup(){
        Zadanie *tmp=glowa;
        ofstream zapis("backup.txt");
        if(tmp){
            int ile_wierszy=0;
            cout<<"zapisywanie do pliku..."<<endl;
            while (tmp){
                //cout<<"# Nr dnia: "<<tmp->dzien<<" Zadanie nr: "<<tmp->nr_zadania<<" Zadanie: "<<tmp->notatka<<endl;
                zapis<<tmp->nr_zadania<<";"<<tmp->dzien<<";"<<tmp->notatka<<";";//<<endl;
                if(tmp->nastepny!=NULL) zapis<<endl;
                tmp=tmp->nastepny;
                ile_wierszy++;
            }
            cout<<"  zapisanych wierszy: "<<ile_wierszy<<endl;
        }
        zapis.close();
    }

    void dodaj_zadanie_z_pliku(int numer_dnia, string notatka){
        Zadanie * nowe_zadanie = new Zadanie;
        liczba_zadan++;
        nowe_zadanie->nr_zadania=liczba_zadan;
        nowe_zadanie->dzien=numer_dnia;
        nowe_zadanie->notatka=notatka;
        nowe_zadanie->nastepny=NULL;

        if(glowa){
            Zadanie *zadanie_tmp=glowa;
            while (zadanie_tmp->nastepny) zadanie_tmp=zadanie_tmp->nastepny;
            zadanie_tmp->nastepny=nowe_zadanie;
        }
        else glowa=nowe_zadanie;
    }

    void odczytaj_backup(){
        Zadanie *tmp=glowa;
        string linia;
        string file_dzien;
        string file_nr_zadania;
        string file_notatka;
        int ile_wierszy=0;
        ifstream odczyt("backup.txt");
        if(odczyt.good() ==true){
            while(odczyt.eof()== false){
                getline(odczyt, file_nr_zadania, ';');
                getline(odczyt, file_dzien, ';');
                getline(odczyt, file_notatka, '\n');
                dodaj_zadanie_z_pliku(stoi(file_dzien), file_notatka);
                //cout<<"backup: "<<file_dzien<<"___"<<file_notatka<<endl;
                //wyswietl_zadania();
                ile_wierszy++;
            }
            odczyt.close();
        }
        cout<<" wczytanych rekordow: "<<ile_wierszy<<endl;
    }
};

void menu_listy_zadan(){
    Lista_zadan zadania;
    int input=1000;
    do {
        zadania.wyswietl_naglowek();
        cout << "# Wybierz opcje z menu:" << endl;
        cout << "#   1 - Dodaj zadanie" << endl;
        cout << "#   2 - Wyswietl wszystkie zadania" << endl;
        cout << "#   3 - Wyswietl zadania dla wybranego dnia" << endl;
        cout << "#   4 - Wyswietl zadania posortowane"<<endl;
        cout << "#   5 - Usun zadanie o wybranym numerze" << endl;
        cout << "#   6 - Usun wszystkie zadania dla wybranego dnia" << endl;
        cout << "#   7 - zapisz zadania do pliku"<< endl;
        cout << "#   8 - odczytaj zadania z pliku"<< endl;
        cout << "#   0 - koniec pracy z programem" << endl;
        cin>>input;
        switch(input){
            case 1:{
                //clrscr();//niby jest w conio.h ale chyba na linuxie
                zadania.dodaj_zadanie();
                break;
            }
            case 2:{
                zadania.wyswietl_zadania();
                break;
            }
            case 3:{
                int input2=1000;
                cout<<"#=============================================================================#"<<endl;
                cout<<"#   Dodawanie notatki na wybrany dzien"<<endl;
                cout<<"Podaj numer dnia do wyswietlenia: ";
                cin>>input2;
                zadania.wyswietl_zadania_dnia(input2);
                break;
            }
            case 4:{
                zadania.wyswietl_zadania_sort();
                break;
            }
            case 5:{
                int input2;
                zadania.wyswietl_zadania();
                cout<<"Podaj numer zadania do usuniecia: ";
                cin>>input2;
                zadania.usun_zadanie_o_numerze(input2);
                break;
            }
            case 6:{
                int input2;
                zadania.wyswietl_zadania();
                //zadania.wyswietl_dni();
                cout<<"Podaj numer dnia, aby usunac wszystkie zadania z tego dnia: ";
                cin>>input2;
                zadania.usun_zadania_z_dnia(input2);
                break;
            }
            case 7:{
                int input2;
                zadania.zapisz_backup();
                break;
            }
            case 8:{
                zadania.odczytaj_backup();
                break;
            }

        }
    }while(input!=0);
}

int main() {
    menu_listy_zadan();
//    Lista_zadan test;
//    test.dodaj_zadanie();
//    test.dodaj_zadanie();
//    test.dodaj_zadanie();
//    test.dodaj_zadanie();
//    test.dodaj_zadanie();
//    test.dodaj_zadanie();
//    test.wyswietl_zadania();
//    cout<<"# Wprowadz numer dnia z listy powyzej: ";
//    int input=99;
//    cin>>input;
//    cout<<endl;
//    test.wyswietl_zadania_dnia(input);
//    cout<<"# czy zadanie istnieje: "<<test.czy_zadanie_istnieje(input)<<endl;
//    cout<<endl;
//    cout<<"# Wprowadz numer zadania z listy do wyswietlenia: ";
//    cin>>input;
//    cout<<"wyswietl_zadanie(numer_zadania)"<<endl;
//    test.wyswietl_zadanie(input);
//    cout<<"usun_zadanie_o_numerze(input)"<<endl;
//    test.usun_zadanie_o_numerze(input);
//    cout<<"wyswietl_zadania()"<<endl;
//    test.wyswietl_zadania();
//    cout<<"wrpowadz nr dnia z ktorego maja byc skasowane zadania:";
//    cin>>input;
//    test.usun_zadania_z_dnia(input);
//    cout<<"wyswietl_zadania()"<<endl;
//    test.wyswietl_zadania();

    cout<<"koniec";
    return 0;
}
