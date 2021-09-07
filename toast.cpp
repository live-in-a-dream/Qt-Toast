#include "toast.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include "QDesktopWidget"
#include "QApplication"
Toast *Toast::m_instance = 0;
Toast::Toast(QObject *parent) : QObject(parent)
{
    mywidget = new QWidget;
    mywidget->setFixedHeight(60);
    m_pLabel = new QLabel;
    m_pLabel->setFixedHeight(30);
    m_pLabel->move(0,0);
    QFont ft;
    ft.setPointSize(10);
    m_pLabel->setFont(ft);
    m_pLabel->setAlignment(Qt::AlignCenter);
    m_pLabel->setStyleSheet("color:white");
    mywidget->setStyleSheet("border: none;background-color:black;border-radius:10px");
    QHBoxLayout * la = new QHBoxLayout;
    la->addWidget(m_pLabel);
    la->setContentsMargins(0,0,0,0);
    mywidget->setLayout(la);
    mywidget->hide();
    mywidget->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    mywidget->setAttribute(Qt::WA_TranslucentBackground,true);
    m_pTimer = new QTimer();
    m_pTimer->setInterval(3000);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(onTimerStayOut()));
}

void Toast::setText(const QString &color,const QString &bgcolor,const int & mestime,const QString &text){
    QApplication::beep();
    QFontMetrics fm(m_pLabel->font());
    int width = fm.boundingRect(text).width() + 30;
    mywidget->setFixedWidth(width);
    m_pLabel->setFixedWidth(width);
    m_pLabel->setText(text);
    QString style = QString("color:").append(StringToRGBA(color));
    m_pLabel->setStyleSheet(style);

    mywidget->setStyleSheet(QString("border: none;border-radius:10px;")
                            .append("background-color:").append(StringToRGBA(bgcolor)));

    QDesktopWidget *pDesk = QApplication::desktop();
    mywidget->move((pDesk->width() - mywidget->width()) / 2, (pDesk->height() - mywidget->height()) / 2);
    mywidget->show();
    m_pTimer->setInterval(mestime);
    m_pTimer->stop();
    m_pTimer->start();
}

void Toast::setError(const QString &text,const int & mestime){
     setText("FFFFFF","FF0000",mestime,text);
}

void Toast::setSuccess(const QString &text,const int & mestime){
     setText("000000","00FF00",mestime,text);
}

void Toast::setWaring(const QString &text,const int & mestime){
     setText("FF0000","FFFF00",mestime,text);
}

void Toast::setTips(const QString &text,const int & mestime){
     setText("FFFFFF","0080FF",mestime,text);
}

QString Toast::StringToRGBA(const QString &color){
    int r = color.mid(0,2).toInt(nullptr,16);
    int g = color.mid(2,2).toInt(nullptr,16);
    int b = color.mid(4,2).toInt(nullptr,16);
    int a = color.length()>=8?color.mid(6,2).toInt(nullptr,16):QString("FF").toInt(nullptr,16);
    QString style = QString("rgba(").append(QString::number(r)).append(",")
            .append(QString::number(g)).append(",")
            .append(QString::number(b)).append(",")
            .append(QString::number(a))
            .append(");");
    return style;
}

void Toast::onTimerStayOut()
{
    m_pTimer->stop();
    mywidget->hide();
}

