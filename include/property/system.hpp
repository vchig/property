#pragma once
#include "property.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace property
{

class system
{
public:
    bool hasProperty( const std::string &name ) const;

    int propertyCount() const;

    std::string propertyName( int i ) const;

    bool propertyIsReadOnly( int i ) const;

    boost::any getProperty( int i ) const;

    boost::any getProperty( const std::string &name );

    template < typename T >
    T getProperty( const std::string &name )
    try {
        return boost::any_cast< T >( getProperty( name ) );
    } catch( const boost::bad_any_cast & ) {
        return T();
    }

    void setProperty( const std::string &name, const boost::any &value );

    void setProperty( int i, const boost::any &value );

protected:
    template < typename C, typename T >
    void makeProperty( const std::string &name, C *object, T ( C::*getter )() const, void ( C::*setter )( const T & ) )
    {
        properties_.insert( std::make_pair(
            name,
            std::shared_ptr< property_base >( new property_rw< decltype( setter ) >( object, getter, setter ) ) ) );
    }

    template < typename C, typename T >
    void makeProperty( const std::string &name, C *object, T ( C::*getter )() const, void ( C::*setter )( T ) )
    {
        properties_.insert( std::make_pair(
            name,
            std::shared_ptr< property_base >( new property_rw< decltype( setter ) >( object, getter, setter ) ) ) );
    }

    template < typename C, typename T >
    void makeProperty( const std::string &name, C *object, T ( C::*getter )() const )
    {
        properties_.insert(
            std::make_pair( name, std::shared_ptr< property_base >( new property_read< C, T >( object, getter ) ) ) );
    }

private:
    std::map< std::string, std::shared_ptr< property_base > > properties_;
};

} // namespace property
