#include "mainwindow.h"

#include <QApplication>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <Xatom.h>
#include <NETWM>
#include <QTime>

void setBypassCompositor(WId wId, long comp)
{

    long compositor = comp;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    _NET_WM_BYPASS_COMPOSITOR = XInternAtom(QX11Info::display(), "_NET_WM_BYPASS_COMPOSITOR", false);
    XChangeProperty(QX11Info::display(), wId, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL,
                    32, XCB_PROP_MODE_REPLACE, (const unsigned char *) &compositor, 1);

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
//    w->setWindowFlags(Qt::FramelessWindowHint);
    setBypassCompositor(w->window()->winId(), 1);
    w->show();
    QTime delayTime = QTime::currentTime().addMSecs(1000);
    while(QTime::currentTime() < delayTime);
    w->hide();
    QTime delayTime1 = QTime::currentTime().addMSecs(1000);
    while(QTime::currentTime() < delayTime1);
    setBypassCompositor(w->window()->winId(), 2);
    w->show();
    return a.exec();
}
