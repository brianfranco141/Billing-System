#pragma once
#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

#include "Bank.hpp"
#include "Bill.hpp"

template< class Strategy>
struct Strategy_t {
  Bank     myChecking_;
  Strategy allBills_;
  double   amount_penalties_;

  Strategy_t( const std::string & name     = "",
              double              starting = 0.0,
              double              salary   = 0.0 );
  void readFile( const std::string & filename );
  bool payBills(const unsigned int &, const unsigned int&);
};

// Aliases for popular strategies for convenience
using QueueStrategy = Strategy_t<std::queue<Bill>>;
using StackStrategy = Strategy_t<std::stack<Bill>>;

using std::getline;
using std::ifstream;
using std::stod;
using std::stoul;
using std::string;
using std::stringstream;


template<typename T>
auto & peek( std::stack<T> & container )
{ return container.top(); }

template<typename T>
auto & peek( std::queue<T> & container )
{ return container.front(); }


template<class Strategy>
Strategy_t<Strategy>::Strategy_t( const std::string & name,
                                  double              starting,
                                  double              salary )
  : myChecking_( name, starting, salary ), amount_penalties_( 0.0 )
{}

template<class Strategy>
bool Strategy_t<Strategy>::payBills(const unsigned int & currMonth,

				    const unsigned int & currDay) {
  //pay the bills starting from top/front as long as there is
  //enough money in the checking account
  //returns true if all bills are paid, false otherwise
  Bill someBill;
  while( allBills_.size() > 0 ) {
    someBill    = peek( allBills_ );
    double fee = 0.0;
    if( someBill.isOverdue( currMonth, currDay ) ) {
      fee = fee + (35 + round(0.1 * someBill.daysOverdue(currMonth, currDay) * someBill.amount_due_)/100);
    }
    
    if( someBill.amount_due_ + fee <= myChecking_.amount_left_ ) {
      myChecking_.amount_left_ -= someBill.amount_due_ + fee;
      allBills_.pop();
      amount_penalties_ += fee;
    }
    else
      break;
  }
  return (allBills_.size() == 0);
}

template<class Strategy>
void Strategy_t<Strategy>::readFile( const std::string & filename )
{
  ifstream inFile( filename );
  Bill     newBill;
  string   line;

  // Read each line
  while( getline( inFile, line ) )
  {
    // Break each line up into 'cells'
    stringstream lineStream( line );
    string       cell;
    while( getline( lineStream, cell, ',' ) ) {
      if( cell == "bill" ) {
          // read the data for the new bill
        getline( lineStream, newBill.payee_, ',' );

        getline( lineStream, cell, ',' );
        newBill.amount_due_ = stod( cell );

        getline( lineStream, cell, '/' );
        newBill.due_month_ = stoul( cell );

        getline( lineStream, cell, '\n' );
        newBill.due_day_ = stoul( cell );

	allBills_.push(newBill);
      }
      
      else if( cell == "paycheck" ) {
	getline( lineStream, cell, '\n' );
	myChecking_.amount_left_ += stod( cell );
      }
      
      else if( cell == "pay" ) {
        // retrieve the date, month and day, of the pay
        getline( lineStream, cell, '/' );
        unsigned int currMonth = stoul( cell );
	
        getline( lineStream, cell, '\n' );
        unsigned int currDay = stoul( cell );
	
	// CALL THE FUNCTION MEMBER TO PAY AS MANY BILLS AS POSSIBLE
	payBills(currMonth, currDay);

      }
    }
  }
  inFile.close();
}
