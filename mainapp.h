#ifndef MAINAPP_H
#define MAINAPP_H

#include "quwiapi.h"
#include <QMainWindow>

namespace Ui {
class MainApp;
}

class MainApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApp(QWidget *parent = nullptr);
    ~MainApp();

private slots:
    void on_logout_clicked();
    void on_projects_clicked();
    void on_get_projects();

private:
    Ui::MainApp *ui;
    QuwiApi* quwi_api;
};

#endif // MAINAPP_H
