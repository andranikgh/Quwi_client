#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "quwiapi.h"
#include "mainapp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();
    void on_logined();
    void on_loged_out();
private:
    Ui::Login *ui;
    QuwiApi* quwi_api;
    MainApp* mainApp;
};
#endif // LOGIN_H
