#include <property/system.hpp>
#include <iterator>

int property::system::propertyCount() const
{
    return static_cast<int>( properties_.size() );
}

std::string property::system::propertyName(int i) const
{
    if( propertyCount() <= i )
        return std::string();
    auto pos = properties_.begin();
    std::advance(pos, i);
    return pos->first;
}

bool property::system::propertyIsReadOnly(int i) const
{
    if( propertyCount() <= i )
        return true;
    auto pos = properties_.begin();
    std::advance(pos, i);
    return pos->second->is_read_only();
}

boost::any property::system::getProperty(int i) const
{
    if( propertyCount() <= i )
        return boost::any();
    auto pos = properties_.begin();
    std::advance(pos, i);
    return pos->second->get();
}

boost::any property::system::getProperty(const std::string &name)
{
    if( properties_.find(name) != properties_.end() )
        return properties_[name]->get();
    return boost::any();
}

void property::system::setProperty(const std::string &name, const boost::any &value)
{
    if( properties_.find(name) != properties_.end() )
    {
        auto& prop = properties_[name];
        if( !prop->is_read_only() )
            prop->set( value );
    }
}
