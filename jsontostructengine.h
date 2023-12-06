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

    void updateOrder(){

    }

    // 定义参数 代码片段
    QStringList creatDefineParameters(){
        QStringList rData;
        for(auto item : orderByNameLength()){
            rData << item->createVariablFragment();
        }
        return rData;
    }

    // 赋值参数 代码片段
    QStringList createAssignmentParameters(){
        QStringList rData;
        for(auto item : orderByNameType()){
            rData << item->assignmentFragment();
        }
        return rData;
    }

    // 通过字段长度重排序
    QList<QSharedPointer<JsonValueItem>> orderByNameLength(){
        auto sortFunc = [](QSharedPointer<JsonValueItem>& a1 ,
                           QSharedPointer<JsonValueItem>& a2){
            return a1->qKeyDefineName().length() < a2->qKeyDefineName().length();
        };

        auto tempList = items;
        std::sort(tempList.begin(),tempList.end(),sortFunc);
        return tempList;
    }

    // 通过类型重排序
    QList<QSharedPointer<JsonValueItem>> orderByNameType(){
        auto sortFunc = [](QSharedPointer<JsonValueItem>& a1 ,
                           QSharedPointer<JsonValueItem>& a2){

            // 特殊处理 将 Array 放在最后位置
            auto a1Type = a1->type == QJsonValue::Array?QJsonValue::Undefined:a1->type;
            auto a2Type = a2->type == QJsonValue::Array?QJsonValue::Undefined:a2->type;
            return a1Type < a2Type;
        };

        auto tempList = items;
        std::sort(tempList.begin(),tempList.end(),sortFunc);
        return tempList;
    }
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

    // 模板
    QString createClassStrTemplate();
    QString createSetArrayDataTemplate();
    QString createSubSetArrayDataTemplateDefine();
    QString createSubSetArrayDataTemplateRealize();
    QString createSubSetArrayTypeDefine();
    QString creatrIncludeTemplate();

private:

    // 检查是否有同名结构体
    JsonObjList checkParentNames(const JsonObjList& structTm , bool toUpdate = false);

private:
    JsonObjList m_structTemplates;
};

#endif // JSONTOSTRUCTENGINE_H
