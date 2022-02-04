// ¶§±m¬X 10927202   »¯¬Ä 10927212 

#include<iostream>  // cin cout
#include<fstream>   // ifstream
#include<string>
#include<string.h>

using namespace std ;

class matrix {

 public:
  char **map = NULL ; // record maze map
  int correct_road[100][100] = { {0}, {0} } ; // record correct road to find G
  int row = 0, col = 0 ; // row ¾î col ª½ 
	int beststep ; // 
	char **shortest_step = NULL ; // record the route if find out G
}; // matrix


int fact_G = 0 ;  // Actually find how many G
bool find_G = false ;
int step = 0 ;

string GetNum() ;
bool is_Num( string str ) ;
void cmd_read ( string file_name, int cmd ) ;
void record_walking ( matrix & maze, int i, int j, int num_G ) ; // record the route in the maze
void path_to_success ( matrix & maze, int i, int j, int num_G ) ; // record success route in the maze
void move( matrix & maze, int i, int j ) ; // record the route in the maze
void find_shortest_path( matrix & maze, int i, int j ) ; // find shortest Path
void delete_maze( matrix & maze ) ; // delete 2D array
void record_walking2 ( matrix & maze, int i, int j, int num_G ) ;


int main() {
 while( true ) {
 	matrix maze ;
    cout << endl ;
    cout << "** Path Finding     **" << endl ;
    cout << "*  0. Quit           *" << endl ;
    cout << "*  1. One  Goal      *" << endl ;
    cout << "*  2. More Goals     *" << endl ;
    cout << "*  3. Shortest Path  *" << endl ;
    cout << "**********************" << endl ;
    cout << "Input a command(0,1,2,3):"  ;
    
    string str ;
    cin >> str ;
    
    while( !is_Num(str) ) { // str is not an integer keep input until the command is integer
      cout << "Input a command(0,1,2,3):"  ;
      cin >> str ;
    } // while
    
    int cmd = stoi(str) ; // let str convert to integer
    
    if ( cmd == 0 )
      break ;
    
    else if ( cmd == 1 || cmd == 2 || cmd == 3) {
      string file_name = GetNum() ;  // Get File Name
      file_name = "input" + file_name + ".txt" ;
      cmd_read ( file_name, cmd );
    } // else if
    
    
    else // cmd is not 0, 1 or 2 or 3
      cout << "Wrong Command! Try Again ! " << endl ;
      
    fact_G = 0 ;
    find_G = false ;
    
    
  } // while
  
} // main

void cmd_read ( string file_name, int cmd ) {
  ifstream file;

  matrix maze ;
  delete_maze(maze) ;
  file.open( file_name, ios::in ) ; // open file

  if (!file.is_open())
    cout << file_name << " does not exist!" << endl ;

  else {
    int num_G ;   // Number of G (goals)
    fact_G = 0 ;  // Actually find how many G
    string str ;
    
    if( cmd == 1 || cmd == 3)
      num_G = 1 ;
      
    else if ( cmd == 2 ) { // cmd == 2
      cout << "Number of G (goals): " ;
      cin >> str ;
      
      while( !is_Num(str) ) { // str is not an integer keep input until the command is integer
        cout << "Input Number: "  ;
        cin >> str ;
        } // while
        
      num_G = stoi(str) ; // let str convert to integer and assign to num_G
    }  // else if
    
    
    file >> maze.col >> maze.row ;  // read file content
    
    maze.map = (char**)malloc(maze.row*sizeof(char*)) ;     //Create a 2D dynamic array
    for(int i = 0 ; i < maze.row ; i++ ) 
    	maze.map[i] = (char*)malloc(maze.col*sizeof(char)) ;
    	
    
    for(int row=0;row<maze.row;++row)      // Read the data into the array
      for(int col=0;col<maze.col;++col)
        file >> maze.map[row][col] ;
		
    int i = 0, j = 0 ;
    if ( cmd == 3 ) {
    	step = 0 ;
    	maze.beststep = maze.col * maze.row ;
    //	move( maze,i,j) ;
    	record_walking2 ( maze, i, j, num_G ) ;
     
    	int row, col ;
    	cout << endl ;
    	for ( row = 0; row < maze.row ; row++ ) { // print the map
        for (  col = 0; col < maze.col ; col++ ) 
          cout << maze.map[row][col] ; 
        cout << endl ;
      } // for
      
      cout << endl ;
      if ( find_G ) {
      	step = 1 ;
      	maze.beststep = maze.col * maze.row ;
      	find_shortest_path( maze, i, j ) ;
      	
      	for ( row = 0; row < maze.row ; row++ ) {
        	for (  col = 0; col < maze.col ; col++ ) {
          	if ( maze.shortest_step[row][col] == 'V')
            	maze.shortest_step[row][col] = 'E' ;
          	cout << maze.shortest_step[row][col] ;
        	} // for
         
        	cout << endl ;
      	} // for
      	
      	cout << endl ;
      	
      	cout << "Shortest path length = " << maze.beststep << endl ;
			} // if
			
			else
				cout << "### There is no path to find a goal! ###" << endl ;
      
		} // if
    
    else { // cmd == 1 || cmd == 2
    	record_walking ( maze, i, j, num_G ) ;
    
    	if ( fact_G != num_G && !find_G ) { // can not find G and can not find the number of num_G
      	cout << endl ;
      	for ( int row = 0; row < maze.row ; row++ ) {
        	for ( int col = 0; col < maze.col ; col++ ) {
          	if ( maze.map[row][col] == 'X' )
            	maze.map[row][col] = 'G' ;
          	cout << maze.map[row][col] ;
        	} // for
          
        	cout << endl ;
      	} // for
      	cout << endl ;
    	} // if
  
    	if( find_G ) { // find the number of num_G
      	find_G = false ;
      	fact_G = 0 ;
      	path_to_success( maze, i, j, num_G ) ;
    	} // if
		} // else
	} // else
  
  
  
  file.close() ; // close file
} // cmdread

