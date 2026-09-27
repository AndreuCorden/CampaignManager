#ifndef WORLDSWINDOW_H
#define WORLDSWINDOW_H

#include <QMainWindow>
#include "WorldsWidget.h"

class WorldsWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WorldsWindow(const QString &username, QWidget *parent = nullptr);
    WorldsWidget* worldsWidget() const { return m_worldsWidget; }

private:
    WorldsWidget *m_worldsWidget;
};

#endif // WORLDSWINDOW_H