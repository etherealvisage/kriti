#ifndef KRITI__SINGLETON_H
#define KRITI__SINGLETON_H

namespace Kriti {

template<typename T>
class Singleton {
public:
    static T *get() {
        return storage();
    }
    static void make() {
        storage() = new T();
    }
    static void destroy() {
        if(storage()) delete storage();
        storage() = nullptr;
    }
private:
    static T *&storage() {
        static T *storage = nullptr;
        return storage;
    }
};

}  // namespace Kriti

#endif
