/* Copyright (C) 2017  jérémie Desesquelles
*                     jdesesquelles@gmail.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <QApplication>
#include <QQmlApplicationEngine>
#include "QQmlContext"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Capture capture;
    engine.rootContext()->setContextProperty("capture", &capture);
    capture.start();
    return app.exec();
}

