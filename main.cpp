#include <iostream>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <vector>
#include <iterator>
#include <math.h>
#include <cmath>
#define _USE_MATH_DEFINES
 
using namespace std;
 
vector<int> random_tab(vector <int>& tab){                                
   srand(time(NULL)); // biblioteka random
   int sizee = 8;
 
   for(int i =0;i<sizee;i++){
   int ran = (rand ()% 100);
   tab.push_back(ran);
   }
   cout<<endl<<"Nasza tablica: ";
	for(int i=0;i<tab.size();i++)
   {
      cout<<tab[i]<<' ';
   }
   cout<<endl;
   int ran_sol =0;
   for(int i=0;i<tab.size();i++){
      ran_sol = ran_sol + tab[i];
   }
   // sprawdzenie czy można podzielić tablicę na pół, przy nieparzystej nie działamy
   if(ran_sol%2==0){
      cout<<"Jest mozliwosc podzielenia tego zbioru"<<endl;;
   }else{
      cout<<"Nie mozna podzielic tego zbioru"<<endl;
   }
 
   return tab;
}
 
int my_tab(vector <int>& tab){
   ifstream plik("dane.txt");
   copy(istream_iterator<int>(plik), istream_iterator<int>(), back_inserter(tab));
   cout<<endl<<"Nasza tablica: ";
	for(int i=0;i<tab.size();i++)
   {
      cout<<tab[i]<<' ';
   }
   cout<<endl;
 
   int ran_sol =0;
   for(int i=0;i<tab.size();i++){
      ran_sol = ran_sol + tab[i];
   }
   if(ran_sol%2==0){
      cout<<"Jest mozliwosc podzielenia tego zbioru"<<endl;;
   }else{
      cout<<"Nie mozna podzielic tego zbioru"<<endl;
   }
   return 0;
}
 
int binarny(int size, vector <int>& tab_temp, vector <int>& tab){
   // przerzucamy na binarne, czyli zapisujemy w dwóch wektorach które elementy będą miały 1, a które 0 i czy będą w danym wektorze po podzieleniu
   int i=0;
   do{
      if(size%2==1)
         tab_temp.insert(tab_temp.end(), 1 );
      else
         tab_temp.insert(tab_temp.end(), 0 );
      size /= 2;
      i++;
   }while(size);
 
   reverse(tab_temp.begin(), tab_temp.end());
 
   if(tab_temp.size()<tab.size()){
   for(int x =tab_temp.size();x<tab.size();x++)
   tab_temp.insert(tab_temp.begin(), 0);
   }
   return 0;
}
 
int fcelu(vector <int>& tab, vector <int> tab_temp, int & wynik, vector <int>& tab_s1, vector <int>& tab_s2){
   int a= 0;
   for(int i = 0; i<tab.size();i++){
      if(tab_temp[a]==1){
         tab_s1.push_back(tab[i]);
      }else if(tab_temp[a]==0){
         tab_s2.push_back(tab[i]);
      }
      a++;
   }
   int s1=0;
   int s2=0;
   for(auto iter = tab_s1.begin(); iter != tab_s1.end(); ++iter){
      s1 =s1 +*iter;
   }
 
   for(auto ite = tab_s2.begin(); ite != tab_s2.end(); ++ite){
      s2 =s2 +*ite;
   }
   wynik = abs(s1 - s2);
   return wynik;
}
 
void pisanie (vector <int>&  tab_s1, vector <int>& tab_s2){
      int wynik;
 
      cout<<endl<<"S1 = [ ";
      for(int a=0;a<tab_s1.size();a++){
         cout<<tab_s1[a]<<" ";
      }cout<<"]";
 
      cout<<endl<<"S2 = [ ";
      for(int a=0;a<tab_s2.size();a++){
         cout<<tab_s2[a]<<" ";
      }cout<<"]"<<endl;
 
      int s1=0;
      int s2=0;
      for(auto iter = tab_s1.begin(); iter != tab_s1.end(); ++iter){
         s1 =s1 +*iter;
      }
      cout<<endl<<"Suma s1 = "<<s1<<endl;
 
      for(auto ite = tab_s2.begin(); ite != tab_s2.end(); ++ite){
         s2 =s2 +*ite;
      }
      cout<<"Suma s2 = "<<s2<<endl;
 
      wynik = abs(s1 - s2);
      cout<<endl<<"Wynik: "<<wynik<<endl;
 
}
 
