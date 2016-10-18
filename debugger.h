#ifndef DEBUGGER_H
#define DEBUGGER_H
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
#include <QThread>
#include <Windows.h>
#include "mainwindow.h"



namespace Debugger {

extern MainWindow* mainWindow;

HANDLE GetHandle();
void Stop();
void Start(QString file, QSet<unsigned int> addr_ref, uint32_t machine_processor, uint32_t machine_halt);
void Step();
void Run();

uint32_t GetRegisterIP();
uint32_t GetRegisterSTACK();

uint32_t GetRegisterN1();

uint32_t GetRegisterN2();

uint32_t GetRegisterN3();

uint32_t GetRegisterR0();

uint32_t GetRegisterR1();

uint32_t GetRegisterR2();

uint32_t GetRegisterR3();

uint32_t GetRegisterR4();

uint32_t GetRegisterR5();

uint32_t GetRegisterR6();

uint32_t GetRegisterR7();

uint32_t GetRegisterR8();

uint32_t GetRegisterR9();

uint32_t GetRegisterRa();

uint32_t GetRegisterRb();

uint32_t GetRegisterRc();

uint32_t GetRegisterRd();

uint32_t GetRegisterRe();

uint32_t GetRegisterRf();

uint32_t GetRegisterR10();

uint32_t GetRegisterR11();


uint32_t GetRegisterR12();

uint32_t GetRegisterR13();

uint32_t GetRegisterR14();

void AddBp(uint32_t address);

void RemoveBp(uint32_t address);

class debug_thread : public QThread{
    Q_OBJECT
public:
    debug_thread(QString file, QSet<unsigned int> addr_ref, uint32_t machine_processor, uint32_t machine_halt);
    void log(QString msg);
    void senduiIP(QString addr);
    void wait();
    void resume();
    uint32_t GetEp(){ return machine_ep; }
    uint32_t GetHaltPoint() { return machine_outpoint; }


    uint32_t IP=0;
    uint32_t stack=0;
    uint32_t N1=0;
    uint32_t N2=0;
    uint32_t N3=0;

    uint32_t R0=0;
    uint32_t R1=0;
    uint32_t R2=0;
    uint32_t R3=0;
    uint32_t R4=0;
    uint32_t R5=0;
    uint32_t R6=0;
    uint32_t R7=0;
    uint32_t R8=0;
    uint32_t R9=0;
    uint32_t Ra=0;
    uint32_t Rb=0;
    uint32_t Rc=0;
    uint32_t Rd=0;
    uint32_t Re=0;
    uint32_t Rf=0;
    uint32_t R10=0;
    uint32_t R11=0;
    uint32_t R12=0;
    uint32_t R13=0;
    uint32_t R14=0;
    void UpdateRegs();
    bool bUpdate() {return _bUpdate;}
    void sbUpdate(bool b) { _bUpdate=b;}


    volatile bool brun;
private:
    QString file;
    QSet<uint32_t> references;
    uint32_t machine_ep;
    uint32_t machine_outpoint;
    uint32_t image_base;

    /*Registers*/

    uint32_t Load32(uint8_t* value);
    uint32_t ReadStack32(int index);
    uint32_t ReadDataReg32(int index);



    volatile bool bWaiting;
    volatile bool _bUpdate;
    volatile bool state;

    void run();
signals:
    void message(QString msg);
    void InstructionPointer(QString addr);
};

}



#endif // CORE_DBG_H

