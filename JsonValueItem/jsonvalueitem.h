#ifndef JSONVALUEITEM_H
#define JSONVALUEITEM_H

#include "tools.h"

#include <QJsonValue>
#include <QSharedPointer>
#include <functional>

class JsonObjectItem;
class JsonValueItemObject;


class JsonValueItem{

public:
    JsonValueItem(){}
    virtual ~JsonValueItem(){}

    QJsonValue::Type type;
    QString jsonKey;
    QJsonValue jsonValue;
    std::function<QString(QString)> updateSubDefineNameFunc = [](QString str){return str;};

    // 更新类型
    virtual QJsonValue::Type getUpdateType(){
        if(type == QJsonValue::Double){
            if(qAbs(jsonValue.toDouble() - jsonValue.toInt()) < 0.0001){
                return static_cast<QJsonValue::Type>(-1);
            }
        }
        return type;
    }

    // 参数名
    virtual QString qKeyParameterName(){
        return Tools::toLowerCaseCamelCase( Tools::namingCheck(jsonKey));
    }

    // 类型名
    virtual QString qKeyDefineName(){
        return Tools::JsonTypeToString(getUpdateType());
    }

    // 子类型名
    virtual QString qKeySubDefineName(){
        return qKeyDefineName();
    }

    // 创建变量语句
    virtual QString createVariablFragment(){
        return qKeyDefineName() + " " + qKeyParameterName() + ";";
    }

    // 赋值语句
    virtual QString assignmentFragment(){
        return QString("%1 = _obj.value( \"%2\").to%3();")
                .arg(qKeyParameterName())
                .arg(jsonKey)
                .arg(Tools::JSonTypeToConversionStr(getUpdateType()));
    }
};

class JsonValueItemArray : public JsonValueItem{


     //JsonValueItem interface
public:
    JsonValueItemArray(){}
    virtual ~JsonValueItemArray()override{}

    virtual QString qKeyParameterName() override{
        return JsonValueItem::qKeyParameterName() + "List";
    }
    virtual QString qKeyDefineName() override{
        auto lay = arrayNestedLayers();
        QString subType = "%1";
        for(int i = 0 ; i < lay ; ++i){
            subType = subType.arg("QList<%1>");
        }
        subType = subType.arg(qKeySubDefineName());

        return subType;
    }
    virtual QString qKeySubDefineName() override{
       return m_child->qKeyDefineName();
    }

    int arrayNestedLayers() const;
    void setArrayNestedLayers(int arrayNestedLayers);

    QSharedPointer<JsonValueItem> child() const;
    void setChild(const QSharedPointer<JsonValueItem> &child);

private:
    QSharedPointer<JsonValueItem> m_child;
    int m_arrayNestedLayers = 0;
};

class JsonValueItemObject : public JsonValueItem{


     //JsonValueItem interface
public:
    JsonValueItemObject(){}
    virtual ~JsonValueItemObject()override{}

    virtual QString qKeyParameterName() override{
        return JsonValueItem::qKeyParameterName();
    }
    virtual QString qKeyDefineName() override{
        auto keyName = Tools::toUpperCaseCamelCase(qKeyParameterName());
        return updateSubDefineNameFunc(keyName);
    }
    virtual QString qKeySubDefineName() override{
        return qKeyDefineName();
    }
};




#endif // JSONVALUEITEM_H
