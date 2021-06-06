#ifndef MAINAPP_H
#define MAINAPP_H

#include "quwiapi.h"
#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainApp;
}

class MainApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApp(QWidget *parent = nullptr);
    ~MainApp();
    void create_project_view(QJsonValue value);


private slots:
    void on_logout_clicked();
    void on_projects_clicked();
    void on_get_projects();
    void on_project_clicked(QListWidgetItem *item);

private:
    Ui::MainApp *ui;
    QuwiApi* quwi_api;
    int clicked_project_id;
};

#endif // MAINAPP_H
