#include "WorldCard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

WorldCard::WorldCard(int worldId, const QString &name, const QString &description, QWidget *parent)
    : QFrame(parent), m_worldId(worldId)
{
    setCursor(Qt::PointingHandCursor);
    setFrameShape(QFrame::StyledPanel);
    setFixedHeight(100);

    setStyleSheet(
        "WorldCard {"
        "  background-color: #2D3748;"
        "  border: 1px solid #4A5568;"
        "  border-radius: 8px;"
        "}"
        "WorldCard:hover {"
        "  background-color: #3A4A60;"
        "  border: 1px solid #D4AF37;"
        "}"
    );

    QVBoxLayout *cardLayout = new QVBoxLayout(this);
    cardLayout->setContentsMargins(16, 12, 16, 12);

    QLabel *titleLabel = new QLabel(name, this);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #D4AF37; border: none; background: transparent;");

    QLabel *descLabel = new QLabel(description.isEmpty() ? "No description provided." : description, this);
    descLabel->setStyleSheet("font-size: 12px; color: #A0AEC0; border: none; background: transparent;");
    descLabel->setWordWrap(true);

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(descLabel, 1);
}

void WorldCard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit cardClicked(m_worldId);
    }
    QFrame::mousePressEvent(event);
}