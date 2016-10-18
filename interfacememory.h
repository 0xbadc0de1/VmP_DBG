#include <QTextDocument>
#include <QTextStream>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <Windows.h>
#include "mainwindow.h"
#ifndef INTERFACEMEMORY_H
#define INTERFACEMEMORY_H


class InterfaceMemory{
private:
    QPlainTextEdit* screen;
    HANDLE hprocess;
public:
    InterfaceMemory(QPlainTextEdit* _screen, HANDLE _hprocess);
    QString Convert(uint8_t* memory);
    int Dump(LPVOID addr);
};

#endif // INTERFACEMEMORY_H

