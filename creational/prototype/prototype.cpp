
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>

class Message
{
public:
    virtual Message* New() = 0;
};

class Person : public Message
{
public:
    virtual Person* New() {
        Person* p = new Person;
        return p;
    }

    void speak1() {
        std::cout << "i m person" << std::endl;
    }
};

class AddressBook : public Message
{
public:
    virtual AddressBook* New() {
        AddressBook* p = new AddressBook;
        return p;
    }

    void speak2() {
        std::cout << "i m addressbook" << std::endl;
    }
};



// 有缺陷的回调
typedef std::function<void (Message* message)> Callback;


void fooPerson(Message* message) {
    auto persion = dynamic_cast<Person*>(message);
    persion->speak1();
}

void fooAddressBook(Message* message) {
    auto addressBook = dynamic_cast<AddressBook*>(message);
    addressBook->speak2();
}


// 无需向下转换的回调

class CallBackBase {
public:
    virtual ~CallBackBase(){};

    virtual void onMessage(Message* message) = 0;
};

template <typename T>
class CallBackT : public CallBackBase {

    typedef std::function<void (T* message)> TemplateCallback;
public:
    CallBackT(const TemplateCallback& callback) 
         : callback_(callback) {}
    
    virtual void onMessage(Message* message) {
        T* down = dynamic_cast<T*>(message);
        callback_(down);
    }

private:
    TemplateCallback callback_;
};


void fooPerson2(Person* persion) {
    persion->speak1();
}

void fooAddressBook2(AddressBook* addressBook) {
    addressBook->speak2();
}



int main() {
    // protobuf 找到Prototype的过程有两步,我这里省去了Descriptor
    // [Name:Descriptor] # DescriptorPool
    // [Descriptor:Prototype] # MessageFactory

    auto personPrototype = new Person;
    auto addressBookPrototype = new AddressBook;

    std::unordered_map<std::string, Message*> prototypeFactory = {
        {"Person", personPrototype},
        {"AddressBook", addressBookPrototype}
    };

    std::string reqType = "Person";

    Message* prototype = prototypeFactory.find(reqType)->second;
    auto newMsg = prototype->New();
    // 反序列化


    // 有缺陷的回调
    std::unordered_map<Message*, Callback> callbacks = {
        {personPrototype, fooPerson},
        {addressBookPrototype, fooAddressBook}
    };

    auto cb = callbacks[prototype];
    cb(newMsg);


    // 无需向下转换的回调
    reqType = "AddressBook";
    prototype = prototypeFactory.find(reqType)->second;
    newMsg = prototype->New();
    // 反序列化

    std::unordered_map<Message*, CallBackBase*> callbacks2 = {
        {personPrototype, new CallBackT<Person>(fooPerson2)},
        {addressBookPrototype, new CallBackT<AddressBook>(fooAddressBook2)}
    };

    auto cb2 = callbacks2[prototype];
    cb2->onMessage(newMsg);


    // 资源一律不释放,操作系统收尸吧

    return 0;
}
