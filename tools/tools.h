#ifndef TOOLS_H
#define TOOLS_H
#include <QJsonValue>

class QString;

class Tools
{
public:
    Tools();

    // 命名检查
    static QString namingCheck(const QString& str,bool* isOk = nullptr);

    // 大驼峰
    static QString toUpperCaseCamelCase(const QString& str);

    //小驼峰
    static QString toLowerCaseCamelCase(const QString& str);

    // Json 类型转 QString
    static QString JsonTypeToString(QJsonValue::Type type);

    // Json 类型转 QJsonValue().to[XXXX]() 中的 XXXX 字符串
    static QString JSonTypeToConversionStr(QJsonValue::Type type);

    // 检查是否是 C++ 关键字
    static bool isCppKeyword(const QString& word);

    // 检查是否是 Qt 类命
    static bool isQtClassName(const QString& className);

    // 获取下一个序号
    // 需要样式：[AB,AC,AD...]
    static QString getNextOrder(bool isAuto = true , const QString& curOrder = "");
};

#endif // TOOLS_H
