#include "WorldCard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDataStream>

WorldCard::WorldCard(int worldId, const QString &name, const QString &description, bool isArchived, QWidget *parent)
    : QFrame(parent), m_worldId(worldId), m_isArchived(isArchived)
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
    cardLayout->setContentsMargins(16, 10, 16, 12);

    // --- Header Row: Title + Options Button ---
    QHBoxLayout *topLayout = new QHBoxLayout();

    QLabel *titleLabel = new QLabel(name, this);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #D4AF37; border: none; background: transparent;");

    // Three-Dots Menu Button
    QToolButton *optionsBtn = new QToolButton(this);
    optionsBtn->setText("⋮");
    optionsBtn->setCursor(Qt::PointingHandCursor);
    optionsBtn->setStyleSheet(
        "QToolButton { color: #A0AEC0; font-size: 18px; font-weight: bold; background: transparent; border: none; padding: 2px 6px; }"
        "QToolButton:hover { color: #D4AF37; background: #1A202C; border-radius: 4px; }"
        "QToolButton::menu-indicator { image: none; }" // Hides standard drop-down arrow
    );

    QMenu *optionsMenu = new QMenu(optionsBtn);
    optionsMenu->setStyleSheet(
        "QMenu { background-color: #1A202C; border: 1px solid #4A5568; color: #E2E8F0; padding: 4px; border-radius: 6px; }"
        "QMenu::item { padding: 6px 16px; border-radius: 4px; }"
        "QMenu::item:selected { background-color: #2D3748; color: #D4AF37; }"
    );

    QAction *archiveAction = optionsMenu->addAction(m_isArchived ? "Reactivate World" : "Archive World");
    QAction *deleteAction = optionsMenu->addAction("Delete World");

    optionsBtn->setMenu(optionsMenu);
    optionsBtn->setPopupMode(QToolButton::InstantPopup);

    connect(archiveAction, &QAction::triggered, this, [this]() {
        emit archiveRequested(m_worldId);
    });

    connect(deleteAction, &QAction::triggered, this, [this]() {
        emit deleteRequested(m_worldId);
    });

    topLayout->addWidget(titleLabel, 1);
    topLayout->addWidget(optionsBtn);

    cardLayout->addLayout(topLayout);

    // Description
    QLabel *descLabel = new QLabel(description.isEmpty() ? "No description provided." : description, this);
    descLabel->setStyleSheet("font-size: 12px; color: #A0AEC0; border: none; background: transparent;");
    descLabel->setWordWrap(true);

    cardLayout->addWidget(descLabel, 1);
}

// --- Drag & Drop Initiation ---
void WorldCard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
    QFrame::mousePressEvent(event);
}

void WorldCard::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

    // Package world ID into MIME data
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << m_worldId;

    mimeData->setData("application/x-worldcard-id", itemData);
    drag->setMimeData(mimeData);

    // Set visual preview thumbnail during drag
    QPixmap pixmap = grab();
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());

    drag->exec(Qt::MoveAction);
}

void WorldCard::mouseReleaseEvent(QMouseEvent *event) {
    // Only trigger click if the user didn't drag
    if (event->button() == Qt::LeftButton) {
        if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
            emit cardClicked(m_worldId);
        }
    }
    QFrame::mouseReleaseEvent(event);
}