void delete_maze( matrix & maze ) {
	
	if ( maze.map != NULL ) {
		for(int i=0;i<maze.row;++i)
    	delete maze.map[i] ;
    delete maze.map ;
    maze.map = NULL ;
	} // if
	
  if ( maze.shortest_step != NULL ) {
  	for ( int i = 0 ; i< maze.row ; ++i)
  		delete maze.shortest_step[i] ;
  	delete maze.shortest_step ;
  	maze.map = NULL ;
	} // if
  
} // delete

void record_walking ( matrix & maze, int i, int j, int num_G ) {
  
  if ( maze.map[i][j] == 'G') {
    fact_G ++ ;
    maze.map[i][j] = 'X' ; // let the map[i][j] convert to X
    
    if ( fact_G == num_G ) {
      find_G = true;
      cout << endl ;
      for (int row = 0; row < maze.row ; row++ ) { // print the map
        for ( int col = 0; col < maze.col ; col++ ) {
          if ( maze.map[row][col] == 'X' )
            maze.map[row][col] = 'G' ;
          cout << maze.map[row][col] ;
        } // for
          
        cout << endl ;
      } // for
      cout << endl ;
    } // if
  
  } // if
    
    if ( maze.map[i][j] == 'E') maze.map[i][j] = 'V'; // record route
    
    if ( j+1 < maze.col && ( maze.map[i][j + 1] == 'E' || maze.map[i][j + 1] == 'G' ) && find_G == false )  record_walking (maze, i, j + 1, num_G ) ; // right is E or G
    if ( i+1 < maze.row && ( maze.map[i + 1][j] == 'E' || maze.map[i + 1][j] == 'G' ) && find_G == false )  record_walking (maze, i + 1, j, num_G ) ; // down is E or G
    if ( j-1 >= 0 && ( maze.map[i][j - 1] == 'E' || maze.map[i][j - 1] == 'G' ) && find_G == false )  record_walking (maze, i, j - 1, num_G ) ; // left is E or G
    if ( i-1 >= 0 && ( maze.map[i - 1][j] == 'E' || maze.map[i - 1][j] == 'G' ) && find_G == false )  record_walking (maze, i - 1, j, num_G ) ; // up is E or G
    
    
} // record_walking


void path_to_success( matrix & maze, int i, int j, int num_G ) {
  
  if ( maze.map[i][j] == 'G' ) {
    fact_G++ ;
    maze.map[i][j] = 'X' ;
    for ( int row = 0 ; row < maze.row ; row++ ) {    // Store the correct route in this array
      for ( int col = 0 ; col < maze.col ; col++ ) {
        if ( maze.map[row][col] == 'R')
          maze.correct_road[row][col] = 1 ;
        if ( maze.map[row][col] == 'X')
            maze.correct_road[row][col] = 2 ;
      } // for
    } //for

    if ( fact_G == num_G ) {    // When the correct number of G is found, print the successful path 
      find_G = true;
      for (int row = 0; row < maze.row ; row++ ) {
        for ( int col = 0; col < maze.col ; col++ ) {
          if ( maze.map[row][col] == 'V')
            maze.map[row][col] = 'E' ;
          if ( maze.map[row][col] == 'X')
            maze.map[row][col] = 'G' ;
          if ( maze.correct_road[row][col] == 1 )
             maze.map[row][col] = 'R' ;
             
          cout << maze.map[row][col] ;
        } // for
         
        cout << endl ;
      } // for
      cout << endl ;
     
    } // if
  
  } // if
  

  if ( maze.map[i][j] == 'V' ) maze.map[i][j] = 'R' ;
  if ( j+1 < maze.col &&  ( maze.map[i][j + 1] == 'V' || maze.map[i][j + 1] == 'G' ) && find_G == false )  path_to_success (maze, i, j + 1, num_G ) ; // in range and right is V or is G
  if ( i+1 < maze.row && ( maze.map[i + 1][j] == 'V' || maze.map[i + 1][j] == 'G' ) && find_G == false )  path_to_success (maze, i + 1, j, num_G ) ;// in range and down is V or is G
  if ( j-1 >= 0 && ( maze.map[i][j - 1] == 'V' || maze.map[i][j - 1] == 'G' ) && find_G == false )  path_to_success (maze, i, j - 1, num_G ) ;// in range and left is V or is G
  if ( i-1 >= 0 && ( maze.map[i - 1][j] == 'V' || maze.map[i - 1][j] == 'G' ) && find_G == false )  path_to_success (maze, i - 1, j, num_G ) ;// in range and up is V or is G
   
  if ( ( maze.map[i][j] == 'R' ) && find_G == false ) maze.map[i][j] = 'E' ;
  if ( ( maze.map[i][j] == 'X' ) && find_G == false ) maze.map[i][j] = 'G' ;
  
} // path_to_success

