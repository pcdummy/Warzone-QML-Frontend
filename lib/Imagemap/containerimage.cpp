#include "containerimage.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace Imagemap;

ContainerImage::ContainerImage(Map *map, const QString &filename) :
    Container(map, filename)
{
    if (!QFile::exists(m_filename))
    {
        m_map->setError(1, "File does not exists.");
        return;
    }

#ifdef IMAGEMAP_DEBUG
    qDebug() << "Loaded container:" << m_filename;
#endif
}


QPixmap ContainerImage::pixmap(const Image &image,
                         const QSize &size,
                         const AspectRatioMode &mode)
{

    QVector2D factors = calculateFactors_(size, image.size, mode);

#ifdef IMAGEMAP_DEBUG
    qDebug() << "\tContainer:" << m_filename;
    qDebug() << "\tMode:" << mode;
    qDebug() << "\tFactors:" << factors;
    qDebug() << "\tSize:" << qRound(image.size.width() * factors.x()) <<
                             qRound(image.size.height() * factors.y());
    qDebug() << "\tPosition:" << qRound(image.xPosition * factors.x()) <<
                                 qRound(image.yPosition * factors.y());
#endif

    // Creates a full scaled copy of the container image with the factors.
    QPixmap full = createScaledContainer_(factors);

    // Extracts the image.
    QPixmap result = full.copy(qRound(image.xPosition * factors.x()),
                               qRound(image.yPosition * factors.y()),
                               qRound(image.size.width() * factors.x()),
                               qRound(image.size.height() * factors.y()));

    return result;
}

QPixmap ContainerImage::createScaledContainer_(const QVector2D &factors)
{
#ifdef IMAGEMAP_DEBUG
    qDebug() << "\tCache is:" << (m_nocache ? "off" : "on");
#endif

    if (m_nocache)
    {
        QPixmap fullpix(m_filename);
        if (fullpix.isNull())
        {
            m_map->setError(1, "Error while loading");
            return QPixmap();
        }

        QSize mySize = fullpix.size();
        mySize.rwidth() *= factors.x();
        mySize.rheight() *= factors.y();

        QPixmap pix = fullpix.scaled(mySize);

#ifdef IMAGEMAP_DEBUG
        qDebug() << "\tGenerated:" << m_filename << pix.size();
#endif

        return pix;
    }
    else if (m_cache.isEmpty())
    {
        QPixmap pix(m_filename);
        if (pix.isNull())
        {
            m_map->setError(1, "Error while loading");
            return QPixmap();
        }

#ifdef IMAGEMAP_DEBUG
        qDebug() << "\tLoaded:" << m_filename << pix.size();
#endif

        m_size = pix.size();
        m_cache.insert(pix.size(), pix);
    }

    if (factors.x() == 1 && factors.y() == 1)
    {
        return m_cache[m_size];
    }

    QSize mySize(qRound(m_size.width() * factors.x()),
                 qRound(m_size.height() * factors.y()));

    if (m_cache.contains(mySize))
    {
        return m_cache[mySize];
    }

    QPixmap pix = m_cache[m_size].scaled(mySize);

#ifdef IMAGEMAP_DEBUG
    qDebug() << "\tGenerated:" << m_filename << pix.size();
#endif

    m_cache.insert(mySize, pix);
    return m_cache[pix.size()];
}