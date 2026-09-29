#ifndef CAMPAIGNSTABWIDGET_H
#define CAMPAIGNSTABWIDGET_H

#include <QWidget>

class QVBoxLayout;

class CampaignsTabWidget : public QWidget {
    Q_OBJECT

public:
    explicit CampaignsTabWidget(QWidget *parent = nullptr);

signals:
    void createCampaignRequested();
    void openCampaignRequested(int campaignId);
    void archiveCampaignRequested(int campaignId);
    void reactivateCampaignRequested(int campaignId);
    void deleteCampaignRequested(int campaignId);

private:
    QVBoxLayout *m_activeLayout;
    QVBoxLayout *m_archivedLayout;
};

#endif // CAMPAIGNSTABWIDGET_H