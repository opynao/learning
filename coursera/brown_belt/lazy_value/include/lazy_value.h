#include <functional>
#include <memory>

template <typename T>
class LazyValue
{
public:
    explicit LazyValue(std::function<T()> init) : init_{init}
    {
    }
    bool HasValue() const
    {
        return static_cast<bool>(upValue_);
    }
    const T &Get() const
    {
        if (!HasValue())
            CreateValue();
        return *upValue_.get();
    }

private:
    void CreateValue() const
    {
        upValue_ = std::make_unique<T>(init_());
    }

private:
    std::function<T()> init_;
    mutable std::unique_ptr<T> upValue_;
};
