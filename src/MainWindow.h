#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    // We define custom C++ signals that other parts of our game can listen to
    void logInRequested();
    void registerRequested();
    void exitRequested();

private:

    QLabel *m_titleLabel;
    QPushButton *m_logInButton;
    QPushButton *m_registerButton;
    QPushButton *m_exitButton;
    QVBoxLayout *m_mainLayout;
};

#endif // MAINWINDOW_H