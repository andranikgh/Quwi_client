#include "mainapp.h"
#include "ui_mainapp.h"


MainApp::MainApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApp)
{
    ui->setupUi(this);
    quwi_api = QuwiApi::get_quwi_api();
    connect(quwi_api, SIGNAL(get_progect_finished()),this, SLOT(on_get_projects()));
}

MainApp::~MainApp()
{
    delete ui;
    delete quwi_api;
}

void MainApp::on_logout_clicked()
{
    quwi_api->logout();
}

void MainApp::on_projects_clicked()
{
    quwi_api->get_projects();
}

void MainApp::on_get_projects()
{
    QJsonObject obj = quwi_api->get_user_projects();
}
