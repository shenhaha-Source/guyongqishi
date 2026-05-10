#include "rulerwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLinearGradient>

rulerwindow::rulerwindow(QWidget *parent) : QDialog(parent)
{
    setFixedSize(800, 800);
    setWindowTitle("游戏规则");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void rulerwindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(35, 45, 65));
    gradient.setColorAt(1, QColor(20, 30, 45));
    painter.fillRect(rect(), gradient);
    painter.setPen(QColor(255, 255, 255));
    painter.setFont(QFont("微软雅黑", 30, QFont::Bold));
    int titleY = height() * 0.1;
    painter.drawText(0, titleY, width(), 60, Qt::AlignCenter, "游戏规则");
    painter.setPen(QColor(100, 130, 180));
    painter.drawLine(150, titleY + 55, width() - 150, titleY + 55);
    int midX = width() / 2;
    int leftStartX = 60;
    int rightStartX = midX + 30;
    int baseY = titleY + 100;
    int lineHeight = 42;
    painter.setPen(QColor(120, 180, 255));
    painter.setFont(QFont("微软雅黑", 20, QFont::Medium));
    painter.drawText(leftStartX, baseY, "🎮 操作键位");
    painter.setFont(QFont("微软雅黑", 17));
    painter.setPen(QColor(220, 230, 245));
    painter.drawText(leftStartX + 25, baseY + lineHeight, "W  -  向上移动");
    painter.drawText(leftStartX + 25, baseY + 2*lineHeight, "S  -  向下移动");
    painter.drawText(leftStartX + 25, baseY + 3*lineHeight, "A  -  向左移动");
    painter.drawText(leftStartX + 25, baseY + 4*lineHeight, "D  -  向右移动");
    painter.drawText(leftStartX + 25, baseY + 5*lineHeight, "K  -  攻击键位");
    painter.drawText(leftStartX + 25, baseY + 6*lineHeight, "L  -  技能键位");
    painter.drawText(leftStartX + 25, baseY + 7*lineHeight, "P -  回血键位");
    painter.drawText(leftStartX + 25, baseY + 8*lineHeight, "M  -  冲刺键位");
    painter.setPen(QColor(120, 180, 255));
    painter.setFont(QFont("微软雅黑", 20, QFont::Medium));
    painter.drawText(rightStartX, baseY, "📋 关卡规则");
    painter.setFont(QFont("微软雅黑", 16));
    painter.setPen(QColor(220, 230, 245));
    painter.drawText(rightStartX + 25, baseY + lineHeight, "1. 第一、二关：消灭所有怪物胜利");
    painter.drawText(rightStartX + 25, baseY + 2*lineHeight, "2. 第三关：击败最终Boss即可胜利");
    painter.setPen(QColor(255, 200, 80));
    painter.drawText(rightStartX + 25, baseY + 3*lineHeight, "⚠️ 特别注意：");
    painter.setPen(QColor(255, 110, 110));
    painter.drawText(rightStartX + 45, baseY + 4*lineHeight, "第二关炸弹人触碰角色扣5滴血");
    painter.setPen(QColor(150, 160, 180));
    painter.setFont(QFont("微软雅黑", 15));
    int tipY = height() * 0.88;
    painter.drawText(0, tipY, width(), 40, Qt::AlignCenter, "点击任意位置返回主界面");
}

void rulerwindow::mousePressEvent(QMouseEvent *event)
{
    emit showmainwindow();
    close();
    QDialog::mousePressEvent(event);
}