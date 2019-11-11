//#include "widget.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>

#include "custom_item.h"
#include "custom_scene.h"

#include <QPushButton>

int _main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    custom_scene scene;
    scene.setSceneRect(0, 0, 400, 300);

    QPushButton* pb1=new QPushButton;
    QPushButton* pb2=new QPushButton;
    QPushButton* pb3=new QPushButton;
    QPushButton* pb4=new QPushButton;
    QGraphicsProxyWidget* b1 = scene.addWidget(pb1);
    QGraphicsProxyWidget* b2 = scene.addWidget(pb2);
    QGraphicsProxyWidget* b3 = scene.addWidget(pb3);
    QGraphicsProxyWidget* b4 = scene.addWidget(pb4);

    custom_item *pItem = new custom_item();
    pItem->setRect(20, 20, 60, 60);
    scene.addItem(pItem);

    QGraphicsGridLayout layout;
    layout.addItem((QGraphicsLayoutItem*)b1,0,0,1,1);
    layout.addItem((QGraphicsLayoutItem*)b2,1,2,3,3);

    //QGraphicsWidget widget;
    //widget.setLayout(&layout);

    //scene.addItem(&widget);

    QGraphicsView view;
    view.setScene(&scene);
    view.show();

    return a.exec();
}




#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

int __main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGroupBox *pGroupBox = new QGroupBox();
    QLabel *pTellLabel = new QLabel();
    QLabel *pAddressLabel = new QLabel();
    QLineEdit *pTellLineEdit = new QLineEdit();
    QLineEdit *pAddressLineEdit = new QLineEdit();

    pGroupBox->setTitle(QStringLiteral("联系方式"));
    pTellLabel->setText(QStringLiteral("电话号码"));
    pAddressLabel->setText(QStringLiteral("居住地址"));
    pTellLineEdit->setPlaceholderText(QStringLiteral("手机/固话"));
    pAddressLineEdit->setPlaceholderText(QStringLiteral("具体到门牌号"));

    QFormLayout *pLayout = new QFormLayout;
    pLayout->addRow(pTellLabel, pTellLineEdit);
    pLayout->addRow(pAddressLabel, pAddressLineEdit);
    pLayout->setSpacing(10);
    pLayout->setMargin(20);
    pGroupBox->setLayout(pLayout);

    QGraphicsScene scene;
    QGraphicsProxyWidget *pProxy = scene.addWidget(pGroupBox);

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}



#include <QGraphicsProxyWidget>

class XGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    XGraphicsProxyWidget (QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);

    void	SetGraphicsMode(GraphicsItemFlags);

protected:
    void	mousePressEvent(QGraphicsSceneMouseEvent*);
    void	mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void	mouseMoveEvent(QGraphicsSceneMouseEvent*);

private:
    void	StartGraphicsMode();
    void	StopGraphicsMode();

    bool	IsGraphicsMode() const;

private:
    GraphicsItemFlags	m_eWidgetFlag;
    GraphicsItemFlags	m_eGraphicsFlag;
};

XGraphicsProxyWidget::XGraphicsProxyWidget( QGraphicsItem * parent /* = 0 */, Qt::WindowFlags wFlags /* = 0 */ ) :
    QGraphicsProxyWidget(parent, wFlags),
    m_eWidgetFlag(flags()),
    m_eGraphicsFlag(0)
{

}

void XGraphicsProxyWidget::SetGraphicsMode(GraphicsItemFlags flags)
{
    m_eGraphicsFlag = flags;
}

void XGraphicsProxyWidget::StartGraphicsMode()
{
    m_eWidgetFlag = flags(); // save

    setFlags(m_eGraphicsFlag);
}

void XGraphicsProxyWidget::StopGraphicsMode()
{
    setFlags(m_eWidgetFlag);
}

bool XGraphicsProxyWidget::IsGraphicsMode() const
{
    return flags() == m_eGraphicsFlag;
}

void XGraphicsProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if (event-> == QEvent::GraphicsSceneMousePress && (event->modifiers() & Qt::ControlModifier))
    if(1)
    {
        StartGraphicsMode();

        QGraphicsProxyWidget::mousePressEvent(event);
        QGraphicsItem::mousePressEvent(event);


    }
    else
    {
        QGraphicsProxyWidget::mousePressEvent(event);
    }
}

void XGraphicsProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (IsGraphicsMode())
    {
        StopGraphicsMode();
        QGraphicsItem::mouseReleaseEvent(event);
    }
    else
    {
        QGraphicsProxyWidget::mouseReleaseEvent(event);
    }
}

void XGraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (IsGraphicsMode())
        QGraphicsItem::mouseMoveEvent(event);
    else
        QGraphicsProxyWidget::mouseMoveEvent(event);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QGraphicsScene *m_pScene = new QGraphicsScene;
        QGraphicsView* m_pView = new QGraphicsView(m_pScene);
        //m_pView->resize(800, 600);
        //setCentralWidget(m_pView);

        QLineEdit* pb = new QLineEdit("text");
        XGraphicsProxyWidget *proxy = new XGraphicsProxyWidget;
        proxy->setWidget(pb);
        proxy->SetGraphicsMode(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        m_pScene->addItem(proxy);

        m_pView->show();

    return a.exec();
}
