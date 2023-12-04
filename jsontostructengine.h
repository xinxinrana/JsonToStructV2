#ifndef JSONTOSTRUCTENGINE_H
#define JSONTOSTRUCTENGINE_H

#include "tools.h"
#include "JsonValueItem/jsonvalueitem.h"


#include <QObject>
#include <QSharedPointer>


class JsonObjectItem{

public:
    QSharedPointer<JsonValueItem> parent;
    QList<QSharedPointer<JsonValueItem>> items;
};



class JsonToStructEngine : public QObject
{
    using JsonObjList =  QList<QSharedPointer<JsonObjectItem>>;

    Q_OBJECT
public:
    explicit JsonToStructEngine(QObject *parent = nullptr);

public slots:

    QString installJsonToStruct(const QJsonObject& json,const QString& Name = "MainStruct");

    int count();

signals:

public slots:

private:
    // 读取Json结构到 m_structTemplates 中
    QSharedPointer<JsonObjectItem> getQtTypeTreeFromJsonObj
    (const QJsonObject &obj, QSharedPointer<JsonValueItem> parent );

    // 创建出结构体字符串
    QString createCodeSegment(const JsonObjList& structTm);

private:

    // 检查是否有同名结构体
    JsonObjList checkParentNames(const JsonObjList& structTm , bool toUpdate = false);

private:
    JsonObjList m_structTemplates;
};

#endif // JSONTOSTRUCTENGINE_H