int algorytm_pp(vector <int> tab, vector <int>& tab_temp, vector <int>  tab_s1, vector <int> tab_s2, int wynik){
   // tu wypisujemy wszystkie możliwości podzielenia wektorów
   int naj;
   vector <int> tab_s1_tmp; 
   vector <int> tab_s2_tmp; 
   int sizee = pow(2,tab.size())/2-1; // dzielimy na dwa, żeby nie było powtórzeń
   int size = sizee;
   for(int in = 1;in <= sizee; in++){
      binarny(size, tab_temp, tab);
      fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);cout<<endl;
      pisanie(tab_s1, tab_s2);
 
      size--;
      tab_temp.resize(0); tab_s1.resize(0); tab_s2.resize(0); 
   }
   return 0;
}
 
int randomsol(vector<int> tab,vector<int>& tab_temp, vector<int>& tab_s1, vector<int>& tab_s2, int& wynik, int& sizee){
   // randomowe losowanie na podstawie binarnej, jak dostaniemy 3 to 0011, więc jeden wektor to 00, a // drugi 11
   srand(time(NULL));
   sizee = pow(2,tab.size())/2-1;
   int size = (rand ()% sizee +1);
   binarny(size, tab_temp, tab);
   fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);cout<<endl;
   // pisanie(tab_s1, tab_s2);
   return size;
}
 
int wspinaczkowyDeterministyczny (vector<int> tab,vector<int> tab_temp, int wynik, vector<int> tab_s1, vector<int> tab_s2, int sizee){
 
   int naj, wynik_tmp, z; 
   int size = randomsol(tab, tab_temp, tab_s1, tab_s2, wynik, sizee);
   int sMax = sizee;
   naj=wynik;
   if(wynik ==0){
      naj =wynik;
      cout<<endl<<"Optimum Globalne:";
      pisanie(tab_s1, tab_s2);
   }else{ 
         size--;
         if(size<=0){
            cout<<"test";
         }else{
         binarny(size, tab_temp, tab);
         fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
         wynik_tmp=wynik;
         size=size+2;
         binarny(size, tab_temp, tab);
         fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
         if(wynik<wynik_tmp){
            z = 1;
         }else if(wynik>wynik_tmp){
            z =0;
         }
         for(int ii=10;ii>0;ii--){
            tab_s1.resize(0);tab_s2.resize(0);tab_temp.resize(0);
            if(z==1){
               if(wynik<=naj){
               pisanie(tab_s1, tab_s2);
               naj=wynik;
               size++;
               }else{
                  break;
               }
            }else if(z==0){
               if(wynik<=naj){
               size--;
               binarny(size, tab_temp, tab);
               fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
               pisanie(tab_s1, tab_s2);
               naj=wynik;
               size--;
               }else{
                  break;
               }
            }
         }           
         }
   }  
   return 0;
}

