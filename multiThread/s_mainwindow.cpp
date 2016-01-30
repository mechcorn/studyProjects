#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::counter=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pBigHandle=new BigHandle();
    m_pBigHandle->setWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pBigHandle;
}

void MainWindow::on_pushButtonWaitingClients_clicked()
{
    ui->plainTextEdit->appendPlainText(QString("Starting..."));
    CreateThread(0, 0, ThreadListening, reinterpret_cast<LPVOID>(m_pBigHandle), 0, 0);
}

void MainWindow::on_pushButtonStartFiveClients_clicked()
{
    wchar_t fileName[]=L"C:\\Qt\\Tools\\QtCreator\\bin\\build-ClientWithTimer-Desktop_Qt_5_2_1_MinGW_32bit-Debug\\debug\\ClientWithTimer.exe";
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    PROCESS_INFORMATION pi[5];
    for(int i=0; i<5; i++)
    {
        if(CreateProcessW(0, fileName, 0, 0, true, 0, 0, 0, &si, &pi[i]))
        {
            //+++++++++++++++++++++++++//
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
            //+++++++++++++++++++++++++//
        }
    }
}

void MainWindow::needUpdatePlainText(QByteArray q)
{
    counter++;
    ui->plainTextEdit->appendPlainText(QString(q) + QString(" #") + QString().setNum(counter));
    //ui->plainTextEdit->appendPlainText(q);
    //ui->plainTextEdit->appendPlainText(QByteArray("OK"));
}
