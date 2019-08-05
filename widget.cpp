#include "widget.h"
#include<QPainter>
#include<QImage>
#include<windows.h>
#include <QPalette>
#include<QMouseEvent>
#include<QMessageBox>
#include<QApplication>
#include<QRect>
#include<QDesktopWidget>
#include<QFile>
#include<QTextStream>
#include <QFileDialog>
#include<QDebug>
#include<QPixmap>
#include"windows.h"
static HWND g_workerw =0;

static BOOL CALLBACK EnumWndCallback(HWND tophandle,LPARAM topparamhandle)
{
    HWND p=FindWindowEx(tophandle,0,L"SHELLDLL_DefView",0);
    if (p!=0)
    {
        g_workerw=FindWindowEx(0,tophandle,L"WorkerW",0);
    }

    return true;
}
Widget::Widget(QWindow *parent) : QWindow(parent),store(this)
{
    HWND hwnProgram=FindWindow(L"Progman",L"Program Manager");
    SendMessageTimeout(hwnProgram,0x052C,0,0,SMTO_NORMAL,1000,0);
    EnumWindows(EnumWndCallback,0);

    if(g_workerw==0)
    {
        abort();
    }
    QWindow *windowDesktop=QWindow::fromWinId((WId)g_workerw);

    this->setParent(windowDesktop);

    this->show();
}

Widget::~Widget()
{

}

bool Widget::event(QEvent *e)
{
    if(e->type()==QEvent::Expose||e->type()==QEvent::Resize)
    {
        QImage image("1.jpg");
        QRect rect(QPoint(0,0),this->size());
        store.resize(this->size());
        store.beginPaint(rect);
        QPainter painter(store.paintDevice());
        painter.fillRect(rect,Qt::white);
        painter.drawImage(0,0,image);
        store.endPaint();
        store.flush(rect);

    }
    return QWindow::event(e);

}
