#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <omp.h>
#include <unordered_map>
#include <set>
#include <string>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <algorithm>

using namespace std;

uint TotalNum = 0;
uint FatherNum = 0;
int RLength = 0;
std::string FileName ;
std::string SaveFileName ;
int Thread = 16;
bool QualityScoreFlag = 0;
bool HeaderFlag = 0;

class RollingHash {
private:
    unsigned long p = 31;
    unsigned long m = 1L << 32;
    string s;
    vector<unsigned long> hashMap;
    vector<unsigned long> pPower;
    void computePPower() {
        pPower.resize(s.size(), 1);
        for (int i = 1; i < s.size(); ++i) {
            pPower[i] = (pPower[i-1] * p) % m;
        }
    }
    void fillHashMap() {
        hashMap.resize(s.size()+1);
        unsigned long curr = 0;
        for (int i = 1; i < hashMap.size(); ++i) {
            curr = (curr*p + s[i-1]) % m;
            hashMap[i] = curr;
        }
    }
public:
    RollingHash(string input) {
        s = input;
        computePPower();
        fillHashMap();
    }
    unsigned long getHashCode(int i, int j) {
        if (i == 0) return hashMap[j];
        // Take consideration of module m.
        // Instead of return (hashMap[j] - hashMap[i]*pPower[j-i]), do the following:
        return (hashMap[j] + m - (hashMap[i]*pPower[j-i])%m) % m;
    }
};

typedef struct CNode{
    /* data struct for child node */
    uint id;
    uint pos;
    CNode(uint id_, uint pos_):id(id_), pos(pos_){}
} cnode;
bool operator<(const CNode &a, const CNode &b){return a.id <= b.id;}

typedef struct FNode{
    /* data struct for father node */
    uint id;
    set<CNode>cns;
    FNode(uint id_):id(id_){}
} fnode;
bool operator<(const FNode &a, const FNode &b){return a.id <= b.id;}

int Hang_Ming_Distance(string &A, string &B, uint pos){
        for(int j=0; j<RLength; j++){
            if(A[j] != B[j+pos]) return 1;
        }
    return 0;
}

unordered_map<unsigned long, set<FNode>>chl;
vector<string>Data;

int Func_R0(string &Read_0, uint id, unsigned long &hashValue);
int Func_R1(string &Read_1, uint id);
int Func_R2(string &Read_2, uint id);
int Func_R3(string &Read_3, uint id);
int Func_Update(unsigned long &Hash_Value, uint id);
int Func_File_Saving(string saveTempFileDir);
int Load_Data();
int Build_CHL();

int main(int argc, char** argv){
    RLength = stoi(argv[1]);
    FileName = std::string(argv[2]);
    SaveFileName = std::string(argv[3]);
    Thread = stoi(argv[4]);
    QualityScoreFlag = stoi(argv[5]);
    HeaderFlag = stoi(argv[6]);

    cout << "STEP1:Begin Cycle-HASH-Linkage~" << endl;
    cout << "   RLength:" << RLength << endl;
    cout << "   FileName:" << FileName << endl;
    cout << "   SaveFileName:" << SaveFileName << endl;
    cout << "   Thread:" << Thread << endl;
    cout << "   QualityScoreFlag:" << QualityScoreFlag << endl;
    cout << "   HeaderFlag:" << HeaderFlag << endl;

    cout << "STEP2:Begin Load Data~" << endl;
    if(Load_Data() != 1)
		{cout << "   Load_Data(*) Wrong!" << endl; return 1;}
    else
		cout << "   Load_Data(*) running over~" << endl;

    cout << "STEP3:Begin Build CHL~" << endl;
    if(Build_CHL() !=1) {cout << "Build_CHL(*) Wrong! " << endl; return 1;}
    else cout << "   Build_CHL(*) running over~" << endl;

    cout << "STEP4:Begin Files SAVING~" << endl;
    if(Func_File_Saving(SaveFileName) != 1) {cout << "Func_File_Saving(*) Wrong!" << endl; return 1;}
    else cout << "   Func_File_Saving(*) over~" << endl;

    cout << "STEP5:End Cycle-HASH-Linkage~" << endl;

    return 0;
}


int Func_R0(string &Read_0, uint id, unsigned long &hashValue){
    RollingHash Hash_0(Read_0);
    uint i = 0;
    int flag = 0;
    while( i < RLength){
        unsigned long hvalue = Hash_0.getHashCode(i, i+RLength);
        if(i==0) hashValue = hvalue;
        //#pragma omp critical
        //{
            unordered_map<unsigned long, set<FNode>>::iterator iter;
            #pragma omp critical
            iter = chl.find(hvalue);
            if(iter != chl.end()){
                for(auto it = (iter->second).begin(); it != (iter->second).end(); it++){
                    if(Hang_Ming_Distance(Data[(*it).id], Read_0, i) == 0){
                        #pragma omp critical
                        (*it).cns.emplace(CNode(id,i));
                        flag = 1;
                        break;
                    }
                }
            }
        //}
        if(flag==1) return 1;
        i++;
    }
    return 0;
}


