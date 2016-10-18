#ifndef CORE_DECOMPILER
#define CORE_DECOMPILER
#define _WIN32_WINNT 0x0601
#include <stdio.h>
#include <tchar.h>
#include "sdk\SDK.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>
#include <unordered_map>
#include <QSet>


typedef unsigned int u32;
typedef unsigned char* memo;

namespace core_decompiler{

void NewDisasm(uint32_t _imagebase, std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start);
void MakeDisasm(std::string dump_file);
void Quit();
QSet<uint32_t> GetTotalAddress();


class vm{
private:
    long handler_1;
    long handler_2;
    long vm_out;
    long temp;
    long handler_start;

    /*
     * handler_f -> Temporary Variable to store the handler trace
     * eax_table -> Temporary vector that stores the eax trace result
     * current_handler -> just some temporary var
     * addresses -> Set of all adresses fetched
     * instruction_va -> va of current function
     */

    //instruction control reference

    void print_handler(std::vector<std::string> handler_to_print);

    //handlers
public:
    vm(std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start);
    vm(uint32_t _imagebase, std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start);
    void dump_handlers(std::string dump_file);
    void dump_instructions(std::string dump_file);

    QSet<uint32_t> addresses;
    std::vector<std::string> handler_f;
    std::vector<uint32_t> eax_table;
    uint32_t current_handler;
    uint32_t instruction_va;
    QSet<uint32_t> GetAddr();
    void ReconHandler();

    long GetEp(){
        return handler_start;
    }

    long GetH1(){
        return handler_1;
    }

    long GetH2(){
        return handler_2;
    }

    long GetVout(){
        return vm_out;
    }



};


}
#endif // CORE_DECOMPILER

