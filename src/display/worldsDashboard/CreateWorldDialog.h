#ifndef CREATEWORLDDIALOG_H
#define CREATEWORLDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class CreateWorldDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreateWorldDialog(QWidget *parent = nullptr);

    QString worldName() const;
    QString worldDescription() const;

private:
    QLineEdit *m_nameInput;
    QTextEdit *m_descriptionInput;
};

#endif // CREATEWORLDDIALOG_H