#include "EmptyCommand.h"
#include "ICommand.h"
#include "UObject.h"

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <print>
#include <functional>

#include <vector>
#include <any>
#include <tuple>
#include <string>




#if 0
namespace otus
{

class TypeErasedHolder
{
  struct TypeKeeperBase
  {
    virtual ~TypeKeeperBase() {}
  };

  template <class ErasedType>
  struct TypeKeeper : TypeKeeperBase
  {
    ErasedType storedObject;

    TypeKeeper(ErasedType&& object) : storedObject(std::move(object)) {}
  };

  std::unique_ptr<TypeKeeperBase> held;

public:
  template <class ErasedType>
  TypeErasedHolder(ErasedType objectToStore) : held(new TypeKeeper<ErasedType>(std::move(objectToStore)))
  {}
};
template<typename T>
struct Constructor
{
    template<typename... Args>
    std::shared_ptr<T> create(Args&&... args)
    {
        //return nullptr;
        return std::make_shared<T>((std::forward<Args>(args)), ...)));
    }
};

struct IBuilder
{
    virtual ~IBuilder() = default;
};

struct Builder
{
    using Function = std::function<std::shared_ptr<otus::ICommand>(std::shared_ptr<otus::UObject> obj)>;
    Builder() = delete;

    Builder(Function&& func)
        : m_func(func)
    {}

    std::shared_ptr<ICommand> operator()(std::shared_ptr<otus::UObject> obj)
    {
        std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);
        return std::invoke(m_func, obj);
    }

    Function m_func;
};

class CreatorBase
{
public:
    CreatorBase(const std::string& key)
        : m_key(key)
    {}
    virtual ~CreatorBase() = default;

    const std::string& key() const { return m_key; }
private:
    std::string m_key;
};

// Intermezzo Class
template<typename T, class... Args> 
class ClassCreator : public CreatorBase
{
public:
    ClassCreator(const std::string& k)
        : CreatorBase(k)
    {}

    virtual T* create(Args&&... args) const = 0;
};


// Concrete Product Creator
template<typename T, class Product, class... Args>
class Creator : public ClassCreator<Args...>
{
public:
    Creator(const std::string& k)
        : ClassCreator<Args...>(k)
    {}

    T* create(Args&&... args) const override
    {
        return new Product(std::forward<Args>(args)...);
    }
};
#endif

namespace otus
{


template<typename... Args>
struct Binder
{
    static std::tuple<Args...> convert_args(std::vector<std::any> any_args)
    {
        auto convert = [i = 0u, &any_args](auto& arg) mutable
        {
            arg = std::any_cast<decltype(arg)>(any_args.at(i));
            ++i;
        };
        std::tuple<Args...> vs;
        std::apply([&](Args& ... args) { (convert(args), ...); }, vs);
        return vs;
    }

    template<typename F>
    decltype(auto) call(F f, std::vector<std::any> args) const
    {
        return std::apply(std::move(f), convert_args(std::move(args)));
        std::make_from_tuple<Foo>(std::move(tuple));
    }
};


struct Builder
{
    using Function = std::function<std::shared_ptr<otus::ICommand>(std::shared_ptr<otus::UObject> obj)>;
    Builder() = delete;

    Builder(Function&& func)
        : m_func{func}
    {}

    template<typename... Args>
    std::shared_ptr<ICommand> operator()(std::shared_ptr<otus::UObject> obj, Args&&... args) const
    {
        std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);
        return std::invoke(m_func, obj);
    }

    Function m_func;
};

template<typename T, typename U>
struct Creator
{
    using Function = std::function<std::shared_ptr<T>(std::shared_ptr<U> obj)>;
    Creator() = delete;

    Creator(Function&& func)
        : m_func{func}
    {}

    std::shared_ptr<T> operator()(std::shared_ptr<U> obj) const
    {
        std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);
        return std::invoke(m_func, obj);
    }

    Function m_func;
};



class IoC
{
public:
    using BuilderMap = std::unordered_map<std::string, Builder>;

    struct RegisterCommand : public ICommand
    {
        RegisterCommand(const std::string& path, Builder&& builder, BuilderMap& map)
            : m_path{path}
            , m_map{map}
            , m_builder{std::move(builder)}
        {}


        void execute() override
        {
            m_map.emplace(m_path, std::move(m_builder));
        }

        std::string m_path;
        BuilderMap& m_map;
        Builder m_builder;
    };

    IoC() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> Resolve(const std::string& path, Args&&... args)
    {
        std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);
        if (path == "Spaceship.Operations.IMovable:position.set")
        {
            return nullptr;

        }

        return (m_scope.at(path))(std::forward<Args>(args)...);
    }

    template<typename T, typename TPath=std::string, typename... Args>
    std::shared_ptr<T> Resolve(const std::string& action, const TPath& path, Args&&... args)
    {
        std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);

        Builder builder(std::forward<Args>(args)...);
        return std::make_shared<RegisterCommand>(path, std::move(builder), m_scope);
    }

private:
    BuilderMap m_scope;
};

}  // namespace otus