int wspinaczkowyDeterministycznyWszystkie (vector<int> tab,vector<int> tab_temp, int wynik, vector<int> tab_s1, vector<int> tab_s2, int sizee){

   int naj, wynik_tmp, z;
   int size = randomsol(tab, tab_temp, tab_s1, tab_s2, wynik, sizee);
   int sMax = sizee;
   naj=wynik;
   if(wynik ==0){
      naj =wynik;
      cout<<endl<<"Optimum Globalne1:";
      pisanie(tab_s1, tab_s2);
   }else{
       for(int ii=100;ii>0;ii--){

         int size_1=size-1;
         int size_2=size+1;
         if(size_1<1){      //sprawdzamy czy nie wychodzimy poza skale w dół bo jak tak to tylko jeden sąsiad
            size = size_2;
         }else if(size_2>sMax){ //sprawdzamy czy nie wychodzimy poza skale w góre bo jak tak to tylko jeden sąsiad
            size = size_1;
         }else{                    // nie jestesmy na krańcach więc 2 sąsiadów
             int wynik_1=0;
             int wynik_2=0;
             size = size_1;
            binarny(size, tab_temp, tab);
            fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);

            wynik_1 = wynik;
            if(wynik_1 ==0){
                naj =wynik_1;
                cout<<endl<<"Optimum Globalne2:";
                pisanie(tab_s1, tab_s2);
                ii =0;
            }
            tab_temp.resize(0);tab_s1.resize(0); tab_s2.resize(0);
            wynik = 0; size =0;
            size = size_2;
            binarny(size, tab_temp, tab);
            fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
            wynik_2=wynik;
            if(wynik_2 ==0){
                naj =wynik_2;
                cout<<endl<<"Optimum Globalne3:";
                cout<<endl<<wynik_2;
                pisanie(tab_s1, tab_s2);
                ii=0;
            }
            wynik_2 = wynik;
            size=0;        // wynik dla drugiego
            if(wynik_1<wynik_2){            // if wybieramy który lepszy wynik
                size = size_1;
                if(wynik_1<=naj){
                        cout<<"najlepszy"<<naj<<"wynik_1  "<<wynik_1<<endl;
                    binarny(size, tab_temp, tab);
                    fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
                    pisanie(tab_s1, tab_s2);
                    naj=wynik;

                }
            }else{
                size= size_2;
                if(wynik_2=naj){
                        cout<<"najlepszy"<<naj<<"wynik_2  "<<wynik_2<<endl;
                    binarny(size, tab_temp, tab);
                    fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
                    pisanie(tab_s1, tab_s2);
                    naj=wynik;
                }
            }
         }
       }
   }

   return 0;
}
 
int wspinaczkowyRandomowy (vector<int> tab,vector<int> tab_temp, int wynik, vector<int> tab_s1, vector<int> tab_s2, int sizee){
   srand(time(NULL));
   int naj; 
   int size = randomsol(tab, tab_temp, tab_s1, tab_s2, wynik, sizee);
   int sMax = sizee;
   naj=wynik;
   if(wynik ==0){
      naj =wynik;
      cout<<endl<<"Optimum Globalne:";
      pisanie(tab_s1, tab_s2);
   }else{     
      for(int ii=100;ii>0;ii--){
         int random = (rand ()% 2);    //0 =>-- ; 1=>++ || jeśli wylosowana liczba jest podzielna przez 2 to w górę, jak nie to w dół
         tab_s1.resize(0);tab_s2.resize(0);tab_temp.resize(0);
         if(random == 0){           //jeżeli random podzielny przez  0 to idziemy w dół 
            size--;
            if(size<=0){            // warunek żeby nie wyjść poza skale w dół
               size++;
            }else{                                   
               binarny(size, tab_temp, tab);        
               fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);              
               if(wynik==0){
                  naj=wynik;
                  cout<<endl<<"Optimum Globalne:";
                  pisanie(tab_s1, tab_s2);
                  ii =0;  
               }else if(wynik<=naj){                    // jak lepszy wynik to bierzemy
                  naj= wynik;
                  pisanie(tab_s1, tab_s2);
               }else{
                  continue;
               }
            }
         }else{                         // jeżeli random NIE_podzielny przez  0 to idziemy w góre
            size++;
            if(size>sMax){              // warunek żeby nie wyjść poza skale w góre
               size--;
            }else{
               binarny(size, tab_temp, tab);
               fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
               if(wynik==0){
                  naj =wynik;
                  cout<<endl<<"Optimum Globalne:";
                  pisanie(tab_s1, tab_s2);
                  ii =0;  
               }else if(wynik<=naj){                     // jak lepszy wynik to bierzemy
                  naj= wynik;
                  pisanie(tab_s1, tab_s2);
               }else{
                  continue;
               }
            }           
         }
      }
   }  
 
   return 0;
}
 
