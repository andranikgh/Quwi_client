#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    mainApp = new MainApp(this);
    mainApp->hide();
    quwi_api = QuwiApi::get_quwi_api();
    connect(quwi_api, SIGNAL(logined()),this, SLOT(on_logined()));
    connect(quwi_api, SIGNAL(loged_out()),this, SLOT(on_loged_out()));
}

Login::~Login()
{
    delete ui;
    delete mainApp;
}

void Login::on_loginButton_clicked()
{
    quwi_api->login(ui->email->text(), ui->password->text());
}

void Login::on_logined()
{
    hide();
    mainApp->show();
}

void Login::on_loged_out()
{
    show();
    mainApp->hide();
}
