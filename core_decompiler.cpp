#define _WIN32_WINNT 0x0601
#include "core_decompiler.h"
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
#include "vm_instruction_set.h"

//handler declaration

std::ofstream dump_;
core_decompiler::vm* decompiler;
LPPROCESS_INFORMATION ProcessInfo;

u32 Load32(memo loc){
    return (loc[3] << (8 * 3)) | (loc[2] << (8 * 2)) | (loc[1] << 8) | loc[0];
}

void core_decompiler::NewDisasm(uint32_t _imagebase, std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start)
{
    decompiler = new core_decompiler::vm(_imagebase,full_path, _vm_out, _handler_1, _handler_2,_handler_start);
}

void core_decompiler::MakeDisasm(std::string dump_file)
{
    if (decompiler != NULL)
    {
        decompiler->dump_instructions(dump_file);
    }
}

void core_decompiler::Quit()
{
    delete decompiler;

}

QSet<uint32_t> core_decompiler::GetTotalAddress(){
    return decompiler->GetAddr();
}


void cbOnHStart(){
   decompiler->instruction_va= GetContextData(UE_ESI);
}



void cbOn_h1(){
    long next_handler = 0;
    unsigned char stack[8];

    next_handler = (long)GetContextData(UE_ESP);
    ReadProcessMemory(ProcessInfo->hProcess, (void*)next_handler, stack, 4, NULL);
    dump_ << "handle: " << std::hex << Load32(stack) << std::endl;
}

void cbOn_h2(){
    long next_handler = 0;
    unsigned char stack[8];

    next_handler = (long)GetContextData(UE_ESP);
    ReadProcessMemory(ProcessInfo->hProcess, (void*)next_handler, stack, 4, NULL);
    dump_ << "handle: " << std::hex << Load32(stack) << std::endl;
}

void cbOn_quit(){
    dump_ << "vm_quit" << std::endl;
    dump_.close();
    StopDebug();
}


void fetch_handler(){

    std::string disasm;
    static uint32_t eip_control = GetContextData(UE_EIP);
    eip_control = GetContextData(UE_EIP);
    disasm.assign((const char*)Disassemble((LPVOID)eip_control));
    decompiler->handler_f.push_back(disasm);
    decompiler->eax_table.push_back(GetContextData(UE_EAX));


    if (eip_control == decompiler->GetVout()+1){

        cbOn_quit();
    }

    if (eip_control != decompiler->GetEp()){
        StepInto(&fetch_handler);
    }

}

void cbOn_get_h(){
    unsigned char stack[8];

    if ( decompiler->handler_f.size() > 2){
         decompiler->ReconHandler();
    }
     decompiler->handler_f.clear();
     decompiler->eax_table.clear();
    //reads what is the handler, in case it is unknown:
    ReadProcessMemory(ProcessInfo->hProcess, (void*)GetContextData(UE_ESP), stack, 4, NULL);
     decompiler->current_handler = Load32(stack);

     dump_ << std::hex <<  decompiler->instruction_va << "|";
     decompiler->addresses << decompiler->instruction_va;
     fetch_handler();

}



void cbOnCreate_dump(LPCREATE_PROCESS_DEBUG_INFO lpCreateProcInfo){
    SetCustomHandler(UE_CH_CREATEPROCESS, NULL);
    SetBPX(decompiler->GetH1(), UE_BREAKPOINT, &cbOn_h1);
    SetBPX(decompiler->GetH2(), UE_BREAKPOINT, &cbOn_h2);
    SetBPX(decompiler->GetVout(), UE_BREAKPOINT, &cbOn_quit);
}

void cbOnCreateDisasm(LPCREATE_PROCESS_DEBUG_INFO lpCreateProcInfo){
    SetCustomHandler(UE_CH_CREATEPROCESS, NULL);
    SetBPX(decompiler->GetEp(), UE_BREAKPOINT, &cbOnHStart);
    SetBPX(decompiler->GetH1(), UE_BREAKPOINT, &cbOn_get_h);
    SetBPX(decompiler->GetH2(), UE_BREAKPOINT, &cbOn_get_h);
    SetBPX(decompiler->GetVout(), UE_BREAKPOINT, &cbOn_quit);
}



