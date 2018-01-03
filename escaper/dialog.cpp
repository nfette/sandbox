#include "dialog.h"
#include "ui_dialog.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QDebug>
#include <QXmlStreamAttribute>
#include <QXmlStreamAttributes>

#include <QtXml>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->lineEdit_1, SIGNAL(textChanged(QString)), SLOT(on_inputs_edited(void)));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), SLOT(on_inputs_edited(void)));
    QButtonGroup * qbg = new QButtonGroup(this);
    qbg->addButton(ui->radioButton_1);
    qbg->addButton(ui->radioButton_2);
    connect(ui->radioButton_1, SIGNAL(toggled(bool)), SLOT(on_inputs_edited(void)));
    on_inputs_edited();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_inputs_edited()
{
    QString arg1 = ui->lineEdit_1->text();
    QString arg2 = ui->lineEdit_2->text();
    QString result = (ui->radioButton_1->isChecked())?post(arg1, arg2):post2(arg1, arg2);
    ui->plainTextEdit->setPlainText(result);
}

void Dialog::on_plainTextEdit_textChanged()
{
    QString xml = ui->plainTextEdit->toPlainText();
    QString arg1, arg2, errorString;
    get(xml, arg1, arg2, errorString);
    ui->lineEdit_3->setText(arg1);
    ui->lineEdit_4->setText(arg2);
    ui->label_error->setText(errorString);

    get2(xml, arg1, arg2, errorString);
    ui->lineEdit_5->setText(arg1);
    ui->lineEdit_6->setText(arg2);
    ui->label_9->setText(errorString);
}

QString Dialog::post(const QString &arg1, const QString &arg2)
{
    QString result;
    QXmlStreamWriter myWriter(&result);
    myWriter.setAutoFormatting(true);
    myWriter.writeStartDocument();
    //myWriter.writeTextElement("root", arg1);
    myWriter.writeStartElement("root");
    myWriter.writeAttribute("myAttribute", arg2);
    myWriter.writeCharacters(arg1);
    myWriter.writeEndElement();
    myWriter.writeEndDocument();
    return result;
}

QString Dialog::post2(const QString &arg1, const QString &arg2)
{
    QDomDocument doc;
    QDomElement el = doc.createElement("root");
    //QDomElement el = doc.documentElement();
    el.setTagName("root");
    el.setAttribute("myAttribute", arg2);
    //el.setNodeValue(arg1);
    QDomText val = doc.createTextNode(arg1);
    el.appendChild(val);
    doc.appendChild(el);
    QString result =  doc.toString(2);
    return result;
}

void Dialog::get(const QString &xml, QString &arg1, QString &arg2, QString &errorString)
{
    QXmlStreamReader myReader(xml);
    QXmlStreamReader::TokenType myType;
    while (!myReader.atEnd())
    {
        myType = myReader.readNext();
        qDebug() << "  Token type/string:" << myType << "/" << myReader.tokenString();
        qDebug() << "  Name:" << myReader.name();
        if (myType == QXmlStreamReader::Characters)
            arg1 = myReader.text().toString();
        if (myType == QXmlStreamReader::StartElement)
            arg2 = myReader.attributes().value("myAttribute").toString();
    }
    qDebug() << "At end?" << myReader.atEnd();
    qDebug() << "Error?" << myReader.errorString();
    qDebug();
    errorString = myReader.errorString();
}

void Dialog::get2(const QString &xml, QString &arg1, QString &arg2, QString &errorString)
{
    QDomDocument doc;
    int errorLine, errorColumn;
    doc.setContent(xml, &errorString, &errorLine, &errorColumn);
    QDomElement rootEl = doc.documentElement();
    arg2 = rootEl.attribute("myAttribute");
    arg1 = rootEl.text();
    qDebug() << arg1;
    qDebug() << arg2;
}
