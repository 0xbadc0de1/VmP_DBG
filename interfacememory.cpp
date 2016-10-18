#include "interfacememory.h"
#include <QString>
InterfaceMemory::InterfaceMemory(QPlainTextEdit* _screen, HANDLE _hprocess)
{
    screen=_screen;
    hprocess=_hprocess;
}

QString InterfaceMemory::Convert(uint8_t* memory){
    QString demp="";
    for(int i =0;i<16;i++){
        if (((memory[i] >= 0x30) && (memory[i]<=0x39)) || ((memory[i] >= 'a') && (memory[i]<='z')) || ((memory[i] >= 'A') && (memory[i]<='Z')))
        {
            QString chr;
            char u[3];
            u[0] = memory[i];
            u[1]=0;
            chr.sprintf("%s", &u);
            demp+= chr;
        }
        else
        {

            demp+= ".";
        }
    }
  return demp;
}

int InterfaceMemory::Dump(LPVOID addr)
{
    MEMORY_BASIC_INFORMATION meminfo;
    uint8_t* memory;
    SIZE_T nbytes=0;
    QString TextDump = "";

    if (!VirtualQueryEx(hprocess,addr, &meminfo, sizeof(MEMORY_BASIC_INFORMATION)))
    {
        return 0;
    }

    memory = (uint8_t*)malloc(0x1000);

    if (meminfo.State==MEM_COMMIT)
    {

        if (meminfo.Type==MEM_MAPPED || meminfo.Type==MEM_PRIVATE || meminfo.Type==MEM_IMAGE)
        {
            if(meminfo.RegionSize>0x1000){
                meminfo.RegionSize=0x1000;
            }
            ReadProcessMemory(hprocess, addr, memory, meminfo.RegionSize,&nbytes);
            if (nbytes!=0){
                 QString ascii="";
                for(int i=0; i< meminfo.RegionSize; i++)
                {

                    if((i%16)==0)
                    {
                        TextDump+= "| "+ascii;
                        TextDump+="\n " + QString::number((uint32_t)addr+i,16)+ "|";
                        ascii=Convert(memory+i);
                    }
                    QString b;
                    b.sprintf("%02X", memory[i]);
                    TextDump += " "+b;

                    screen->document()->setPlainText(TextDump);
                }
                free(memory);
                return 1;
            }

            free(memory);
            return 1;
        }

            free(memory);
            return 0;
    }


    free(memory);
    return 0;
}
