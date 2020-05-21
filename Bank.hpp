#pragma once
#include <iostream>
#include <string>


struct Bank {
 
    std::string name_;
    double amount_starting_;
    double amount_salary_;
    double amount_left_ = 0;

    Bank( const std::string & name="", const double & starting=0.0, const double & salary=0.0);
};
