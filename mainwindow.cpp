#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debugger.h"
#include "interfacememory.h"
#include "interfacedisasm.h"
#include "dialogboxwaitfordisasm.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    debug_stats=false;
    Debugger::mainWindow=this;
    ui->setupUi(this);
    InitUi();
    DisasmInterface =new InterfaceDisasm(this->ui->plainTextEdit_ASM);
    LoadsOrSaves=false;
}

void MainWindow::InitUi(){

    QList<int> Split_sz;
    Split_sz << 200 << 50;
    ui->splitter_2->setSizes(Split_sz);
/*
    QSplitter* mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(ui->tabWidget);
    mainSplitter->addWidget(ui->plainTextEditMEMDMP);
    mainSplitter->setStretchFactor(3, 1);
    setCentralWidget(mainSplitter);

    Split_sz[0]=300;
    Split_sz[1]=50;
    mainSplitter->setSizes(Split_sz);

  */
  //setting up registers tab:
    ui->treeWidget_REGISTERS->setColumnCount(2);
    QStringList TreeLabels;
    TreeLabels << "Registers" << "Value";
    ui->treeWidget_REGISTERS->setHeaderLabels(TreeLabels);
    ui->statusBar->showMessage(tr("Welcome"));
    InitRegs();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateRegs()
{

    IP->setText(1,QString::number(Debugger::GetRegisterIP(),16));
    stack->setText(1,QString::number(Debugger::GetRegisterSTACK(),16));
    N1->setText(1,QString::number(Debugger::GetRegisterN1(),16));
    N2->setText(1,QString::number(Debugger::GetRegisterN2(),16));
    N3->setText(1,QString::number(Debugger::GetRegisterN3(),16));
    R0->setText(1,QString::number(Debugger::GetRegisterR0(),16));
    R1->setText(1,QString::number(Debugger::GetRegisterR1(),16));
    R2->setText(1,QString::number(Debugger::GetRegisterR2(),16));
    R3->setText(1,QString::number(Debugger::GetRegisterR3(),16));
    R4->setText(1,QString::number(Debugger::GetRegisterR4(),16));
    R5->setText(1,QString::number(Debugger::GetRegisterR5(),16));
    R6->setText(1,QString::number(Debugger::GetRegisterR6(),16));
    R7->setText(1,QString::number(Debugger::GetRegisterR7(),16));
    R8->setText(1,QString::number(Debugger::GetRegisterR8(),16));
    R9->setText(1,QString::number(Debugger::GetRegisterR9(),16));
    Ra->setText(1,QString::number(Debugger::GetRegisterRa(),16));
    Rb->setText(1,QString::number(Debugger::GetRegisterRb(),16));
    Rc->setText(1,QString::number(Debugger::GetRegisterRc(),16));
    Rd->setText(1,QString::number(Debugger::GetRegisterRd(),16));
    Re->setText(1,QString::number(Debugger::GetRegisterRe(),16));
    Rf->setText(1,QString::number(Debugger::GetRegisterRf(),16));
    R10->setText(1,QString::number(Debugger::GetRegisterR10(),16));
    R11->setText(1,QString::number(Debugger::GetRegisterR11(),16));
    R12->setText(1,QString::number(Debugger::GetRegisterR12(),16));
    R13->setText(1,QString::number(Debugger::GetRegisterR13(),16));
    R14->setText(1,QString::number(Debugger::GetRegisterR14(),16));



}

void MainWindow::InitRegs()
{
    Data_Rtab = new QTreeWidgetItem(ui->treeWidget_REGISTERS);
    Data_Rtab->setText(0, "DATA REGS");
    Data_Rtab->setText(1, " ");
    ui->treeWidget_REGISTERS->addTopLevelItem(Data_Rtab);

    Main_rtab = new QTreeWidgetItem(ui->treeWidget_REGISTERS);
    Main_rtab->setText(0, "MAIN REGS");
    Main_rtab->setText(1, " ");
    ui->treeWidget_REGISTERS->addTopLevelItem(Main_rtab);

    IP = new QTreeWidgetItem();
    IP->setText(0, "IP ");
    IP->setText(1,"0");
    Main_rtab->addChild(IP);

    stack = new QTreeWidgetItem();
    stack->setText(0, "STACK ");
    stack->setText(1,"0");
    Main_rtab->addChild(stack);

    N1 = new QTreeWidgetItem();
    N1->setText(0, "N1 ");
    N1->setText(1,"0");
    Main_rtab->addChild(N1);

    N2 = new QTreeWidgetItem();
    N2->setText(0, "N2 ");
    N2->setText(1,"0");
    Main_rtab->addChild(N2);

    N3 = new QTreeWidgetItem();
    N3->setText(0, "N3 ");
    N3->setText(1,"0");
    Main_rtab->addChild(N3);

    R0 = new QTreeWidgetItem();
    R0->setText(0, "R0 ");
    R0->setText(1,"0");
    Data_Rtab->addChild(R0);

    R1 = new QTreeWidgetItem();
    R1->setText(0, "R1 ");
    R1->setText(1,"0");
    Data_Rtab->addChild(R1);

    R2 = new QTreeWidgetItem();
    R2->setText(0, "R2 ");
    R2->setText(1,"0");
    Data_Rtab->addChild(R2);

    R3 = new QTreeWidgetItem();
    R3->setText(0, "R3 ");
    R3->setText(1,"0");
    Data_Rtab->addChild(R3);

    R4 = new QTreeWidgetItem();
    R4->setText(0, "R4 ");
    R4->setText(1,"0");
    Data_Rtab->addChild(R4);

    R5 = new QTreeWidgetItem();
    R5->setText(0, "R5 ");
    R5->setText(1,"0");
    Data_Rtab->addChild(R5);

    R6 = new QTreeWidgetItem();
    R6->setText(0, "R6 ");
    R6->setText(1,"0");
    Data_Rtab->addChild(R6);

    R7 = new QTreeWidgetItem();
    R7->setText(0, "R7 ");
    R7->setText(1,"0");
    Data_Rtab->addChild(R7);

    R8 = new QTreeWidgetItem();
    R8->setText(0, "R8 ");
    R8->setText(1,"0");
    Data_Rtab->addChild(R8);

    R9 = new QTreeWidgetItem();
    R9->setText(0, "R9 ");
    R9->setText(1,"0");
    Data_Rtab->addChild(R9);

    Ra = new QTreeWidgetItem();
    Ra->setText(0, "Ra ");
    Ra->setText(1,"0");
    Data_Rtab->addChild(Ra);

    Rb = new QTreeWidgetItem();
    Rb->setText(0, "Rb ");
    Rb->setText(1,"0");
    Data_Rtab->addChild(Rb);

    Rc = new QTreeWidgetItem();
    Rc->setText(0, "Rc ");
    Rc->setText(1,"0");
    Data_Rtab->addChild(Rc);

    Rd = new QTreeWidgetItem();
    Rd->setText(0, "Rd ");
    Rd->setText(1,"0");
    Data_Rtab->addChild(Rd);

    Re = new QTreeWidgetItem();
    Re->setText(0, "Re ");
    Re->setText(1,"0");
    Data_Rtab->addChild(Re);

    Rf = new QTreeWidgetItem();
    Rf->setText(0, "Rf ");
    Rf->setText(1,"0");
    Data_Rtab->addChild(Rf);

    R10 = new QTreeWidgetItem();
    R10->setText(0, "R10 ");
    R10->setText(1,"0");
    Data_Rtab->addChild(R10);

    R11 = new QTreeWidgetItem();
    R11->setText(0, "R11 ");
    R11->setText(1,"0");
    Data_Rtab->addChild(R11);

    R12 = new QTreeWidgetItem();
    R12->setText(0, "R12 ");
    R12->setText(1,"0");
    Data_Rtab->addChild(R12);

    R13 = new QTreeWidgetItem();
    R13->setText(0, "R13 ");
    R13->setText(1,"0");
    Data_Rtab->addChild(R13);

    R14 = new QTreeWidgetItem();
    R14->setText(0, "R14 ");
    R14->setText(1,"0");
    Data_Rtab->addChild(R14);

}

void MainWindow::log(QString logged)
{
    ui->plainTextEdit_LOG->appendPlainText(logged);
}
bool MainWindow::restore_project(QString location)
{
    QString vm_asm;
    QFile project_file(location);
    if(!project_file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QDataStream input(&project_file);
    input.setVersion(QDataStream::Qt_5_4);
    input >> img_base;
    input >> machine_entry;
    input >> handler_1;
    input >> handler_2;
    input >> machine_quit;
    input >> vm_asm;
    ui->plainTextEdit_ASM->document()->setPlainText(vm_asm);
    input >> addresses;
    input >> bin_loc;
    project_file.close();
    LoadsOrSaves=true;
    return true;
}

bool MainWindow::save_project(QString location)
{
    QFile project_file(location);
    if(!project_file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QDataStream project_out(&project_file);
    project_out.setVersion(QDataStream::Qt_5_4);
    project_out << img_base << machine_entry << handler_1 << handler_2 << machine_quit;
    project_out << ui->plainTextEdit_ASM->document()->toPlainText();
    project_out << addresses;
    project_out << bin_loc;
    project_file.flush();
    project_file.close();
    LoadsOrSaves=true;
    return true;
}

void MainWindow::load_asm(QString file_loc)
{
    QFile asm_dump(file_loc);
    if(asm_dump.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream asm_stream(&asm_dump);
        QString asm_text = asm_stream.readAll();
      //  ui->textEdit_ASM->setText(asm_text);
        ui->plainTextEdit_ASM->document()->setPlainText(asm_text);
        asm_dump.close();
    }
}

void MainWindow::update_view(QString addr)
{
    DisasmInterface->HighLighLine(addr);
}

void MainWindow::on_actionOpen_Session_triggered()
{
    bool ok = false;
    QString read;
    std::string file_loc = "";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/",
                                                     tr("Executables (*.exe)"));

   QMessageBox::information(NULL, "Please wait", "please wait while the decompiler works.");
   bin_loc = fileName;

   log("loaded file: "+fileName);
   file_loc = fileName.toStdString();
   img_base = GetPE32Data((char*)file_loc.data(),0,UE_IMAGEBASE);
   log("retrieved PE image base: 0x"+ QString::number(img_base,16));

   while(ok==false)
   {
       read = QInputDialog::getText(this, tr("Machine Entry Point: "),
                                                        tr("machine ep rva (hex): "), QLineEdit::Normal,
                                                        NULL, &ok);
       if(read == false){
           return;
       }
       machine_entry = read.toInt(&ok,16);
   }

   log("machine ep (from user): 0x" + QString::number(machine_entry,16));
   ok = false;
   QMessageBox::information(this, "Information","Now you will enter the handlers. If there is only one you should enter the second with the same value as the first");

   while(ok==false)
   {
       read = QInputDialog::getText(this, tr("Machine Handler #1: "),
                                                        tr("machine h_1 rva (hex): "), QLineEdit::Normal,
                                                       NULL, &ok);
       if (read==false){
           return;
       }
       handler_1 = read.toInt(&ok,16);

   }

   log("machine handler #1 (from user): 0x" + QString::number(handler_1,16));
   ok =false;
   while(ok==false)
   {
       read = QInputDialog::getText(this, tr("Machine Handler #2: "),
                                                        tr("machine h_2 rva (hex): "), QLineEdit::Normal,
                                                        NULL, &ok);
       if (read == false)
       {
           return;
       }
       handler_2 = read.toInt(&ok,16);
   }

   log("machine handler #2 (from user): 0x" + QString::number(handler_2,16));
   ok = false;
   while(ok==false)
   {
       read = QInputDialog::getText(this, tr("Machine Exit Address: "),
                                                        tr("machine exit rva (hex): "), QLineEdit::Normal,
                                                       NULL, &ok);
       if (read == false){
           return;
       }
       machine_quit = read.toInt(&ok,16);
   }

   log("machine quit adress (from user): 0x" + QString::number(machine_quit,16));
   log("decompilation process started...");

   core_decompiler::NewDisasm(img_base,file_loc,machine_quit,handler_1, handler_2, machine_entry);
   core_decompiler::MakeDisasm("dump.txt");
   addresses=core_decompiler::GetTotalAddress();


   log("decompilation process ended..");
   load_asm("dump.txt");
   core_decompiler::Quit();
}

void MainWindow::on_actionSave_Session_triggered()
{
    QString sFile = QFileDialog::getSaveFileName(this,"Saving your project");
    if(sFile == NULL)
    {
        return;
    }
    if(!save_project(sFile))
    {
        QMessageBox::warning(this, "ERROR while saving!","could not save your project file.",QMessageBox::Ok, QMessageBox::Cancel);
    }

}

void MainWindow::on_actionRestore_Session_triggered()
{
    QString opFile = QFileDialog::getOpenFileName(this, "Opening your project");
    if (opFile == NULL)
    {
        return;
    }

    if(!restore_project(opFile))
    {
        QMessageBox::warning(this, "ERROR while loading!","could not load your project file.",QMessageBox::Ok, QMessageBox::Cancel);
    }

    log("Loaded Project File: " + opFile);
    log("machine ep: 0x" + QString::number(machine_entry,16));
    log("machine handler solver #1: 0x" + QString::number(handler_1,16));
    log("machine handler solver #2: 0x" + QString::number(handler_2,16));
    log("machine exit point: 0x" + QString::number(machine_quit,16));
    log("Binary Location: "+bin_loc);

}

void MainWindow::on_actionQuit_triggered()
{
   MainWindow::close();
}

void MainWindow::on_actionStart_Debugg_triggered()
{

    if (!LoadsOrSaves)
    {
        QMessageBox::information(this, "Warning", "your session must have been saved before you can continue");
    }

    if (debug_stats){
        debugMessage("Debugger already started.");
        return;
    }

    DisasmInterface->ToTop();
    debug_stats=true;
    Debugger::Start(bin_loc,addresses,machine_entry,machine_quit);
    this->MemDumper = new InterfaceMemory(ui->plainTextEdit_MEMORY,Debugger::GetHandle());

}

void MainWindow::on_actionStop_Debugg_triggered()
{
    if (!debug_stats){
        debugMessage("Debugger not initialized.");
        return;
    }
    debug_stats=false;
    Debugger::Stop();
    delete this->MemDumper;
    this->MemDumper= NULL;
}

void MainWindow::on_actionBaby_Step_triggered()
{
    if(!debug_stats){
        debugMessage("Debugger not initialized");
        return;
    }
    Debugger::Step();
    UpdateRegs();
}

void MainWindow::debugMessage(QString msg){
      ui->statusBar->showMessage(msg);
}

void MainWindow::disasmLine(QString address){
    update_view(address);
}

void MainWindow::on_actionGiant_Step_triggered()
{
    if(!debug_stats){
        debugMessage("Debugger not initialized");
        return;
    }


    Debugger::Step();
    UpdateRegs();
    while(!addresses.contains(Debugger::GetRegisterIP())){
        Debugger::Step();
        UpdateRegs();
    }

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,
                             "About VMPDBG",
                             "Hello, \n This is an early alpha release of VMPDBG. I am sure I will add a lot of\n more code soon. Check the contents of the readme file for more details\n\n -xsrtsect 2015");
}

void MainWindow::on_actionDump_Memory_triggered()
{
    QString read;
    LPVOID VAloc=NULL;
    bool ok =false;

 QMessageBox::information(this, "Warning", "Dumping memory will take a while. Please be patient.");

    if (this->MemDumper!=NULL)
    {
        while(!ok)
        {
        read = QInputDialog::getText(this, tr("Memory Dumper"),
                                                         tr("VA: "), QLineEdit::Normal,
                                                        NULL,NULL);
        if (read==false){
            return;
        }
        VAloc = (LPVOID)read.toInt(&ok,16);
        }

        this->MemDumper->Dump(VAloc);


    }
}

void MainWindow::on_actionRun_triggered()
{
    if(!debug_stats){
        debugMessage("Debugger not initialized");
        return;
    }

    Debugger::Run();
    UpdateRegs();
}

void MainWindow::on_actionAdd_Breakpoint_triggered()
{
    QString read;
    bool ok = false;
    uint32_t vmip_ptr=0;

    read = QInputDialog::getText(this, tr("Insert Breakpoint"),
                                                     tr("Address: "), QLineEdit::Normal,
                                                    NULL,NULL);
    if(read==false)
    {
        return;
    }
    vmip_ptr=read.toInt(&ok, 16);

    if (!ok)
    {
        return;
    }

    Debugger::AddBp(vmip_ptr);
    QMessageBox::information(this,"Breakpoint Added","The brakpoint has been Added.");
}

void MainWindow::on_actionRemove_Breakpoint_triggered()
{
    QString read;
    bool ok = false;
    uint32_t vmip_ptr=0;

    read = QInputDialog::getText(this, tr("Insert Breakpoint"),
                                                     tr("Address: "), QLineEdit::Normal,
                                                    NULL,NULL);
    if(read==false)
    {
        return;
    }
    vmip_ptr=read.toInt(&ok, 16);

    if (!ok)
    {
        return;
    }

    Debugger::RemoveBp(vmip_ptr);

    QMessageBox::information(this,"Breakpoint Removed","The brakpoint has been removed.");
}
