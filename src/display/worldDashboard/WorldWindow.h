#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#include <QMainWindow>
#include <QString>

class WorldWidget;
class QLabel;

class WorldWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WorldWindow(const QString &username, QWidget *parent = nullptr);

    WorldWidget* worldWidget() const { return m_worldWidget; }
    void setWorldDetails(const QString &name, const QString &description);

signals:
    void backToWorldsRequested();

private:
    WorldWidget *m_worldWidget;
    QLabel *m_titleLabel;
};

#endif // WORLDWINDOW_H