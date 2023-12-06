#include "tools.h"

#include <QMap>
#include <QDebug>
#include <QObject>
#include <QSet>
#include <QString>
#include <QStringList>


Tools::Tools()
{

}

QString Tools::namingCheck(const QString &str, bool *isOk)
{
    static QSet<QString> hasPrint;
    auto newName = QString("Rename") + str ;

    bool needUpdate = false;
    auto t1 = toUpperCaseCamelCase(str);
    auto t2 = toLowerCaseCamelCase(str);
    if(t1 == t2 || isCppKeyword(str) || isQtClassName(str)){
        needUpdate = true;
        if(hasPrint.contains(str) == false)
            qDebug() << "key: "<< str <<QStringLiteral("不适合作为类名，已经被修改为： %1").arg(newName);
        hasPrint << str;
    }



    if(needUpdate){
        if(isOk) (*isOk) = false;
        return newName;
    }
    if(isOk) (*isOk) = true;
    return str;
}


QString Tools::toUpperCaseCamelCase(const QString &str)
{
    // 将字符串分割为单词
    QStringList words = str.split(' ');

    // 将每个单词的首字母转换为大写，并拼接起来
    QString result;
    for (const QString& word : words) {
        if (!word.isEmpty()) {
            result.append(word.left(1).toUpper());
            result.append(word.mid(1));
        }
    }

    return result;
}

QString Tools::toLowerCaseCamelCase(const QString &str)
{
    QString rData = toUpperCaseCamelCase(str);

    if(!rData.isEmpty()){
        auto aChar = rData.at(0).toLower();
        rData.replace(0,1,aChar);
    }
    return rData;
}

QString Tools::JsonTypeToString(QJsonValue::Type type)
{
    QMap<QJsonValue::Type,QString> map;
    map.insert(static_cast<QJsonValue::Type>(-1),"int");
    map.insert(QJsonValue::Null,"QVariant");
    map.insert(QJsonValue::Bool,"bool");
    map.insert(QJsonValue::Double,"double");
    map.insert(QJsonValue::String,"QString");
    map.insert(QJsonValue::Array,"QList");
    map.insert(QJsonValue::Object,"Object");
    map.insert(QJsonValue::Undefined,"Undefined");

    return map.value(type);
}

QString Tools::JSonTypeToConversionStr(QJsonValue::Type type)
{
    QMap<QJsonValue::Type,QString> map;
    map.insert(static_cast<QJsonValue::Type>(-1),"Int");
    map.insert(QJsonValue::Null,"String");
    map.insert(QJsonValue::Bool,"Bool");
    map.insert(QJsonValue::Double,"Double");
    map.insert(QJsonValue::String,"String");
    map.insert(QJsonValue::Array,"Array");
    map.insert(QJsonValue::Object,"Object");
    map.insert(QJsonValue::Undefined,"String");

    return map.value(type);
}

bool Tools::isCppKeyword(const QString &word) {
    static const QSet<QString> cppKeywords = {
        "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool",
        "break", "case", "catch", "char", "class", "compl", "const",
        "constexpr", "continue", "default", "delete", "do", "double",
        "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int",
        "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
        "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
        "register", "reinterpret_cast", "return", "short", "signed",
        "sizeof", "static", "static_cast", "struct", "switch",
        "template", "this", "throw", "true", "try", "typedef",
        "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while",
        // C++11, C++14, C++17, and C++20 keywords can be added here
    };
    return cppKeywords.contains(word.toLower());
}

