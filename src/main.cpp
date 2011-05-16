#include <QtGui/QApplication>

// WZ
#include <QtCore/QTextCodec>

// WZ OpenGL
#include <QtOpenGL/QGLWidget>

// QML Viewer
#include <lib/Imagemap/loader.h>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>


#include "Frontend/qmlimagemapprovider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // From WZ
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    // From wz: setup opengl
    QGL::setPreferredPaintEngine(QPaintEngine::OpenGL);
    QGLFormat format;
    format.setDoubleBuffer(true);
    format.setAlpha(true);
    format.setSampleBuffers(true);
    format.setSamples(16);
    QGLWidget *glWidget = new QGLWidget(format);
    if (!glWidget->isValid())
    {
        qFatal("Cannot create a GL Context!");
    }

    // Add data/frontend/images/imagemap.js to the imagemap loader
    if (!Imagemap::Loader::instance().addImagemap(app.applicationDirPath() + "/../../data/frontend/images/imagemap.js"))
    {
        // abort() on errors.
        qFatal(qPrintable(Imagemap::Loader::instance().errorString()));
    }

    // Now setup the QML viewer
    QDeclarativeView *view = new QDeclarativeView;
    view->setViewport(glWidget);
    //connect(viewer->engine(), SIGNAL(viewer->engine()->quit()), SLOT(close()));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    QMLImagemapProvider* improvider = new QMLImagemapProvider();
    improvider->setBasePath("data");
    view->engine()->addImageProvider("imagemap", improvider);
    view->setSource(QUrl::fromLocalFile(app.applicationDirPath() + "/../../data/frontend/main.qml"));
    view->show();

    return app.exec();
}
