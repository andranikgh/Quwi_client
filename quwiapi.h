#ifndef QUWIAPI_H
#define QUWIAPI_H

#include <memory>

#include <QObject>
#include <QUrl>
#include <QJsonObject>

class QuwiApi : public QObject
{
    Q_OBJECT

public:
    ~QuwiApi();
    QuwiApi(QuwiApi &copy) = delete;
    void operator=(const QuwiApi &) = delete;
    static QuwiApi* get_quwi_api();
    void login(QString email, QString password);
    void set_token(QString token);
    QString get_token() const;
    void logout();
    void get_projects();
    QJsonObject get_user_projects() const;

signals:
    void logined();
    void tocken_changed();
    void loged_out();
    void get_progect_finished();

private:
    QuwiApi();
    static QuwiApi* quwi_api;
    QString token;
    QJsonObject user_projects;
    const QUrl login_url = QStringLiteral("https://api.quwi.com/v2/auth/login");
    const QUrl projects_url = QStringLiteral("https://api.quwi.com/v2/projects-manage/index");
    const QUrl logout_url = QStringLiteral("https://api.quwi.com/v2/auth/logout");

};

#endif // QUWIAPI_H
