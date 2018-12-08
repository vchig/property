#pragma once
#include <boost/any.hpp>
#include <functional>

namespace property {

struct property_base
{
    virtual ~property_base();
    virtual boost::any get() const = 0;
    virtual void set(const boost::any&) = 0;
    virtual bool is_read_only() const = 0;
};

template <typename C, typename T>
struct property_read
        : public property_base
{
    typedef T       (C::*getter_type)() const;

    property_read(C* obj, getter_type getter)
        : object_(obj), getter_(getter)
    {
    }

    boost::any get() const override
    {
        return (object_->*getter_)();
    }

    void set(const boost::any&) override
    {
    }

    bool is_read_only() const override
    {
        return true;
    }

protected:
    C* object_;             ///! Указатель на класс
    getter_type getter_;    ///! Указатель на метод геттера
};

template <typename T>
struct property_rw;

template <typename C, typename T>
struct property_rw<void (C::*)(const T&)>
    : public property_read<C,T>
{
    typedef void    (C::*setter_type)(const T&);

    typedef property_read<C,T>  read_type;
    typedef typename read_type::getter_type getter_type;

    property_rw(C* obj, getter_type getter, setter_type setter)
        : property_read<C,T>(obj, getter),
          setter_(setter)
    {
    }

    void set(const boost::any& value) override
    {
        (read_type::object_->*setter_)( boost::any_cast<T>(value) );
    }

    bool is_read_only() const override
    {
        return false;
    }

private:
    setter_type setter_;    ///! Указатель на метод сеттера
};

template <typename C, typename T>
struct property_rw<void (C::*)(T)>
    : public property_read<C,T>
{
    typedef void    (C::*setter_type)(T);

    typedef property_read<C,T>  read_type;
    typedef typename read_type::getter_type getter_type;

    property_rw(C* obj, getter_type getter, setter_type setter)
        : property_read<C,T>(obj, getter),
          setter_(setter)
    {
    }

    void set(const boost::any& value) override
    {
        (read_type::object_->*setter_)( boost::any_cast<T>(value) );
    }

    bool is_read_only() const override
    {
        return false;
    }

private:
    setter_type setter_;    ///! Указатель на метод сеттера
};

} // namespace property
