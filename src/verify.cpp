/* *****************************************************
authors: SH
date: 20230102
describe: a cpp files for test decompression results
******************************************************** */
// g++ verify.cpp -std=c++11 -O3 -o verify.out
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

unsigned int RSHash(char *str){
        unsigned int b = 378551 ;
        unsigned int a = 63689 ;
        unsigned int hash = 0 ;
        while (*str){
            hash = hash * a + ( * str ++ );
            a *= b;}
        return (hash & 0x7FFFFFFF );}

int hanming_(string A, string B){
    int key = min(A.length(), B.length());
    for(int i=0; i< key; i++){
        if(A[i] != B[i]) return 1;
    }
    return 0;
}

int main(int argc, const char *argv[]){
    string PathA ;
    string PathB ;
    switch(3){ // check parameters
        case 3:
            PathA = argv[1]; // fastq format files
            PathB = argv[2]; // decompression files path
            break;
        default:
        cerr <<"Wrong Parameters!" << endl;
        exit(-1);
    }
    ifstream A; A.open(PathA, std::ios::in);
    ifstream B; B.open(PathB, std::ios::in);
    if(!A || !B) return 0;
    string AA, BB;
    int count = 0;
    int Num = 0;
    cout << "FileA:" << PathA << endl;
    cout << "FileB:" << PathB << endl;
    string AA1,AA3,AA4;
    while(A.peek() != EOF){
        getline(A, AA1);
        getline(A, AA);
        getline(A, AA3);
        getline(A, AA4);
        getline(B, BB);
        count++;
        if(hanming_(AA, BB) == 1){
            Num = Num + 1;
            cout << "hash verify wrong! at : " << count << endl;
            cout << AA << endl;
            cout << BB << endl;
            cout << endl;
        }
    }
    cout << "Unable to recover sequencing reads: " << Num << endl;

    A.close(); B.close();


}