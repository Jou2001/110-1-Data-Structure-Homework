 // 第七組 10927202 陽彩柔 10927212 趙珀 
#include<iostream>
#include<fstream>  // ifstream
#include<vector>
#include<time.h>   // clock
#include<conio.h>  // getch
#include<iomanip>  // setprecision 

using namespace std ;

struct job ;
struct Abort ;
struct Done ;
class Queue ;
  
bool open = true ; // check the file exist
double readFinish, sortFinish, writeFinish ;
string file_name ;

bool alreadysorted = false ;
string GetNum( ) ;          // get the file number
bool is_Num( string str ) ; // check the string 

void read(vector<job> &list ) ;        // read data 
void shellshort( vector<job> &list ) ; // sort data 
void printVector( vector<job> list) ;  // print data 
void file_out( vector<job> &list ) ;   // write sort data 
void printTime( double readFinish, double sortFinish, double writeFinish ) ; // print time 
void readfile( vector<job> &list ) ; // read sort data
void work( vector<job> list, vector<Done> &Done_List, vector<Abort> &Abort_List, Queue Queue  ) ; // do mission 2
void file_out2( vector<Done> Done_List ,vector<Abort> Abort_List ) ; // write output data
void work2( vector<job> list, vector<Done> &Done_List, vector<Abort> &Abort_List, Queue Queue1, Queue Queue2  );
void file_out3( vector<Done> Done_List ,vector<Abort> Abort_List ) ; // write data

struct job {
  int OID ;
  int Arrival ;
  int Duration ;
  int TimeOut ;
}; // job

struct Done {
	int OID ;
	int Departure ;
	int Delay ;
	int CID ;
}; // Done

struct Abort {
	int OID ;
	int abort ;
	int Delay ;
	int CID ;
}; // Abort

class Queue {
	
private:
	struct Data {
		int OID ;
  	int Arrival ;
  	int Duration ;	
  	int TimeOut ;
  	Data *next ;
	}; // Data
	
	Data *backPtr = NULL ;

public:
	int size = 0 ; // calculate the size of queue 
	bool isEmpty() {
  	if ( backPtr == NULL ) return true ;
  	else return false ;
	} // isEmpty
	
  void enqueue( job newItem ) {
  	Data * newPtr = new Data ;
  	newPtr->OID = newItem.OID ;
  	newPtr->Arrival = newItem.Arrival ;
  	newPtr->Duration = newItem.Duration ;
  	newPtr->TimeOut = newItem.TimeOut ;
  	
  	if( isEmpty() ) newPtr->next = newPtr ;
  	else {
  		newPtr->next = backPtr->next ;  
  		backPtr->next = newPtr ;
		} // else
  	backPtr = newPtr ;
  	++size ;
	} // enqueue
	
  void dequeue( job &queue_info ) {
  	if ( !isEmpty() ) {
  		Data * tempPtr = backPtr->next ;
  		
  		queue_info.OID = tempPtr->OID ;
			queue_info.Arrival = tempPtr->Arrival ;
			queue_info.Duration = tempPtr->Duration ;
			queue_info.TimeOut = tempPtr->TimeOut ;
			
			if ( backPtr == backPtr->next) 	backPtr = NULL ;
			else backPtr->next = tempPtr->next ;
			
			tempPtr->next = NULL ;
			--size ;
			delete tempPtr ;
		} // if
	} // dequeue
	
	
	void Print () {
		
		if ( ! isEmpty() ) {
			Data * temp = backPtr->next ;
			while( temp != backPtr ) {
				cout << temp->OID << endl ;
				temp = temp -> next ;
			} // while()s

			cout << backPtr->OID << endl ;
		} // if() s 
	} // Print()
} ; // Queue


