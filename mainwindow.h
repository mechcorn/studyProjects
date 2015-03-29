#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QMessageBox>
#include "bighandle.h"
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static DWORD WINAPI ThreadClientInteract(LPVOID p)//потоковая функция для обмена с конкретным клиентом
    {
        HANDLE hP=reinterpret_cast<BigHandle*>(p)->getHandle();

        DWORD dwRead;
        DWORD dwWrite;

        QByteArray buf;
        buf.resize(256);

//------------------------------------читаем из реализации канала для конкретного клиента--------------------------------------
                ReadFile(hP,
                         buf.data(),
                         buf.length(),
                         &dwRead,
                         0
                         );
                buf.resize(dwRead);

                emit reinterpret_cast<BigHandle*>(p)->sendSignal(buf);

                buf.clear();
                QByteArray ok("Received");
                buf.append(ok);
                buf.resize(256);

                WriteFile(hP,//a handle
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
//---------------------------------------------отключение от канала и его закрытие---------------------------------------------
        //FlushFileBuffers(hP);
        DisconnectNamedPipe(hP);
        CloseHandle(hP);

        delete reinterpret_cast<BigHandle*>(p);

        return 0;
    }

    static DWORD WINAPI ThreadListening(LPVOID p)//потоковая функция для прослушивания (ожидание подключения клиентов)
    {
        QWidget* mainGui=reinterpret_cast<BigHandle*>(p)->getWidget();//указатель на окно пользовательского интерфейса

        HANDLE hNamedPipe;//дескриптор именованного канала

        wchar_t lpName[]=L"\\\\.\\Pipe\\MyNamedPipe";
        DWORD dwOpenMode=PIPE_ACCESS_DUPLEX;
        DWORD dwPipeMode=PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;//данные записываются сообщениями, читаются сообщениями, канал будет
                                                                               //работать в блокирующем режиме, т.е. процесс будет ожидать окончания операции
                                                                               //чтения или записи
        DWORD nMaxInstances=PIPE_UNLIMITED_INSTANCES;
        DWORD nOutBufferSize=256;
        DWORD nInBufferSize=256;
        DWORD nDefaultTimeOut=100;

        LPSECURITY_ATTRIBUTES lpSecurityAttributes=0;//защита по умолчанию. Дескриптор не может быть унаследован дочерним процессом

        while(true)
        {

            hNamedPipe=CreateNamedPipe(
                                       lpName, //имя канала в форме UNC
                                       dwOpenMode,//три группы флагов: напрвление, контроль ввода/вывода и параметры безопасности
                                       dwPipeMode,//режим, характеризующий способы чтения/записи
                                       nMaxInstances,//максимальное количество экземпляров, которые можно создать для данного канала
                                                     //(соответственно количество клиентов данного сервера). Это значение должно быть указано
                                                     //при создании всех экземпляров. Можно указать значение от 1 до PIPE_UNLIMITED_INSTANCES
                                                     //(в этом случае количество лимитируется только ресурсами системы)
                                       nOutBufferSize,//размер буфера в байтах, зарезервированного для записи(выходной буфер).
                                                      //Замечание: размеры буферов для чтения и для записи являются на самом деле вашим пожеланием системе
                                                      //(и должны быть  разумными)
                                       nInBufferSize,//размер входного буфера в байтах(для чтения из канала)
                                       nDefaultTimeOut,//время ожидания в мс(как долго клиент будет ожидать соединения с именованным каналом).
                                                       //Это значение по умолчанию используется только клиентами, которые вызывают функцию WaitNamedPipe()
                                                       //и в качестве соответствующего параметра указывают NMPWAIT_USE_DEFAULT_WAIT. Это значение должно быть указано
                                                       //при создании всех экземпяров канала
                                       lpSecurityAttributes//если NULL, то дескриптор защиты по умолчанию и возвращаемый дескриптор не может быть унаследован
                                                           //дочерним процессом
                                       );

    //---------------------------------------------ожидаем пока подключится клиент, и блокируем пока клиент не вызовет соответствующую функцию------------------------------------
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                                        LPOVERLAPPED lpOverlapped=0;//функция перейдёт в состояние ожидания, как как канал будет создан для работы
                                                                    //в синхронном блокирующем режиме

                                        if(hNamedPipe!=INVALID_HANDLE_VALUE)
                                        {
                                            //----------------------------ожидание подключения клиента--------------------
                                            /*bool connected=*/ConnectNamedPipe(//Возвращаемое значение: TRUE в случае успеха (в синхронном режиме - если подключился клиент)
                                                                            //Замечание: если клиент успел подключиться после вызова CreateNamedPipe, но до вызова ConnectNamedPipe(),
                                                                            //то возвращается FALSE, но GetLastError() вернет ERROR_PIPE_CONNECTED. В такой ситуации соединение всё равно установлено!
                                                                            hNamedPipe,//дескриптор, возвращённый CreateNamedPipe()
                                                                            lpOverlapped//используется только  в случае перекрывающегося ввода/вывода обмена данными
                                                                                        //(если канал был создан с флагом FILE_FLAG_OVERLAPPED). Для синхронного - 0
                                                                                        //(в этом случае сервис ConnectNamedPipe() не возвращает управление пока клиент не подключится к каналу).
                                                                                        );
                                        }

    //----------------------------------создаём новый поток, в который передаём дескриптор именованного канала для обмена с конкретным клиентом--------------------------------------------------
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        BigHandle* pAnotherHandle=new BigHandle();
        pAnotherHandle->setHandle(hNamedPipe);
        connect(pAnotherHandle, SIGNAL(needAdd(QByteArray)), mainGui, SLOT(needUpdatePlainText(QByteArray)));

        CreateThread(0, 0, ThreadClientInteract, reinterpret_cast<LPVOID>(pAnotherHandle), 0, 0);
        }

        return 0;
    }

private slots:
    void on_pushButtonWaitingClients_clicked();

    void on_pushButtonStartFiveClients_clicked();

    void needUpdatePlainText(QByteArray q);

private:
    Ui::MainWindow *ui;
    BigHandle* m_pBigHandle;
    static int counter;
};

#endif // MAINWINDOW_H
