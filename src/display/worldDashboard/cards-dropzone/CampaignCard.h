#ifndef CAMPAIGNCARD_H
#define CAMPAIGNCARD_H

#include <QFrame>
#include <QPoint>

class CampaignCard : public QFrame {
    Q_OBJECT

public:
    explicit CampaignCard(int campaignId, const QString &name, const QString &description, bool isArchived = false, QWidget *parent = nullptr);

signals:
    void cardClicked(int campaignId);
    void archiveRequested(int campaignId);
    void deleteRequested(int campaignId);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int m_campaignId;
    bool m_isArchived;
    QPoint m_dragStartPosition;
};

#endif // CAMPAIGNCARD_H