int Func_R1(string &Read_1, uint id){
    RollingHash Hash_1(Read_1);
    uint i = 0;
    int flag = 0;
    while( i < RLength){
       // #pragma omp critical
       //{
            unordered_map<unsigned long, set<FNode>>::iterator iter;
            #pragma omp critical
            iter = chl.find(Hash_1.getHashCode(i, i+RLength));
            if(iter != chl.end()){
                for(auto it = (iter->second).begin(); it != (iter->second).end(); it++){
                    if(Hang_Ming_Distance(Data[(*it).id], Read_1, i) == 0){
                        #pragma omp critical
                        (*it).cns.emplace(CNode(id,i + RLength));
                        flag = 1;
                        break;
                    }
                }
            }
       //}
        if(flag==1) return 1; // update success flag
        i++;
    }
    return 0;
}


int Func_R2(string &Read_2, uint id){
    RollingHash Hash_2(Read_2);
    int flag = 0;
    uint i = 0;
    while( i < RLength){
        //#pragma omp critical
        //{
            unordered_map<unsigned long, set<FNode>>::iterator iter;
            #pragma omp critical
            iter = chl.find(Hash_2.getHashCode(i, i+RLength));
            if(iter != chl.end()){
                for(auto it = (iter->second).begin(); it != (iter->second).end(); it++){
                    if(Hang_Ming_Distance(Data[(*it).id], Read_2, i) == 0){
                        #pragma omp critical
                        (*it).cns.emplace(CNode(id,i + 2*RLength));
                        flag = 1;
                        break;
                    }

                }
            }
        //}
        if(flag==1) return 1;
        i++;
    }
    return 0;
}


int Func_R3(string &Read_3, uint id){
    RollingHash Hash_3(Read_3);
    int flag = 0;
    uint i = 0;
    while( i < RLength){
        //#pragma omp critical
        //{
            unordered_map<unsigned long, set<FNode>>::iterator iter;
            #pragma omp critical
            iter = chl.find(Hash_3.getHashCode(i, i+RLength));
            if(iter != chl.end()){
                for(auto it = (iter->second).begin(); it != (iter->second).end(); it++){
                    if(Hang_Ming_Distance(Data[(*it).id], Read_3, i) == 0){
                        #pragma omp critical
                        (*it).cns.emplace(CNode(id,i + 3*RLength));
                        flag = 1;
                        break;
                    }

                }
            }
        //}
        if(flag==1) return 1;
        i++;
    }
    return 0;
}


int Load_Data(){
    //a function for load fastq format reads to shared memory
    ifstream FastQ_In;
    ofstream Header_Out;
    ofstream QualityScore_Out;
    //cout << FileName << endl;
    FastQ_In.open(FileName,std::ios::in);
    if(!FastQ_In) return 0;
    //cout << "1111" << endl;
    if(HeaderFlag == 1) Header_Out.open(SaveFileName + ".header");
    if(QualityScoreFlag == 1) QualityScore_Out.open(SaveFileName + ".quality_score");
    int i = 0;
    int j = 0;
    string line;
    while(getline(FastQ_In, line)){
        switch(i){
            case 0: if(HeaderFlag == 1) Header_Out << line << "\n"; break;
            //case 1: Data[j] = line; break;
            case 1: if(line.length() != RLength){
                        cout << "Please Fix Read to Same Length!" << endl;
                        cout << "Length A:" << RLength << endl;
                        cout << "Length B:" << line.length() << endl;
                        cout << "Wrong Palace : " << j << "--->" << line << endl;
                        return 0;
                        }
                        else Data.push_back(line); //cout << line << endl;
                        break;
            case 2: break;
            case 3: if(QualityScoreFlag == 1) QualityScore_Out << line << "\n"; break;
        }
    i = (i+1)%4;
    j ++;
    }
    FastQ_In.close();
    //cout << "22222" << endl;
    if(QualityScoreFlag == 1) QualityScore_Out.close();
    if(HeaderFlag == 1) Header_Out.close();
    TotalNum = Data.size();
    cout << "   Data.size(): " << Data.size() << endl;
    return 1;
}


