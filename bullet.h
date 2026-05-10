#ifndef BULLET_H
#define BULLET_H
#include <QPixmap>
#include <QRect>
class bullet
{
public:
    bullet(int sx, int sy, double dx, double dy,int type);
    ~bullet();
    void update();
    void draw(QPainter* p);
    QRect rect() ;
    bool isactive() ;
    void setinactive();
    int damage() const { return attack; }
    int  gettype();
    void getattck(int a);
private:
    int mytype;
    QPixmap pix;
    int x, y;
    double dx, dy;
    double speed;
    bool active;

    int attack=1;
};
#endif // BULLET_H



