#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_inputs_edited();

    void on_plainTextEdit_textChanged();

private:
    Ui::Dialog *ui;

    QString post(const QString &arg1, const QString &arg2);
    QString post2(const QString &arg1, const QString &arg2);
    void get(const QString &xml, QString &arg1, QString &arg2, QString &errorString);
    void get2(const QString &xml, QString &arg1, QString &arg2, QString &errorString);
};

#endif // DIALOG_H