int Func_Update(unsigned long &Hash_Value, uint id){
    /* update Father Node Chain*/
    //#pragma omp critical
    //{
        unordered_map<unsigned long, set<FNode>>::iterator iter;
        #pragma omp critical
        iter = chl.find(Hash_Value);

        if(iter == chl.end()){
            set<FNode>hns;
            #pragma omp critical
            hns.emplace(FNode(id));
            #pragma omp critical
            chl.emplace(Hash_Value, hns);
        }
        else{
            bool flag = 0;
            for(auto it = (iter->second).begin(); it!=(iter->second).end(); it++){
                if(Hang_Ming_Distance(Data[(*it).id], Data[id], 0) == 0){
                    #pragma omp critical
                    (*it).cns.emplace(CNode(id,0));
                    flag = 1;
                    break;
                }
            }
            if(flag==0) {
                #pragma omp critical
                (iter->second).emplace(FNode(id));
            }

        }
    //}
    return 1;
}

int Build_CHL(){
    // cpu parallel build cycle-hash-linkage
    int count_flag = 0;
    #pragma omp parallel for num_threads(Thread)
    for(uint i=0; i<TotalNum; i++){
        #pragma omp critical
        {
            count_flag ++;
            if(count_flag % 500000 == 0) cout << "   LOG:" << count_flag << "/" << TotalNum << " --> " << float(count_flag)/float(TotalNum)*100 << "%" << endl;
            if(count_flag % TotalNum == 0) cout << "   LOG:" << count_flag << "/" << TotalNum << " --> " << float(count_flag)/float(TotalNum)*100 << "%" << endl;
        }
        // 1. 正向循环状态
        string Read_0 = Data[i].substr(0, RLength) + Data[i].substr(0,RLength);
        unsigned long hashValue = 0;
        if(Func_R0(Read_0, i, hashValue) == 1) continue;

        // 2. 补序列状态
        string Read_1 = Read_0.substr(0, 2*RLength);
        for(int j=0; j<2*RLength; j++){
            if(Read_1[j] == 'A') Read_1[j]='T';
            else if(Read_1[j] == 'C') Read_1[j]='G';
            else if(Read_1[j] == 'G') Read_1[j]='C';
            else if(Read_1[j] == 'T') Read_1[j]='A';
            else continue;
        }
        if(Func_R1(Read_1, i) == 1) continue;

        // 3. 逆序列循环状态
        reverse(Read_0.begin(), Read_0.end());
        if(Func_R2(Read_0, i) == 1) continue;

        // 4. 补序列逆循环状态
        reverse(Read_1.begin(), Read_1.end());
        if(Func_R3(Read_1, i) == 1) continue;

        // 5 更新
        if(Func_Update(hashValue, i) == 1) continue;
    }
    return 1;
}

int Func_File_Saving(string saveTempFileDir){
    //cout << "***************" << "saving files" << "*********************" << endl;
    string File_Name_reads = saveTempFileDir + "/reads.txt";
    string File_Name_id_1 = saveTempFileDir + "/id_1.txt";
    string File_Name_id_and_pos = saveTempFileDir + "/id_pos.txt";
    string File_Name_count = saveTempFileDir + "/count.txt";
    string File_Name_info = saveTempFileDir + "/info.txt";
    cout << "  File_Name_reads:" << File_Name_reads << endl;
    cout << "   File_Name_count:" << File_Name_count << endl;
    cout << "   File_Name_id_1:" << File_Name_id_1 << endl;
    cout << "   File_Name_id_and_pos:" << File_Name_id_and_pos << endl;
    cout << "   File_Name_info:" << File_Name_info << endl;
    ofstream Stream_read; Stream_read.open(File_Name_reads);
    ofstream Stream_id_1;   Stream_id_1.open(File_Name_id_1);
    ofstream Stream_id_and_pos; Stream_id_and_pos.open(File_Name_id_and_pos);
    ofstream Stream_count; Stream_count.open(File_Name_count);
    ofstream Stream_info; Stream_info.open(File_Name_info);
    for(auto it1 = chl.begin(); it1 != chl.end(); it1++){ // 外层unordered_map
        for(auto it2 = (it1->second).begin(); it2 != (it1->second).end(); it2++){ // 里层set<Fnode>
            Stream_read << Data[(*it2).id] << "\n";
            Stream_id_1 << (*it2).id << "\n";
            Stream_count << (*it2).cns.size() << "\n";
            FatherNum ++;
            for(auto it3 = (*it2).cns.begin(); it3 != (*it2).cns.end(); it3++){
                Stream_id_and_pos << (*it3).id << "\n" << (*it3).pos << "\n";
            }

        }
    }
    Stream_info << TotalNum << "\n";
    Stream_info << FatherNum << "\n";
    Stream_info << RLength << "\n";
    Stream_read.close();
    Stream_count.close();
    Stream_id_and_pos.close();
    Stream_id_1.close();
    Stream_info.close();
    cout << "   FatherNum : " << FatherNum << endl;
    return 1;
}

