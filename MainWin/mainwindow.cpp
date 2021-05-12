#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextBlock>
#include <string>

using namespace std;

QTextEdit editor;
QStringList comparacionRAM;
QStringList comparacionCode;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Run_clicked()
{
    lineCount ++;
    QTextEdit editor;
    QString texto = ui->CodeEditor->toPlainText();
    editor.setText(texto);
    QTextDocument *doc = editor.document();
    QTextBlock bloque = doc->findBlockByLineNumber(lineCount);
    QString lineatexto = bloque.text();
    if (lineatexto != "") {

        ui->CurrentLine->setText(lineatexto);

        QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

        QUrl url = QUrl("http://localhost:5000/newline");

        QJsonObject param;

        param.insert("line", QJsonValue::fromVariant(lineatexto));

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply* reply = mgr->post(request, QJsonDocument(param).toJson(QJsonDocument::Compact));

        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());

                //parse json
                QJsonDocument jsonDoc = QJsonDocument::fromJson(contents.toUtf8());
                QJsonObject jsonObj = jsonDoc.object();

                QString tipoMensaje = jsonObj["tipoMensaje"].toString();
                QString mensaje = jsonObj["mensaje"].toString();

                if (tipoMensaje == "Cout"){
                    ui->Stdout->setText(mensaje);
                }
                else if (tipoMensaje == "Asignacion"){
                    ui->RamView->append(mensaje);
                }

                else if (tipoMensaje == "Declaracion"){
                    ui->RamView->append(mensaje);

                }

                else if (tipoMensaje == "Error"){
                    ui->AppLog->setText(mensaje);

                }
            }
            else{
                QString err = reply->errorString();
                qDebug() << err;
            }
            reply->deleteLater();
        });
    }

}

void MainWindow::on_Stop_clicked() {
    lineCount = -1;
    ui->RamView->clear();
    ui->CurrentLine->clear();
    ui->Stdout->clear();
    ui->AppLog->clear();

    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    const QUrl url(QStringLiteral("http://localhost:5000/clear"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mgr->get(request);
}

