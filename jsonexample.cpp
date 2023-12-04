#include "jsonexample.h"
#include <QString>

static const QString complexStr = (R"(
{
    "_links": {
        "delete": {
            "href": "/api/v1/complex-data/12345",
            "methods": [
                "DELETE"
            ]
        },
        "self": {
            "href": "/api/v1/complex-data/12345",
            "methods": [
                "GET"
            ]
        },
        "update": {
            "href": "/api/v1/complex-data/12345",
            "methods": [
                "PUT"
            ]
        }
    },
    "_meta": {
        "currentPage": 1,
        "firstLink": "/api/v1/complex-data?page=1&perPage=10",
        "lastLink": "/api/v1/complex-data?page=",
        "nextLink": null,
        "perPage": 10,
        "previousLink": null,
        "selfLink": "/api/v1/complex-data?page=1&perPage=10",
        "totalItems": 3,
        "totalPages": 1,
        "version": 1,
        "testTheList":[
            [["s1","s2"],["s12","s21"]],[["s222","sxxx"],["s12","sc"]]
        ],
        "testTheList2":[
            [{"key":1,"key2":true},{"key":1,"key2":false}],[{"key":100,"key2":true},{"key":20,"key2":false}]
        ]
    },
    "company": {
        "departments": [
            {
                "head": "Alice",
                "name": "Engineering"
            },
            {
                "head": "Bob",
                "name": "Management"
            }
        ],
        "employees": [
            {
                "id": 1,
                "name": "Alice",
                "role": "Engineer",
                "salary": 100000
            },
            {
                "id": 2,
                "name": "Bob",
                "role": "Manager",
                "salary": 120000
            }
        ],
        "name": "Example Corp",
        "self": {
            "hello":1,
            "world":true
            }
    },
    "createdAt": "2023-05-23T10:00:00Z",
    "customFields": {
        "field1": "value1",
        "field2": "value2",
        "field3": {
            "subField1": "subValue1",
            "subField2": "subValue2"
        }
    },
    "isActive": true,
    "notes": [
        "This is a complex JSON file example."
    ],
    "person": {
        "address": {
            "city": "Anytown",
            "country": "USA",
            "postalCode": "12345",
            "state": "CA",
            "street": "123 Main St"
        },
        "age": 30,
        "email": "johndoe@example.com",
        "familyMembers": [
            {
                "name": "Jane Doe",
                "relation": "spouse"
            },
            {
                "name": "Baby Doe",
                "relation": "child"
            }
        ],
        "hobbies": [
            "reading",
            "traveling"
        ],
        "isMarried": false,
        "name": "John Doe",
        "phoneNumbers": [
            {
                "number": "555-1234",
                "type": "home"
            },
            {
                "number": "555-5678",
                "type": "work"
            }
        ]
    },
    "transactions": [
        {
            "amount": 100,
            "date": "2023-01-01",
            "id": 1,
            "product": {
                "name": "Product A",
                "price": 100,
                "quantity": 1
            },
            "type": "purchase"
        },
        {
            "amount": 200,
            "date": "2023-01-02",
            "id": 2,
            "product": {
                "name": "Product B",
                "price": 200,
                "quantity": 1
            },
            "type": "refund"
        }
    ],
    "updatedAt": "2023-05-23T11:00:00Z"
}
)");

static const QString simpleStr(R"(
{
  "users": [
    {
      "id": 1,
      "name": "John Doe",
      "email": "john@example.com",
      "age": 30,
      "address": {
        "street": "123 Main St",
        "city": "New York",
        "state": "NY",
        "postalCode": "10001"
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
      ]
    },
    {
      "id": 2,
      "name": "Jane Smith",
      "email": "jane@example.com",
      "age": 25,
      "address": {
        "street": "456 Elm St",
        "city": "San Francisco",
        "state": "CA",
        "postalCode": "94101"
      },
      "phoneNumbers": [
        {
          "type": "home",
          "number": "555-9876"
        },
        {
          "type": "mobile",
          "number": "555-4321"
        }
      ]
    }
  ]
}
)");

const QString jsonExample::complexJson()
{


    return complexStr;
}

const QString jsonExample::simpleJson()
{
    return simpleStr;
}

jsonExample::jsonExample()
{

}





