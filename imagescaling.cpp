// imagescaling.cpp
#include "imagescaling.h"
#include <QPromise>

Images::Images(QObject *parent)
    : QObject{parent}
{
    connect(&scalingWatcher, &QFutureWatcher<QList<QImage>>::finished,
            this, &Images::scaleFinished);
}

void Images::getUrls(const QStringList &urlStrings)
{
    urls.clear();
    for (const QString &urlString : urlStrings) {
        urls.append(QUrl(urlString));
    }
}

void Images::process()
{
    if (urls.empty()) {
        setStatusMessage("No URLs provided.");
        return;
    }

    replies.clear();
    emit downloadStarted();
    downloadFuture = download();
    setStatusMessage("Downloading...");

    downloadFuture
        .then([this](auto) {
            setStatusMessage("Scaling images...");
            emit scalingStarted();
            scalingWatcher.setFuture(QtConcurrent::run(&Images::scaleImages, this, downloadFuture.results()));
        })
        .onCanceled([this] {
            setStatusMessage("Download canceled.");
            emit downloadCancelled();
        })
        .onFailed([this](const std::exception &ex) {
            QString error = QString::fromStdString(ex.what());
            setStatusMessage("Download failed: " + error);
            emit downloadFailed(error);
        });
}

QFuture<QByteArray> Images::download()
{
    auto promise = QSharedPointer<QPromise<QByteArray>>(new QPromise<QByteArray>());
    promise->start();

    for (const QUrl &url : urls) {
        QNetworkRequest request(url);
        auto reply = QSharedPointer<QNetworkReply>(qnam.get(request));
        replies.push_back(reply);

        // Connect to the finished signal
        connect(reply.get(), &QNetworkReply::finished, this, [this, reply, promise]() {
            if (promise->isCanceled()) {
                if (!promise->future().isFinished())
                    promise->finish();
                return;
            }

            if (reply->error() != QNetworkReply::NoError) {
                if (!promise->future().isFinished()) {
                    promise->setException(std::make_exception_ptr(reply->errorString().toStdString()));
                    promise->finish();
                }
                return;
            }

            // Read the data and add to results
            promise->addResult(reply->readAll());

            // Check if all downloads are complete
            if (promise->future().resultCount() == urls.size()) {
                promise->finish();
                emit downloadCompleted();
            }
        });

        // Connect to the error signal
        connect(reply.get(), &QNetworkReply::errorOccurred, this, [promise](QNetworkReply::NetworkError error) {
            if (!promise->future().isFinished()) {
                promise->setException(std::make_exception_ptr(error));
                promise->finish();
            }
        });
    }

    return promise->future();
}

void Images::scaleFinished()
{
    QList<QImage> scaledImages = scalingWatcher.result();
    m_imageList.clear();

    for (const QImage &image : scaledImages) {
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "JPEG");
        QString base64 = QString("data:image/jpeg;base64,") + QString::fromLatin1(imageData.toBase64());
        m_imageList.append(base64);
    }

    emit imageListChanged();
    setStatusMessage("Images processed successfully");
    emit scalingCompleted();
}

QList<QImage> Images::scaleImages(const QList<QByteArray> &data)
{
    QList<QImage> scaled;
    for (const QByteArray &imgData : data) {
        QImage image;
        if (image.loadFromData(imgData)) {
            scaled.append(image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    return scaled;
}

void Images::cancel()
{
    setStatusMessage("Canceling...");
    downloadFuture.cancel();
    abortDownload();
    emit downloadCancelled();
}

void Images::clearImages()
{
    m_imageList.clear();
    emit imageListChanged();
}

void Images::abortDownload()
{
    for (const auto &reply : replies) {
        if (reply) {
            reply->abort();
        }
    }
    replies.clear();
}

void Images::setStatusMessage(const QString &statusMsg)
{
    m_statusMessage = statusMsg;
    emit statusMessageChanged();
}
