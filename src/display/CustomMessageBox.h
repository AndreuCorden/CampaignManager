#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QDialog>
#include <QString>

class CustomMessageBox : public QDialog {
    Q_OBJECT
public:
    enum IconType { Information, Warning, Critical };

    explicit CustomMessageBox(IconType icon, const QString &title, const QString &message, QWidget *parent = nullptr);

    static void information(QWidget *parent, const QString &title, const QString &message);
    static void warning(QWidget *parent, const QString &title, const QString &message);
    static void critical(QWidget *parent, const QString &title, const QString &message);

protected:
    void showEvent(QShowEvent *event) override;
};

#endif // CUSTOMMESSAGEBOX_H