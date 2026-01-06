#include <iostream>
#include "Example.hpp"

int Example::_object_counter = 0;

Example::Example() // default constructor
    : _tag(boost::uuids::random_generator()())
{
    _object_counter++;
    std::cout << "Created object:\n"
              << "\tnum_of_obj: " << Example::_object_counter << "\n\tuuid: " << this->_tag << "\n";
}

Example::Example(Example const &rhs) // copy constructor
    : _tag(rhs._tag)
{
    _object_counter++;
    std::cout << "Created object:\n"
              << "\tnum_of_obj: " << Example::_object_counter << "\n\tuuid: " << this->_tag << "\n";
}

Example::~Example()
{
    std::cout << "Destroyed object:\n"
              << "\tnum_of_obj: " << Example::_object_counter << "\n\tuuid: " << this->_tag << "\n";
    _object_counter--;
}

int Example::getObjCnt()
{
    return Example::_object_counter;
}