core_decompiler::vm::vm(uint32_t _imagebase, std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start){
    char* c_str = (char*)full_path.c_str();
    ProcessInfo = (LPPROCESS_INFORMATION)InitDebug(c_str, NULL, NULL);

    vm_out = _vm_out+_imagebase;
    handler_1 = _handler_1 + _imagebase;
    handler_2 = _handler_2 + _imagebase;
    handler_start = _handler_start + _imagebase;
    temp=0;
    handler_f= std::vector<std::string>{};
    eax_table = std::vector<uint32_t>{};
    addresses = QSet<uint32_t>{};
    current_handler=0;
    instruction_va=0;
    addresses.clear();
}

core_decompiler::vm::vm(std::string full_path, uint32_t _vm_out, uint32_t _handler_1, uint32_t _handler_2, uint32_t _handler_start){
    char* c_str = (char*)full_path.c_str();
    ProcessInfo = (LPPROCESS_INFORMATION)InitDebug(c_str, NULL, NULL);

    vm_out = _vm_out;
    handler_1 = _handler_1;
    handler_2 = _handler_2;
    handler_start = _handler_start;

    temp=0;
    handler_f= std::vector<std::string>{};
    eax_table = std::vector<uint32_t>{};
    addresses = QSet<uint32_t>{};
    current_handler=0;
    instruction_va=0;
    addresses.clear();
}


void core_decompiler::vm::dump_handlers(std::string dump_file){
    dump_.open(dump_file);
    SetCustomHandler(UE_CH_CREATEPROCESS, &cbOnCreate_dump);
    DebugLoop();
}

void core_decompiler::vm::dump_instructions(std::string dump_file){
    dump_.open(dump_file);
    SetCustomHandler(UE_CH_CREATEPROCESS, &cbOnCreateDisasm);
    DebugLoop();
}



void core_decompiler::vm::ReconHandler(){

    std::vector<uint32_t> match;
    std::vector<std::string> curr_hand;
    std::vector<uint32_t> wr;
    type_handler found;
    std::unordered_map<uint32_t, hashmap>::const_iterator got_from_htable = hashtable.find(current_handler);

    //std::cout << handler_f.size() << std::endl;

    if (got_from_htable != hashtable.end()){
        match = std::get<1>(hashtable[current_handler]);
        curr_hand = std::get<0>(hashtable[current_handler]);
        dump_ << curr_hand[0];
        if (curr_hand[1] != ""){
            dump_ << std::hex << eax_table[match[atol(curr_hand[1].c_str()) - 1]] / atol(curr_hand[1].c_str() + 2);
        }
        dump_ << std::endl;
        return;
    }

    int n_match = 2;

    for (int j = 0; j < good_handlers.size(); j++){
        curr_hand = good_handlers[j];
        n_match = 2;
        for (int i = 0; i < handler_f.size() && n_match != curr_hand.size(); i++){
            if (handler_f[i] == curr_hand[n_match]){
                match.push_back(i);
                n_match++;
                if (n_match == curr_hand.size()){
                    dump_ << curr_hand[0];
                    if (curr_hand[1] != ""){
                        dump_ << std::hex<< eax_table[match[atol(curr_hand[1].c_str()) - 1]] / atol(curr_hand[1].c_str()+2);
                    }
                    dump_ << std::endl;
                    hashtable[current_handler] = hashmap(curr_hand, match);
                    return;
                }
            }
        }
    }

    dump_ << " unknown handler: " <<std::hex << current_handler <<std::dec<< " match:" << n_match-2 << std::endl;
}

QSet<uint32_t> core_decompiler::vm::GetAddr()
{
    return addresses;
}

void core_decompiler::vm::print_handler(std::vector<std::string> handler_to_print){
    for (int i = 0; i < handler_to_print.size(); i++){
        std::cout << handler_to_print[i] << std::endl;
    }

}
