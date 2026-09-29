#include "TimelineTabWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

TimelineTabWidget::TimelineTabWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);

    QHBoxLayout *header = new QHBoxLayout();
    QLabel *title = new QLabel("Chronological History & Parallel Campaign Timelines", this);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #D4AF37;");

    QPushButton *addEventBtn = new QPushButton("+ Add Timeline Period", this);
    addEventBtn->setStyleSheet("QPushButton { background-color: #2D3748; color: #D4AF37; padding: 6px 12px; font-weight: bold; border-radius: 4px; }");

    header->addWidget(title);
    header->addStretch();
    header->addWidget(addEventBtn);
    mainLayout->addLayout(header);

    m_swimlaneTable = new QTableWidget(this);
    m_swimlaneTable->setStyleSheet(
        "QTableWidget { background-color: #1A202C; gridline-color: #2D3748; color: #E2E8F0; border: 1px solid #4A5568; }"
        "QHeaderView::section { background-color: #2D3748; color: #D4AF37; font-weight: bold; border: 1px solid #4A5568; padding: 4px; }"
    );

    mainLayout->addWidget(m_swimlaneTable);

    populateSampleTimeline();
    setupSwimlaneView();
}

void TimelineTabWidget::populateSampleTimeline() {
    m_spans = {
        {"World Made & Peace Era", 1, 100, "🌐 World Era", "#2B6CB0"},
        {"Campaign A: Stuff Happened", 101, 102, "⚔️ Campaign A", "#C53030"},
        {"World Golden Age", 103, 140, "🌐 World Era", "#2B6CB0"},
        {"Campaign B: Sunken Crown", 135, 145, "⚔️ Campaign B", "#D69E2E"},
        {"Campaign C: War of Three Kings", 144, 146, "⚔️ Campaign C", "#38A169"},
        {"World Great War Era", 200, 220, "🌐 World Era", "#2B6CB0"},
        {"Campaign D: Wartime Siege", 205, 219, "⚔️ Campaign D", "#805AD5"}
    };
}

void TimelineTabWidget::setupSwimlaneView() {
    QStringList tracks = {"🌐 World Era", "⚔️ Campaign A", "⚔️ Campaign B", "⚔️ Campaign C", "⚔️ Campaign D"};
    
    m_swimlaneTable->setRowCount(tracks.size());
    m_swimlaneTable->setVerticalHeaderLabels(tracks);

    // Columns represent time blocks from Year 0 to Year 230 in 10-year increments
    int startYear = 0;
    int endYear = 230;
    int step = 10;
    int numCols = (endYear - startYear) / step;

    m_swimlaneTable->setColumnCount(numCols);
    QStringList colHeaders;
    for (int i = 0; i < numCols; ++i) {
        colHeaders << QString("Yr %1-%2").arg(i * step).arg((i + 1) * step);
    }
    m_swimlaneTable->setHorizontalHeaderLabels(colHeaders);
    m_swimlaneTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (const auto &span : m_spans) {
        int trackIndex = tracks.indexOf(span.trackName);
        if (trackIndex == -1) continue;

        int startCol = span.startYear / step;
        int endCol = span.endYear / step;
        int spanLength = qMax(1, endCol - startCol + 1);

        QTableWidgetItem *item = new QTableWidgetItem(QString("%1 (Y%2-%3)").arg(span.title).arg(span.startYear).arg(span.endYear));
        item->setTextAlignment(Qt::AlignCenter);
        item->setBackground(QColor(span.colorHex));
        item->setForeground(Qt::white);

        m_swimlaneTable->setItem(trackIndex, startCol, item);
        if (spanLength > 1) {
            m_swimlaneTable->setSpan(trackIndex, startCol, 1, spanLength);
        }
    }
}