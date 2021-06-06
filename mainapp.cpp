#include "mainapp.h"
#include "ui_mainapp.h"


MainApp::MainApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApp)
{
    ui->setupUi(this);
    quwi_api = QuwiApi::get_quwi_api();
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

}
