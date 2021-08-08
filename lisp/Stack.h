#include <vector>
#include <optional>

#ifndef LS_STACK
#define LS_STACK

template <class Type>
using Option = std::optional<Type>;

template <class T>
class Stack
{
public:
    void push(T element);

    Option<T> pop();

    Option<T> pop(int idx);

    bool good_index(int idx);

private:
    std::vector<T> data_;
};

template <class T>
bool Stack<T>::good_index(int idx)
{
    if (idx >= data_.size())
    {
        return false;
    }
    if (idx < 0)
    {
        return false;
    }
    return true;
}

template <class T>
void Stack<T>::push(T element)
{
    data_.push_back(element);
}

template <class T>
Option<T> Stack<T>::pop()
{
    if (data_.empty())
    {
        return std::nullopt;
    }

    auto element = data_.back();
    data_.pop();
    return optional(element);
}

/// \returns Element at the idx element from the bottom if the value is negative
///     the index is counted from the top (idx=-1 takes the last element put on the stack)
template <class T>
Option<T> Stack<T>::pop(int idx)
{
    if (idx < 0)
    {
        idx = data_.size() + idx;
    }

    if (!good_index(idx))
    {
        return std::nullopt;
    }

    auto element = data_[idx];
    data_.erase(idx);
    return optional(element);
}

#endif