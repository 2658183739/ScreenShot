#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "QBuffer"
#include "QEventLoop"
#include "QPixmap"
#include "QDebug"
#include "QJsonArray"

class ImgOcrClient : public QObject {
    Q_OBJECT
public:
    ImgOcrClient::ImgOcrClient(QObject *parent = nullptr) : QObject(parent) {
        m_manager = new QNetworkAccessManager(this);
        m_clientId = "";
        m_clientSecret = "";
        m_accessToken = "";
    }
    QString getAccessToken();
    QStringList makeOcrRequest(const QPixmap &pixmap);
private:
    QNetworkAccessManager *m_manager;
    QString m_clientId;
    QString m_clientSecret;
    QString m_accessToken;
};
