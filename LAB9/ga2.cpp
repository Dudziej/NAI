#include <iostream>
#include <functional>
#include <random>
#include <algorithm>
#include <utility>
#include <string_view>
#include <vector>

using namespace ::std;
random_device rdev;
default_random_engine dre(rdev());

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

void krzyzowanie_jednopunktowe(vector<int> x,vector<int> y){
    uniform_int_distribution<int> uid(0, 128);
    int iksigrek = uid(dre);
    for(int j = 0; j < iksigrek; j++){
        swap(x[j], y[j]);
    }
    cout<<"Po Krzyzowaniu 1:"<<endl;
    print(x);
    cout<<endl;
    cout<<"Po Krzyzowaniu 2:"<<endl;
    print(y);
    cout<<endl;
}

void mutacja(vector<int>phen){
    uniform_int_distribution<int> uid(0, 128);
    int iksigrek = uid(dre);
    if(phen[iksigrek]==1){
        phen[iksigrek]=0;
        }else{
        phen[iksigrek]=1;
    }
    cout<<"Po mutacji "<<iksigrek<<" elementu:"<<endl;
    print(phen);
    cout<<endl;
}


void selekcja(vector<int>tournament){
 uniform_int_distribution<int> uid(0, 128);
    int iksigrek = uid(dre);
    cout<<"Zwycięzca"<<" na pozycji "<<iksigrek<<":"<<endl;
    cout<<tournament[iksigrek]<<endl;
    cout<<endl;
}


int main(){
    auto phenotype = []() {
        vector<int>vec;
        for(int i = 0; i<128; i++){
           uniform_int_distribution<int> uid(0, 1);
           vec.push_back(uid(dre));
        }return vec;
    };
    
    vector<int>phenotypee = phenotype();
    cout<<"Phenotype 1:   "<<endl;
    print(phenotypee);
    cout<<endl;

    vector<int>phenotypeee = phenotype();
    cout<<"Phenotype 2:   "<<endl;
    print(phenotypeee);
    cout<<endl;

    krzyzowanie_jednopunktowe(phenotypee, phenotypeee);
    mutacja(phenotypee);
    selekcja(phenotypee);
}