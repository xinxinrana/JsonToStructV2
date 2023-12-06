#ifndef STRUCTTEST_H
#define STRUCTTEST_H

#include <QList>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>






class PhoneNumbers;

class Departments;

class TestTheList2;

class QString;

class Employees;

class FamilyMembers;

class Transactions;

template <typename T>
void __JsonToStructFunc__setArray(T& arr,const QJsonArray& data)
{
   auto item = arr.value(0);
   for(auto aValue : data){
       auto curItem = item;
       __JsonToStructFunc__setData(curItem ,aValue);
       arr.append(curItem);
   }
}

template <typename T>
void __JsonToStructFunc__setData(T& arr,const QJsonValue& data){
   __JsonToStructFunc__setArray(arr , data.toArray());
}


void __JsonToStructFunc__setData(QString& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(TestTheList2& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(Departments& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(Employees& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(FamilyMembers& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(PhoneNumbers& arr,const QJsonValue& data);


void __JsonToStructFunc__setData(Transactions& arr,const QJsonValue& data);


class Renamedelete{

public:

    QString href;

    QList<QString> methodsList;


    void operator=(const QJsonObject& _obj){

        href = _obj.value( "href").toString();
        const auto& arr_methodsList = _obj.value("methods").toArray();/*newLine*/__JsonToStructFunc__setArray(methodsList,arr_methodsList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Self{

public:

    QString href;

    QList<QString> methodsList;


    void operator=(const QJsonObject& _obj){

        href = _obj.value( "href").toString();
        const auto& arr_methodsList = _obj.value("methods").toArray();/*newLine*/__JsonToStructFunc__setArray(methodsList,arr_methodsList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Update{

public:

    QString href;

    QList<QString> methodsList;


    void operator=(const QJsonObject& _obj){

        href = _obj.value( "href").toString();
        const auto& arr_methodsList = _obj.value("methods").toArray();/*newLine*/__JsonToStructFunc__setArray(methodsList,arr_methodsList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Rename_links{

public:

    Self self;

    Update update;

    Renamedelete renamedelete;


    void operator=(const QJsonObject& _obj){

        renamedelete = _obj.value( "delete").toObject();
        self = _obj.value( "self").toObject();
        update = _obj.value( "update").toObject();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class TestTheList2{

public:

    int key;

    bool key2;


    void operator=(const QJsonObject& _obj){

        key2 = _obj.value( "key2").toBool();
        key = _obj.value( "key").toInt();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Rename_meta{

public:

    int currentPage;

    int perPage;

    int totalItems;

    int totalPages;

    int version;

    QString firstLink;

    QString lastLink;

    QString selfLink;

    QList<QList<TestTheList2>> testTheList2List;

    QList<QList<QList<QString>>> testTheListList;


    void operator=(const QJsonObject& _obj){

        currentPage = _obj.value( "currentPage").toInt();
        perPage = _obj.value( "perPage").toInt();
        totalItems = _obj.value( "totalItems").toInt();
        totalPages = _obj.value( "totalPages").toInt();
        version = _obj.value( "version").toInt();
        firstLink = _obj.value( "firstLink").toString();
        lastLink = _obj.value( "lastLink").toString();
        selfLink = _obj.value( "selfLink").toString();
        const auto& arr_testTheListList = _obj.value("testTheList").toArray();/*newLine*/__JsonToStructFunc__setArray(testTheListList,arr_testTheListList);
        const auto& arr_testTheList2List = _obj.value("testTheList2").toArray();/*newLine*/__JsonToStructFunc__setArray(testTheList2List,arr_testTheList2List);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Departments{

public:

    QString head;

    QString name;


    void operator=(const QJsonObject& _obj){

        head = _obj.value( "head").toString();
        name = _obj.value( "name").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Employees{

public:

    int id;

    int salary;

    QString name;

    QString role;


    void operator=(const QJsonObject& _obj){

        id = _obj.value( "id").toInt();
        salary = _obj.value( "salary").toInt();
        name = _obj.value( "name").toString();
        role = _obj.value( "role").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class SelfA{

public:

    int hello;

    bool world;


    void operator=(const QJsonObject& _obj){

        world = _obj.value( "world").toBool();
        hello = _obj.value( "hello").toInt();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Company{

public:

    SelfA self;

    QString name;

    QList<Employees> employeesList;

    QList<Departments> departmentsList;


    void operator=(const QJsonObject& _obj){

        name = _obj.value( "name").toString();
        self = _obj.value( "self").toObject();
        const auto& arr_departmentsList = _obj.value("departments").toArray();/*newLine*/__JsonToStructFunc__setArray(departmentsList,arr_departmentsList);
        const auto& arr_employeesList = _obj.value("employees").toArray();/*newLine*/__JsonToStructFunc__setArray(employeesList,arr_employeesList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Field3{

public:

    QString subField1;

    QString subField2;


    void operator=(const QJsonObject& _obj){

        subField1 = _obj.value( "subField1").toString();
        subField2 = _obj.value( "subField2").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class CustomFields{

public:

    Field3 field3;

    QString field1;

    QString field2;


    void operator=(const QJsonObject& _obj){

        field1 = _obj.value( "field1").toString();
        field2 = _obj.value( "field2").toString();
        field3 = _obj.value( "field3").toObject();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Address{

public:

    QString city;

    QString country;

    QString postalCode;

    QString state;

    QString street;


    void operator=(const QJsonObject& _obj){

        city = _obj.value( "city").toString();
        country = _obj.value( "country").toString();
        postalCode = _obj.value( "postalCode").toString();
        state = _obj.value( "state").toString();
        street = _obj.value( "street").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class FamilyMembers{

public:

    QString name;

    QString relation;


    void operator=(const QJsonObject& _obj){

        name = _obj.value( "name").toString();
        relation = _obj.value( "relation").toString();
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



class Person{

public:

    int age;

    bool isMarried;

    Address address;

    QString email;

    QString name;

    QList<QString> hobbiesList;

    QList<PhoneNumbers> phoneNumbersList;

    QList<FamilyMembers> familyMembersList;


    void operator=(const QJsonObject& _obj){

        isMarried = _obj.value( "isMarried").toBool();
        age = _obj.value( "age").toInt();
        email = _obj.value( "email").toString();
        name = _obj.value( "name").toString();
        address = _obj.value( "address").toObject();
        const auto& arr_familyMembersList = _obj.value("familyMembers").toArray();/*newLine*/__JsonToStructFunc__setArray(familyMembersList,arr_familyMembersList);
        const auto& arr_hobbiesList = _obj.value("hobbies").toArray();/*newLine*/__JsonToStructFunc__setArray(hobbiesList,arr_hobbiesList);
        const auto& arr_phoneNumbersList = _obj.value("phoneNumbers").toArray();/*newLine*/__JsonToStructFunc__setArray(phoneNumbersList,arr_phoneNumbersList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Product{

public:

    int price;

    int quantity;

    QString name;


    void operator=(const QJsonObject& _obj){

        price = _obj.value( "price").toInt();
        quantity = _obj.value( "quantity").toInt();
        name = _obj.value( "name").toString();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class Transactions{

public:

    int amount;

    int id;

    QString date;

    Product product;

    QString type;


    void operator=(const QJsonObject& _obj){

        amount = _obj.value( "amount").toInt();
        id = _obj.value( "id").toInt();
        date = _obj.value( "date").toString();
        type = _obj.value( "type").toString();
        product = _obj.value( "product").toObject();
    }

   QJsonObject toJsonObject(){

       // %5
   }
};



class MainStruct{

public:

    bool isActive;

    Person person;

    Company company;

    QString createdAt;

    QString updatedAt;

    Rename_meta rename_meta;

    Rename_links rename_links;

    CustomFields customFields;

    QList<QString> notesList;

    QList<Transactions> transactionsList;


    void operator=(const QJsonObject& _obj){

        isActive = _obj.value( "isActive").toBool();
        createdAt = _obj.value( "createdAt").toString();
        updatedAt = _obj.value( "updatedAt").toString();
        rename_links = _obj.value( "_links").toObject();
        rename_meta = _obj.value( "_meta").toObject();
        company = _obj.value( "company").toObject();
        customFields = _obj.value( "customFields").toObject();
        person = _obj.value( "person").toObject();
        const auto& arr_notesList = _obj.value("notes").toArray();/*newLine*/__JsonToStructFunc__setArray(notesList,arr_notesList);
        const auto& arr_transactionsList = _obj.value("transactions").toArray();/*newLine*/__JsonToStructFunc__setArray(transactionsList,arr_transactionsList);
    }

   QJsonObject toJsonObject(){

       // %5
   }
};




void __JsonToStructFunc__setData(QString& arr,const QJsonValue& data){
arr = data.toString();
}

void __JsonToStructFunc__setData(TestTheList2& arr,const QJsonValue& data){
arr = data.toObject();
}

void __JsonToStructFunc__setData(Departments& arr,const QJsonValue& data){
arr = data.toObject();
}

void __JsonToStructFunc__setData(Employees& arr,const QJsonValue& data){
arr = data.toObject();
}

void __JsonToStructFunc__setData(FamilyMembers& arr,const QJsonValue& data){
arr = data.toObject();
}

void __JsonToStructFunc__setData(PhoneNumbers& arr,const QJsonValue& data){
arr = data.toObject();
}

void __JsonToStructFunc__setData(Transactions& arr,const QJsonValue& data){
arr = data.toObject();
}





#endif // STRUCTTEST_H
