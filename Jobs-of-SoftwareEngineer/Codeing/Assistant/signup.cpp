#include "signup.h"
#include "ui_signup.h"
#include<QMessageBox>
SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_goToLoginPushButton_clicked()
{
    close();
}

void SignUp::on_signupPushButton_clicked()
{
    if(!ui->userLineEdit->text().isEmpty()&&!ui->idLineEdit->text().isEmpty()&&!ui->depLineEdit->text().isEmpty()&&!ui->genderLineEdit->text().isEmpty()&&!ui->pwd1LineEdit->text().isEmpty()&&!ui->pwd2LineEdit->text().isEmpty())
    {
        if(ui->pwd1LineEdit->text()!=ui->pwd2LineEdit->text())
        {
                int ret1=QMessageBox::warning(this,tr("Warning"),tr("Inconsistent passwords!"),QMessageBox::Ok);
                if(ret1==QMessageBox::Ok)
                {
                    ui->pwd1LineEdit->clear();ui->pwd2LineEdit->clear();
                }
        }
        else
        {
            QMessageBox::information(this,tr("Hint"),tr("Register Success"),QMessageBox::Ok);
            // signUpInfo(string,string,string,string,string,string,string,string);
        }

    }
    else
       QMessageBox::warning(this,tr("Warning"),tr("Input cannot be empty!"),QMessageBox::Ok);

}
