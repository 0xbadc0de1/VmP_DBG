#include "interfacedisasm.h"

InterfaceDisasm::InterfaceDisasm(QPlainTextEdit* _screen)
{
    screen=_screen;
    current_cursor = _screen->textCursor();
    current_cursor.movePosition(QTextCursor::Start,  QTextCursor::MoveAnchor); // moves the cursor to the top
    screen->setTextCursor(current_cursor); //sets the pain text edit cursor to the top

}
void InterfaceDisasm::HighLighLine(QString addr)
{

    screen->setTextCursor(current_cursor);
   screen->find(addr); //finds addr string now cursor should be on the found line
   current_cursor = screen->textCursor();

   QList<QTextEdit::ExtraSelection> Extra_selections; //create extra selections
   QTextEdit::ExtraSelection selection; //selection

   QColor line_color = QColor(Qt::cyan).darker(200);
   selection.format.setBackground(line_color);
   selection.format.setProperty(QTextFormat::FullWidthSelection, true);
   selection.cursor = current_cursor;
   selection.cursor.clearSelection();
   Extra_selections.append(selection);
   screen->setExtraSelections(Extra_selections); //formats selection stuff and applies to the current_cursor

}

void InterfaceDisasm::ToTop(){
    current_cursor.movePosition(QTextCursor::Start,  QTextCursor::MoveAnchor); // moves the cursor to the top
    screen->setTextCursor(current_cursor); //sets the pain text edit cursor to the top
}
