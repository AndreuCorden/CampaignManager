#include "CustomMessageBox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QShowEvent>

CustomMessageBox::CustomMessageBox(IconType icon, const QString &title, const QString &message, QWidget *parent)
    : QDialog(parent)
{
    // 1. Remove native OS title bar and keep dialog properties
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose, false);

    // 2. Custom styling matching main window theme
    setStyleSheet(
        "CustomMessageBox {"
        "   background-color: #1A202C;"
        "   border: 2px solid #D4AF37;"
        "   border-radius: 6px;"
        "}"
        "QLabel#titleLabel {"
        "   color: #D4AF37;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"
        "QLabel#messageLabel {"
        "   color: #E2E8F0;"
        "   font-size: 13px;"
        "}"
        "QPushButton {"
        "   background-color: #2D3748;"
        "   color: #D4AF37;"
        "   border: 1px solid #D4AF37;"
        "   border-radius: 4px;"
        "   padding: 6px 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #D4AF37;"
        "   color: #1A202C;"
        "}"
    );

    // 3. Layout construction
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 16, 20, 16);
    layout->setSpacing(12);

    QLabel *titleLbl = new QLabel(title, this);
    titleLbl->setObjectName("titleLabel");

    QLabel *msgLbl = new QLabel(message, this);
    msgLbl->setObjectName("messageLabel");
    msgLbl->setWordWrap(true);

    QPushButton *okBtn = new QPushButton("OK", this);
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);

    layout->addWidget(titleLbl);
    layout->addWidget(msgLbl);
    layout->addSpacing(8);
    layout->addLayout(btnLayout);

    setMinimumWidth(320);
}

// Automatically centers the frameless window over m_window upon display
void CustomMessageBox::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    if (parentWidget()) {
        QPoint center = parentWidget()->geometry().center() - rect().center();
        move(center);
    }
}

void CustomMessageBox::information(QWidget *parent, const QString &title, const QString &message) {
    CustomMessageBox box(Information, title, message, parent);
    box.exec();
}

void CustomMessageBox::warning(QWidget *parent, const QString &title, const QString &message) {
    CustomMessageBox box(Warning, title, message, parent);
    box.exec();
}

void CustomMessageBox::critical(QWidget *parent, const QString &title, const QString &message) {
    CustomMessageBox box(Critical, title, message, parent);
    box.exec();
}