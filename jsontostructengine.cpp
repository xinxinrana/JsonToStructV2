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

    QString head,middle,end;

    QList<QSharedPointer<JsonValueItem>> arraySubValues;
    auto classT = createClassStrTemplate();
    for(auto aClass : structTm){
        if(aClass->items.count() == 0 )continue;

        auto aClassStr = classT.arg(aClass->parent->qKeySubDefineName())
                .arg(aClass->creatDefineParameters().join("\n\n    "))
                .arg(aClass->items.at(0)->formalParName())
                .arg(aClass->createAssignmentParameters().join("\n        "));

        middle += aClassStr +"\n\n";

        // 处理 List 赋值问题
        for(auto &aValue : aClass->items){
            if(aValue->type == QJsonValue::Array){
                arraySubValues << aValue.staticCast<JsonValueItemArray>()->child();
            }
        }
    }

    if(arraySubValues.isEmpty() == false){
        head += createSetArrayDataTemplate();

        QSet<QString> arraySubDefineName;
        for(auto subType : arraySubValues){
            if(arraySubDefineName.contains(subType->qKeyDefineName())){
                continue;
            }
            arraySubDefineName << subType->qKeyDefineName();
            head += "\n";
            head += createSubSetArrayDataTemplateDefine().arg(subType->qKeyDefineName());

            end += createSubSetArrayDataTemplateRealize().arg(subType->qKeyDefineName())
                    .arg(Tools::JSonTypeToConversionStr(subType->getUpdateType()));
        }

        QString defineNames;
        for(auto defineName : arraySubDefineName){
            defineNames += createSubSetArrayTypeDefine().arg(defineName) ;
        }
        head.insert(0,defineNames);
    }
    head.insert(0,creatrIncludeTemplate());

    QString Template1 =
R"(
%1
%2
%3
)";
    return Template1.arg(head).arg(middle).arg(end);
}

QString JsonToStructEngine::createClassStrTemplate()
{
    return QString(R"(
class %1{

public:

    %2


    void operator=(const QJsonObject& %3){

        %4
    }

   QJsonObject toJsonObject(){

       // %5
   }
};
                   )");
}

QString JsonToStructEngine::createSetArrayDataTemplate()
{
    return QString(R"(
template <typename T>
void __JsonToStructFunc__setArray(T& arr,const QJsonArray& data)
{
   auto item = arr.value(0);
   for(auto aValue : data){
       __JsonToStructFunc__setData(item ,aValue);
       arr.append(item);
   }
}

template <typename T>
void __JsonToStructFunc__setData(T& arr,const QJsonValue& data){
   __JsonToStructFunc__setArray(arr , data.toArray());
}
)");
}

QString JsonToStructEngine::createSubSetArrayDataTemplateDefine()
{
    return QString(R"(
void __JsonToStructFunc__setData(%1& arr,const QJsonValue& data);
)");
}

QString JsonToStructEngine::createSubSetArrayDataTemplateRealize()
{
    return QString(R"(
void __JsonToStructFunc__setData(%1& arr,const QJsonValue& data){
arr = data.to%2();
}
)");
}

QString JsonToStructEngine::createSubSetArrayTypeDefine()
{
    return QString(R"(
class %1;
                   )");
}

QString JsonToStructEngine::creatrIncludeTemplate()
{
    return QString(R"(

#include <QList>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

)");
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
            qDebug() << oldName << QStringLiteral("由于重名已经更新为 %1")
                        .arg(oldName + suffix);

            aStruct->parent->updateClassNameFunc =
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
