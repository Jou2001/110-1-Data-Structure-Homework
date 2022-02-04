// 10927202 陽彩柔

#include<stdio.h>    // printf
#include<string>     // stoi string
#include<iostream>   // cin cout
#include <time.h>    // time

#define llu unsigned long long int // using unsigned long long int can let the range bigger than int
using namespace std ;

int GetNum() ;
bool is_Num( string input ) ;
llu HowMany( int input, int number ) ;
void find_Per( int input, int several ) ;

llu num[100] = {0}, tmp = 0, cmd ;
int outer_times = 0, inner_times = 0, divisor = 1 ;
int number[10] = {0,1,2,3,4,5,6,7,8,9} ;

int size,k = 1;
int result[] = {0} ;
double start ;
double e_nd ;

int main() {
  int input ;
  while( true ) {
    cout << endl << "** Fibonacci Series Generator  **" ;
    cout << endl << "*  0. Quit                      *" ;
    cout << endl << "*  1. Iterative Generation      *" ;
    cout << endl << "*  2. Recursive Generation      *" ;
    cout << endl << "*  3. Permutation Generator     *" ;
    cout << endl << "*********************************" ;
    cout << endl << "Input a command(0,1,2,3):"  ;
    
    string str ;
    cin >> str ;
    
    while( !is_Num(str) ) { // str is not an integer keep input until the command is integer
      cout << "Input a command(0,1,2,3):"  ;
      cin >> str ;
    } // while
    
    cmd = stoi(str) ; // let str convert to integer
    
    if ( cmd == 0 )
      break ;
    
    else if ( cmd == 3 ) {
      input = GetNum() ;
      int several = HowMany(input, 10) ;
      start = clock() ;
      size = 0 , k = 1;
      find_Per( input, several );
      e_nd = clock() ;
      printf( "%f ms\n", (e_nd - start)  ) ;
    } // else if
        
    else
      cout << endl << endl << "Command Does Not Exist. Try Again! " ;

    } // while

  } // main


llu HowMany( int input, int number ) { // calculate how many possible several
  if( input > 0 )
    return (number) * HowMany( --input, number-1 ) ;
  else
    return 1 ;
} // HowMany


void find_Per( int input, int several ) {
  int i,j;
  bool repeat = false ;
  
  if( size == input ) {
    for( int b = 0 ; b < input && repeat == false ; b++ ) { // check repeat
      for( int a = b+1 ; a < input  ; a++ ) {
        if( result[b] == result[a] )
          repeat = true ;
      } // for
    } // for
    
    
    if ( repeat == false ) {
      if ( k <= several ) {
        printf( "[%3d] ", k) ;
        k++ ;
      } // if
      
      for(i=0; i< input ; i++ ) //i<input &&
        printf( "%d ", result[i] ) ;
  
      printf( "\n" ) ;
    } // if
    
    size--;
  } // if
  
  else {
    for( i=0 ; i< 10 ; i++ ) {
      for( j=1 ; j<=size ; j++ ){
        if( result[j] == i )
          break;
      } // for
          
      if( j>size ) {
        result[size] = i;
        size++;
        find_Per(input, several );
      } // if
    } //for
    size--;
  } // else
  
} // find_Per

bool is_Num( string input ) { // check the string input is an integer or not
  
  for( int i = 0 ; i < input.size() ; i++ ) { // input.size can return the length of the string input
    if( input[i] >= '0' && input[i] <= '9' ) // Use ASCII to know whether the input[i] is an integer
      continue ;
    else
      return false ; // String input have an element that is not integer
  } // for
  return true ; // In string input all of the elements are an integer
  
} // is_Num

int GetNum() { // Get a number from user and make sure the number no more than 92
  string input ;
  
  while(true) {
    if ( cmd == 3 )
      cout << "Enter a positive integer agree [2,9]:" ;
    else
      cout << "Enter a positive integer no more than 92:" ;
    cin >> input ;
    
    if ( !is_Num( input ) ) // Input is not integer
      cout << "Not an integer Please try again! " << endl ;
   
    else { // Input is an integer
      int num = stoi(input) ; // convert input from string to int
      if ( cmd == 3 ) {
        if( num >= 2 && num <= 9 )
          return num ;
        else
          cout << "Wrong integer Please try again! " << endl ;
      } // if
      
      else {
        if ( num >= 0 && num <= 92 )
          return num ;
        else
          cout << "Wrong integer Please try again! " << endl ;
      } // else
    } // else
  } // while
} // GetNum
