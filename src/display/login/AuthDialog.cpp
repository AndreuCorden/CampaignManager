// AuthDialog.cpp
#include "AuthDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

AuthDialog::AuthDialog(Mode mode, QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setWindowTitle(mode == Login ? "Log In" : "Register");
    resize(300, 180);

    QLabel *userLabel = new QLabel("Username:", this);
    m_usernameEdit = new QLineEdit(this);

    QLabel *passLabel = new QLabel("Password:", this);
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *confirmBtn = new QPushButton(mode == Login ? "Log In" : "Create Account", this);
    QPushButton *cancelBtn = new QPushButton("Cancel", this);

    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(userLabel);
    layout->addWidget(m_usernameEdit);
    layout->addWidget(passLabel);
    layout->addWidget(m_passwordEdit);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
}

QString AuthDialog::username() const { return m_usernameEdit->text().trimmed(); }
QString AuthDialog::password() const { return m_passwordEdit->text(); }