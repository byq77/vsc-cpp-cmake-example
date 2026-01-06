#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Example
{
public:
    Example();
    Example(Example const &);
    virtual ~Example();
    const boost::uuids::uuid &getTag() const { return _tag; }
    static int getObjCnt();

protected:
    static int _object_counter;

private:
    boost::uuids::uuid _tag;
};
