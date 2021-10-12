#include <utility>
#include <string>
#include <memory>
#include <type_traits>

template <typename T>
class Singleton
{
    //    static_assert(!std::is_constructible<T>::value);

public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
    static std::shared_ptr<T> GetInstance()
    {
        if (!m_spInstance)
            m_spInstance.reset(MakeInstancePtr());
        return m_spInstance;
    }

private:
    Singleton() = default;

protected:
    virtual ~Singleton() = default;

private:
    static std::shared_ptr<T> m_spInstance;
    static T *MakeInstancePtr()
    {
        return new T();
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::m_spInstance = nullptr;