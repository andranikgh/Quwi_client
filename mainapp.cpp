#include "mainapp.h"
#include "ui_mainapp.h"
#include <QInputDialog>
#include <QDir>


MainApp::MainApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApp)
{
    ui->setupUi(this);
    quwi_api = QuwiApi::get_quwi_api();
    connect(quwi_api, SIGNAL(get_progect_finished()),this, SLOT(on_get_projects()));
    connect(ui->list_widget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(on_project_clicked(QListWidgetItem*)));
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
    QJsonValue projects_list = obj.value(QString("projects"));
    QJsonValue project;
    int i = -1;
    do {
        i++;
        project = projects_list[i];
        create_project_view(project);
    } while (!project.isUndefined());
 }

void MainApp::create_project_view(QJsonValue value)
{
    const QIcon icon;
    const QString project_name = value["name"].toString();
    QListWidgetItem* t = new QListWidgetItem(project_name);
    ui->list_widget->addItem(t);
}

void MainApp::on_project_clicked(QListWidgetItem *item)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Project name:"), QLineEdit::Normal,
                                            item->text(), &ok);
       if (ok && !text.isEmpty()) {
           item->setText(text);
           //ToDo add generic id.
           quwi_api->change_groject_name(text, 1097);
       }
}
