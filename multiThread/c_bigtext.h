#ifndef BIGTEXT_H
#define BIGTEXT_H

#include <QObject>
#include <QString>

class BigText : public QObject
{
    Q_OBJECT
public:
    explicit BigText(QObject *parent = 0);
    void setString(QString* pStr);
    QString* getString();
    void setWidget(QWidget* qw);
    QWidget* getWidget();

    void sendSignal(QByteArray mes);//посылка сигнала

signals:
    void needAdd(QByteArray mes);//сигнал о необходимости добавить подтверждение в окне GUI

public slots:

private:
    QString* m_pTextForGui;//текст для отправки в gui клиента
    QWidget* m_qw;//указатель на окно пользовательского интерфейса

};

#endif // BIGTEXT_H
