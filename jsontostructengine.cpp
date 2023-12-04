#include "jsontostructengine.h"

#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#include <QString>

static JsonValueItem* creatMainItem(const QString &Name ){
    auto item = new JsonValueItemObject;
    item->type = QJsonValue::Object;
    item->jsonKey = Name;
    return item;
}

JsonToStructEngine::JsonToStructEngine(QObject *parent) : QObject(parent)
{

}

QString JsonToStructEngine::installJsonToStruct(const QJsonObject &json,
                                                const QString& Name)
{
    auto parent = creatMainItem(Name);
    getQtTypeTreeFromJsonObj(json,QSharedPointer<JsonValueItem>(parent));

    // update
    checkParentNames(m_structTemplates,true);

    return createCodeSegment(m_structTemplates);
}

int JsonToStructEngine::count()
{
    return m_structTemplates.count();
}

QSharedPointer<JsonObjectItem> JsonToStructEngine::getQtTypeTreeFromJsonObj(const QJsonObject &obj,
                                                  QSharedPointer<JsonValueItem> parent)
{
    QSharedPointer<JsonObjectItem> oItem(new JsonObjectItem);
    oItem->parent = parent;


    for(auto key : obj.keys()){

        // 构造 value 对象
        QSharedPointer<JsonValueItem> vItem (new JsonValueItem);
        auto curJsonValueType = obj.value(key).type();
        if(curJsonValueType == QJsonValue::Array){
            vItem.reset(new JsonValueItemArray);
        }else if(curJsonValueType == QJsonValue::Object){
            vItem.reset(new JsonValueItemObject);
        }

        // 初始化 value 对象
        vItem->jsonValue = obj.value(key);
        vItem->type = vItem->jsonValue.type();
        vItem->jsonKey = key;

        // 拦截错误类型
        QSet<QJsonValue::Type> errorType;
        errorType << QJsonValue::Null << QJsonValue::Undefined;
        if(errorType.contains(vItem->type)){
            qDebug() << key  << QStringLiteral("是Null 或 Undefined类型，无法转换");
            continue;
        }

        // 给不同的 value 对象进行递归构造
        if(vItem->type == QJsonValue::Object){
            getQtTypeTreeFromJsonObj(vItem->jsonValue.toObject(),vItem);
        }
        else if(vItem->type == QJsonValue::Array){

            QSharedPointer<JsonValueItemArray> arr
                    = vItem.staticCast<JsonValueItemArray>();
            int arrayNestedLayers = 0;
            // 循环到不为数组
            auto arrItem = vItem->jsonValue;
            while(arrItem.type() == QJsonValue::Array){
                arrayNestedLayers++;
                auto itemArr = arrItem.toArray();
                if(itemArr.count() > 0){
                    arrItem = itemArr.at(0);
                }
            }

            // 构造 Array 的子 value 对象
            QSharedPointer<JsonValueItem> vSubItem (new JsonValueItem);

            // 当 Array 的子对象是 Object 时继续递归
            if(arrItem.type() == QJsonValue::Object){
                 vSubItem.reset(new JsonValueItemObject);
                 getQtTypeTreeFromJsonObj(arrItem.toObject(),vItem);
            }
            else if(arrItem.type() == QJsonValue::Array){
                qDebug()<<__FUNCTION__<<"数组是空对象无法得出具体类型";
            }


            vSubItem->jsonValue = arrItem;
            vSubItem->type = arrItem.type();
            vSubItem->jsonKey = key;
            arr->setChild(vSubItem);
            arr->setArrayNestedLayers(arrayNestedLayers);

        }

        oItem->items.append(vItem);
    }

    m_structTemplates.append(oItem);
    return oItem;
}

QString JsonToStructEngine::createCodeSegment(const JsonObjList &structTm)
{
    for(auto aStruct : structTm){
        qDebug() << aStruct->parent->qKeySubDefineName();
        for(auto aValue : aStruct->items){
            QString itemStr;
            itemStr += aValue->qKeyDefineName() += "____";
            itemStr += aValue->qKeySubDefineName() += "____";
            itemStr += aValue->qKeyParameterName();
            qDebug() << itemStr;
        }
        qDebug() << "++++++++++++++";
    }
    return QString();

//    QString Template1 =
//R"(
//%1
//%2
//%3
//)";
//    QString head,middle,end;

//    QString structs;
//    for(auto aStruct : structTm){
//        aStruct->parent->qKeySubDefine();
//    }

    //    return QString();
}

JsonToStructEngine::JsonObjList JsonToStructEngine::checkParentNames
(const JsonToStructEngine::JsonObjList &structTm, bool toUpdate)
{
    JsonToStructEngine::JsonObjList rData;
    QSet<QString> names;
    for(auto JsonObj : structTm){
        auto subDefineName = JsonObj->parent->qKeySubDefineName();
        if(names.contains(subDefineName)){
            rData << JsonObj;
        }
        names << subDefineName;
    }
    if(toUpdate){
        for(auto aStruct : rData){
            auto suffix = Tools::getNextOrder();
            auto oldName = aStruct->parent->qKeySubDefineName();
            qDebug()<<oldName<< QStringLiteral("由于重名已经更新为 %1").arg(oldName + suffix);

            aStruct->parent->updateSubDefineNameFunc =
                    [suffix](QString str)->QString{return str + suffix;};
        }
    }

    return rData;
}

int JsonValueItemArray::arrayNestedLayers() const
{
    return m_arrayNestedLayers;
}

void JsonValueItemArray::setArrayNestedLayers(int arrayNestedLayers)
{
    m_arrayNestedLayers = arrayNestedLayers;
}

QSharedPointer<JsonValueItem> JsonValueItemArray::child() const
{
    return m_child;
}

void JsonValueItemArray::setChild(const QSharedPointer<JsonValueItem> &child)
{
    m_child = child;
}
