#include <memory>

namespace otus
{
    template<typename T>
    struct Constructor
    {
        template<typename... Args>
        std::shared_ptr<T> create(Args&&... args)
        {
            return std::make_shared<T>((std::forward<Args>(args)), ...)));
        }
    };


class IoC
{
public:

    struct Register
    {


    };

    IoC() = default;

    template<typename InterfaceType, typename ObjectType, typename... Args>
    std::shared_ptr<InterfaceType> Resolve(const std::string& path, Args&&... args)
    {




        
        (std::forward<Args>(args)), ...);

    }

private:

    template<typename T, typename... Args>
    std::shared_ptr<T> create(std::shared_ptr<T> obj)
    {
        return obj;
    }

};

}  // namespace otus
