#ifndef JSONVALUEITEM_H
#define JSONVALUEITEM_H

#include "tools.h"

#include <QJsonValue>
#include <QSharedPointer>
#include <functional>

class JsonObjectItem;
class JsonValueItemObject;


class JsonValueItem{
    using UpdateClassNameFunc = std::function<QString(QString)>;
public:
    JsonValueItem(){}
    virtual ~JsonValueItem(){}

    QJsonValue::Type type;
    QString jsonKey;
    QJsonValue jsonValue;
    static QString newLineMark(){return "/*newLine*/";}
    UpdateClassNameFunc updateClassNameFunc = [](QString str){return str;};

    // 更新类型（部分 int 被识别为 double 的问题）
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
        return QString("%1 = %4.value( \"%2\").to%3();")
                .arg(qKeyParameterName())
                .arg(jsonKey)
                .arg(Tools::JSonTypeToConversionStr(getUpdateType()))
                .arg(formalParName());
    }

    QString formalParName(){
        return "_obj";
    }
};

class JsonValueItemArray : public JsonValueItem{


     //JsonValueItem interface
public:
    JsonValueItemArray(){}
    virtual ~JsonValueItemArray()override{}

    // 参数名
    virtual QString qKeyParameterName() override{
        return JsonValueItem::qKeyParameterName() + "List";
    }

    // 定义名
    virtual QString qKeyDefineName() override{
        auto lay = arrayNestedLayers();
        QString subType = "%1";
        for(int i = 0 ; i < lay ; ++i){
            subType = subType.arg("QList<%1>");
        }
        subType = subType.arg(qKeySubDefineName());

        return subType;
    }

    // 子类型名
    virtual QString qKeySubDefineName() override{
       return m_child->qKeyDefineName();
    }

    // 赋值语句
    virtual QString assignmentFragment()override{

        QString rData(R"(const auto& %1 = %4.value("%2").toArray();%5__JsonToStructFunc__setArray(%3,%1);)"
        );

        rData = rData
                .arg(QString("arr_")+qKeyParameterName())
                .arg(jsonKey)
                .arg(qKeyParameterName())
                .arg(formalParName())
                .arg(newLineMark());

        return rData;
    }

    // 数组层数 [ 1 - max ]
    int arrayNestedLayers() const;
    void setArrayNestedLayers(int arrayNestedLayers);

    // 数组内层对象
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
        return updateClassNameFunc(keyName);
    }

    virtual QString qKeySubDefineName() override{
        return qKeyDefineName();
    }
};




#endif // JSONVALUEITEM_H
