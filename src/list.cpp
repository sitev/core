#include "cj.h"

namespace cj {

    //--------------------------------------------------------------------------------------------------
    //----------          ����� List          ----------------------------------------------------------
    //--------------------------------------------------------------------------------------------------

    List::List() {
        memory = NULL;//iMemory = NULL;
        count = capacity = 0;
    }
    List::~List() {
        memory = NULL;//iMemory = NULL;
    }
    void List::assign(List *list) {
        this->clear();
        if (list == NULL) return;
        int count = list->getCount();
        for (int i = 0; i < count; i++) {
            this->add(list->getItem(i));
        }
    }
    int List::getCapacity() {
        return capacity;
    }
    void List::setCapacity(int value) {
        capacity = value;
        //	if (memory == NULL) memory = (Object**)malloc(value * sizeof(Object*));
        //	else
        try {
            memory = (Object**)realloc(memory, value * sizeof(Object*));
        }
        catch (...) {
            printf("List: error realloc\n");
            memory = NULL;
            capacity = 0;
        }
        //iMemory = memory;
    }
    int List::getCount() {
        return count;
    }
    Object* List::add(Object* item) {
        if (count >= capacity || memory == NULL) {
            setCapacity(capacity + LIST_CAPACITY_STEP);
        }
        memory[count] = (Object*)item;
        count++;

        return item;
    }
    void List::insert(int index, Object* item) {
        if (count >= capacity || memory == NULL) {
            setCapacity(capacity + LIST_CAPACITY_STEP);
        }
        for (int i = count - 1; i >= index; i--) {
            memory[i + 1] = memory[i];
        }
        memory[index] = (Object*)item;
        count++;
    }
    Object* List::getItem(int index) {
        if (memory == NULL) return NULL;
        Object *res = memory[index];
        return res;
    }
    Object* List::getFirst() {
        if (memory == NULL) return NULL;
        if (count == 0) return NULL;
        return getItem(0);
    }
    Object* List::getLast() {
        if (memory == NULL) return NULL;
        if (count == 0) return NULL;
        return getItem(count - 1);
    }
    void List::setItem(int index, Object* item) {
        if (memory == NULL) return;
        memory[index] = (Object*)item;
    }
    void List::change(int index1, int index2) {
        Object *data1 = getItem(index1);
        Object *data2 = getItem(index2);
        setItem(index1, data2);
        setItem(index2, data1);
    }
    void List::moveTo(int index1, int index2) {
        if (memory == NULL) return;
        if (index1 == index2) return;
        if (index1 <= count || index2 <= count) return;
        if (index1 > index2) {
            Object *data = memory[index1];
            for (int i = index1 - 1; i >= index2; i--) {
                memory[i + 1] = memory[i];
            }
            memory[index2] = data;
        }
    }
    int List::indexOf(Object* item) {
        if (memory == NULL) return -1;
        for (int i = 0; i < count; i++)
        {
            Object *cur = getItem(i);
            if (cur == item) return i;
        }
        return -1;
    }
    void List::del(int index) {
        if (memory == NULL) return;
        if (index < 0) return;
        if (count == 0) return;
        if (index >= count) return;

        for (int i = index; i < count - 1; i++) {
            memory[i] = memory[i + 1];
        }
        count--;
    }
    int List::del(Object* item) {
        int index = indexOf(item);
        del(index);
        return index;
    }
    void List::remove(int index) {
        if (memory == NULL) return;
        if (index < 0) return;
        if (count == 0) return;
        delete memory[index];

        for (int i = index; i < count - 1; i++) {
            memory[i] = memory[i + 1];
        }
        count--;
    }
    int List::remove(Object* item) {
        int index = indexOf(item);
        remove(index);
        return index;
    }
    void List::clear() {
        if (memory == NULL) return;
        int count;
        while ((count = getCount()) != 0)
        {
            del(count - 1);
        }
    }
    void List::kill() {
        if (memory == NULL) return;
        int count;
        while ((count = getCount()) != 0)
        {
            remove(count - 1);
        }
    }

    //---------------------------------------------------------------------------
    //----------  StringList   ----------------------------------------------------
    //---------------------------------------------------------------------------
    StringList::StringList()
    {
    }
    String StringList::getClassName()
    {
        return "StringList";
    }
    void StringList::add(String* str)
    {
        String *S = new String(*str);
        List::add(S);
    }
    void StringList::add(String str)
    {
        String *S = new String(str);
        List::add(S);
    }
    void StringList::insert(int index, String str)
    {
        String *S = new String(str);
        List::insert(index, S);
    }
    String* StringList::getItem(int index)
    {
        return (String*)List::getItem(index);
    }
    String StringList::getString(int index)
    {
        return *((String*)List::getItem(index));
    }
    void StringList::setItem(String* str, int index)
    {
        List::setItem(index, str);
    }
    void StringList::setString(String str, int index)
    {
        String *S = new String(str);
        List::setItem(index, S);
    }
    int StringList::indexOf(String* Item)
    {
        return List::indexOf(Item);
    }
    int StringList::remove(String* Item)
    {
        return List::remove(Item);
    }
    int StringList::remove(String str)
    {
        int count = getCount();
        for (int i = 0; i < count; i++)
        {
            if (str == getString(i))
            {
                remove(i);
                return i;
            }
        }
        return -1;
    }
    bool StringList::find(String str)
    {
        int count = getCount();
        for (int i = 0; i < count; i++)
        {
            if (str == getString(i)) return true;
        }
        return false;
    }


    //--------------------------------------------------------------------------------------------------
    //----------          ParameterList          -------------------------------------------------------
    //--------------------------------------------------------------------------------------------------

    ParamList::ParamList() {
    }

    ParamList::~ParamList() {
    }

    void ParamList::add(String name, String value) {
        pars.insert(std::pair<string, string>(name.to_string(), value.to_string()));
    }

    void ParamList::insert(String name, String value) {
        pars.insert(std::pair<string, string>(name.to_string(), value.to_string()));
    }

    void ParamList::clear() {
        pars.clear();
    }
    int ParamList::getCount() {
        return pars.size();
    }
    /*bool ParamList::parse(String s) {
        return true;
    }*/

    String ParamList::getValue(String name) {
        string v = pars[name.to_string()];
        //printf("getValue: %s = %s\n", name.to_string().c_str(), v.c_str());
        return pars[name.to_string()];
    }

    String ParamList::getName(int index) {
        auto iter = pars.begin();
        for (int i = 0; i < index; i++) iter++;
        return iter->first;
    }

    String ParamList::getValue(int index) {
        auto iter = pars.begin();
        for (int i = 0; i < index; i++) iter++;
        return iter->second;
    }

    void ParamList::add(string name, string value) {
        pars.insert(std::pair<string, string>(name, value));
    }
    void ParamList::insert(string name, string value) {
        pars.insert(std::pair<string, string>(name, value));
    }
    string ParamList::getValue_s(string name) {
        return pars[name];
    }
    string ParamList::getName_s(int index) {
        auto iter = pars.begin();
        for (int i = 0; i < index; i++) iter++;
        return iter->first;
    }
    string ParamList::getValue_s(int index) {
        auto iter = pars.begin();
        for (int i = 0; i < index; i++) iter++;
        return iter->second;
    }

}
