// g++ RCHL.cpp -std=c++11 -fpermissive -fopenmp -O3 -o RCHL.out
//  ./RCHL.out /public/home/jd_sunhui/genCompressor/PSR2C/src/test out.dna
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <omp.h>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
using namespace std;
uint RLength = 0;
uint getSum(uint* data, uint pos){
    uint sum = 0;
    for(uint i=0; i<pos; i++) sum = sum + data[i];
    return sum;
}
inline string Func_RO(string& Fread, uint pos){
    // 逆循环回到原始状态
    if(pos==0) return Fread.substr(0, RLength);
    else return Fread.substr(RLength-pos, pos) + Fread.substr(0, RLength - pos);
}
inline string Func_R1(string& Fread, uint pos){
    pos = pos - RLength;
    string Sread = Fread.substr(0, RLength);
    for(int i=0; i<RLength; i++){
        if(Sread[i] == 'A') Sread[i]='T';
        else if(Sread[i] == 'C') Sread[i]='G';
        else if(Sread[i] == 'G') Sread[i]='C';
        else if(Sread[i] == 'T') Sread[i]='A';
        else continue;
    }
    if(pos==0) return Sread;
    else return Sread.substr(RLength-pos, pos) + Sread.substr(0, RLength-pos);
}
inline string Func_R2(string& Fread, uint pos){
    pos = pos - 2*RLength;
    if(pos==0){
        string Sread = Fread.substr(0, RLength);
        reverse(Sread.begin(), Sread.end());
        return Sread;
    }
    else{
        string Sread = Fread.substr(RLength-pos, pos) + Fread.substr(0, RLength - pos);
        reverse(Sread.begin(), Sread.end());
        return Sread;
    }
}
inline string Func_R3(string& Fread, uint pos){
    pos = pos - 3*RLength;
    if(pos == 0){
        string Sread = Fread.substr(0, RLength);
        reverse(Sread.begin(), Sread.end());
        for(int i=0; i<RLength; i++){
        if(Sread[i] == 'A') Sread[i]='T';
        else if(Sread[i] == 'C') Sread[i]='G';
        else if(Sread[i] == 'G') Sread[i]='C';
        else if(Sread[i] == 'T') Sread[i]='A';
        else continue;
    }
        return Sread;
    }
    else{
        string Sread = Fread.substr(RLength-pos, pos) + Fread.substr(0, RLength - pos);
        reverse(Sread.begin(), Sread.end());
        for(int i=0; i<RLength; i++){
        if(Sread[i] == 'A') Sread[i]='T';
        else if(Sread[i] == 'C') Sread[i]='G';
        else if(Sread[i] == 'G') Sread[i]='C';
        else if(Sread[i] == 'T') Sread[i]='A';
        else continue;
    }
        return Sread;
    }
}
int main(int argc, char** argv){
    string Dir = std::string(argv[1]);
    string SaveDir = std::string(argv[2]);
    int Thread = stoi(argv[3]);
    uint ReadsNum = 10;
    uint FatherNum = 10;
    string File_Name_reads = Dir + "/reads.txt";
    string File_Name_id_1 = Dir + "/id_1.txt";
    string File_Name_id_and_pos = Dir + "/id_pos.txt";
    string File_Name_count = Dir + "/count.txt";
    string File_Name_info = Dir + "/info.txt";
    string line1, line2, line3;
    ifstream Stream_info; Stream_info.open(File_Name_info, std::ios::in);
    //cout << File_Name_info << endl;
    getline(Stream_info, line1);
    getline(Stream_info, line2);
    getline(Stream_info, line3);
    Stream_info.close();
    //cout << line1 << endl << line2 << endl << line3 << endl;
    ReadsNum = stoi(line1);
    FatherNum = stoi(line2);
    RLength = stoi(line3);
    cout << "STEP1:Get Parameter over~" << endl;
    cout << "   ReadsNum:" << ReadsNum << endl;
    cout << "   FatherNum:" << FatherNum << endl;
    cout << "   RLength:" << RLength << endl;
    cout << "   InputDir:" << Dir << endl;

    string Data[ReadsNum];
    uint Fid[FatherNum];
    uint Count[FatherNum];
    uint Id[ReadsNum - FatherNum];
    uint Pos[ReadsNum - FatherNum];

    ifstream Stream_read; Stream_read.open(File_Name_reads);
    ifstream Stream_id_1;   Stream_id_1.open(File_Name_id_1);
    ifstream Stream_id_and_pos; Stream_id_and_pos.open(File_Name_id_and_pos);
    ifstream Stream_count; Stream_count.open(File_Name_count);

    string reads_, fid_, id_, pos_, count_;
    for(int i=0; i<FatherNum; i++){
        getline(Stream_id_1, fid_);
        getline(Stream_count, count_);
        getline(Stream_read, reads_);
        Fid[i] = stoi(fid_);
        Count[i] = stoi(count_);
        Data[Fid[i]] = reads_;
    }
    for(int i=0; i<(ReadsNum-FatherNum); i++){
        getline(Stream_id_and_pos, id_);
        getline(Stream_id_and_pos, pos_);
        Id[i] = stoi(id_);
        Pos[i] = stoi(pos_);
    }
   cout << "STEP2:Load File over~" << endl;

   cout << "STEP3:Paralle Recover Row Data." << endl;
   cout << "   CPU Cores:" << Thread << endl;
   int count_flag = 0;
   #pragma omp parallel for num_threads(Thread)
   for(int i=0; i<FatherNum; i++){

       int BeginPos = getSum(Count, i); // find files index
       //cout << "BeginPos :" << BeginPos << endl;
       for(int j=BeginPos; j<BeginPos+Count[i]; j++){ // sub-cycle
            uint get_pos = Pos[j];
            uint get_id = Id[j];
            uint father_id = Fid[i];
            string recovered_read;
            if((get_pos>=0) && (get_pos<RLength)) Data[get_id] = Func_RO(Data[father_id], get_pos);
            else if((get_pos>=RLength) && (get_pos<2*RLength)) Data[get_id] = Func_R1(Data[father_id], get_pos);
            else if((get_pos>=2*RLength) && (get_pos<3*RLength)) Data[get_id] = Func_R2(Data[father_id], get_pos);
            else if((get_pos>=3*RLength) && (get_pos<4*RLength)) Data[get_id] = Func_R3(Data[father_id], get_pos);
            else {cout << "SOME-THING WRONG!" << endl; exit;}

       }

        #pragma omp critical
        {
            count_flag ++;
            if(count_flag % 500000 == 0) cout << "   LOG:" << count_flag << "/" << FatherNum << " --> " << float(count_flag)/float(FatherNum)*100 << "%" << endl;
            if(count_flag % FatherNum == 0) cout << "   LOG:" << count_flag << "/" << FatherNum << " --> " << float(count_flag)/float(FatherNum)*100 << "%" << endl;
        }
   }


    ofstream Stream_OUT;
    Stream_OUT.open(SaveDir);
    for(uint i=0; i<ReadsNum; i++) Stream_OUT << Data[i] << "\n";
    Stream_OUT.close();
    cout << "STEP5:Save File Over." << endl;
    cout << "   OutputSavedPath:" << SaveDir << endl;
}