int main() {
  while( true ){
    cout << endl ;
    cout << "** Simulate FIFO Queues by SQF   **" << endl ;
    cout << "*  0. Quit                        *" << endl ;
    cout << "*  1. Sort a file                 *" << endl ;
    cout << "*  2. Simulate one FIFO queue     *" << endl ;
    cout << "*  3. Simulate two queues by SQF  *" << endl ;
    cout << "***********************************" << endl ;
    cout << "Input a command(0,1,2,3):"  ;
    
    string str ;
    cin >> str ;
    
    while( !is_Num(str) ) { // str is not an integer keep input until the command is integer
      cout << "Command does not exist!" << endl ;
      cout << "Input a command(0,1,2,3):" ;
      cin >> str ;
    } // while
    
    int cmd = stoi(str) ; // let str convert to integer
    
    if ( cmd == 0 )
      break ;
              
    else if ( cmd == 1) {
    	vector<job> list ;
      read(list) ;
      if (open) {           // file exist
      	printVector(list) ; // print file content
      	shellshort(list) ;  // use shell short to sort the file data
    		file_out(list) ;    // write sort data
    		cout << endl << "請按任意鍵繼續..." << endl ;
				int ch = getch() ; 
    		printTime( readFinish, sortFinish, writeFinish ) ;
    		cout << endl << "See sorted" << file_name << ".txt" << endl ;
    	} // if
    } // else if
    
    else if ( cmd == 2 ) {
    	vector<job> list ;
    	vector<Done> Done_List ;
    	vector<Abort> Abort_List ;
    	Queue Queue ;
    	readfile(list) ;
   		if(open) {
				work( list, Done_List, Abort_List, Queue ) ; // do mission 2
    		file_out2( Done_List, Abort_List ) ;         // write output data
    		cout << endl << "The simulation is running..." << endl <<  "See output" << file_name << ".txt" << endl ;
    	} // if
		} // else if
		
		else if ( cmd == 3 ) {
			vector<job> list ;
			vector<Done> Done_List ;
    	vector<Abort> Abort_List ;
    	Queue Queue1, Queue2 ;
			readfile(list) ; 
			if(open) {
				work2( list, Done_List, Abort_List, Queue1, Queue2 ) ; // do mission 2
    		file_out3( Done_List, Abort_List ) ;         // write output data
    		cout << endl << "The simulation is running..." << endl <<  "See double" << file_name << ".txt" << endl ;
    	} // if
		} // else if
    
    else cout << "Command does not exist!" << endl ; // cmd is not 1 or 2
  } // while
} // main

