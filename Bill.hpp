#pragma once
#include <iostream>
#include <string>


struct Bill {

    std::string payee_;
    double amount_due_;
    unsigned int due_month_;
    unsigned int due_day_;

    Bill( std::string  name="",
        const double & dues=0.0,
        const unsigned int & month=0,
        const unsigned int & day=0);
    bool isOverdue(const unsigned int &currMonth, const unsigned int& currDay );
    unsigned int daysOverdue(const unsigned int &currMonth, const unsigned int& currDay );
};
