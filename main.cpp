#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gameboard.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameBoard model;
    qmlRegisterType<GameBoard> ("Game", 1, 0, "GameBoardModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