void work2( vector<job> list, vector<Done> &Done_List, vector<Abort> &Abort_List, Queue Queue1, Queue Queue2  ) { // do mission 3
	int nowTime1 = 0, nowTime2 = 0, nowTime = 0 ;
	job queue_info ;
	Done temp1 ;
	Abort temp2 ;
	bool is_1or2 = true;
	
	while ( !list.empty() ) { 
	
	  is_1or2 = true ;
		if ( list[0].Arrival >= nowTime1 || list[0].Arrival >= nowTime2 ) {

			if( Queue1.isEmpty() && Queue2.isEmpty() )	{
				if ( list[0].Arrival >= nowTime1 ) {
					temp1.OID = list[0].OID ;
					temp1.Departure = list[0].Arrival + list[0].Duration ;
					temp1.Delay = 0 ;
					temp1.CID = 1;
					nowTime1 = temp1.Departure;
				} // if
					
				else if ( list[0].Arrival >= nowTime2 ) {
					temp1.OID = list[0].OID ;
					temp1.Departure = list[0].Arrival + list[0].Duration ;
					temp1.Delay = 0 ;
					temp1.CID = 2;
					nowTime2 = temp1.Departure;
				} // else if
						
				Done_List.push_back(temp1) ;		  
			} // if
			
			else { // QUEUE IS NOT EMPTY
				for ( int i = 0 ; !Queue1.isEmpty() && list[0].Arrival >= nowTime1 ; i++ ) {
					Queue1.dequeue(queue_info) ;
					nowTime = nowTime1 ;
					is_1or2 = true ;
					if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
						temp2.OID = queue_info.OID ;
						temp2.abort = nowTime ;
						temp2.Delay = nowTime - queue_info.Arrival ;
						if(is_1or2) temp2.CID = 1;
						else temp2.CID = 2;
						Abort_List.push_back(temp2) ;
		
					} //  if
					
					else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
						temp2.OID = queue_info.OID ;
						temp2.abort = queue_info.TimeOut ;
						temp2.Delay = temp2.abort - queue_info.Arrival ;
						if(is_1or2) temp2.CID = 1;
						else temp2.CID = 2;
						Abort_List.push_back(temp2) ;
						if(temp2.abort > nowTime && is_1or2 == true )
							nowTime1 = temp2.abort ;
						else if(temp2.abort > nowTime && is_1or2 == false )
							nowTime2 = temp2.abort ;
					} // else if
						
					else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
						temp1.OID = queue_info.OID ;
						temp1.Departure = nowTime + queue_info.Duration ;
						temp1.Delay = nowTime - queue_info.Arrival ;
						if(is_1or2) temp1.CID = 1;
						else temp1.CID = 2;
						Done_List.push_back(temp1) ;
						if( is_1or2 == true )
							nowTime1 = temp1.Departure ; 
						else
							nowTime2 = temp1.Departure ;
		
					} // else if 
							
				} // for
					
				for( int i = 0 ;  (!Queue2.isEmpty() && list[0].Arrival >= nowTime2) ; i++ ) {
					Queue2.dequeue(queue_info) ;
					nowTime = nowTime2 ;
					is_1or2 = false ;
					if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
						temp2.OID = queue_info.OID ;
						temp2.abort = nowTime ;
						temp2.Delay = nowTime - queue_info.Arrival ;
						if(is_1or2) temp2.CID = 1;
						else temp2.CID = 2;
						Abort_List.push_back(temp2) ;
					} //  if
					
					else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
						temp2.OID = queue_info.OID ;
						temp2.abort = queue_info.TimeOut ;
						temp2.Delay = temp2.abort - queue_info.Arrival ;
						if(is_1or2) temp2.CID = 1;
						else temp2.CID = 2;
						Abort_List.push_back(temp2) ;
						if(temp2.abort > nowTime && is_1or2 == true )
							nowTime1 = temp2.abort ;
						else if(temp2.abort > nowTime && is_1or2 == false )
							nowTime2 = temp2.abort ;
					} // else if
						
					else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
						temp1.OID = queue_info.OID ;
						temp1.Departure = nowTime + queue_info.Duration ;
						temp1.Delay = nowTime - queue_info.Arrival ;
						if(is_1or2) temp1.CID = 1;
						else temp1.CID = 2;
						Done_List.push_back(temp1) ;
						if( is_1or2 == true )
							nowTime1 = temp1.Departure ; 
						else
							nowTime2 = temp1.Departure ;
					} // else if 
														
				} // for
						
				if ( Queue1.size <= Queue2.size && list[0].Arrival >= nowTime1 ) {
					if ( Queue1.isEmpty() ) {
						temp1.OID = list[0].OID ;
						temp1.Departure = list[0].Arrival + list[0].Duration ;
						temp1.Delay = 0 ;
						temp1.CID = 1;
						Done_List.push_back(temp1) ;
						nowTime1 = temp1.Departure ; 
					} // if()

				} // if()

				else if( Queue1.size <= Queue2.size ) 
					Queue1.enqueue( list[0] ) ;

				else if ( list[0].Arrival >= nowTime2 ){
					if ( Queue2.isEmpty() ) {
						temp1.OID = list[0].OID ;
						temp1.Departure = list[0].Arrival + list[0].Duration ;
						temp1.Delay = 0 ;
						temp1.CID = 2;		
						Done_List.push_back(temp1) ;	
						nowTime2 = temp1.Departure ; 

					} // if()
				} // else if
				 
				else 
					Queue2.enqueue( list[0] ) ;
					
			} // else	( QUEUE IS NOT EMPTY )
			
		} // if 

		else if ( Queue1.size == 3 && Queue2.size == 3 ) {
			temp2.OID = list[0].OID ;
			temp2.abort = list[0].Arrival ;
			temp2.Delay = 0 ;
			temp2.CID = 0 ; 
			Abort_List.push_back(temp2) ; 
		} // else if

		else  {	 
			if ( Queue1.size <= Queue2.size) Queue1.enqueue(list[0]) ;
			else if ( Queue1.size > Queue2.size ) Queue2.enqueue( list[0]) ;	
		} // else 
	
		list.erase( list.begin() ) ;
			
	} // while
	

	while( (!Queue1.isEmpty() || !Queue2.isEmpty() )  ) {
		
		if( !Queue1.isEmpty() ) {
			Queue1.dequeue(queue_info) ;
			nowTime = nowTime1;
			is_1or2 = true;
		} // if
		
		else if( !Queue2.isEmpty() ){
			Queue2.dequeue(queue_info) ;
			nowTime = nowTime2;
			is_1or2 = false;
		} //else if
		
		if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
			temp2.OID = queue_info.OID ;
			temp2.abort = nowTime ;
			temp2.Delay = nowTime - queue_info.Arrival ;
			if(is_1or2) temp2.CID = 1;
			else temp2.CID = 2;
			Abort_List.push_back(temp2) ;
		} //  if
					
		else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
			temp2.OID = queue_info.OID ;
			temp2.abort = queue_info.TimeOut ;
			temp2.Delay = temp2.abort - queue_info.Arrival ;
			if(is_1or2) temp2.CID = 1;
			else temp2.CID = 2;
			Abort_List.push_back(temp2) ;
			if(temp2.abort > nowTime && is_1or2 == true )
				nowTime1 = temp2.abort ;
			else if(temp2.abort > nowTime && is_1or2 == false )
				nowTime2 = temp2.abort ;
		} // else if
				
		else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
			temp1.OID = queue_info.OID ;
			temp1.Departure = nowTime + queue_info.Duration ;
			temp1.Delay = nowTime - queue_info.Arrival ;
			if(is_1or2) temp1.CID = 1;
			else temp1.CID = 2;
			Done_List.push_back(temp1) ;
			if( is_1or2 == true )
				nowTime1 = temp1.Departure ;
			else
				nowTime2 = temp1.Departure ;

		} // else if
		
	} // while
		
} // work2


