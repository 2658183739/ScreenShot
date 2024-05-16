#include "imgocrclient.h"

QString ImgOcrClient::getAccessToken()
{
    QUrl url("https://aip.baidubce.com/oauth/2.0/token");
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Accept", "application/json");

    QString data = "grant_type=client_credentials&client_id=" + m_clientId + "&client_secret=" + m_clientSecret;
    QNetworkReply *reply = m_manager->post(request, data.toUtf8());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error()) {
        return "";
    }

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = json.object();

    return obj["access_token"].toString();
}

QStringList ImgOcrClient::makeOcrRequest(const QPixmap &pixmap)
{
    if (m_accessToken.isEmpty()) {
        m_accessToken = getAccessToken();
        if (m_accessToken.isEmpty()) {
            //return;
        }
    }
    qDebug() << m_accessToken;

    // 1. 获取图像数据
    QImage image = pixmap.toImage();
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "JPEG"); // or "PNG", "BMP" depending on the format

    // 3. urlencode
    QByteArray base64Data = imageData.toBase64();
    QString data = "image=" + QUrl::toPercentEncoding(base64Data);

    QUrl url("https://aip.baidubce.com/rest/2.0/ocr/v1/accurate?access_token=" +  m_accessToken);
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Accept",  "application/json");

    QNetworkReply *reply = m_manager->post(request, data.toUtf8());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error()) {
        // handle error
        //return;
    }

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = json.object();

    QJsonArray wordsResultArray = obj["words_result"].toArray();
    QStringList words;
    for (QJsonValue value : wordsResultArray) {
        QJsonObject wordObj = value.toObject();
        QString word = wordObj["words"].toString();
        words.append(word);
    }

    return words;

}
