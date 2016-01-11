#ifndef __BINGCHEN_EXCEPTION_H_
#define __BINGCHEN_EXCEPTION_H_

#include <string>
#include <exception>

namespace bingchen {

class exception : public std::exception
{
private: 
    std::string backTrace_;
    std::string message_;

    void fillBackTrace();

public:
    explicit exception(const char* msg);
    explicit exception(const std::string& msg);
    virtual ~exception() throw();

    virtual const char* what() const throw();
    const char* getBackTrace() const throw();
};

};

#endif