void work( vector<job> list, vector<Done> &Done_List, vector<Abort> &Abort_List, Queue Queue  ) { // do mission 2
	int nowTime = 0 ;
	job queue_info ;
	Done temp1 ;
	Abort temp2 ;

	while ( !list.empty() ) { 
	
		if ( list[0].Arrival >= nowTime ) {

			if( Queue.isEmpty() )	{
				if ( list[0].Arrival >= nowTime ) {
					temp1.OID = list[0].OID ;
					temp1.Departure = list[0].Arrival + list[0].Duration ;
					temp1.Delay = 0 ;
					nowTime = temp1.Departure ;
					Done_List.push_back(temp1) ;
				} // if
			} // if
			
			else { // QUEUE IS NOT EMPTY
				for ( int i = 0 ; !Queue.isEmpty() && list[0].Arrival >= nowTime ; i++ ) {
					Queue.dequeue(queue_info) ;
					if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
						temp2.OID = queue_info.OID ;
						temp2.abort = nowTime ;
						temp2.Delay = nowTime - queue_info.Arrival ;
						Abort_List.push_back(temp2) ;
					} //  if
					
					else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
						temp2.OID = queue_info.OID ;
						temp2.abort = queue_info.TimeOut ;
						temp2.Delay = temp2.abort - queue_info.Arrival ;
						Abort_List.push_back(temp2) ;
						if(temp2.abort > nowTime )
							nowTime = temp2.abort ;
					} // else if
						
					else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
						temp1.OID = queue_info.OID ;
						temp1.Departure = nowTime + queue_info.Duration ;
						temp1.Delay = nowTime - queue_info.Arrival ;
						Done_List.push_back(temp1) ;
						nowTime = temp1.Departure ; 
					} // else if 
							
				} // for
					
				if ( list[0].Arrival >= nowTime ) {
					if ( Queue.isEmpty() ) {
						temp1.OID = list[0].OID ;
						temp1.Departure = list[0].Arrival + list[0].Duration ;
						temp1.Delay = 0 ;
						Done_List.push_back(temp1) ;
						nowTime = temp1.Departure ; 
					} // if()
				} // if()
				 
				else // list[0].Arrival < nowTime
					Queue.enqueue( list[0] ) ;
					
			} // else	( QUEUE IS NOT EMPTY )
			
		} // if ( list[0].Arrival >= nowTime ) 

		else if ( Queue.size == 3 ) {
			temp2.OID = list[0].OID ;
			temp2.abort = list[0].Arrival ;
			temp2.Delay = 0 ;
			Abort_List.push_back(temp2) ; 
		} // else if

		else // list[0].Arrival >= nowTime
			if ( Queue.size < 3 ) Queue.enqueue(list[0]) ;
	
		list.erase( list.begin() ) ;
			
	} // while
	

	while( !Queue.isEmpty() ) {
		Queue.dequeue(queue_info) ;
		
		if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
			temp2.OID = queue_info.OID ;
			temp2.abort = nowTime ;
			temp2.Delay = nowTime - queue_info.Arrival ;
			Abort_List.push_back(temp2) ;
		} //  if
					
		else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
			temp2.OID = queue_info.OID ;
			temp2.abort = queue_info.TimeOut ;
			temp2.Delay = temp2.abort - queue_info.Arrival ;
			Abort_List.push_back(temp2) ;
			if(temp2.abort > nowTime )
				nowTime = temp2.abort ;
		} // else if
				
		else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
			temp1.OID = queue_info.OID ;
			temp1.Departure = nowTime + queue_info.Duration ;
			temp1.Delay = nowTime - queue_info.Arrival ;
			Done_List.push_back(temp1) ;
			nowTime = temp1.Departure ;
		} // else if
		
	} // while
		
} // work

