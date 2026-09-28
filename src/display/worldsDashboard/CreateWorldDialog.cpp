#include "CreateWorldDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

CreateWorldDialog::CreateWorldDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setFixedSize(400, 300);
    setStyleSheet("background-color: #1A202C; color: #E2E8F0;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(12);

    QLabel *titleLabel = new QLabel("Construct a New Setting", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #D4AF37;");
    layout->addWidget(titleLabel);

    // Name Input
    layout->addWidget(new QLabel("World Name:", this));
    m_nameInput = new QLineEdit(this);
    m_nameInput->setPlaceholderText("e.g. Eldoria, The Iron Kingdoms...");
    m_nameInput->setStyleSheet("padding: 8px; background-color: #2D3748; color: white; border-radius: 4px;");
    layout->addWidget(m_nameInput);

    // Description Input
    layout->addWidget(new QLabel("Brief Lore / Overview:", this));
    m_descriptionInput = new QTextEdit(this);
    m_descriptionInput->setPlaceholderText("A high fantasy realm torn by wild magic...");
    m_descriptionInput->setStyleSheet("padding: 8px; background-color: #2D3748; color: white; border-radius: 4px;");
    layout->addWidget(m_descriptionInput);

    // Action Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *cancelBtn = new QPushButton("Cancel", this);
    QPushButton *createBtn = new QPushButton("Create World", this);

    cancelBtn->setCursor(Qt::PointingHandCursor);
    createBtn->setCursor(Qt::PointingHandCursor);

    cancelBtn->setStyleSheet("padding: 6px 16px; background-color: #4A5568; color: white; border-radius: 4px;");
    createBtn->setStyleSheet("padding: 6px 16px; background-color: #D4AF37; color: #1A202C; border-radius: 4px; font-weight: bold;");

    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(createBtn);

    layout->addLayout(btnLayout);

    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(createBtn, &QPushButton::clicked, this, &QDialog::accept);
}

QString CreateWorldDialog::worldName() const {
    return m_nameInput->text().trimmed();
}

QString CreateWorldDialog::worldDescription() const {
    return m_descriptionInput->toPlainText().trimmed();
}