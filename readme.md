# JsonToStructV2 

JsonToStructV2 是一个通过 json 自动生成数据数据类代码片段的小工具：

<!-- ![界面](.\doc\show.png) -->

![show](https://github.com/xinxinrana/JsonToStructV2/assets/102397752/01b8a968-1a8d-4feb-8c01-50d719eac2fc)


```Json
{  
  "name": "John Doe",  
  "age": 30,  
  "email": "johndoe@example.com",  
  "address": {  
    "street": "123 Main Street",  
    "city": "New York",  
    "state": "NY",  
    "country": "USA"  
  },  
  "phoneNumbers": [  
    {  
      "type": "home",  
      "number": "555-1234"  
    },  
    {  
      "type": "work",  
      "number": "555-5678"  
    }  
  ],  
  "interests": ["reading", "traveling", "photography"],  
  "isStudent": false,  
  "isEmployed": true  
}
```

生成代码：

```c++



#include <QList>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>


class PhoneNumbers;
                   
class QString;
                   
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


void __JsonToStructFunc__setData(QString& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(PhoneNumbers& arr,const QJsonValue& data);


class Address{

public:

    QString city;

    QString country;

    QString state;

    QString street;


    void operator=(const QJsonObject& _obj){

        city = _obj.value( "city").toString();
        country = _obj.value( "country").toString();
        state = _obj.value( "state").toString();
        street = _obj.value( "street").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};
                   


class PhoneNumbers{

public:

    QString number;

    QString type;


    void operator=(const QJsonObject& _obj){

        number = _obj.value( "number").toString();
        type = _obj.value( "type").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};
                   


class MainStruct{

public:

    int age;

    bool isEmployed;

    bool isStudent;

    Address address;

    QString email;

    QString name;

    QList<QString> interestsList;

    QList<PhoneNumbers> phoneNumbersList;


    void operator=(const QJsonObject& _obj){

        isEmployed = _obj.value( "isEmployed").toBool();
        isStudent = _obj.value( "isStudent").toBool();
        age = _obj.value( "age").toInt();
        email = _obj.value( "email").toString();
        name = _obj.value( "name").toString();
        address = _obj.value( "address").toObject();
        const auto& arr_interestsList = _obj.value("interests").toArray();/*newLine*/__JsonToStructFunc__setArray(interestsList,arr_interestsList);
        const auto& arr_phoneNumbersList = _obj.value("phoneNumbers").toArray();/*newLine*/__JsonToStructFunc__setArray(phoneNumbersList,arr_phoneNumbersList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};
                   



void __JsonToStructFunc__setData(QString& arr,const QJsonValue& data){
arr = data.toString();
}

void __JsonToStructFunc__setData(PhoneNumbers& arr,const QJsonValue& data){
arr = data.toObject();
}


```

