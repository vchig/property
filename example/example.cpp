#include <iostream>
#include <property/system.hpp>
#include <type_traits>

class Test : public property::system
{
    float val;
    std::string msg;
public:
    Test()
    {
        msg = "Message";
        makeProperty<Test, float>("value", this, &Test::value, &Test::setVal);
        makeProperty<Test, std::string>("message", this, &Test::message);
    }

    void setVal(const float& v) { val = v; }
    float value() const { return val; }
    std::string message() const { return msg; }
};

int main(int, char**)
{
    Test t;
    std::cout << "Count properties: " << t.propertyCount() << std::endl;
    for( int i = 0; i < t.propertyCount(); ++i )
        std::cout << "Name: " << t.propertyName(i) << std::endl;
    t.setProperty("value", 34.41f);
    std::cout << "Get property 'value': " << t.getProperty<float>("value") << std::endl;
    std::cout << "Get property 'message': " << boost::any_cast<std::string>(t.getProperty("message")) << std::endl;

    return 0;
}
