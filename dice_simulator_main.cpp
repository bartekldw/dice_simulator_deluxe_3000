#include <iostream>
#include <random>
#include <utility>
#define fast_io ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#define log_err(msg)(cerr<<"\033[1;31m[BŁĄD]\033[0m "<<msg<<endl)
using namespace std;
constexpr int max_value = 20;
pair<int,int> maks_los(int* tab, int size){
    int max_indeks = 0;
    int max_liczba = *(tab);
    for(int i = 1; i < size; ++i){
        if (*(tab+i) > max_liczba){
            max_liczba = *(tab+i);
            max_indeks = i;
        }
    }
    return {max_liczba, max_indeks};
}
void wyswietl_wykres(int* tab, int size, int maks_wartosc, int maks_oczko){
    for(int i = 0; i < size; ++i){
        cout << i+1 << ": ";
        if (*(tab+i) != 0){
            int dlugosc = (*(tab+i) * (long long)max_value) / maks_wartosc;
            for(int j = 0; j < dlugosc; ++j){
                cout << "*";
            }
        }
        else cout << "-";
        if (i == maks_oczko){
            cout << "\033[1;31m";
            cout << " (" << *(tab+i) << ")";
            cout << "\033[0m";
        }
        else cout << " (" << *(tab+i) << ")";
        cout << endl;
    }
}
int main(){
    fast_io;
    cout << "\033[1;36m---GENERATOR KOSTKI---\033[0m" << endl << flush;
    int oczka;
    cout << "Ile oczek: " << flush;
    cin >> oczka;
    if (oczka <= 0){
        log_err("Bledne dane!");
        return 1;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,oczka);
    long long liczba_testow;
    cout << "Liczba testów: " << flush;
    cin >> liczba_testow;
    if (liczba_testow <= 0){
        log_err("Bledne dane!");
        return 1;
    }
    if (oczka == 1){
        cout << oczka << " oczko wylosowano " << liczba_testow << " razy!" << endl;
        return 0;
    }
    int *ile_razy = new int[oczka]{0};
    int losowa = 0;
    cout << "\033[1;36mGeneruje...\033[0m" << endl;
    try{
        for(int i = 0; i < liczba_testow; ++i){
            losowa = distrib(gen);
            *((ile_razy+losowa)-1) += 1;
        }
        cout << "\033[1;32mWygenerowano pomyślnie!\033[0m" << endl;
    }
    catch(...){
        log_err("Wystąpil nieoczekiwany blad podczas generowania!");
    }
    pair<int, int> wynik = maks_los(ile_razy,oczka);
    cout << "\033[1;36m---Najwiecej razy wylosowano \033[0m" << "\033[1;31m" << wynik.second+1 << (wynik.second+1 >= 5 ? " oczek" : (wynik.second+1 == 1 ? " oczko" : " oczka")) << ": \033[0m\033[1;36m" << wynik.first << " razy!---\033[0m" << endl;
    wyswietl_wykres(ile_razy, oczka, wynik.first, wynik.second);
    delete[] ile_razy;
    return 0;
}
