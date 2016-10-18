#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _WIN32_WINNT 0x0601
#include <QMainWindow>
#include <QString>
#include <QTextDocument>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QSet>

#include "core_decompiler.h"
#include "interfacedisasm.h"
#include "interfacememory.h"
#include <stdint.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void log(QString logged);
    void load_asm(QString file_loc);
    void update_view(QString addr);
    bool save_project(QString location);
    bool restore_project(QString location);
    void InitRegs();
    void UpdateRegs();


private slots:
    void on_actionOpen_Session_triggered();

    void on_actionSave_Session_triggered();

    void on_actionRestore_Session_triggered();

    void on_actionQuit_triggered();

    void on_actionStart_Debugg_triggered();

    void on_actionStop_Debugg_triggered();

    void on_actionBaby_Step_triggered();

   void debugMessage(QString msg);
   void disasmLine(QString address);

   void on_actionGiant_Step_triggered();

   void on_actionAbout_triggered();

   void on_actionDump_Memory_triggered();

   void on_actionRun_triggered();

   void on_actionAdd_Breakpoint_triggered();

   void on_actionRemove_Breakpoint_triggered();

private:

   void InitUi();
    bool LoadsOrSaves;
    bool debug_stats;
    Ui::MainWindow *ui;
    uint32_t img_base;
    uint32_t machine_entry;
    uint32_t handler_1;
    uint32_t handler_2;
    uint32_t machine_quit;
    QSet<uint32_t> addresses;
    QString bin_loc;
    InterfaceDisasm* DisasmInterface;
    InterfaceMemory* MemDumper;

    //machine registers (UI);
    QTreeWidgetItem* Data_Rtab;
    QTreeWidgetItem* Main_rtab;
    QTreeWidgetItem* IP;
    QTreeWidgetItem* stack;
    QTreeWidgetItem* N1;
    QTreeWidgetItem* N2;
    QTreeWidgetItem* N3;

    QTreeWidgetItem* R0;
    QTreeWidgetItem* R1;
    QTreeWidgetItem* R2;
    QTreeWidgetItem* R3;
    QTreeWidgetItem* R4;
    QTreeWidgetItem* R5;
    QTreeWidgetItem* R6;
    QTreeWidgetItem* R7;
    QTreeWidgetItem* R8;
    QTreeWidgetItem* R9;
    QTreeWidgetItem* Ra;
    QTreeWidgetItem* Rb;
    QTreeWidgetItem* Rc;
    QTreeWidgetItem* Rd;
    QTreeWidgetItem* Re;
    QTreeWidgetItem* Rf;
    QTreeWidgetItem* R10;
    QTreeWidgetItem* R11;
    QTreeWidgetItem* R12;
    QTreeWidgetItem* R13;
    QTreeWidgetItem* R14;

};

#endif // MAINWINDOW_H
