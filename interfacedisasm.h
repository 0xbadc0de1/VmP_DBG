#include <QTextDocument>
#include <QTextStream>
#include <QMainWindow>
#include <QPlainTextEdit>
#include "mainwindow.h"
#ifndef INTERFACEDISASM_H
#define INTERFACEDISASM_H


class InterfaceDisasm{
private:
    QPlainTextEdit* screen;
    QTextCursor current_cursor;
public:
    InterfaceDisasm(QPlainTextEdit* _screen);
    void HighLighLine(QString addr);
    void ToTop();
};

#endif // INTERFACEDISASM_H

