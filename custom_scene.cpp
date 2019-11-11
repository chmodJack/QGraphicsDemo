#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "custom_scene.h"
#include "custom_item.h"

// 自定义 Scene
void custom_scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene clicked.";
    QGraphicsScene::mousePressEvent(event);

    if (!event->isAccepted())
    {
        if (event->button() == Qt::LeftButton)
        {
            // 在 Scene 上添加一个自定义 item
            QPointF point = event->scenePos();
            custom_item *item = new custom_item();
            item->setRect(point.x()-30, point.y()-30, 60, 60);
            addItem(item);
        }
        else if (event->button() == Qt::RightButton)
        {
            // 检测光标下是否有 item
            QGraphicsItem *itemToRemove = NULL;
            foreach (QGraphicsItem *item, items(event->scenePos()))
            {
                if (item->type() == QGraphicsItem::UserType+1)
                {
                    itemToRemove = item;
                    break;
                }
            }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
                removeItem(itemToRemove);
        }
    }
}

void custom_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene moved.";
    QGraphicsScene::mouseMoveEvent(event);
}

void custom_scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
    {
        // 移除所有选中的 items
        qDebug() << "selected items " << selectedItems().size();
        while (!selectedItems().isEmpty())
        {
            removeItem(selectedItems().front());
        }
    }
    else
    {
        QGraphicsScene::keyPressEvent(event);
    }
}
