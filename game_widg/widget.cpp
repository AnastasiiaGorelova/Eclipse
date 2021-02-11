#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

//ближайшее TODO::
//
//вынести все константы
//в widget.cpp и widget.h посмотреть как разнести по разным классам (сейчас там хаос :)))
//добавить изображения отдельной папкой к проекту и прописать к ним относительный путь
//верхняя панель
//поменять начальную установку корабля (чтобы в самом начале игры был в середине)
//установить таймер
//вшить систему жизней
//когда будет вводиться система доп жизней, надо будет менять типы объектов
//отслеживание вылета астероидов за границу
//рандом астероидов --> фиксированные размеры + (пока не понятно как) отслеживать, чтобы два не вылетали рядом (издежать накладки графики)
//сменить графику на более крупную, все размыто
//+пофиксить изображение корабля, чтобы было симметричным
//возможно: смена управления бластерами на бесконечно стреляющие
//минимальное меню

//верхняя панель: прямоугольник унаследованный от сцены, покрасим в черный, лэйбл с таймером унаследованный от

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap img("/home/alena/Documents/Eclipse/images/background.jpeg");
    ui->graphicsView->setBackgroundBrush(img);

    scene = new QGraphicsScene(0, 0, 800, 600, this); //устанавливаем координаты отображения, указываем родителя
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect()); //добавляем прямоугольник по формату сцены
    scene->setStickyFocus(true); //теперь мы не можем потерять фокус с корабля

    scene->addItem(new Ship(scene->height()));

    animation = new QTimer(this);

    connect(animation, SIGNAL(timeout()), scene, SLOT(advance())); //от кого - какой сигнал - кому - что сделать, advance -смена кадра
                                                                   //метод - это метод классам Item, в нем в цикле вызывается каждый из элементов, которые содержит сцена - с параметром ноль, второй - единица
                                                                  //при первом проходе вычисляем новое состояние элемента (например столкновения или др взаиможействия), во второй фазе - отрисовываем или
                                                                  // меняем положение элемента

    animation->start(1000/60); //частота- 60 кадров в секунду, цисло в скобках - как часто запускается таймер

    generator = new QTimer(this);

    connect(generator, SIGNAL(timeout()), this, SLOT(OnGenerate())); //каждую секунду на сцену быдет добавляться новый астероид

    generator->start(1000);
}

Asteroids::Asteroids(int x) : QGraphicsPixmapItem(0) { //вызываем конструктор родительского класса
    int p = rand()%130;
    while(p < 90){
        p = rand()%130;
    }
    setPixmap(QPixmap("/home/alena/Documents/Eclipse/images/RegularAsteroid.png").scaled(p, p));
    setPos(rand()%(x - pixmap().width()), 0); //смещение системы координат
}

Widget::~Widget()
{
    delete ui;
}

void Widget::OnGenerate(){
    scene->addItem(new Asteroids(scene->sceneRect().width())); //добавляем новый астероид на сцену
}

void Asteroids::advance(int phase){
    if (phase) {
        moveBy(0, speed); //смещение относительно ранего состоятния объекта, т.е. хотим оставить сост по x и сместить на 2 по y.
        if (data(0).toBool()){
            delete this;
        }
    }
}

Ship::Ship(int scene_w)  : QGraphicsPixmapItem(0) {
    setPixmap(QPixmap("/home/alena/Documents/Eclipse/images/SpaceShip.png").scaled(130, 130));
    setPos(0, scene_w - pixmap().height()); //делаем так, чтобы кораль стал ровно по нижнему краю окна
    setFlag(QGraphicsItem::ItemIsFocusable); //элемент может получить фокус, т.е. теперь мы можем им управять с клавиатуры, наша программа настроена на корабль и только
    setFocus();
}

void Ship::advance(int phase){
    if (phase) {
        moveBy(shipSpeed, 0);
    }
}

void Ship::keyPressEvent(QKeyEvent *event){ //событие: нажали кнопку
    switch (event->key()){ //возвращает код нажатой клавиши
    case Qt::Key_Left:
        shipSpeed = -6; //двигаем влево, корабль смещается относительно своих координат
        break;
    case Qt::Key_Right:
        shipSpeed = 6;
        break;
    case Qt::Key_Space:
        scene()->addItem(new Shot(QPointF(mapToScene(pixmap().width()/2 - 8, 0)), 0)); //fix it! костыль, изображение не симметричное
                                                //поменяли родителя, иначе пуля будет кататься вслед за самолетом уже после вылета
                                               //ьеперь родитель - сцена, из-за того, что фактический родитель - 0 (последний ноль в строке), надо добалять элемент на сцену ручками (сделано в начале строки)
        break;
    default:
        break;
    }
}

void Ship::keyReleaseEvent(QKeyEvent *event){ //событие: отпустили кнопку
    switch (event->key()){ //возвращает код отпущенной клавиши
    case Qt::Key_Left:
        shipSpeed = 0; //останавливаем корабль
        break;
    case Qt::Key_Right:
        shipSpeed = 0;
        break;
    default:
        break;
    }
}


Shot::Shot(QPointF initPos, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    shotSpeed = 5;
    setPixmap(QPixmap("/home/alena/Documents/Eclipse/images/FireShot.png"));
    setPos(initPos);
}

void Shot::advance(int phase) {
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()){ //возращает список элементов, с которыми столкнулся нам элемент, проходимся по этому списку
            if (item->type() == Asteroids::Type){
            item->setData(0, true); //позволяется хранить ключ - значения об объекте
            //удалить астроид прямо здесь мы не можем, приведем к ошибке, удалять объекты можем в из advance
            setData(0, true);
            }
        }

    } else {
        moveBy(0, -shotSpeed);
        if (data(0).toBool()){
            delete this;
        }
    }
}

int Asteroids::type() const{ //необходимо, для того, чтобы проверить тип графического элемента, (например, появится меню, чтобы мы случайно его не убили пулей:)
    return Type;
}
