#include "dialog.h"
#include "ui_dialog.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QDebug>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_lineEdit_textEdited(const QString &arg1)
{
    qDebug() << ui->lineEdit->property("text");

    QString result;

    QXmlStreamWriter myWriter(&result);
    myWriter.writeStartDocument();
    myWriter.writeTextElement("root", arg1);
//    myWriter.writeCharacters(arg1);
    myWriter.writeEndDocument();

    ui->lineEdit_2->setText(result);
}

void Dialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString result;

    QXmlStreamReader myReader(arg1);
    QXmlStreamReader::TokenType myType;

    qDebug() << "Parsing XML input";
    while (!myReader.atEnd())
    {
        myType = myReader.readNext();
        qDebug() << "  Token type/string:" << myType << "/" << myReader.tokenString();
        qDebug() << "  Name:" << myReader.name();
        if (myType == QXmlStreamReader::Characters)
            result = myReader.text().toString();
    }
    qDebug() << "At end?" << myReader.atEnd();
    qDebug() << "Error?" << myReader.errorString();
    qDebug();
    ui->label_5->setText(myReader.errorString());

    ui->lineEdit_3->setText(result);
}
