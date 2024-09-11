#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <vector>
#include <iostream>
#include <windows.h>
#include "single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct SelfAsm {
    int mnemonicIndex;
    char* opBit1;
    char* op1;
    char* opBit2;
    char* op2;
};

struct BofPayload {
    map<string, int> bofFuncOffsetMap;
    char* obfMap;
    PVOID pRdata;
    int rdataLength;
    char* selfAsm;
    int selfAsmLength; // SelfAsm �ṹ������
    map<int, DWORD_PTR> vtAddrMap; // index -> �����ַ
    map<DWORD_PTR, int> indexMap; // �����ַ -> index
    map<DWORD_PTR, SelfAsm*> selfAsmMap; // �����ַ -> �Զ�����
    vector<PVOID> relocPtrVector;
};

void ParsePayload(char* payload, int payloadLength, BofPayload& bofPayload);
void MagicInvoke(char* bofFuncName, char*& commandPara, int commandParaLength, char*& outputData, int& outputDataLength, PVOID* specialParaList, BofPayload& bofPayload);

#endif