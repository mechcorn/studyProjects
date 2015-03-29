#ifndef BIGHANDLE_H
#define BIGHANDLE_H

#include <QObject>
#include <windows.h>
#include <QByteArray>

class BigHandle : public QObject
{
    Q_OBJECT
public:
    explicit BigHandle(QObject *parent = 0);

    void setHandle(HANDLE h);
    HANDLE getHandle();

    void setWidget(QWidget* qw);
    QWidget* getWidget();

    void sendSignal(QByteArray mes);//посылка сигнала

signals:
    void needAdd(QByteArray mes);//сигнал о необходимости добавить подтверждение в окне GUI

public slots:

private:
    HANDLE m_h;
    QWidget* m_qw;//указатель на окно пользовательского интерфейса
};

#endif // BIGHANDLE_H
