#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

#include "quwiapi.h"

QuwiApi* QuwiApi::quwi_api = nullptr;

QuwiApi::QuwiApi() :QObject()
{

}

QuwiApi::~QuwiApi()
{
    delete quwi_api;
}

//Get method to return unique quwi api instance.
QuwiApi* QuwiApi::get_quwi_api()
{
    if (nullptr == quwi_api) {
         quwi_api = new QuwiApi();
    }
    return quwi_api;
}

//Set token and send signal.
void QuwiApi::set_token(QString token)
{
    if (this->token != token) {
        this->token = token;
        emit tocken_changed();
    }
}

//Get method for token.
QString QuwiApi::get_token() const
{
    return token;
}

//Method to sent login request to Quwi Api
void QuwiApi::login(QString email, QString password)
{
       QNetworkAccessManager *mgr = new QNetworkAccessManager();
       QNetworkRequest request(login_url);

       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

       QJsonObject data;
       data["email"] = email;
       data["password"] = password;
       QJsonDocument doc(data);
       QByteArray pData = doc.toJson();

       QNetworkReply *reply = mgr->post(request, pData);

       QObject::connect(reply, &QNetworkReply::finished, [=](){
           if(reply->error() == QNetworkReply::NoError){
               QString contents = QString::fromUtf8(reply->readAll());
               qDebug() << contents;
               QJsonDocument doc = QJsonDocument::fromJson(contents.toUtf8());
               QJsonObject obj = doc.object();
               set_token(obj["token"].toString());
               emit logined();
           }
           else{
               set_token("");
               QString err = reply->errorString();
               qDebug() << err;
           }
           reply->deleteLater();
       });

}

void QuwiApi::logout()
{
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QNetworkRequest request(logout_url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["anywhere"] = true;
    QJsonDocument doc(data);
    QByteArray pData = doc.toJson();

    QNetworkReply *reply = mgr->post(request, pData);

    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            set_token("");
            emit loged_out();
        } else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
}

void QuwiApi::get_projects()
{
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QNetworkRequest request(projects_url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const QByteArray data = "Bearer " + get_token().toUtf8();
    request.setRawHeader(QByteArray("Authorization"), QByteArray(data));


    QNetworkReply *reply = mgr->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
            QJsonDocument doc = QJsonDocument::fromJson(contents.toUtf8());
            user_projects = doc.object();
            emit get_progect_finished();
        }
        else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
}

QJsonObject QuwiApi::get_user_projects() const
{
    return user_projects;
}

// TODO Add Param To use id.
void QuwiApi::change_groject_name(QString name, int id)
{
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QNetworkRequest request(change_project_name_url);

    //request.setRawHeader(QByteArray("Content-Type"), QByteArray("multipart/form-data"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const QByteArray token = "Bearer " + get_token().toUtf8();
    request.setRawHeader(QByteArray("Authorization"), QByteArray(token));

    QJsonObject data;
    data["name"] = name;
    QJsonDocument doc(data);
    QByteArray pData = doc.toJson();

    QNetworkReply *reply = mgr->post(request, pData);

    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
        } else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
}
