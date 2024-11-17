// imagescaling.h
#ifndef IMAGESCALING_H
#define IMAGESCALING_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFuture>
#include <QFutureWatcher>
#include <QImage>
#include <QBuffer>
#include <QtConcurrent>
#include <QUrl>

class Images : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList imageList READ imageList NOTIFY imageListChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)

public:
    explicit Images(QObject *parent = nullptr);

    // Public methods exposed to QML
    Q_INVOKABLE void getUrls(const QStringList &urlStrings);
    Q_INVOKABLE void process();
    Q_INVOKABLE void cancel();
    Q_INVOKABLE void clearImages();

    // Getters for properties
    QStringList imageList() const { return m_imageList; }
    QString statusMessage() const { return m_statusMessage; }

signals:
    void downloadStarted();
    void downloadCompleted();
    void downloadCancelled();
    void downloadFailed(const QString &error);
    void scalingStarted();
    void scalingCompleted();
    void imageListChanged();
    void statusMessageChanged();

private:
    // Network and download handling
    QNetworkAccessManager qnam;
    QList<QSharedPointer<QNetworkReply>> replies;
    QList<QUrl> urls;
    QFuture<QByteArray> downloadFuture;

    // Image processing
    QFutureWatcher<QList<QImage>> scalingWatcher;
    QStringList m_imageList;
    QString m_statusMessage;

    // Private methods
    QFuture<QByteArray> download();
    QList<QImage> scaleImages(const QList<QByteArray> &data);
    void scaleFinished();
    void abortDownload();
    void setStatusMessage(const QString &statusMsg);
};

#endif // IMAGESCALING_H
