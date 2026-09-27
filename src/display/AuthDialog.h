// AuthDialog.h
#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QLineEdit>

class AuthDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { Login, Register };
    explicit AuthDialog(Mode mode, QWidget *parent = nullptr);

    QString username() const;
    QString password() const;

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
};

#endif // AUTHDIALOG_H