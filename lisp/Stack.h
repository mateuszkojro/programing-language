#include <vector>
#include <optional>

template<class Type>
using option = std::optional<Type>;

template <class T>
class Stack
{
public:
    using option = std::optional<T>;

    void push(T *element);

    option pop();

    option pop(int idx);

private:
    std::vector<T> data_;
};

template<class T>
void Stack<T>::push(T* element){
    data_.push_back(element);
}

template <class T>
option<T> Stack<T>::pop()
{
    auto element = data_.back();
    data_.pop();
    return optional(element);
}

template <class T>
option<T> Stack<T>::pop(int idx)
{
    throw std::exception("Not implemented");
    data_.pop();
    return std::nullopt;
}