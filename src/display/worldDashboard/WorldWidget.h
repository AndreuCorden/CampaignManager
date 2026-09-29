#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>

class CampaignsTabWidget;
class WikiTabWidget;
class MapsTabWidget;
class TimelineTabWidget;

class WorldWidget : public QWidget {
    Q_OBJECT

public:
    explicit WorldWidget(QWidget *parent = nullptr);

    void setWorldDetails(const QString &name, const QString &description);

    CampaignsTabWidget* campaignsTab() const { return m_campaignsTab; }
    WikiTabWidget* wikiTab() const { return m_wikiTab; }
    MapsTabWidget* mapsTab() const { return m_mapsTab; }
    TimelineTabWidget* timelineTab() const { return m_timelineTab; }

private:
    CampaignsTabWidget *m_campaignsTab;
    WikiTabWidget *m_wikiTab;
    MapsTabWidget *m_mapsTab;
    TimelineTabWidget *m_timelineTab;
};

#endif // WORLDWIDGET_H