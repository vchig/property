#pragma once
#include <boost/any.hpp>

namespace property {

struct property_base
{
    virtual ~property_base();
    virtual boost::any get() const = 0;
    virtual void set(const boost::any&) = 0;
    virtual bool is_read_only() const = 0;
};

template< typename C, typename T >
struct property : public property_base
{
    // property_base interface
public:
    typedef T       (C::*getter_type)() const;
    typedef void    (C::*setter_type)(const T&);

    property(C* obj, getter_type getter, setter_type setter = nullptr)
        : object_(obj), getter_(getter), setter_(setter)
    {
    }

    boost::any get() const override
    {
        return (object_->*getter_)();
    }
    void set(const boost::any& value) override
    {
        (object_->*setter_)( boost::any_cast<T>(value) );
    }

    bool is_read_only() const override
    {
        return setter_ == nullptr;
    }

private:
    C* object_;             ///! Указатель на класс
    getter_type getter_;    ///! Указатель на метод геттера
    setter_type setter_;    ///! Указатель на метод сеттера
};

} // namespace property
