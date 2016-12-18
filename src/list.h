#pragma once

namespace cj {

#define LIST_CAPACITY_STEP 256
    class List : public Object
    {
        int count, capacity;
        Object **memory;
    public:
        List();
        virtual ~List();
        virtual void assign(List *list);

        virtual int getCapacity();
        virtual void setCapacity(int value);
        virtual int getCount();
        virtual Object* add(Object* item);
        virtual void insert(int index, Object* item);
        virtual Object* getItem(int index);
        virtual Object* getFirst();
        virtual Object* getLast();
        virtual void setItem(int index, Object* item);
        virtual void change(int index1, int index2);
        virtual void moveTo(int index1, int index2);
        virtual int indexOf(Object* item);
        virtual void del(int index);
        virtual int del(Object *item);
        virtual void remove(int index);
        virtual int remove(Object* item);
        virtual void clear();
        virtual void kill();
    };


    class StringList : public List
    {
    public:
        StringList();
        String getClassName();
        void add(String* str);
        void add(String str);
        void insert(int index, String str);
        String* getItem(int index);
        String getString(int index);
        void setItem(String* str, int index);
        void setString(String str, int index);
        int indexOf(String* Item);
        int remove(String* Item);
        int remove(String str);
        bool find(String str);
    };

    class ParamList : public Object {
    public:
        map<string, string> pars;
        ParamList();
        virtual ~ParamList();

        virtual void add(String name, String value);
        virtual void insert(String name, String value);
        virtual void clear();
        virtual int getCount();
        virtual bool parse(String s);
        virtual String getValue(String name);
        virtual String getName(int index);
        virtual String getValue(int index);

        virtual void add(string name, string value);
        virtual void insert(string name, string value);
        virtual string getValue_s(string name);
        virtual string getName_s(int index);
        virtual string getValue_s(int index);
    };

    class Map : public ParamList {

    };

}