bool Tools::isQtClassName(const QString &className) {
    static const QSet<QString> QKeys
    {   "QApplication", "QCoreApplication" ,
        "QWidget", "QMainWindow" ,
        "QPushButton", "QLabel" ,
        "QLineEdit", "QTextEdit" ,
        "QCheckBox", "QRadioButton" ,
        "QComboBox", "QListWidget" ,
        "QTableWidget", "QTreeWidget" ,
        "QMenuBar", "QToolBar" ,
        "QStatusBar", "QDialog" ,
        "QFileDialog", "QColorDialog" ,
        "QFontDialog", "QMessageBox" ,
        "QInputDialog", "QProgressDialog" ,
        "QPainter", "QPen" ,
        "QBrush", "QColor" ,
        "QFont", "QPixmap" ,
        "QImage", "QSvgRenderer" ,
        "QGraphicsScene", "QGraphicsView" ,
        "QGraphicsItem", "QGraphicsPixmapItem" ,
        "QGraphicsTextItem", "QGraphicsEllipseItem" ,
        "QGraphicsRectItem", "QGraphicsPolygonItem" ,
        "QGraphicsPathItem", "QGraphicsLineItem" ,
        "QGraphicsSceneMouseEvent", "QGraphicsSceneWheelEvent" ,
        "QGraphicsSceneKeyEvent", "QGraphicsSceneHoverEvent" ,
        "QTimer", "QElapsedTimer" ,
        "QString", "QByteArray" ,
        "QList", "QVector" ,
        "QMap", "QHash" ,
        "QSet", "QMultiMap" ,
        "QMultiHash", "QObject" ,
        "QEvent", "QChildEvent" ,
        "QConnectionList", "QMetaObject" ,
        "QMimeData", "QVariant" ,
        "QBitArray", "QDateTime" ,
        "QUrl", "QJsonObject" ,
        "QJsonArray", "QJsonValue" ,
        "QFile", "QDir" ,
        "QTextStream", "QDataStream" ,
        "QBuffer", "QTextCodec" ,
        "QLocale", "QRegularExpression" ,
        "QXmlStreamReader", "QXmlStreamWriter" ,
        "QXmlSimpleReader", "QtConcurrent" ,
        "QtConcurrentRun", "QtConcurrentFilter" ,
        "QtConcurrentMap", "QtConcurrentReduce" ,
        "QFuture", "QFutureWatcher" ,
        "QtNetworkAccessManager", "QNetworkRequest" ,
        "QNetworkReply", "QSslError" ,
        "QSslCertificate", "QSslKey" ,
        "QSslConfiguration", "QSslSocket" ,
        "QTcpSocket", "QTcpServer" ,
        "QUdpSocket", "QHostInfo" ,
        "QNetworkInterface", "QAbstractSocket" ,
        "QAbstractItemModel", "QStringListModel" ,
        "QFileSystemModel", "QStandardItemModel" ,
        "QXmlItemModel", "QSortFilterProxyModel" ,
        "QAbstractListModel", "QAbstractTableModel" ,
        "QAbstractProxyModel", "QAbstractItemView" ,
        "QListView", "QTableView" ,
        "QTreeView", "QColumnView" ,
        "QDataWidgetMapper", "QDirModel" ,
        "QFileIconProvider", "QFontDatabase" ,
        "QFontMetrics", "QFontMetricsF" ,
        "QFontInfo", "QPainterPath" ,
        "QTextCursor", "QTextDocument" ,
        "QTextFragment", "QTextCharFormat" ,
        "QTextBlockFormat", "QTextListFormat" ,
        "QTextTableFormat", "QTextFrameFormat" ,
        "QTextImageFormat", "QPrinter" ,
        "QPainterPrinter", "QPagedPaintDevice" ,
        "QPdfWriter", "QSvgGenerator" };

    return QKeys.contains(toUpperCaseCamelCase(className));
}

QString Tools::getNextOrder(bool isAuto, const QString &curOrder)
{
    static QString autoStr('A'-1);
    QString cur = isAuto||curOrder.isEmpty() ? autoStr : curOrder.toUpper();
    if(cur.back().isUpper() == false){
        cur = autoStr;
        isAuto = true;
    }

    auto tempCur = cur;
    int index = 1;
    while(tempCur.back().toLatin1() + 1 > 'Z'){
        index++;
        tempCur.remove(tempCur.size()-1,1);
        if(tempCur.isEmpty()){
            break;
        }
    }

    if(tempCur.isEmpty()){
        cur.insert(0,'A');
        cur.replace('Z','A');
    }

    // 当前位置 +1
    auto oldChar = cur.at(cur.size() - index).toLatin1();
    auto newChar = QChar(oldChar + 1);
    cur.replace(cur.size() - index , 1 , newChar);

    if(index > 1){
        cur.replace(cur.size() - index +1 , index - 1 , QString(index - 1,'A'));
    }

    if(isAuto)autoStr = cur;

    return isAuto ? curOrder + autoStr : cur;
}
