#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QMessageBox>
#include "bigtext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static DWORD WINAPI ThreadFunc(LPVOID p)//потоковая функция с помощью функции ожидания отслеживает
                                            //периодические срабатывания таймера и генерирует заявки серверу
    {
        wchar_t lpNamedPipeName[]=L"\\\\.\\Pipe\\MyNamedPipe";
        DWORD dwDesiredAccess=GENERIC_READ | GENERIC_WRITE;
        DWORD dwShareMode=0;
        LPSECURITY_ATTRIBUTES lpSecurityAttributes=0;//дескриптор не наследуется
        DWORD dwCreationDisposition=OPEN_EXISTING;
        DWORD dwFlagsAndAttributes=FILE_ATTRIBUTE_NORMAL;
        HANDLE hTemplateFile=0;
        HANDLE hNamedPipe;

        //QString* pStr=reinterpret_cast<QString*>(p);
        QString* pStr=reinterpret_cast<BigText*>(p)->getString();
        QString text=*pStr;
        DWORD dwWrite;
        QByteArray buf;
        buf.append(text);
        buf.resize(256);

        while(true)
        {
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        WaitForSingleObject(hTimer, INFINITE);//при срабатывании таймера поток пробуждается
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

            //------------------------------------------подключаемся к именованному каналу-------------------------------------------
                    hNamedPipe=CreateFile(
                                                 lpNamedPipeName,//имя канала
                                                 dwDesiredAccess,//режим использования канала клиентом (должен быть согласован
                                                                 //с параметром dwOpenMode CreateNamedPipe() создания канала:
                                                                 //GENERIC_READ - чтение данных
                                                                 //GENERIC_WRITE - запись данных
                                                                 //GENERIC_READ | GENERIC_WRITE - запись и чтение)
                                                 dwShareMode,//должен быть 0, т.к. в каждый момент времени только один клиент
                                                             //может обращаться с одной из реализаций сервера
                                                 lpSecurityAttributes,//защита и возможность наследования
                                                 dwCreationDisposition,//должен быть OPEN_EXISTING, т.к.  речь идёт о подключении
                                                                       //к существующему каналу
                                                 dwFlagsAndAttributes,//всегда должны быть установлены в FILE_ATTRIBUTE_NORMAL
                                                 hTemplateFile//должен быть 0, т.к. данный параметр не имеет отношения к именованным каналам
                                );
                 //------------------по умолчанию клиент создаётся в байтовом режиме обмена данными (PIPE_READMODE_BYTE) и блокирующем режиме
                 //ожидания (PIPE_WAIT), для изменения этих режимов следует вызвать функцию SetNamedPipeHandleState--------------------------

                        //по тику таймера повзаимодейтсвовать и отключиться

            if(hNamedPipe!=INVALID_HANDLE_VALUE)//если подключились к каналу
            {
                //----------------------------------------------пишем в канал------------------------------------------------------------------

                            WriteFile(hNamedPipe,//a handle
                                      buf.data()/*lpBuffer*/,//a pointer to the buffer containing the data to be written to the file or device
                                      buf.length()/*nNumberOfBytesToWrite*/,//the number of bytes to be written to the file or device
                                      &dwWrite/*lpNummberOfBytesWritten*/,//a pointer to the variable that receives the number of bytes written when using
                                      //a synchronous hFile parameter. WriteFile sets this value to zero before doing any work or error checking.
                                      //use NULL for this parameter if this is an asynchronous operation to avoid potentially erroneous results.
                                      //this parameter can be NULL only when the lpOverlapped parameter is not NULL
                                      0//lpOverlapped. a pointer to an OVERLAPPED structure is required if the hFile parameter was opened with
                                      //FILE_FLAG_OVERLAPPED? otherwise this parameter can be NULL.
                                      );
                            buf.resize(dwWrite);

                //--------------------------------------------читаем из канала-----------------------------------------------------------------

                            DWORD dwRead;
                            QByteArray buf;
                            buf.resize(256);
                                ReadFile(hNamedPipe,
                                         buf.data(),
                                         buf.length(),
                                         &dwRead,
                                         0
                                         );
                                buf.resize(dwRead);

                                emit reinterpret_cast<BigText*>(p)->sendSignal(buf);

                //--------------------------------------------закрываем канал------------------------------------------------------------------
                                CloseHandle(hNamedPipe);
        }
}
        delete pStr;//удаляем динамически созданный объект QString в динамически созданном объекте BigText
        delete reinterpret_cast<BigText*>(p);
        return 0;
    }

private slots:
    void on_pushButtonCreatePipe_2_clicked();

    void on_pushButtonCloseHandle_2_clicked();

    void needUpdatePlainText(QByteArray q);

private:
    Ui::MainWindow *ui;

    static HANDLE hTimer;//дескриптор таймера
    QString* m_pText;//текст для отправки клиентом серверу
    HANDLE hThreadGlobal;
    BigText* m_bigString;

    static int counter;
};

#endif // MAINWINDOW_H
