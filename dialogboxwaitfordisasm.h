#ifndef DIALOGBOXWAITFORDISASM_H
#define DIALOGBOXWAITFORDISASM_H

#include <QDialog>

namespace Ui {
class DialogBoxWaitForDisasm;
}

class DialogBoxWaitForDisasm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBoxWaitForDisasm(QWidget *parent = 0);
    ~DialogBoxWaitForDisasm();

private:
    Ui::DialogBoxWaitForDisasm *ui;
};

#endif // DIALOGBOXWAITFORDISASM_H
