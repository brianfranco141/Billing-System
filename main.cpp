#include <iostream>
#include <string>
#include <cmath>   // abs()

#include "Strategies.hpp"

using namespace std;

static int       testCount = 0;
static const int testTotal = 20;

bool assertTrue( const string & nameOfTest, double expected, double actual );

template <typename T, typename U>
bool assertTrue( const string & nameOfTest, const T & expected, const U & actual );


int main(int argc, char const *argv[]) {
  {
    QueueStrategy q1;
    q1.readFile( "data1.txt" );
    
    std::cout <<" Queue Strategy: file data1.txt" << std::endl;
    assertTrue( "Amount left", 1000.0, q1.myChecking_.amount_left_ );
    assertTrue( "Number of bills", 4, q1.allBills_.size() );
    assertTrue( "First bill: Payee", "Chase credit card", q1.allBills_.front().payee_ );
    assertTrue( "First bill: Amount due", 535.49, q1.allBills_.front().amount_due_ );
    assertTrue( "First bill: Month due", 1, q1.allBills_.front().due_month_  );
    assertTrue( "First bill: Day due", 17, q1.allBills_.front().due_day_ );
    std::cout << std::endl;
  }
 
  {
    StackStrategy s1;
    s1.readFile( "data1.txt" );
    
    std::cout <<" Stack Strategy: file data1.txt" << std::endl;
    assertTrue( "Amount left", 1000.0, s1.myChecking_.amount_left_ );
    assertTrue( "Number of bills", 4, s1.allBills_.size() );
    assertTrue( "First bill: Payee", "Republic Services trash", s1.allBills_.top().payee_ );
    assertTrue( "First bill: Amount due", 62.75, s1.allBills_.top().amount_due_ );
    assertTrue( "First bill: Month due", 1, s1.allBills_.top().due_month_  );
    assertTrue( "First bill: Day due", 13, s1.allBills_.top().due_day_ );
    std::cout << std::endl;
  }
  {
    QueueStrategy q2;
    q2.readFile( "data2.txt" );
    
    std::cout <<" Queue Strategy: file data2.txt" << std::endl;
    assertTrue( "Amount left in checking account", 325.33, q2.myChecking_.amount_left_ );
    assertTrue( "Amount penalties in overdue bills", 81.29,  q2.amount_penalties_ );
    std::cout << std::endl;
  }
  
  {
    StackStrategy s2;
    s2.readFile( "data2.txt" );
    
    std::cout <<" Stack Strategy: file data2.txt" << std::endl;
    assertTrue( "Amount left in checking account", 900.37, s2.myChecking_.amount_left_ );
    assertTrue( "Amount penalties in overdue bills", 36.88,  s2.amount_penalties_        );
    std::cout << std::endl;
  }
  {
    QueueStrategy q3;
    q3.readFile( "data3.txt" );
    
    std::cout <<" Queue Strategy: file data3.txt" << std::endl;
    assertTrue( "Amount left in checking account",   45.54,  q3.myChecking_.amount_left_ );
    assertTrue( "Amount penalties in overdue bills", 239.22, q3.amount_penalties_ );
    std::cout << std::endl;
  }
  
  {
    StackStrategy s3;
    s3.readFile( "data3.txt" );
    
    std::cout <<" Stack Strategy: file data3.txt" << std::endl;
    assertTrue( "Amount left in checking account", 30.69,  s3.myChecking_.amount_left_ );
    assertTrue( "Amount penalties in overdue bills", 254.07, s3.amount_penalties_        );
    std::cout << std::endl;
  }
 
  cout << endl << testCount << " tests passed out of " << testTotal << " total tests" << endl;
  return 0;
}


bool assertTrue (const string& nameOfTest, double expected, double actual) {
  if ( abs(expected - actual) < 0.005 )  {
    // Green colored text
    cout << "\033[32m" << "PASSED "
	 << "\033[0m" << nameOfTest << ": expected and actual " << actual << endl;
    testCount++;
    return true;
  }
  // Red colored text
  cout << "\033[31m" << "FAILED "
       << "\033[0m" << nameOfTest << ": expected " << expected << " but actual " << actual << endl;
  return false;
}



template <typename T, typename U>
bool assertTrue(const string& nameOfTest, const T& expected, const U& actual) {
  if (expected == actual) {
    // Green colored text
    cout << "\033[32m" << "PASSED "
	 << "\033[0m" << nameOfTest << ": expected and actual " << actual << endl;
    testCount++;
    return true;
  }
  // Red colored text
  cout << "\033[31m" << "FAILED "
       << "\033[0m" << nameOfTest << ": expected " << expected << " but actually " << actual << endl;
  return false;
}
