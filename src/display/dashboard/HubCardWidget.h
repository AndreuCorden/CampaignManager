#ifndef HUBCARDWIDGET_H
#define HUBCARDWIDGET_H

#include <QFrame>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class HubCardWidget : public QFrame {
    Q_OBJECT

public:
    explicit HubCardWidget(const QString &title, 
                          const QString &subtitle,
                          QWidget *parent = nullptr);

    void setMetricText(const QString &metric);
    void setRecentSnippet(const QString &snippet);
    void setMetricCount(int count);

signals:
    void cardClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QLabel *m_metricLabel;
    QLabel *m_snippetLabel;
};

#endif // HUBCARDWIDGET_H