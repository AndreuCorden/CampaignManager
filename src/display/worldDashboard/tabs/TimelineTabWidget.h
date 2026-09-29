#ifndef TIMELINETABWIDGET_H
#define TIMELINETABWIDGET_H

#include <QWidget>
#include <QList>
#include <QString>

class QTableWidget;

struct TimelineSpan {
    QString title;
    int startYear;
    int endYear;
    QString trackName; // "World Era", "Campaign A", "Campaign B", etc.
    QString colorHex;
};

class TimelineTabWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimelineTabWidget(QWidget *parent = nullptr);

private:
    QTableWidget *m_swimlaneTable;
    QList<TimelineSpan> m_spans;

    void setupSwimlaneView();
    void populateSampleTimeline();
};

#endif // TIMELINETABWIDGET_H