#ifndef MAPSTABWIDGET_H
#define MAPSTABWIDGET_H

#include <QWidget>

class QListWidget;
class QLabel;

class MapsTabWidget : public QWidget {
    Q_OBJECT

public:
    explicit MapsTabWidget(QWidget *parent = nullptr);

private:
    QListWidget *m_worldMapsList;
    QListWidget *m_campaignMapsList;
    QLabel *m_mapViewerPlaceholder;
};

#endif // MAPSTABWIDGET_H