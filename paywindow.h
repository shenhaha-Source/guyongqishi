#ifndef PAYWINDOW_H
#define PAYWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStringList>

class PayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PayWindow(QWidget *parent = nullptr);

private slots:
    void pay1Yuan();
    void pay3Yuan();
    void redeemCode();
signals:
    void oneYuanReward();
    void activateThreeYuan();
private:
    QPushButton *btn1Yuan;
    QPushButton *btn3Yuan;
    QLineEdit   *editCode;
    QPushButton *btnRedeem;
    QLabel      *labelTip;

    // 兑换码库
    QStringList code1List;   // 1元兑换码
    QStringList code3List;   // 3元兑换码
    QStringList usedCode;    // 已使用兑换码
};

#endif // PAYWINDOW_H
