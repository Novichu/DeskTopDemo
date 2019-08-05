#ifndef WIDGET_H
#define WIDGET_H

#include <QWindow>
#include<QBackingStore>

class Widget : public QWindow
{


public:
    explicit Widget(QWindow *parent = nullptr);
    ~Widget();

    bool event(QEvent *);
private:
   QBackingStore store;
};

#endif // WIDGET_H
