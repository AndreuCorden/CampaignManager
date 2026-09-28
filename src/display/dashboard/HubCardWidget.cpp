#include "HubCardWidget.h"
#include <QMouseEvent>

HubCardWidget::HubCardWidget(const QString &title, 
                             const QString &subtitle, 
                             QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setCursor(Qt::PointingHandCursor);

    // Dark fantasy card styling
    setStyleSheet(
        "HubCardWidget {"
        "   background-color: #2D3748;"
        "   border: 2px solid #4A5568;"
        "   border-radius: 8px;"
        "}"
        "HubCardWidget:hover {"
        "   border: 2px solid #D4AF37;"
        "   background-color: #323D4F;"
        "}"
        "QLabel#cardTitle {"
        "   color: #D4AF37;"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "}"
        "QLabel#cardSubtitle {"
        "   color: #A0AEC0;"
        "   font-size: 12px;"
        "}"
        "QLabel#cardMetric {"
        "   color: #FFFFFF;"
        "   font-size: 28px;"
        "   font-weight: bold;"
        "}"
        "QLabel#cardSnippet {"
        "   color: #CBD5E0;"
        "   font-size: 12px;"
        "   font-style: italic;"
        "}"
    );

    m_titleLabel = new QLabel(title, this);
    m_titleLabel->setObjectName("cardTitle");

    m_subtitleLabel = new QLabel(subtitle, this);
    m_subtitleLabel->setObjectName("cardSubtitle");

    m_metricLabel = new QLabel("0 Items", this);
    m_metricLabel->setObjectName("cardMetric");

    m_snippetLabel = new QLabel("No recent edits", this);
    m_snippetLabel->setObjectName("cardSnippet");
    m_snippetLabel->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_subtitleLabel);
    layout->addSpacing(10);
    layout->addWidget(m_metricLabel);
    layout->addWidget(m_snippetLabel);
    layout->addStretch();
}

void HubCardWidget::setMetricText(const QString &metric) {
    m_metricLabel->setText(metric);
}

void HubCardWidget::setRecentSnippet(const QString &snippet) {
    m_snippetLabel->setText(snippet);
}

void HubCardWidget::setMetricCount(int count) {
    setMetricText(QString::number(count));
}

void HubCardWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit cardClicked();
    }
    QFrame::mousePressEvent(event);
}