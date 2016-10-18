#include "dialogboxwaitfordisasm.h"
#include "ui_dialogboxwaitfordisasm.h"

DialogBoxWaitForDisasm::DialogBoxWaitForDisasm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBoxWaitForDisasm)
{
    ui->setupUi(this);
}

DialogBoxWaitForDisasm::~DialogBoxWaitForDisasm()
{
    delete ui;
}