/*
void work( vector<job> list, vector<Done> &Done_List, vector<Abort> &Abort_List, Queue Queue  ) { // do mission 2
	int nowTime = 0 ;
	job queue_info ;
	Done temp1 ;
	Abort temp2 ;
	
	while ( !list.empty() ) {
			
		
		if ( nowTime == 0 ) { // first list
			temp1.OID = list[0].OID ;
			temp1.Departure = list[0].Arrival + list[0].Duration ;
			temp1.Delay = 0 ;
			Done_List.push_back(temp1) ;
			list.erase( list.begin() ) ;  // erase the first data of list
			nowTime = temp1.Departure ;
		} // if
		  
		else if ( Queue.size < 3  ) {
			if ( list[0].Arrival <= nowTime ) {
				Queue.enqueue(list[0]) ; // put list[0] into queue
				list.erase( list.begin() ) ;
			} // if	
			
			else if ( list[0].Arrival > nowTime ) {
				if(Queue.isEmpty())	{
					temp1.OID = list[0].OID ;
					temp1.Departure = list[0].Arrival + list[0].Duration ;
					temp1.Delay = 0 ;
					Done_List.push_back(temp1) ;
					list.erase( list.begin() ) ;
					nowTime = temp1.Departure ;
				} // if
				  
				else { // QUEUE IS NOT EMPTY
					Queue.dequeue(queue_info) ;	
					if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時
						temp2.OID = queue_info.OID ;
						temp2.abort = nowTime ;
						temp2.Delay = nowTime - queue_info.Arrival ;
						Abort_List.push_back(temp2) ;
					} //  if
					
					else if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{  //  // 4.3 CPU執行過程中發生逾時 
						temp2.OID = queue_info.OID ;
						temp2.abort = queue_info.TimeOut ;
						temp2.Delay = temp2.abort - queue_info.Arrival ;
						Abort_List.push_back(temp2) ;
						if(temp2.abort > nowTime)
							nowTime = temp2.abort ;
					} // else if
				
					else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
						temp1.OID = queue_info.OID ;
						temp1.Departure = nowTime + queue_info.Duration ;
						temp1.Delay = nowTime - queue_info.Arrival ;
						Done_List.push_back(temp1) ;
						nowTime = temp1.Departure ;
					} // else if
					
				} // else	( QUEUE IS NOT EMPTY )
			}	// else if
			
		} // else if (  Queue.size < 3 )
		
		else if ( Queue.size == 3 ) {
			if ( list[0].Arrival < nowTime ) { // 4.1進入佇列前就發現佇列滿 
				temp2.OID = list[0].OID ;
				temp2.abort = list[0].Arrival ;
				temp2.Delay = 0 ;
				Abort_List.push_back(temp2) ;
				list.erase( list.begin() ) ;
			} // if
			
			else if( list[0].Arrival == nowTime ) {
				Queue.dequeue(queue_info) ;
				if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{ // 4.3 CPU執行過程中發生逾時  
					temp2.OID = queue_info.OID ;
					temp2.abort = nowTime ;
					temp2.Delay = temp2.abort - queue_info.Arrival ;
					Abort_List.push_back(temp2) ;
					if(temp2.abort > nowTime)
						nowTime = temp2.abort ;
					Queue.enqueue(list[0]) ;
					list.erase( list.begin() ) ;
				} // if
				
				else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
					temp1.OID = queue_info.OID ;
					temp1.Departure = nowTime + queue_info.Duration ;
					temp1.Delay = nowTime - queue_info.Arrival ;
					Done_List.push_back(temp1) ;
					nowTime = temp1.Departure ;
					Queue.enqueue(list[0]) ;
					list.erase( list.begin() ) ;
				} // else if
			} // else if
			
			else if ( list[0].Arrival > nowTime )  {  
				Queue.dequeue(queue_info) ;	
				if ( queue_info.TimeOut < ( nowTime + queue_info.Duration ) )	{ // 4.3 CPU執行過程中發生逾時 
					temp2.OID = queue_info.OID ;
					temp2.abort = queue_info.TimeOut ;
					temp2.Delay = temp2.abort - queue_info.Arrival ;
					Abort_List.push_back(temp2) ;
					if(temp2.abort > nowTime)
						nowTime = temp2.abort ;
				} // if
				
				else if ( queue_info.TimeOut >= ( nowTime + queue_info.Duration ) ) {
					temp1.OID = queue_info.OID ;
					temp1.Departure = nowTime + queue_info.Duration ;
					temp1.Delay = nowTime - queue_info.Arrival ;
					Done_List.push_back(temp1) ;
					nowTime = temp1.Departure ;
				} // else if
			} // else if
			
		} // else if
			
	} // while
	
	while(!Queue.isEmpty()) {
		Queue.dequeue(queue_info) ;	
		if ( queue_info.TimeOut <= ( nowTime ) )	{  //  4.2從佇列取出時發現逾時 
			temp2.OID = queue_info.OID ;
			temp2.abort = nowTime ;
			temp2.Delay = nowTime - queue_info.Arrival ;
			Abort_List.push_back(temp2) ;
		} // if
				
		else if ( queue_info.TimeOut > ( nowTime + queue_info.Duration ) ) {
			temp1.OID = queue_info.OID ;
			temp1.Departure = nowTime + queue_info.Duration ;
			temp1.Delay = nowTime - queue_info.Arrival ;
			Done_List.push_back(temp1) ;
			nowTime = temp1.Departure ;
		} // else if
					
		else if(queue_info.TimeOut < ( nowTime + queue_info.Duration ))  {  // 4.3 CPU執行過程中發生逾時 
			temp2.OID = queue_info.OID ;
			temp2.abort = queue_info.TimeOut;	
			temp2.Delay = temp2.abort - queue_info.Arrival ;	
			if(temp2.abort > nowTime)
				nowTime = temp2.abort ;
			Abort_List.push_back(temp2) ;
		} // else if
	} // while
		
} // work
*/

