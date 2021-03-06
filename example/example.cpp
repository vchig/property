#include <iostream>
#include <property/system.hpp>
#include <type_traits>

class Test : public property::system
{
    std::string msg_;
    float       value_;
    int         counter_;

public:
    Test()
    {
        value_   = 123.1114f;
        counter_ = 8871;
        msg_     = "Message";
        makeProperty< Test, int >( "counter", this, &Test::counter );
        makeProperty< Test, float >( "value", this, &Test::value, &Test::setValue );
        makeProperty< Test, std::string >( "message", this, &Test::message, &Test::setMessage );
    }

    float value() const { return value_; }
    void  setValue( float f ) { value_ = f; }

    int counter() const { return counter_; }

    std::string message() const { return msg_; }
    void        setMessage( const std::string &msg ) { msg_ = msg; }
};

class Foo
{
public:
    property::Property< int >         a;
    property::Property< int >         b;
    property::Property< double >      c;
    property::Property< std::string > str;
};

int main( int, char ** )
{
    Test t;
    std::cout << "Count properties: " << t.propertyCount() << std::endl;
    for( int i = 0; i < t.propertyCount(); ++i ) std::cout << "Name: " << t.propertyName( i ) << std::endl;
    std::cout << "Get property 'value': " << t.getProperty< float >( "value" ) << std::endl;
    std::cout << "Get property 'counter': " << t.getProperty< int >( "counter" ) << std::endl;
    std::cout << "Get property 'message': " << boost::any_cast< std::string >( t.getProperty( "message" ) )
              << std::endl;
    t.setProperty( "value", 34.41f );
    t.setProperty( "message", std::string( "New message" ) );
    std::cout << "Get property 'value': " << t.getProperty< float >( "value" ) << std::endl;
    std::cout << "Get property 'message': " << boost::any_cast< std::string >( t.getProperty( "message" ) )
              << std::endl;

    Foo foo;

    std::cout << "Foo property value: " << foo.a << " " << foo.b << " " << foo.c << " " << foo.str.get() << std::endl;
    foo.a   = 12;
    foo.b   = 34;
    foo.c   = 23.1;
    foo.str = "ASD";
    std::cout << "Foo property value: " << foo.a << " " << foo.b << " " << foo.c << " " << foo.str.get() << std::endl;

    return 0;
}