void record_walking2 ( matrix & maze, int i, int j, int num_G ) {
  
  if ( maze.map[i][j] == 'G' && fact_G != num_G ) {
    fact_G ++ ;
    find_G = true ;
    if( step < maze.beststep ) 
			maze.beststep = step ;
  } // if
    
    if ( maze.map[i][j] == 'E') maze.map[i][j] = 'V'; // record route
    step++ ;
    if ( j+1 < maze.col && ( maze.map[i][j + 1] == 'E' || maze.map[i][j + 1] == 'G' ) )  record_walking2 (maze, i, j + 1, num_G ) ; // right is E or G
    if ( i+1 < maze.row && ( maze.map[i + 1][j] == 'E' || maze.map[i + 1][j] == 'G' )  )  record_walking2 (maze, i + 1, j, num_G ) ; // down is E or G
    if ( j-1 >= 0 && ( maze.map[i][j - 1] == 'E' || maze.map[i][j - 1] == 'G' )  )  record_walking2 (maze, i, j - 1, num_G ) ; // left is E or G
    if ( i-1 >= 0 && ( maze.map[i - 1][j] == 'E' || maze.map[i - 1][j] == 'G' )  )  record_walking2 (maze, i - 1, j, num_G ) ; // up is E or G
    step-- ;
    
} // record_walking2


void move( matrix & maze, int i, int j ) {
	if(maze.map[i][j] == 'G' ) {
		find_G = true ;
		if( step < maze.beststep ) 
			maze.beststep = step ;
			
	} // if
	
	if ( i == maze.row || i < 0 || j == maze.col || j < 0 || maze.map[i][j] != 'E' || step == maze.beststep )
		return ;
		
	maze.map[i][j] = 'V' ;
	step ++ ;
	if ( j+1 < maze.row ) move( maze, i, j+1 ) ;
	if ( i+1 < maze.col ) move( maze, i+1, j) ;
	if ( j - 1 >= 0 ) move( maze, i, j-1 ) ;
	if ( i - 1 >= 0 ) move( maze, i-1, j) ;
	step -- ;
} // move

void find_shortest_path( matrix & maze, int i, int j ) {
	
	if ( maze.map[i][j] == 'G') {

		if ( step < maze.beststep ) {
			maze.beststep = step ;
			maze.shortest_step = (char**)malloc(maze.row*sizeof(char*)) ;     //Create a 2D dynamic array
		
  	  for(int k = 0 ; k < maze.row ; k++ ) {
    		maze.shortest_step[k] = (char*)malloc(maze.col*sizeof(char)) ; 
    		strcpy( maze.shortest_step[k], maze.map[k] ) ;
			} // for
		
		} //if
	
	} // if

	if ( i == maze.row || i < 0 || j == maze.col || j < 0 || maze.map[i][j] != 'V' || step == maze.beststep )
		return ;
		
	maze.map[i][j] = 'R' ;
	step++ ;
	if ( j+1 < maze.row  ) find_shortest_path( maze, i, j+1 ) ; 
	if ( i+1 < maze.col   ) find_shortest_path( maze, i+1, j ) ; 
	if ( j - 1 >= 0  ) find_shortest_path( maze, i, j-1  ) ; 
	if ( i - 1 >= 0   ) find_shortest_path( maze, i-1, j ) ; 
	maze.map[i][j] = 'V';
	step-- ;

} // find_shortest_path

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
    
   cout << "Input a file number (e.g. 201, 202, .....):" ;
   cin >> input ;
   if ( !is_Num( input ) ) // Input is not integer
     cout << "Not an integer Please try again! " << endl ;
   
   else// Input is an integer
     return input ;
    
  } // while
} // GetNum



