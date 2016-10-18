#include "debugger.h"
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
#include <QString>
#include <QMessageBox>
#include <set>
#include "mainwindow.h"


namespace Debugger
{
MainWindow* mainWindow;
debug_thread* debugThread;
PROCESS_INFORMATION* pi;
std::set<uintptr_t> BreakPoints;

/*Registers*/

HANDLE GetHandle(){
    while(!debugThread->bUpdate())
    {

    }
    return pi->hProcess;
}

uint32_t GetRegisterIP(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->IP;
}

uint32_t GetRegisterSTACK(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->stack;
}

uint32_t GetRegisterN1(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->N1;
}

uint32_t GetRegisterN2(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->N2;
}

uint32_t GetRegisterN3(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->N3;
}

uint32_t GetRegisterR0(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R0;
}

uint32_t GetRegisterR1(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R1;
}

uint32_t GetRegisterR2(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R2;
}

uint32_t GetRegisterR3(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R3;
}

uint32_t GetRegisterR4(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R4;
}

uint32_t GetRegisterR5(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R5;
}

uint32_t GetRegisterR6(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R6;
}

uint32_t GetRegisterR7(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R7;
}

uint32_t GetRegisterR8(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R8;
}

uint32_t GetRegisterR9(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R9;
}

uint32_t GetRegisterRa(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Ra;
}

uint32_t GetRegisterRb(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Rb;
}

uint32_t GetRegisterRc(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Rc;
}

uint32_t GetRegisterRd(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Rd;
}

uint32_t GetRegisterRe(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Re;
}

uint32_t GetRegisterRf(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->Rf;
}

uint32_t GetRegisterR10(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R10;
}

uint32_t GetRegisterR11(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R11;
}


uint32_t GetRegisterR12(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R12;
}

uint32_t GetRegisterR13(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R13;
}

uint32_t GetRegisterR14(){
    while(!debugThread->bUpdate())
    {

    }
    return debugThread->R14;
}

uint32_t debug_thread::Load32(uint8_t* value){
    return (value[3] << (8 * 3)) | (value[2] << (8 * 2)) | (value[1] << 8) | value[0];
}

uint32_t debug_thread::ReadStack32(int index)
{
    unsigned char stack[8];
    ReadProcessMemory(pi->hProcess, (void*)(GetContextData(UE_EBP)+index*4), stack, 4, NULL);
    return Load32(stack);
}

uint32_t debug_thread::ReadDataReg32(int index)
{
    unsigned char segment[8];
    ReadProcessMemory(pi->hProcess, (void*)(GetContextData(UE_EDI)+index*4), segment, 4, NULL);
    return Load32(segment);
}

void debug_thread::UpdateRegs()
{
    //ESI - IP
    //EDI - data regs
    //EBP - machine stack
/*
    while(!debugThread->bUpdate())
    {
        Sleep(100);
    }
*/
    debugThread->IP = GetContextData(UE_ESI);
    debugThread->stack = GetContextData(UE_EBP);
    debugThread->N1 = ReadStack32(0);
    debugThread->N2 = ReadStack32(1);
    debugThread->N3 = ReadStack32(2);

    debugThread->R0=ReadDataReg32(0);

    debugThread->R1=ReadDataReg32(1);

    debugThread->R2=ReadDataReg32(2);

    debugThread->R3=ReadDataReg32(3);

    debugThread->R4=ReadDataReg32(4);

    debugThread->R5=ReadDataReg32(5);

    debugThread->R6=ReadDataReg32(6);

    debugThread->R7=ReadDataReg32(7);

    debugThread->R8=ReadDataReg32(8);

    debugThread->R9=ReadDataReg32(9);

    debugThread->Ra=ReadDataReg32(10);

    debugThread->Rb=ReadDataReg32(11);

    debugThread->Rc=ReadDataReg32(12);

    debugThread->Rd=ReadDataReg32(13);

    debugThread->Re=ReadDataReg32(14);

    debugThread->Rf=ReadDataReg32(15);

    debugThread->R10=ReadDataReg32(16);

    debugThread->R11=ReadDataReg32(17);

    debugThread->R12=ReadDataReg32(18);

    debugThread->R13=ReadDataReg32(19);

    debugThread->R14=ReadDataReg32(20);

   // debugThread->sbUpdate(false);
}

void waitForAction()
{
    debugThread->wait();
}


void cbOnVmEp(){
    if(debugThread->brun)
    {
        uint32_t vm_ptr = GetContextData(UE_ESI);
        if (BreakPoints.count(vm_ptr))
        {
            debugThread->log("Breakpoint reached.");
            debugThread->senduiIP(QString::number(GetContextData(UE_ESI),16));
            debugThread->UpdateRegs();
            debugThread->sbUpdate(true);
            debugThread->brun=false;
            waitForAction();
        }
        return;
    }

    debugThread->log("VM at: " + QString::number(GetContextData(UE_ESI),16));
    debugThread->senduiIP(QString::number(GetContextData(UE_ESI),16));
    debugThread->UpdateRegs();
    debugThread->sbUpdate(true);
    waitForAction();
}

void cbOnVmHalt(){
    debugThread->log("The VM halted.");
    StopDebug();
}

void cbOnCreateProcess(void* ExceptionData)
{
    SetCustomHandler(UE_CH_CREATEPROCESS, NULL);
    SetBPX(debugThread->GetEp(), UE_BREAKPOINT, &cbOnVmEp);
    SetBPX(debugThread->GetHaltPoint(), UE_BREAKPOINT, &cbOnVmHalt);
    debugThread->log("Debugger Started!");
}


debug_thread::debug_thread(QString file, QSet<unsigned int> addr_ref, uint32_t machine_processor, uint32_t machine_halt)
{
    this->file = file;
    this->bWaiting = false;
    this->_bUpdate = false;
    this->references = addr_ref;
    this->image_base = GetPE32Data((char*)file.toUtf8().constData(),0,UE_IMAGEBASE);
    this->machine_ep = machine_processor+image_base;
    this->machine_outpoint = machine_halt+image_base;
    this->state = false;

}

void debug_thread::log(QString msg)
{
    emit message(msg);
}


void debug_thread::senduiIP(QString addr)
{
    emit InstructionPointer(addr);
}

void debug_thread::wait()
{
    bWaiting = true;
    while(bWaiting) Sleep(100);
}

void debug_thread::resume()
{
    bWaiting = false;
}

void debug_thread::run()
{
    pi=(PROCESS_INFORMATION*)InitDebug((char*)file.toUtf8().constData(), 0, 0);
    if(!pi)
        log("> InitDebug failed!");
    else
    {
        log("> " + file + " loaded!");
        SetCustomHandler(UE_CH_CREATEPROCESS, (void*)cbOnCreateProcess);
        DebugLoop();
        log("> finished!");
    }
}


void Start(QString file, QSet<unsigned int> addr_ref, uint32_t machine_processor, uint32_t machine_halt)
{
    BreakPoints.clear();
    debugThread = new debug_thread(file, addr_ref, machine_processor, machine_halt);
    mainWindow->connect(debugThread, SIGNAL(message(QString)), mainWindow, SLOT(debugMessage(QString)));
    mainWindow->connect(debugThread, SIGNAL(InstructionPointer(QString)), mainWindow, SLOT(disasmLine(QString)));
    debugThread->start();
    debugThread->brun=false;
}

void Stop()
{

    StopDebug();
    debugThread->resume();
}

void Step()
{
    debugThread->sbUpdate(false);
    debugThread->resume();
}

void Run()
{

    debugThread->brun=true;
    debugThread->sbUpdate(false);
    debugThread->resume();
}

void AddBp(uint32_t address)
{
    BreakPoints.insert(address);

}

void RemoveBp(uint32_t address)
{
    BreakPoints.erase(address);
}


}