void readfile( vector<job> &list ) { // read file content
	job temp ;
  string OiD, arrival, duration, timeout, final_file_name ;
  ifstream file ;
  
  if( alreadysorted == true ) {
  	final_file_name = "sorted" + file_name + ".txt";
  	file.open( final_file_name, ios::in ) ; // open file
  }//if
  
  else {
 		file_name = GetNum() ;  // Get File Name
  	final_file_name = "sorted" + file_name + ".txt" ;
  	file.open( final_file_name, ios::in ) ; // open file
  } // else

  if ( !file.is_open() ) {
		open = false ;
    cout << endl << final_file_name << " does not exist!" << endl ;
	} // if
	
  else{
  	open = true ;
    file >> OiD >> arrival >> duration >> timeout ;   
    while( !file.eof() ) {
      file >> temp.OID  ;
      file >> temp.Arrival ;
      file >> temp.Duration ;
      file >> temp.TimeOut ;
      if ( !file.fail()) 
        list.push_back(temp) ;	
    } // while
  } // else
  file.close() ;
  alreadysorted = false; 

} // readfile
 
void read( vector<job> &list ) { // read data
  job temp ;
  string OiD, arrival, duration, timeout, final_file_name ;
  alreadysorted = true;
  ifstream file ;
  file_name = GetNum() ;  // Get File Name
  final_file_name = "input" + file_name + ".txt" ;
  file.open( final_file_name, ios::in ) ; // open file
  

  if ( !file.is_open() ) {
		open = false ;
    cout << endl << final_file_name << " does not exist!" << endl ;
	} // if
	
  else{
  	double start = clock() ; // start to calculate the time it takes to read files
  	open = true ;
    file >> OiD >> arrival >> duration >> timeout ;   
    while( !file.eof() ) {
      file >> temp.OID  ;
      file >> temp.Arrival ;
      file >> temp.Duration ;
      file >> temp.TimeOut ;
      if ( !file.fail()) 
        list.push_back(temp) ;	
    } // while
    readFinish = clock() ; // end to calculate the time it takes to read files
    readFinish -= start ;
  } // else
  file.close() ;
} // read

