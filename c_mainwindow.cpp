#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::counter=0;
HANDLE MainWindow::hTimer=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_bigString=new BigText();
    m_bigString->setWidget(this);

    connect(m_bigString, SIGNAL(needAdd(QByteArray)), this, SLOT(needUpdatePlainText(QByteArray)));

    hThreadGlobal=0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_bigString;
}

void MainWindow::on_pushButtonCreatePipe_2_clicked()
{
    if(!hThreadGlobal)
    {
        LONG period=ui->horizontalSliderTimerDelay->sliderPosition();
        wchar_t lpNamedPipeName[]=L"\\\\.\\Pipe\\MyNamedPipe";
        DWORD nTimeOut=NMPWAIT_WAIT_FOREVER;

       bool exists=WaitNamedPipeW(
                                  lpNamedPipeName,//имя объекта "именованный канал"
                                  nTimeOut//как долго клиент хочет ждать, пока сервер завершит операцию
                                          //ConnectNamedPipe(). Для "бесконечного ожидания - NMPWAIT_WAIT_FOREVER"
                                  );
       if(exists)//если канал существует
       {
           hTimer=CreateWaitableTimerW(0, FALSE, 0);//синхронизации, неименованный
           if(hTimer!=0)
           {
               //настройка таймера
               LARGE_INTEGER time;//время запуска
               time.QuadPart=-10000000LL;//относительно момента вызова функции SetWaitableTimer()
               SetWaitableTimer(hTimer, &time, period/*500сделать возможность выбрать из интерфейса*/, 0, 0, FALSE);//через интервал time от момента вызова, с интервалом 500 мс,
                                                                 //процедура не задана, данные для процедуры не заданы
               m_pText=new QString(ui->lineEdit_2->text());
                m_bigString->setString(m_pText);

    //---------------------------------------------------------запуск потока-----------------------------------------------------
               hThreadGlobal=CreateThread(0, 0, ThreadFunc, reinterpret_cast<LPVOID>(/*m_pText*/m_bigString), 0, 0);//безопасность - по умолчанию, стек - по умолчанию,
                                                                      //параметр потоковой функции 0, создаваемый поток готов
                                                                      //к выполнению, идентификатор не нужен
           }
    //---------------------------------------------------------------------------------------------------------------------------
       }
    }
}

void MainWindow::on_pushButtonCloseHandle_2_clicked()
{
    TerminateThread(hThreadGlobal, 100);
    CloseHandle(hThreadGlobal);//закрываем дескриптор порождённого потока
    hThreadGlobal=0;
    CloseHandle(hTimer);//закрываем дескриптор таймера
}

void MainWindow::needUpdatePlainText(QByteArray q)
{
    counter++;
    ui->plainTextEditAck->appendPlainText(QString(q) + QString(" #") + QString().setNum(counter));
}
