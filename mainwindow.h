#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QDialog>
#include"volumedialog.h"
#include "paywindow.h"
extern int g_playerAttack;
extern int g_playerMaxHp;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 绘制背景图
    void paintEvent(QPaintEvent *event) override;

private slots:
    // 开始游戏按钮点击事件
    void onvulueClicked();
    void onStartGameClicked();
    void onguanqiaClicked();
    void onRuleClicked();
private slots:
   void onPayClicked();
private:
    int guanqia=1;
    PayWindow *m_payWin = nullptr; // 声明变量
private:

    QPushButton *startBtn;
    QPushButton *guanqiaBtn;
    QPushButton *ruleBtn;
    QPushButton *vulumBtn;
    QMediaPlayer *m_mainMusic;
    QAudioOutput *m_mainAudio;
    VolumeDialog *m_volumeDialog;
    QPushButton *payBtn;

};

#endif // MAINWINDOW_H