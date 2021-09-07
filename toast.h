#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include "QObject"
#include "QHBoxLayout"
namespace Ui {
class Toast;
}

class Toast : public QObject
{
    Q_OBJECT

public:
    explicit Toast(QObject *parent = nullptr);

    static Toast* Instance()
    {
        static QMutex mutex;
        if (!m_instance) {
            QMutexLocker locker(&mutex);
            if (!m_instance)
                m_instance = new Toast;
        }
        return m_instance;
    }
    void setText(const QString &color="FFFFFF",const QString &bgcolor = "000000",const int & mestime=3000,const QString &textconst="");
    //错误
    void setError(const QString &text,const int & mestime = 3000);
    //成功
    void setSuccess(const QString &text,const int & mestime = 3000);
    //警告
    void setWaring(const QString &text,const int & mestime = 3000);
    //提示
    void setTips(const QString &text,const int & mestime = 3000);
signals:

private slots:
    void onTimerStayOut();
private:
    QWidget * mywidget;
    static Toast* m_instance;
    QLabel * m_pLabel;
    QTimer * m_pTimer;
    qreal m_dTransparent;

    QString StringToRGBA(const QString &color);
private:
    Ui::Toast *ui;
};

#endif // TOAST_H