void printVector( vector<job> list) { // print data
	cout << endl << '\t' << "OID" << '\t' << "Arrival" << '\t' << "Duration" << '\t' << "TimeOut" << endl ;
  for( int i = 0 ; i < list.size(); ++i )
    cout << "(" << i+1 << ")" << '\t' <<list[i].OID << '\t' << list[i].Arrival << '\t' << list[i].Duration << '\t' << list[i].TimeOut << endl ;
  return ;
} // printVector

void shellshort( vector<job> &list ) { // sort data
  int len = list.size();
  double start = clock() ; // start to calculate the time it takes to sort data
  for( int k=len/2 ; k>0 ; k/=2 ) {
    for( int i=k ; i<len ; i++ ) {
      for( int j=i-k ; j>=0 ; j-=k ) {
        if(list[j].Arrival == list[j+k].Arrival) {
        	if(list[j].OID > list[j+k].OID) 
        		swap(list[j+k],list[j]);
				} // if
        else if(list[j].Arrival > list[j+k].Arrival) 
					swap(list[j+k],list[j]);
        else break;
    	} // for
		} // for	
	} // for
	sortFinish = clock() ; // end to calculate the time it takes to sort data
	sortFinish -= start ;
} // shellshort

void file_out( vector<job> &list ) { // write data 
	fstream file ;
	string final_file_name = "sorted" + file_name + ".txt" ;
	file.open(final_file_name,ios::out ) ;
	
	if(!file) cout << "can't open" ;
	
	else {
		double start = clock() ; // start to calculate the time it takes to write data
		file << "OID" << '\t' << "Arrival" << '\t' << "Duration" << '\t' << "TimeOut" << endl ; // 將資料輸出至檔案 
  	for( int i = 0 ; i < list.size(); ++i )
    	file << list[i].OID << '\t' << list[i].Arrival << '\t' << list[i].Duration << '\t' << list[i].TimeOut << endl ;
    writeFinish = clock() ; // end to calculate the time it takes to write data
    writeFinish -= start ;
	} // else
	
  file.close();
} // file_out

