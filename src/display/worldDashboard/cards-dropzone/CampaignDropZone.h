#ifndef CAMPAIGNDROPZONE_H
#define CAMPAIGNDROPZONE_H

#include <QFrame>

class QVBoxLayout;

class CampaignDropZone : public QFrame {
    Q_OBJECT

public:
    explicit CampaignDropZone(QWidget *parent = nullptr);
    QVBoxLayout* contentLayout() const { return m_layout; }

signals:
    void campaignDropped(int campaignId);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QVBoxLayout *m_layout;
};

#endif // CAMPAIGNDROPZONE_H