#ifndef KRITI__GLOBALS_H
#define KRITI__GLOBALS_H

#define KRITI_GLOBAL(type) \
    public: enum { kritiGlobal }; \
    private: \
    friend class ::Kriti::GlobalHelper<type>;

namespace Kriti {

template<typename T>
class GlobalHelper {
private:
    GlobalHelper() = delete;
public:
    static T *get() {
        return get_private();
    }

    static void make() {
        get_private() = new T();
    }

    static void destroy() {
        delete get_private();
        get_private() = nullptr;
    }
private:
    static T *&get_private() {
        static_assert(T::kritiGlobal >= 0,
            "Need ::kritiGlobal enum to be used in Globals");

        static T *storage = nullptr;
        return storage;
    }
};

template<typename T>
T *Global() {
    return GlobalHelper<T>::get();
}

}  // namespace Kriti

#endif
