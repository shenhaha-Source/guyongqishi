#include "paywindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
extern int g_playerAttack;
extern int g_playerMaxHp;

PayWindow::PayWindow(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(450, 320);
    setWindowTitle("充值赞助 | 兑换福利");
    setStyleSheet("background-color:#1b1b1b;");

    // 兑换码列表
    code1List = {
        "ONE00y551","ONE00772","ONE00399","ONE00777554","ONEuuug005",
    };
    code3List = {
        "THRygf001","THRgff002","THdghR003","THffR004","TddHR005",
    };

    // 5元赞助按钮
    btn1Yuan = new QPushButton("💎 赞助 5元", this);
    btn1Yuan->setGeometry(60, 40, 140, 55);
    btn1Yuan->setStyleSheet(R"(
        QPushButton{background:#0088ff;color:white;font-size:15px;border-radius:8px;}
        QPushButton:hover{background:#00a0ff;}
    )");

    // 6元赞助按钮
    btn3Yuan = new QPushButton("👑 赞助 6元", this);
    btn3Yuan->setGeometry(250, 40, 140, 55);
    btn3Yuan->setStyleSheet(R"(
        QPushButton{background:#ff5500;color:white;font-size:15px;border-radius:8px;}
        QPushButton:hover{background:#ff7722;}
    )");

    // 兑换码标签
    QLabel *labCode = new QLabel("输入兑换码：", this);
    labCode->setGeometry(60, 120, 100, 35);
    labCode->setStyleSheet("color:#eeeeee;font-size:14px;");

    // 输入框
    editCode = new QLineEdit(this);
    editCode->setGeometry(160, 120, 180, 35);
    editCode->setPlaceholderText("请输入兑换码");
    editCode->setStyleSheet(R"(
        QLineEdit{background:#2a2a2a;border:1px solid #444;color:white;padding-left:8px;font-size:14px;}
    )");

    // 兑换按钮
    btnRedeem = new QPushButton("立即兑换", this);
    btnRedeem->setGeometry(350, 120, 70, 35);
    btnRedeem->setStyleSheet(R"(
        QPushButton{background:#22bb22;color:white;border-radius:4px;}
        QPushButton:hover{background:#22cc22;}
    )");

    // 提示
    labelTip = new QLabel("提示：赞助后自动领取兑换码", this);
    labelTip->setGeometry(60, 180, 350, 40);
    labelTip->setStyleSheet("color:#cccccc;font-size:13px;");

    // 关闭
    QPushButton *btnClose = new QPushButton("关闭窗口", this);
    btnClose->setGeometry(150, 240, 140, 45);
    btnClose->setStyleSheet(R"(
        QPushButton{background:#666;color:white;font-size:14px;border-radius:8px;}
        QPushButton:hover{background:#888;}
    )");

    // 绑定
    connect(btn1Yuan, &QPushButton::clicked, this, &PayWindow::pay1Yuan);
    connect(btn3Yuan, &QPushButton::clicked, this, &PayWindow::pay3Yuan);
    connect(btnRedeem, &QPushButton::clicked, this, &PayWindow::redeemCode);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::close);
}

// 5元赞助
void PayWindow::pay1Yuan()
{
    QString url = "https://ifdian.net/order/create?plan_id=03b1614049ea11f18ea352540025c377&product_type=0&remark=&affiliate_code=";
    QDesktopServices::openUrl(QUrl(url));
    labelTip->setText("已打开5元赞助页面，赞助后自动领兑换码");
}

// 6元赞助
void PayWindow::pay3Yuan()
{
    QString url = "https://ifdian.net/order/create?plan_id=0267d7d849ea11f1886352540025c377&product_type=0&remark=&affiliate_code=";
    QDesktopServices::openUrl(QUrl(url));
    labelTip->setText("已打开6元赞助页面，赞助后自动领兑换码");
}
void PayWindow::redeemCode()
{
    QString code = editCode->text().trimmed();
    if (code.isEmpty()) {
        labelTip->setText("请输入兑换码！");
        return;
    }
    if (usedCode.contains(code)) {
        labelTip->setText("❌ 该兑换码已使用！");
        editCode->clear();
        return;
    }

    // 5元兑换
    if (code1List.contains(code)) {
        usedCode.append(code);
        labelTip->setText("✅ 5元礼包兑换成功！攻击×2 血量×3！");
        g_playerAttack = 2;
        g_playerMaxHp  = 45;
        emit oneYuanReward();
        editCode->clear();
        return;
    }

    // 6元兑换
    if (code3List.contains(code)) {
        usedCode.append(code);
        labelTip->setText("✅ 6元礼包兑换成功！伤害翻倍+血量提升！");
        g_playerAttack = 4;
        g_playerMaxHp  = 100;

        emit activateThreeYuan();
        editCode->clear();
        return;
    }

    labelTip->setText("❌ 无效兑换码");
    editCode->clear();
}