void file_out2( vector<Done> Done_List ,vector<Abort> Abort_List ) { // write data
	fstream file ;
	string final_file_name = "output" + file_name + ".txt" ;
	file.open(final_file_name,ios::out ) ;
	double count=0,count_Success=0,sum_of_Delay = 0,Delay=0,Success=0;
	
	if(!file) cout << "can't open" ;
	
	else {
		file << "\t" << "[Abort Jobs]" << endl ;
		file << '\t' << "OID" << '\t' << "Abort" << '\t' << "Delay" << endl ; // 將資料輸出至檔案 
  	for( int i = 0 ; i < Abort_List.size(); ++i ) {
    	file << "[" << i+1 << "]\t" << Abort_List[i].OID << '\t' << Abort_List[i].abort << '\t' << Abort_List[i].Delay << endl ;
    	count+=1; 
    	sum_of_Delay+=Abort_List[i].Delay;
    }	// for
    	
    file << "\t" << "[Done Jobs]" << endl ;
		file << '\t' << "OID" << '\t' << "Departure" << '\t' << "Delay" << endl ; // 將資料輸出至檔案 
  	for( int i = 0 ; i < Done_List.size(); ++i ) {
    	file << "[" << i+1 << "]\t" << Done_List[i].OID << '\t' << Done_List[i].Departure << '\t' << Done_List[i].Delay << endl ;
    	count+=1; 
    	sum_of_Delay+=Done_List[i].Delay;
    	count_Success+=1;
		} // for	  
	
		Delay = sum_of_Delay/count;
		Success = (count_Success/count)*100;

		file << "[Average Delay] " << setprecision(2) << fixed << Delay	 << " ms"<< endl ;
  	file << "[Success Rate] " << setprecision(2) << fixed << Success << " %"<< endl ;
	} // else
	
	
  file.close();
} // file_out

void file_out3( vector<Done> Done_List ,vector<Abort> Abort_List ) { // write data
	fstream file ;
	string final_file_name = "double" + file_name + ".txt" ;
	file.open(final_file_name,ios::out ) ;
	double count=0,count_Success=0,sum_of_Delay = 0,Delay=0,Success=0;
	
	if(!file) cout << "can't open" ;
	
	else {
		file << "\t" << "[Abort Jobs]" << endl ;
		file << '\t' << "OID" << '\t' << "CID" << '\t' << "Abort" << '\t' << "Delay" << endl ; // 將資料輸出至檔案 
  	for( int i = 0 ; i < Abort_List.size(); ++i ) {
    	file << "[" << i+1 << "]\t" << Abort_List[i].OID << '\t' << Abort_List[i].CID << '\t' << Abort_List[i].abort << '\t' << Abort_List[i].Delay << endl ;
    	count+=1; 
    	sum_of_Delay+=Abort_List[i].Delay;
    }	// for
    	
    file << "\t" << "[Done Jobs]" << endl ;
		file << '\t' << "OID" << '\t' << "CID" << '\t' << "Departure" << '\t' << "Delay" << endl ; // 將資料輸出至檔案 
  	for( int i = 0 ; i < Done_List.size(); ++i ) {
    	file << "[" << i+1 << "]\t" << Done_List[i].OID << '\t' << Done_List[i].CID << '\t' << Done_List[i].Departure << '\t' << Done_List[i].Delay << endl ;
    	count+=1; 
    	sum_of_Delay+=Done_List[i].Delay;
    	count_Success+=1;
		} // for	  
	
		Delay = sum_of_Delay/count;
		Success = (count_Success/count)*100;

		file << "[Average Delay] " << setprecision(2) << fixed << Delay	 << " ms"<< endl ;
  	file << "[Success Rate] " << setprecision(2) << fixed << Success << " %"<< endl ;
	} // else
	
	
  file.close();
} // file_out

void printTime( double readFinish, double sortFinish, double writeFinish )  {
	cout << endl ;
	cout << "Reading data: " << readFinish << " ms" << endl ;
	cout << "Sorting data: " << sortFinish << " ms" << endl ;
	cout << "Writing data: " << writeFinish << " ms" << endl ;
} // printTime

bool is_Num( string str ) { // check the string input is an integer or not
 
  for( int i = 0 ; i < str.size() ; i++ ) { // input.size can return the length of the string input
    if( str[i] >= '0' && str[i] <= '9' ) // Use ASCII to know whether the input[i] is an integer
      continue ;
    else
      return false ; // String input have an element that is not integer
  } // for
  return true ; // In string input all of the elements are an integer
  
} // is_Num

string GetNum( ) { // Get a number from user and make sure the number no more than
 string input ;
 while(true) {
   cout << "Input a file number (e.g. 401, 402, .....):" ;
   cin >> input ;
   if ( !is_Num( input ) ) // Input is not integer
     cout << "Not an integer Please try again! " << endl ;
   else // Input is an integer
     return input ;
  } // while
} // GetNum
