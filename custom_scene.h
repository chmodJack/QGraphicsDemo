#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

class custom_scene : public QGraphicsScene
{
protected:
    // 左键：添加item  右键：移除item
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    // Backspace键移除item
    void keyPressEvent(QKeyEvent *event);
};

#endif // CUSTOM_SCENE_H