int wyzarzania(vector<int> tab,vector<int> tab_temp, int wynik, vector<int> tab_s1, vector<int> tab_s2, int sizee){
   srand(time(NULL));
   int naj, odchylenie_dol,odchylenie_gora, r_odchylenie; 
   float P, odchylenie;
   int size = randomsol(tab, tab_temp, tab_s1, tab_s2, wynik, sizee);
   int sMax = sizee;
   naj=wynik;
   for(int i=0;i<tab.size();i++)
   {
      odchylenie=odchylenie+tab[i];         // początkowe odchylenie = suma wszystkich liczb
   }
   if(wynik ==0){
      naj =wynik;
      cout<<endl<<"Optimum Globalne:";
      pisanie(tab_s1, tab_s2);
   }else{
      naj=wynik;
      for(int i = 3*odchylenie;i>0;i--){ // im większe odchylenie tym mogę szukać dalszego sąsiada
         // cout<<i;
         cout<<"Odchylenie: "<<odchylenie<<endl;
         tab_s1.resize(0);tab_s2.resize(0);tab_temp.resize(0);
         odchylenie_dol=size-odchylenie;
         odchylenie_gora=size+odchylenie;
         if(odchylenie_dol<0){                  //  // warunek żeby nie wyjść poza skale w góre i w dół
            odchylenie_dol=1;
         }if(odchylenie_gora>sMax){
            odchylenie_gora=sMax;
         }
         r_odchylenie=odchylenie_gora-odchylenie_dol;
         size =odchylenie_dol + (rand ()% r_odchylenie);        // randomowy wybór na podstawie odchyleń
         binarny(size, tab_temp, tab);
         fcelu(tab,tab_temp, wynik, tab_s1, tab_s2);
         if(wynik==0){
            naj =wynik;
            cout<<endl<<"Optimum Globalne:";
            pisanie(tab_s1, tab_s2);
            i=0;
         }else if(wynik<=naj){
            naj=wynik;
            pisanie(tab_s1, tab_s2);
         }else{
            float pot_P = (wynik-naj)/odchylenie;
            P=pow(M_E,-(pot_P));
            float Uk = 0.0001+rand()%100*0.01;
            if(Uk<P){
               naj=wynik;
               pisanie(tab_s1, tab_s2);
            }else{
               cout<<"Wynik: "<<naj<<endl;
            }
         }  
         if(i%3==0){
            odchylenie=odchylenie*0.9;
         }else{
            continue;
         }
 
      }      
   }
 
   return 0;
}
 
int selection(vector <int> wektor_p, vector < vector < int > >& wektor_d, vector <int>& rodzic, vector <int>& rodzic2, vector<int> tab_temp){
   int osobnik = (rand ()% wektor_p.size() +0);
   // cout << "Osobnik1" << osobnik;
   int osobnik2 = (rand ()% wektor_p.size() +0);
   // cout << "Osobnik2: " << osobnik2;
// wybieramy 2 randomowo
   for(int i = 0; i<wektor_d.size();i++){    // tworzymy na podstawie wektora_d rodziców
      if(wektor_d[i][0]==wektor_p[osobnik]){
         for(int j=0;j<tab_temp.size();j++){
            rodzic.push_back(wektor_d[i][j+1]);
         }
         i=wektor_d.size();
      }
   }
 
   for(int i = 0; i<wektor_d.size();i++){    
      if(wektor_d[i][0]==wektor_p[osobnik2]){
         for(int j=0;j<tab_temp.size();j++){
            rodzic2.push_back(wektor_d[i][j+1]);
         }
         i=wektor_d.size();
      }
   } 
 
   cout<<"rodzic: ";
   for(int i=0;i<rodzic.size();i++){
      cout<<rodzic[i]<<" ";
   }cout<<endl;
 
   cout<<"rodzic2: ";
   for(int i=0;i<rodzic2.size();i++){
      cout<<rodzic2[i]<<" ";
   }cout<<endl<<endl;
 
   return 0;
}
 
