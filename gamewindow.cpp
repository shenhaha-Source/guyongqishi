#include "gamewindow.h"
#include"guanqiawindow.h"
#include <QLabel>
#include <QFont>
#include<QPainter>
#include<QkeyEvent>
#include <QMessageBox>
#include"bullet.h"
#include <QSpacerItem>
#include <QGridLayout>
#include <QApplication>
#include <QTimer>
GameWindow::GameWindow(int level,QWidget *parent)
    : QWidget(parent) ,wodelevel(level),tujibing(nullptr)
{
    // 翻滚技能初始化
    // 初始化变量
    setFixedSize(1600, 1000);
    isRolling = false;
    rollSpeed = 10;
    rollRemain =200;
    rollCdTimer = 0;
    rollCdMax = 120;
    rollAnimFrame = 0;

    // 加载8方向翻滚帧（按你的文件路径修改）
    // 0: 上
    rollFrames[0][0].load(":/roll/up0.png");
    rollFrames[0][1].load(":/roll/up1.png");
    rollFrames[0][2].load(":/roll/up2.png");
    rollFrames[0][3].load(":/roll/up3.png");
    rollFrames[0][4].load(":/roll/up4.png");
    rollFrames[0][5].load(":/roll/up5.png");
    rollFrames[0][6].load(":/roll/up6.png");
    rollFrames[0][7].load(":/roll/up7.png");

    // 1: 右上
    rollFrames[1][0].load(":/roll/right0.png");
    rollFrames[1][1].load(":/roll/right1.png");
    rollFrames[1][2].load(":/roll/right2.png");
    rollFrames[1][3].load(":/roll/right3.png");
    rollFrames[1][4].load(":/roll/right4.png");
    rollFrames[1][5].load(":/roll/right5.png");
    rollFrames[1][6].load(":/roll/right6.png");
    rollFrames[1][7].load(":/roll/right7.png");
    // 2: 右
    rollFrames[2][0].load(":/roll/right0.png");
    rollFrames[2][1].load(":/roll/right1.png");
    rollFrames[2][2].load(":/roll/right2.png");
    rollFrames[2][3].load(":/roll/right3.png");
    rollFrames[2][4].load(":/roll/right4.png");
    rollFrames[2][5].load(":/roll/right5.png");
    rollFrames[2][6].load(":/roll/right6.png");
    rollFrames[2][7].load(":/roll/right7.png");
    // 3: 右下
    rollFrames[3][0].load(":/roll/right0.png");
    rollFrames[3][1].load(":/roll/right1.png");
    rollFrames[3][2].load(":/roll/right2.png");
    rollFrames[3][3].load(":/roll/right3.png");
    rollFrames[3][4].load(":/roll/right4.png");
    rollFrames[3][5].load(":/roll/right5.png");
    rollFrames[3][6].load(":/roll/right6.png");
    rollFrames[3][7].load(":/roll/right7.png");
    // 4: 下
    rollFrames[4][0].load(":/roll/up0.png");
    rollFrames[4][1].load(":/roll/up1.png");
    rollFrames[4][2].load(":/roll/up2.png");
    rollFrames[4][3].load(":/roll/up3.png");
    rollFrames[4][4].load(":/roll/up4.png");
    rollFrames[4][5].load(":/roll/up5.png");
    rollFrames[4][6].load(":/roll/up6.png");
    rollFrames[4][7].load(":/roll/up7.png");
    // ...
    // 5: 左下
    rollFrames[5][0].load(":/roll/left0.png");
    rollFrames[5][1].load(":/roll/left1.png");
    rollFrames[5][2].load(":/roll/left2.png");
    rollFrames[5][3].load(":/roll/left3.png");
    rollFrames[5][4].load(":/roll/left4.png");
    rollFrames[5][5].load(":/roll/left5.png");
    rollFrames[5][6].load(":/roll/left6.png");
    rollFrames[5][7].load(":/roll/left7.png");
    // 6: 左
    rollFrames[6][0].load(":/roll/left0.png");
    rollFrames[6][1].load(":/roll/left1.png");
    rollFrames[6][2].load(":/roll/left2.png");
    rollFrames[6][3].load(":/roll/left3.png");
    rollFrames[6][4].load(":/roll/left4.png");
    rollFrames[6][5].load(":/roll/left5.png");
    rollFrames[6][6].load(":/roll/left6.png");
    rollFrames[6][7].load(":/roll/left7.png");
    // 7: 左上
    rollFrames[7][0].load(":/roll/left0.png");
    rollFrames[7][1].load(":/roll/left1.png");
    rollFrames[7][2].load(":/roll/left2.png");
    rollFrames[7][3].load(":/roll/left3.png");
    rollFrames[7][4].load(":/roll/left4.png");
    rollFrames[7][5].load(":/roll/left5.png");
    rollFrames[7][6].load(":/roll/left6.png");
    rollFrames[7][7].load(":/roll/left7.png");
    // ...
    m_skill1Icon.load(":/obstacle/huo (2).png");
    m_skill1TotalCd = 30000;
    m_skill1LeftCd = 0;
    m_healTotalCd = 20000;
    m_healLeftCd  = 0;
    m_healEffect.setVolume(0.8);
    // 纯代码内置模拟回血音效，不用任何外部文件
    bossAnimIndex = 0;
    bossAnimDelay = 0;
    bossFaceRight = true;

    // 加载向左 6 张
    bossLeft[0].load(":/boss/left1.png");
    bossLeft[1].load(":/boss/left2.png");
    bossLeft[2].load(":/boss/left3.png");
    bossLeft[3].load(":/boss/left4.png");
    bossLeft[4].load(":/boss/left5.png");
    bossLeft[5].load(":/boss/left6.png");

    // 加载向右 6 张
    bossRight[0].load(":/boss/right1.png");
    bossRight[1].load(":/boss/right2.png");
    bossRight[2].load(":/boss/right3.png");
    bossRight[3].load(":/boss/right4.png");
    bossRight[4].load(":/boss/right5.png");
    bossRight[5].load(":/boss/right6.png");
    m_healEffect.setVolume(0.8);
    if (wodelevel == 1) {
        level1();
    } else if (wodelevel == 2) {
        level2();
    } else if (wodelevel == 3) {
        level3();
    }
    m_gameMusic = new QMediaPlayer(this);
    m_hurtSound = new QMediaPlayer(this);
    m_bossgame = new QMediaPlayer(this);
    // 为每个QMediaPlayer创建独立的音频输出
    m_gameAudio = new QAudioOutput(this);
    m_hurtAudio = new QAudioOutput(this);
    m_gameMusic->setAudioOutput(m_gameAudio);
    m_hurtSound->setAudioOutput(m_hurtAudio);
     m_bossaudio = new QAudioOutput(this);
    m_bossgame->setAudioOutput(m_bossaudio);
    // 加载文件（用setSource替代setMedia）
    m_gameMusic->setSource(QUrl("qrc:/shengyin/shoujiha (2).mp3"));
    m_hurtSound->setSource(QUrl("qrc:/shengyin/shouji.mp3"));
    m_bossgame->setSource(QUrl("qrc:/shengyin/haha.mp3")); // 你自己改路径
    // 音量控制（通过QAudioOutput）
    m_gameAudio->setVolume( g_gameBgmVolume);  // 0-1之间，对应50%
    m_hurtAudio->setVolume(g_hurtVolume);  // 100%
    // 回血音效（QSoundEffect用setSource）
    m_bossaudio->setVolume(0.5);
    m_gameMusic->play();
    // 启动游戏循环（必须加！否则画面完全不动）
    gametimer = new QTimer(this);
    connect(gametimer, &QTimer::timeout, this, &GameWindow::gameupdate);
    gametimer->start(16);

}
class FailMessageBox : public QMessageBox
{
public:
    explicit FailMessageBox(QWidget *parent = nullptr) : QMessageBox(parent) {
    this->setFixedSize(1000, 700);
    this->setStyleSheet(R"(
            QMessageBox {
                background-color: #f8f8f8;
                font-family: 微软雅黑;
                font-size: 16px; /* 全局文字大小 */
                padding: 20px;    /* 内边距，让内容不贴边 */
            }
            QMessageBox QLabel {
                font-size: 18px; /* 提示文字大小 */
                color: #333;
            }
            QMessageBox QPushButton {
                background-color: #ff4444;
                color: white;
                font-size: 14px;
                border: none;
                padding: 10px 30px; /* 按钮内边距，增大按钮 */
                border-radius: 8px;
                margin-top: 20px;   /* 按钮和文字拉开距离 */
            }
            QPushButton:hover {
                background-color: #ff6666;
            }
        )");}
protected:
    // 重写鼠标按下事件：任意鼠标键都关闭弹窗

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton ||
            event->button() == Qt::RightButton ||
            event->button() == Qt::MiddleButton)
        {

            this->accept();

            this->accept(); // 关闭弹窗
        }
        QMessageBox::mousePressEvent(event); }
};
void GameWindow::drawSkill(QPainter *p, int x, int y, int size,

                           QPixmap &icon, int leftMs, int totalMs

                           ){
    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    QRect rect(x, y, size, size);
    p->drawPixmap(rect, icon.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    if (leftMs > 0)
    {
        p->setBrush(QColor(0, 0, 0, 160));
        p->setPen(Qt::NoPen);
        p->drawRect(rect);

    // 画技能图标
    QRect rect(x, y, size, size);
    p->drawPixmap(rect, icon.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if (leftMs > 0)
    {
        // 黑色遮罩
        p->setBrush(QColor(0, 0, 0, 160));
        p->setPen(Qt::NoPen);
        p->drawRect(rect);

        // 关键转成整数秒 直接向下取整

        int sec = leftMs / 1000;
        p->setPen(Qt::white);
        QFont f("微软雅黑", 22, QFont::Bold);
        p->setFont(f);
        p->drawText(rect, Qt::AlignCenter, QString::number(sec));
    }

    p->restore();
    }}

    void GameWindow::applyOneYuanBuff()
{
    qishi.hitpointsmax=45;
    qishi.sethit_points(-30) ;
    qishi.setattack(2);

    update();
}
void GameWindow::activateThreeYuanBuff(){
       qishi.hitpointsmax=100;
  qishi.sethit_points(-90) ;
    qishi.setattack(4);
    update();
}
void GameWindow::drawHealSkill(QPainter *p, int x, int y, int size, int leftMs, int totalMs)
{
    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    QRect iconRect(x, y, size, size);
    p->setBrush(QColor(30, 130, 60));
    QPen pen(QColor(80, 200, 120), 2);
    p->setPen(pen);
    p->drawEllipse(iconRect);
    p->setBrush(Qt::white);
    p->setPen(Qt::white);
    int cx = x + size/2;
    int cy = y + size/2;
    int r  = size / 5;
    p->drawRect(cx - r/2, cy - r, r, r*2);
    p->drawRect(cx - r, cy - r/2, r*2, r);
    if(leftMs > 0)
    {
        p->setBrush(QColor(0,0,0,160));
        p->setPen(Qt::NoPen);
        p->drawEllipse(iconRect);
        int sec = leftMs / 1000;
        p->setPen(Qt::white);
        QFont f("微软雅黑", 22, QFont::Bold);
        p->setFont(f);
        p->drawText(iconRect, Qt::AlignCenter, QString::number(sec));
    }

    p->restore();
}
void GameWindow::playerdead()
{
    if (gametimer) gametimer->stop();
    clearLevel();
    FailMessageBox failBox;
    failBox.setWindowTitle("废物！游戏失败");
    failBox.setText("<font size='14' color='#d32f2f'>废物！游戏失败</font><br>骑士阵亡<br>点击鼠标任意键返回主界面");
    failBox.setWindowTitle("废物！游戏失败");
    failBox.setText("<font size='14' color='#d32f2f'>游戏失败</font><br>骑士阵亡<br>点击鼠标任意键返回主界面");
    QSpacerItem* hSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)failBox.layout();
    layout->addItem(hSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    failBox.setStyleSheet(R"(
    QMessageBox {
        background-color: #1e1e1e;
        color: white;
        font-family: 微软雅黑;
        font-size: 12px;
    }
    QPushButton {
        background-color: #d32f2f;
        color: white;
        border: none;
        padding: 6px 18px;
        border-radius: 4px;
    }
    QPushButton:hover {
        background-color: #ff5252;
    }
    )");
    m_gameMusic->stop();
        failBox.exec();
    emit playerdie();
}
void GameWindow::monsterdead(){
    if (gametimer) gametimer->stop();
    clearLevel();
    FailMessageBox failBox;
    failBox.setWindowTitle("游戏胜利！");
    failBox.setText("<font size='14' color='#d32f2f'>游戏胜利</font><br>怪物清除完毕<br>点击鼠标任意键返回主界面");
    QSpacerItem* hSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)failBox.layout();
    layout->addItem(hSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    failBox.setStyleSheet(R"(
    QMessageBox {
        background-color: #1e1e1e;
        color: white;
        font-family: 微软雅黑;
        font-size: 12px;
    }
    QPushButton {
        background-color: #d32f2f;
        color: white;
        border: none;
        padding: 6px 18px;
        border-radius: 4px;
    }
    QPushButton:hover {
        background-color: #ff5252;
    }
    )");
    m_gameMusic->stop();
    failBox.exec();
    emit monsterdie();
}
void GameWindow::shootbullet(){
    if(time2>0){
        return ;
    }
    time2=time1;
    if (m_monsterList.isEmpty())
        return;
    // 1. 找到离玩家最近的怪物
    monster* nearest = nullptr;
    double minDist = 1e9;

    int px = qishi.getX() + 25;
    int py =qishi.getY() + 25;

    for (auto* m : m_monsterList) {
        int mx = m->getX() + 25;
        int my = m->getY() + 25;

        double dx = mx - px;
        double dy = my - py;
        double dist = sqrt(dx*dx + dy*dy);

        if (dist < minDist) {
            minDist = dist;
            nearest = m;
        }
    }
    if (!nearest)
        return;
    // 2. 计算指向最近怪物的方向（直线）
    int tx = nearest->getX() + 25;
    int ty = nearest->getY() + 25;

    double dx = tx - px;
    double dy = ty - py;
    double len = sqrt(dx*dx + dy*dy) + 0.0001;
    double dirX = dx / len;
    double dirY = dy / len;
    // 3. 发射子弹
    m_bullets.push_back(new bullet(px, py, dirX, dirY,1));
    if(time7<time8){
        m_bullets.push_back(new bullet(px, py, dirX+0.3, dirY-0.4,1));
        m_bullets.push_back(new bullet(px, py, dirX+0.9, dirY+0.8,1));
        m_bullets.push_back(new bullet(px, py, dirX+0.7, dirY-0.1,1));
    }

}
void GameWindow::level1(){
    clearLevel();
    cur=1;
    bgPix.load(":/gamewindow/gamewindow.1.png");
    obstacle* obs1 = new obstacle;
    obs1->setpoints(200, 200);
    obs1->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs1);

    // ---------- 障碍物 2 ----------
    obstacle* obs2 = new obstacle;
    obs2->setpoints(1200, 200);
    obs2->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs2);

    // ---------- 障碍物 3 ----------
    obstacle* obs3 = new obstacle;
    obs3->setpoints(300, 700);
    obs3->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs3);
    obstacle* obs4= new obstacle;
    obs4->setpoints(1200, 700);
    obs4->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs4);

    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(100, 150);

    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(250, 200);

    m_monsterList.append(new monster(4));
    m_monsterList.last()->setpoints(400, 180);


    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(550, 220);

    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(700, 160);

    /*m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(550, 220);
    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(700, 160);*/
    m_monsterList.append(new monster(2));
    m_monsterList.last()->setpoints(900, 400);
    m_monsterList.append(new monster(2));
    m_monsterList.last()->setpoints(1150, 750);

    m_monsterList.append(new monster(3));
    m_monsterList.last()->setpoints(1350, 900);

    m_monsterList.append(new monster(3));
    m_monsterList.last()->setpoints(1500, 680);}
void GameWindow::level2(){
    clearLevel();
    cur=2;
    bgPix.load(":/gamewindow/gamewindow2.png");
    obstacle* obs1 = new obstacle;
    obs1->setpoints(200, 200);
    obs1->setpicture(":/obstacle/obstacle3(1).jpg");
    m_obstacles.append(obs1);

    // 障碍物 2
    obstacle* obs2 = new obstacle;
    obs2->setpoints(600, 450);
    obs2->setpicture(":/obstacle/obstacle2.jpg");
    m_obstacles.append(obs2);

    //  障碍物 3
    obstacle* obs3 = new obstacle;
    obs3->setpoints(1200, 700);
    obs3->setpicture(":/obstacle/obstacle3(1).jpg");
     m_obstacles.append(obs3);
    tujibing=new jimonster(1);
    tujibing->setpoints(900,900);
    m_monsterList.append(new monster(1));
    m_monsterList.last()->setpoints(250, 200);
    m_monsterList.append(new monster(2));
    m_monsterList.last()->setpoints(400, 180);
    m_monsterList.append(new monster(3));
    m_monsterList.last()->setpoints(250, 200);
    m_monsterList.append(new monster(4));
    m_monsterList.last()->setpoints(400, 180);

}
void GameWindow::level3(){
    clearLevel();
    cur=3;
    bgPix.load(":/gamewindow/gamewindow3.png");
    obstacle* obs1 = new obstacle;
    obs1->setpoints(200, 150);
    obs1->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs1);

    //障碍物 2
    obstacle* obs2 = new obstacle;
    obs2->setpoints(200, 700);
    obs2->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs2);

    // 障碍物 3
    obstacle* obs3 = new obstacle;
    obs3->setpoints(1200, 700);
    obs3->setpicture(":/obstacle/obstacle1(2).jpg");
    m_obstacles.append(obs3);
    m_monsterList.append(new monster(5));
    m_monsterList.last()->setpoints(600, 600);
}
bool flag1=false;
bool flag2=false;
void GameWindow::paintEvent(QPaintEvent*event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), bgPix);
    if (isRolling)
    {
        // 取当前方向、当前帧的图片
        const QPixmap &frame = rollFrames[rollDirIndex][rollAnimFrame];
        // 绘制（和你原来的骑士位置一致）
        painter.drawPixmap(qishi.getX(), qishi.getY(), frame);

    }
    else
    {
        qishi.draw(painter); // 正常状态用原来的绘制
    }
    for (auto* monster : m_monsterList) {
        // 如果是 BOSS，专门画左右行走动画
        if(cur==3 && monster->gettype()>=5)
        {
            if(bossFaceRight) {
                painter.drawPixmap(monster->getX(), monster->getY(),
                                   bossRight[bossAnimIndex]);
            } else {
                painter.drawPixmap(monster->getX(), monster->getY(),
                                   bossLeft[bossAnimIndex]);
            }
        }
        else {
            monster->darw(painter); // 普通怪物正常画
        }
    }
    QWidget::paintEvent(event);

    for (auto* b : m_bullets) b->draw(&painter);
    if(tujibing!=nullptr){
        tujibing->darw(painter);}
    for (obstacle* obs : m_obstacles) {
        obs->draw(painter);
    }
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿，让血条更顺滑

    //  1. 绘制血条背景（灰色，代表空血）
    QRect hpBgRect(20, 20, 200, 30);
    painter.setBrush(QColor(80, 80, 80)); // 背景灰色
    painter.setPen(QColor(200, 200, 200)); // 边框浅灰色
    painter.drawRoundedRect(hpBgRect, 5, 5);

    // 2. 绘制当前血量条（红色，随血量变化）
    // 计算血量条宽度：(当前血量/最大血量)*背景宽度
    int hpbarwidth = (qishi.gethit_points() * 1.0 / qishi.hitpointsmax) * hpBgRect.width();
    QRect hpbarrect(20, 20, hpbarwidth, 30); // 和背景位置一致，宽度随血量变
    painter.setBrush(QColor(220, 0, 0)); // 血量条红色
    painter.setPen(Qt::NoPen); // 血量条无边框
    painter.drawRoundedRect(hpbarrect, 5, 5);

    // 3. 绘制血量数值
    painter.setPen(Qt::white); // 文字白色
    painter.setFont(QFont("微软雅黑", 12, QFont::Bold)); // 字体+大小+加粗
    // 文字位置：血条正中间
    QString hpText = QString("%1/%2").arg(qishi.gethit_points()).arg(qishi.hitpointsmax);
    painter.drawText(hpBgRect, Qt::AlignCenter, hpText);
    QRect shieldBgRect(20, hpBgRect.y() + hpBgRect.height() + 10, 200, 30);
    // 护盾背景
    painter.setBrush(QColor(60, 60, 80));
    painter.setPen(QColor(180, 180, 200));
    painter.drawRoundedRect(shieldBgRect, 5, 5);
    // 当前护盾条
    // 护盾最大值是5，计算宽度：(当前护盾/最大护盾)*背景宽度
    int shieldBarWidth = (qishi.getbarrier() * 1.0 / 5.0 * shieldBgRect.width());
    QRect shieldBarRect(20, shieldBgRect.y(), shieldBarWidth, 30);
    painter.setBrush(QColor(0, 150, 255)); // 天蓝色护盾条
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(shieldBarRect, 5, 5);
    // 护盾数值（5/5）
    painter.setPen(Qt::white);
    painter.setFont(QFont("微软雅黑", 12, QFont::Bold));
    QString shieldText = QString("护盾: %1/%2").arg(qishi.getbarrier()).arg(5.0);
    painter.drawText(shieldBgRect, Qt::AlignCenter, shieldText);
    if(cur==3){
        monster*boss=nullptr;
        for(monster*m:m_monsterList){
            if(m->gettype()>=5){
                boss=m;
                break;
            }
        }
        if(boss!=nullptr){
            painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

            // 1. 绘制血条背景（灰色，代表空血）
            QRect bosshpBgRect(400, 20, 400, 30); // 位置(20,20)，宽200，高30
            painter.setBrush(QColor(80, 80, 80)); // 背景灰色
            painter.setPen(QColor(200, 200, 200)); // 边框浅灰色
            painter.drawRoundedRect(bosshpBgRect, 5, 5); // 圆角矩形
            int hpbaarwidth = (boss->gethit_points() * 1.0 / 240.0) * bosshpBgRect.width();
            QRect hpbaarrect(400, 20, hpbaarwidth, 30); // 和背景位置一致，宽度随血量变
            painter.setBrush(QColor(220, 0, 0)); // 血量条红色
            painter.setPen(Qt::NoPen); // 血量条无边框
            painter.drawRoundedRect(hpbaarrect, 5, 5);

            // 绘制血量数值
            painter.setPen(Qt::white); // 文字白色
            painter.setFont(QFont("微软雅黑", 12, QFont::Bold)); // 字体+大小+加粗
            // 文字位置：血条正中间
            QString hpText = QString("%1/%2").arg(boss->gethit_points()).arg(240.0);
            painter.drawText(bosshpBgRect, Qt::AlignCenter, hpText);
            QRect shieldBgRect(20, bosshpBgRect.y() + bosshpBgRect.height() + 10, 200, 30);
        }
    }
    int skillSize = 80;
    int posY = 20 + 30 + 10 + 30 + 20; // 血条高30 + 间距10 + 护盾条高30 + 额外间距20
    drawSkill(&painter, 20, posY, skillSize,
              m_skill1Icon, m_skill1LeftCd, m_skill1TotalCd);

    drawHealSkill(&painter, 110, posY, 80, m_healLeftCd, m_healTotalCd);

    }