int crossover(vector <int> wektor_p, vector < vector < int > >& wektor_d, vector <int>& rodzic, vector <int>& rodzic2, vector<int> tab_temp){
   int punkt = (rand ()% (tab_temp.size()-1) +1); // wybieramy wielkość crossover
   // na podstawie rodziców robimy swaapa, jak są takie same wartości to nawet nie ma co zamieniać
   swap_ranges(rodzic.begin(), rodzic.begin()+punkt, rodzic2.begin());
 
   cout<<"rodzic po krzyzowaniu: ";
   for(int i=0;i<rodzic.size();i++){
      cout<<rodzic[i]<<" ";
   }cout<<endl;
 
   cout<<"rodzic2 po krzyzowaniu: ";
   for(int i=0;i<rodzic2.size();i++){
      cout<<rodzic2[i]<<" ";
   }cout<<endl;
 
   return 0;
}
 
int mutation(vector < vector < int > >& wektor_d){
   //  wybieram małe prawdopodobieństwo, żeby rzadko występowało jak w prawdziwym życiu
   for(int i=0;i<wektor_d.size();i++){
      for(int j=1;j<wektor_d[i].size();j++){
         int m =rand ()%10000;
 
         if(m==5){ // jeżeli trafimy na 5 to robimy mutację
         cout<< "test";
            if(wektor_d[i][j]==0){
               wektor_d[j].erase(wektor_d[j].begin()+j);
               wektor_d[j].insert(wektor_d[j].begin()+j,1,1);
            }else{
               wektor_d[j].erase(wektor_d[j].begin()+j);
               wektor_d[j].insert(wektor_d[j].begin()+j,1,0);
            } 
         } 
      }    
   }
 
   return 0;
}
 
 
int genetyczny(vector<int> tab,vector<int> tab_temp,vector <int> tab_s1, vector <int> tab_s2, int wynik){
   ifstream plik("ilosc.txt"); int a;
   plik>> a;
   vector < vector < int > > wektor_d; int naj;  // wektor d macierz wszystkich wartości
   int sizee = pow(2,tab.size())/2-1; int suma=0; int pop_size=tab.size()*0.70; // % wielkości tablicy, sizee - długość tablicy dzielimy na 2, nie chcemy mieć wszędzie 0 lub 1
   if(pop_size%2!=0){pop_size=pop_size+1;} // dodajemy 1 żeby pozbyć się po przecinku
   vector <int> wektor_wynik;vector<int> temp;
   vector <int> wektor_p;  //prawdopodobinstwo
   srand(time(NULL));
   for(int i =0;i<pop_size;i++){                                        ///////losujemy populacje poczatkowa 
      tab_temp.resize(0);tab_s1.resize(0); tab_s2.resize(0);
      int size = (rand ()% sizee +1);int w =0; // losujemy wartość dzięki której podzieliliśmy tablice
      binarny(size, tab_temp, tab); // przerzucamy na podzielenie tablicy
      fcelu(tab,tab_temp, wynik, tab_s1, tab_s2); // wyliczamy funkcję celu
         cout<<"Wynik: "<<wynik<<endl;
 
         cout<<"Tab_temp: ";
         for(int a=0;a<tab_temp.size();a++){
            cout<<tab_temp[a]<<" ";
         }
         cout<<endl<<endl;
 
      temp.push_back(wynik);
      for(int j=0;j<tab_temp.size();j++){
         temp.push_back(tab_temp[j]);
      }
      wektor_d.push_back(temp); // wypełnianie  wektora d
      temp.resize(0);
 
      wektor_wynik.push_back(wynik);    
      suma = suma + wynik;     
   }
 
   for(int i = 0; i<wektor_wynik.size(); i++){
      int p = 0; // im wartość bliżej 0 tym jest bardziej nagradzane
      if(wektor_wynik[i]==0){ // jeżeli ma 0 to nagradzamy p * 20 czyli jeden z wierszy
         p = suma*20;
         // cout<< "Suma: "<< suma << endl;
         // cout<< "p: " << p << endl;
      }else{
         p = suma/wektor_wynik[i]*10; // jeżeli inny wynik to jest mniejsza nagroda
         // cout << "Suma: " << suma << endl;
         // cout << "p: " << p << endl;
      }
      for(p;p>0;p--)
      {
         wektor_p.push_back(wektor_wynik[i]);
      }
   }
 
   cout<<"Pierwsza populacja: "<<endl;
   for(int i=0;i<wektor_d.size();i++){
      for(int j=0;j<wektor_d[i].size();j++)
         cout<<wektor_d[i][j]<<" ";
   cout<<endl;}cout<<endl;
 
  /*cout<<"Wartosci prawdo: ";
   for (int jj = 0; jj < wektor_p.size(); jj++)  
      cout << wektor_p[jj] << " ";
   cout << endl;   
 
   cout<<"Wartości wynikow: ";
   for (int jj = 0; jj < wektor_wynik.size(); jj++)  
      cout << wektor_wynik[jj] << " ";
   cout << endl; */
 
 
   tab_s1.resize(0); tab_s2.resize(0); wektor_wynik.resize(0);
   vector < vector < int > > v1;
   vector <int> rodzic;vector <int> rodzic2; int z =0;
   for(int z=0;z<a;z++){ 
      v1.resize(0);
      for(int i=0;i<pop_size/2;i++){
         selection(wektor_p, wektor_d, rodzic, rodzic2, tab_temp);
         crossover(wektor_p, wektor_d, rodzic, rodzic2, tab_temp);
 
         fcelu(tab,rodzic, wynik, tab_s1, tab_s2);
         //pisanie(tab_s1, tab_s2);
         rodzic.insert(rodzic.begin(), wynik);
         v1.push_back(rodzic); 
         wektor_wynik.push_back(wynik);
 
 
         tab_s1.resize(0); tab_s2.resize(0);
         fcelu(tab,rodzic2, wynik, tab_s1, tab_s2);
         //pisanie(tab_s1, tab_s2);
         rodzic2.insert(rodzic2.begin(), wynik);
         v1.push_back(rodzic2); 
         wektor_wynik.push_back(wynik);
 
 
         rodzic.resize(0);rodzic2.resize(0);tab_s1.resize(0); tab_s2.resize(0);
      }
      //mutation(wektor_d);
      wektor_d.resize(0);
      copy( v1.begin(), v1.end(), back_inserter(wektor_d) );
      mutation(wektor_d);
 
 
      cout<<"Populacja po "<<z+1<<" cyklu algorytmu genetycznego:"<<endl;
      for(int i=0;i<v1.size();i++){
         for(int j=0;j<v1[i].size();j++)
            cout<<v1[i][j]<<" ";
      cout<<endl;}cout<<endl; 
 
      wektor_p.resize(0);
      for(int i = 0; i<wektor_wynik.size(); i++){ 
         int p = 0;
         if(wektor_wynik[i]==0){
            p = suma*20;
         }else{
            p = suma/wektor_wynik[i]*10;
         }
         for(p;p>0;p--){
            wektor_p.push_back(wektor_wynik[i]);
         }
      }
 
   /*cout<<"Wartosci prawdo: ";
   for (int jj = 0; jj < wektor_p.size(); jj++)  
      cout << wektor_p[jj] << " ";
   cout << endl;  
      cout<<"Wartości wynikow: ";
      for (int jj = 0; jj < wektor_wynik.size(); jj++)  
         cout << wektor_wynik[jj] << " ";
      cout << endl;*/     
 
      wektor_wynik.resize(0);v1.resize(0);
   }
 
   return 0;
}
 
 
int main() {
  vector <int> tab;vector <int> tab_temp; vector <int> tab_s1; vector <int> tab_s2; int wynik; int sizee;   
 
   random_tab(tab);                 
   // my_tab(tab);
 
   // fcelu(tab, tab_temp);
   // algorytm_pp(tab, tab_temp, tab_s1, tab_s2, wynik);
   // randomsol(tab, tab_temp, tab_s1, tab_s2, wynik, sizee);
   // wspinaczkowyRandomowy(tab, tab_temp, wynik, tab_s1, tab_s2, sizee);
   // wspinaczkowyDeterministyczny(tab, tab_temp, wynik, tab_s1, tab_s2, sizee);
   wspinaczkowyDeterministycznyWszystkie(tab, tab_temp, wynik, tab_s1, tab_s2, sizee);
   // wyzarzania(tab, tab_temp, wynik, tab_s1, tab_s2, sizee);
   // genetyczny(tab, tab_temp, tab_s1, tab_s2, wynik);
 
 
   return 0;
}