void GameWindow::clearLevel()
{
    // 清空背景
    bgPix = QPixmap();
    qDeleteAll(m_monsterList);
    m_monsterList.clear();qDeleteAll(m_bullets);
    m_bullets.clear();
        // 子弹只清空列表
        // 重置关卡相关变量
    qDeleteAll(m_obstacles);
    m_obstacles.clear();
        time2 = 0;
        time4 = 50;
        if(tujibing!=nullptr){
            delete tujibing;
        }
}
void GameWindow::gameupdate(){
    //计算技能的冷却时间
    if (m_skill1LeftCd > 0)
    {
        m_skill1LeftCd -= 16;
        if (m_skill1LeftCd < 0) m_skill1LeftCd = 0;
    }
    //技能的持续时间
    if(time7<time8){
        time7+=16;
        if(time7>time8){
            time7=time8;
        }
    }
    //这个是突击兵的碰撞间隔时长
    if(time10<=500){
        time10+=16;
        if(time10>500){
            time10=500;
        }
    }
    //这个是受到击打间隔最短间隔时长
    if(time9<500){
        time9+=16;
        if(time9>=500){
            time9=500;
        }
    }
    //骑士死亡，执行死亡函数
    if(qishi.gethit_points()<=0){
        playerdead();
    }
    //如果怪物死亡或者kaka(boss死亡）执行怪物死亡函数
    if((m_monsterList.isEmpty()||kaka==true)&&qishi.gethit_points()>0){
        cur=1;
        kaka=false;
        monsterdead();
    }
    if(time6>0){
        time6--;
    }
    if(time2>0){
        time2--;
    }
    if(time4>0){
        time4--;
    }

    if( m_healLeftCd>=0){
        m_healLeftCd-=16;
        if( m_healTotalCd<=0){
            m_healTotalCd=0;
        }
    }

    // 翻滚逻辑
    // ===================== 最终丝滑8方向翻滚 =====================
    // 翻滚逻辑
    // ===================== 【丝滑翻滚位移 —— 完全不闪现】 =====================
    static int rollAnimDelay = 0;

    if (rollCdTimer > 0) rollCdTimer--;

    if (isRolling)
    {
        // 固定每帧移动一点点，绝对不闪现
        float speed = 14.5f;       // 慢一点，平滑
        float diag = 14.5f;       // 斜向速度
        float moveX = 0, moveY = 0;

        switch (rollDirIndex)
        {
        case 0: moveY = -speed; break;
        case 1: moveX = diag; moveY = -diag; break;
        case 2: moveX = speed; break;
        case 3: moveX = diag; moveY = diag; break;
        case 4: moveY = speed; break;
        case 5: moveX = -diag; moveY = diag; break;
        case 6: moveX = -speed; break;
        case 7: moveX = -diag; moveY = -diag; break;
        }

        // 真正平滑位移
        qishi.setX(qishi.getX() + moveX);
        qishi.setY(qishi.getY() + moveY);

        // 控制翻滚距离：距离短一点、时间长一点，就不会闪现
        rollRemain -= speed;
        if (rollRemain <= 0) {
            isRolling = false;
            rollCdTimer = 20;
            rollAnimFrame = 0;
            rollAnimDelay = 0;
        }

        // 动画播放
        rollAnimDelay++;
        if (rollAnimDelay >= 2) {
            rollAnimFrame++;
            rollAnimDelay = 0;
        }
        if (rollAnimFrame >= 8) rollAnimFrame = 7;
        if(qishi.getX()<0){
            qishi.setX(0);
        }
        if(qishi.getX()>this->width()-qishi.geiwidth()){
            qishi.setX(this->width()-qishi.geiwidth());
        }
        if(qishi.getY()<0){
            qishi.setY(0);
        }
        if(qishi.getY()>this->height()-qishi.getheight()){
            qishi.setY(this->height()-qishi.getheight());
        }
        update();
    }

    // ========================================================================

    if(tujibing!=nullptr){
        tujibing->settarget(qishi.getX(),qishi.getY());
        tujibing->update();}
    if(cur==3){
        //这个是boss召唤小怪间隔时长

        bossAnimDelay++;
        if(bossAnimDelay >= 10) {  // 数字越小动画越快
            bossAnimIndex++;
            bossAnimDelay = 0;
            if(bossAnimIndex >=6) bossAnimIndex =0;
        }
        static int faceTimer = 0;
        faceTimer++;
        static int bosstime1=1000;
        //这个是攻击间隔时长
        static int bosstime2=100;
         monster* boss = nullptr;
        for(monster*m:m_monsterList){
            if(m->gettype()>=5){
                boss=m;
            break;}}
        /*if(!boss){
            return;
        }*/
        if(boss!=nullptr&&boss->gethit_points()>0){

            if(faceTimer >= 15)
            {
                faceTimer = 0;
                if(boss->getX() < qishi.getX())
                    bossFaceRight = true;
                else
                    bossFaceRight = false;
            }
                int bx=boss->getX()+boss->getwidth()/2;
                int by=boss->getY()+boss->getheigth()/2;
                int px=qishi.getX()+qishi.geiwidth()/2;
                int py=qishi.getY()+qishi.getheight()/2;
                int hx=px-bx;
                int hy=py-by;
                double len=sqrt(hx*hx+hy*hy)+0.001;
                //召唤小怪
                if(bosstime1<=0){
                    bosstime1=1000;
                    m_bossgame->setPosition(0);
                    m_bossgame->play();
                    monster*q1=new monster(2);
                    q1->setpoints(bx+200,by+200);
                    m_monsterList.push_back(q1);
                    monster*q2=new monster(2);
                    q2->setpoints(bx+200,by-200);
                    m_monsterList.push_back(q2);
                        monster*q3=new monster(2);
                    q3->setpoints(bx-200,by-200);
                        m_monsterList.push_back(q3);

                }
                bosstime1--;
                //发射子弹
                if(bosstime2<=0){
                    bosstime2=60;
                    m_bullets.push_back(new bullet(bx, by, hx/len, hy/len, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.42, hy/len+0.66, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len-0.255, hy/len-0.88, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.7, hy/len-0.11, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.12, hy/len+0.32, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len-0.26, hy/len-0.19, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.33, hy/len-0.22, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.26, hy/len+0.52, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len-0.22, hy/len-0.12, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.17, hy/len, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len+0.32, hy/len+0.12, 5));
                    m_bullets.push_back(new bullet(bx, by, hx/len-0.29, hy/len-0.12, 5));

                }
                bosstime2--;
        }
            if(boss==nullptr){
                kaka=true;
            }
            update();}
    QRect playerRect(qishi.getX(),qishi.getY() , qishi.geiwidth(), qishi.getheight());
    for (obstacle* obs : m_obstacles) {
        QRect orc = obs->rect();
        if (playerRect.intersects(orc)) {
            // 简单推开，防止穿过去
            int leftDiff   = playerRect.right() - orc.left();
            int rightDiff  = orc.right() - playerRect.left();
            int topDiff    = playerRect.bottom() - orc.top();
            int bottomDiff = orc.bottom() - playerRect.top();

            // 找出重叠最短的一边，单向推开
            int minDiff = qMin(qMin(leftDiff, rightDiff), qMin(topDiff, bottomDiff));
            const int push = 6; // 轻微推开

            if(minDiff == leftDiff)
            {
                qishi.setX(orc.left() - qishi.geiwidth());
            }
            else if(minDiff == rightDiff)
            {
                qishi.setX(orc.right());
            }
            else if(minDiff == topDiff)
            {
                qishi.setY(orc.top() - qishi.getheight());
            }
            else if(minDiff == bottomDiff)
            {
                qishi.setY(orc.bottom());
            }
        }
    }
    for (auto* monster : m_monsterList) {
        monster->settarget(qishi.getX(),qishi.getY());
        monster->update();
        QRect mRect(
            monster->getX(),
            monster->getY(),
            monster->getwidth(),
            monster->getheigth()
            );
        int maxxx = this->width() - monster->getwidth();
        int maxll = this->height() - monster->getheigth();
        if(monster->getX()+monster->getwidth()>this->width()){
            monster->setX(maxxx);
        }
        if(monster->getY()>maxll){
            monster->setY(maxll);
        }
        //怪物撞障碍物
            if (mRect.intersects(playerRect)) {
                int leftDiff   = mRect.right() - playerRect.left();
                int rightDiff  = playerRect.right() - mRect.left();
                int topDiff    = mRect.bottom() - playerRect.top();
                int bottomDiff = playerRect.bottom() - mRect.top();

                // 找出重叠最短的一边，单向推开
                int minDiff = qMin(qMin(leftDiff, rightDiff), qMin(topDiff, bottomDiff));
                const int push = 6; // 轻微推开

                if(minDiff == leftDiff)
                {
                    monster->setX(playerRect.left() - monster->getwidth());
                }
                else if(minDiff == rightDiff)
                {
                    monster->setX(playerRect.right());
                }
                else if(minDiff == topDiff)
                {
                    monster->setY(playerRect.top() - monster->getheigth());
                }
                else if(minDiff == bottomDiff)
                {
                    monster->setY(playerRect.bottom());
                }
            }
            for(obstacle*w:m_obstacles){
                if(mRect.intersects(w->rect())){
                    int leftDiff   = mRect.right() - w->rect().left();
                    int rightDiff  = w->rect().right() - mRect.left();
                    int topDiff    = mRect.bottom() - w->rect().top();
                    int bottomDiff = w->rect().bottom() - mRect.top();


                    int minDiff = qMin(qMin(leftDiff, rightDiff), qMin(topDiff, bottomDiff));
                    const int push = 12;

                    if(minDiff == leftDiff)
                    {
                        monster->setX(w->rect().left() - monster->getwidth());
                    }
                    else if(minDiff == rightDiff)
                    {
                        monster->setX(w->rect().right());
                    }
                    else if(minDiff == topDiff)
                    {
                        monster->setY(w->rect().top() - monster->getheigth());
                    }
                    else if(minDiff == bottomDiff)
                    {
                        monster->setY(w->rect().bottom());
                    }

                }
            }
    }
    //如果突击兵碰到骑士，如果还有护盾减去五滴护盾，否则减去五滴血
    if(tujibing!=nullptr){
        QRect tujibingRect(tujibing->getX(),tujibing->getY() , tujibing->getwidth(), tujibing->getheigth());
        if (tujibing->rect().intersects(playerRect)){
            if(time10==500){
                if(qishi.getbarrier()>0){
                    qishi.set_barrier(5);
                    time10=0;
                }else{
                qishi.sethit_points(5);
                    time10=0;}
            }
        }}
for (auto it = m_bullets.begin(); it != m_bullets.end();) {
        bullet* b = *it;
        b->update();

        if (!b->isactive()) {
            delete b;
            it = m_bullets.erase(it);
            continue;
        }
        bool hihi=false;
        for(obstacle*obs:m_obstacles){
            if(obs->rect().intersects(b->rect())){
                hihi=true;
                break;
            }}
        if(hihi){
            delete b;
            it=m_bullets.erase(it);
            continue;
        }
        if(b->gettype()==1){
            bool hit = false;
        for (auto mit = m_monsterList.begin(); mit != m_monsterList.end();) {
               monster* m = *mit;
            if (b->rect().intersects(m->rect())) {

                m->takedamage(qishi.getattack());

                hit = true;

                if (m->isdead()) {
                    delete m;
                    mit = m_monsterList.erase(mit);
                } else {
                    ++mit;
                }
                break;
            } else {
                ++mit;
            }
        }

        if (hit) {
            delete b;
            it = m_bullets.erase(it);
        } else {
            ++it;
        }}
        if (b->gettype()>1) {
            bool hit=false;
            if (b->rect().intersects(playerRect)) {
                // 骑士掉
            if(qishi.getbarrier()>0){
                qishi.set_barrier(1);
                if(time9==500){
                 m_hurtSound->setPosition(0);
                m_hurtSound->play();
                 time9=0;
                }
                hit=true;
                }
            //护盾消失则掉血
            else if(qishi.getbarrier()<=0){
                qishi.sethit_points(1);
                    if(time9==500){
                        m_hurtSound->setPosition(0);
                        m_hurtSound->play();
                        time9=0;
                    }
                    hit = true;}
            }
        //子弹打中，则子弹消失
        if (hit) {
                delete b;
             it = m_bullets.erase(it);
        } else {
            ++it;
        }
        }}
    for (int i = 0; i < m_monsterList.size(); ++i) {
        monster* a = m_monsterList[i];
        QRect ra = a->rect();
        for (int j = i+1; j < m_monsterList.size(); ++j) {
            monster* b = m_monsterList[j];
            QRect rb = b->rect();
            if (ra.intersects(rb)) {

                int dx = b->getX()-a->getX();
                int dy = b->getY()-a->getY();
                double len = sqrt(dx*dx + dy*dy) + 1;

                // 互相推开
                int push = 3;
                a->setpoints(a->getX() - dx/len*push, a->getY()- dy/len*push);
                b->setpoints(b->getX() + dx/len*push, b->getY() + dy/len*push);
            }
        }
    }
    //护盾随时间自动恢复
    if(time6==0){
        time6=time5;
        qishi.set_barrier(-1);
    }
    if (time4 == 0) {
        time4=time3;
        for (monster* m : m_monsterList) {
            int mx = m->getX() + m->getwidth()/2;
            int my = m->getY() + m->getheigth()/2;
            int px = qishi.getX() + qishi.geiwidth()/2;
            int py = qishi.getY() + qishi.getheight()/2;
            double dx = px - mx;
            double dy = py - my;
            double len = sqrt(dx*dx + dy*dy) + 0.0001;
            int mytype=m->gettype();
            if(mytype==1){
                m_bullets.push_back(new bullet(mx, my, dx/len, dy/len, mytype+1));}
            if(mytype==2){
                  m_bullets.push_back(new bullet(mx, my, dx/len+0.22, dy/len+0.12, mytype+1));
                  m_bullets.push_back(new bullet(mx, my, dx/len-0.22, dy/len-0.12, mytype+1));
            }
            if(mytype==3){
               m_bullets.push_back(new bullet(mx, my, dx/len, dy/len, mytype+1));
            }
            if(mytype==4){
                m_bullets.push_back(new bullet(mx, my, dx/len, dy/len, mytype+1));
                m_bullets.push_back(new bullet(mx, my, dx/len+0.22, dy/len+0.12, mytype+1));
                m_bullets.push_back(new bullet(mx, my, dx/len-0.22, dy/len-0.12, mytype+1));
            }
            else{};
        }}
    int currentIndex = qishi.getwalkindex();
    int currentTimer = qishi.getwalktimer();
    //骑士的行为移动函数
    if(!isRolling){
    if(KeyW){
        qishi.moveup();
        qishi.setwalkindex(-1);
        qishi.setwalktimer(0);
        qishi.isleftmove=false;
        qishi.isrightmove=false;
        }
    if(keyA){
            if(!flag1){
            qishi.setwalkindex(-1);
            qishi.setwalktimer(0);
            flag1=true;
            flag2=false;
            }
            qishi.stopright=false;
            qishi.stopleft=true;
            qishi.isrightmove=false;
            qishi.isleftmove=true;
            if(qishi.isleftmove){
                if (currentIndex == -1)
                {
                    qishi.setwalkindex(0);
                }
                currentTimer++;
                if (currentTimer >= 6)
                {
                    // 切换到下一张图
                    int newIndex = currentIndex + 1;
                    if (newIndex >= 4)
                        newIndex = 0;

                    // 给walkindex和walktimer赋值
                    qishi.setwalkindex(newIndex);
                    qishi.setwalktimer(0);  // 计时器重置
                }
                else
                {
                    // 计时器未到，更新计时器的值
                    qishi.setwalktimer(currentTimer);
                }
        qishi.moveleft();
            }}
    if(keyD){
        if(!flag2){
            qishi.setwalkindex(-1);
            qishi.setwalktimer(0);
            flag2=true;
            flag1=false;
        }
        qishi.stopright=true;
        qishi.stopleft=false;
        qishi.isrightmove=true;
        qishi.isleftmove=false;
        if(qishi.isrightmove){
        if (currentIndex == -1)
        {

            qishi.setwalkindex(0);
        }

        // 控制动画切换速度
        currentTimer++;
        if (currentTimer >= 6)
        {
            // 切换到下一张图
            int newIndex = currentIndex + 1;
            if (newIndex >= 4)
                newIndex = 0;

            // 给walkindex和walktimer赋值
            qishi.setwalkindex(newIndex);
            qishi.setwalktimer(0);  // 计时器重置
        }
        else
        {

            qishi.setwalktimer(currentTimer);
        }
        qishi.moveright();}
}
    if(keyS){
        qishi.setwalkindex(-1);
        qishi.setwalktimer(0);
        qishi.isleftmove=false;
        qishi.isrightmove=false;
        qishi.movedown();
    }
    if(keyK){
        shootbullet();
    }
    int maxX=this->width()-qishi.geiwidth();
    int maxY=this->height()-qishi.getheight();
    if(qishi.getX()<0){
        qishi.setX(0);
    }
    if(qishi.getX()>maxX){
        qishi.setX(maxX);
    }
    if(qishi.getY()<0){
        qishi.setY(0);
    }
    if(qishi.getY()>maxY){
        qishi.setY(maxY);
    }
    update();
    }}

    void GameWindow:: keyPressEvent(QKeyEvent*event){
        if(event->isAutoRepeat()){
            return ;
        }
        switch(event->key()){
        case Qt::Key_W:
            KeyW=true;
            break;
        case Qt::Key_S:
            keyS=true;
            break;
        case Qt::Key_A:
            keyA=true;
            break;
        case Qt::Key_D:
            keyD=true;
            break;
        case Qt::Key_K:
            keyK=true;
            break;
        case Qt::Key_L:
            if (m_skill1LeftCd <= 0)
            {
                m_skill1LeftCd = m_skill1TotalCd; // 重置为总冷却时间
                time7=0;
            }
            else
            {
            }
            break;

        case Qt::Key_P:
        {
            if(m_healLeftCd <= 0)
            {
                // 回4滴血
                int hp = qishi.gethit_points() + 4;
                if(hp>qishi.hitpointsmax){
                    qishi.sethit_points(qishi.gethit_points()-qishi.hitpointsmax);
                }
                else{
                    qishi.sethit_points(-4);}

                // ======================================
                // 就把回血声音 加在这里！！！
                // ======================================


                // CD 20秒
                m_healLeftCd = m_healTotalCd;
            }
            break;
        }
        case Qt::Key_M:
        {
            if (!isRolling && rollCdTimer <= 0)
            {
                int dx = 0, dy = 0;
                if (keyA) dx = -1;
                if (keyD) dx = 1;
                if (KeyW) dy = -1;
                if (keyS) dy = 1;

                if (dx == 0 && dy == 0) break; // 无方向不触发

                // 核心：8方向索引判断
                if      (dy == -1 && dx == 0) rollDirIndex = 0; // 上
                else if (dy == -1 && dx == 1) rollDirIndex = 1; // 右上
                else if (dy == 0  && dx == 1) rollDirIndex = 2; // 右
                else if (dy == 1  && dx == 1) rollDirIndex = 3; // 右下
                else if (dy == 1  && dx == 0) rollDirIndex = 4; // 下
                else if (dy == 1  && dx == -1) rollDirIndex = 5; // 左下
                else if (dy == 0  && dx == -1) rollDirIndex = 6; // 左
                else if (dy == -1 && dx == -1) rollDirIndex = 7; // 左上

                // 初始化翻滚状态
                isRolling = true;
                rollRemain = 200; // 翻滚总距离，和动画时长匹配
                rollAnimFrame = 0;
            }
            break;
        }
        }}
    void GameWindow::keyReleaseEvent(QKeyEvent *event)
    {
        if(event->isAutoRepeat()){
            return ;
        }

        switch(event->key()){
        case Qt::Key_W:
            KeyW = false;
            break;
        case Qt::Key_S:
            keyS = false;
            break;
        case Qt::Key_A:
            keyA = false;
            break;
        case Qt::Key_D:
            keyD = false;
            break;
        case Qt::Key_K:
            keyK = false;
            break;

        // 下面这些按键松开不需要处理
        case Qt::Key_L:
        case Qt::Key_P:
        case Qt::Key_M:
            break;
        }
    }




