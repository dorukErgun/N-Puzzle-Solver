#include <iostream>
#include <ctime>//Used for random number generation only.
#include <cstdlib>//Used for random number generation only.
#include <fstream>
#include <vector>

using namespace std;

const int MAX_BOARD_SIZE = 9;

class NPuzzle{
private:

    //Class to represent board
    class Board{
    public:

        //Getters
        inline int getRow() const; 
        inline int getColumn() const;
        inline bool getGameConfiguration() const;         
        inline int getSolvedBoardElement(int x, int y) const;
        inline int getBoardElement(int x, int y) const;            

        //Setters
        inline void setRow(int x);
        inline void setColumn(int x);        
        inline void setGameConfiguration(bool config);  

        //Other member functions
        void print();
        bool LMove();
        bool RMove();
        bool UMove();
        bool DMove();
        int string_parser(char x);
        int readFromFile(string text_name);
        void writeToFile(string text_name);
        void reset();
        void setSize(int r, int c);
        bool move(char m);
        bool isSolved();
        void setSpace_x(int a);
        void setSpace_y(int a);
        void setLast_move(char p);
        char getLast_move();

    private:
        
        int space_x=0;
        int space_y=0;
        int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; //Keeps the game data for last configuration.
        int temp_board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; //Keeps the solved game data for last configuration.
        bool game_configuration = false; //Set our game config with this variable.   
        int row;
        int column;
        char last_move = ' ';   

    };

    vector<Board> Boards;
    vector<char> last_plays;
    Board gameBoard; //Board object to use Board class functions.
    char lastPlays[3] = {' ', ' ', ' '}; //Keeps the last plays for intelligent move. 

public:

    //Getters
    inline static  int getMoveCounter();
    inline vector<Board> getBoard(); 

    //Setters
    inline static  void setMoveCounter(int m);    
    inline void setGameConfiguration(bool config);
    inline void pushToBoardsVector(Board& B);

    //Other member functions   
    void print();
    void printReport();
    int readFromFile(string text_name);
    void writeToFile(string text_name);
    void shuffle(int n); 
    void reset();
    void setSize(int r, int c);
    void moveRandom();
    bool moveIntelligent();
    bool move(char m);
    void solvePuzzle(); 
    void lastPlayUpdater(char lastPlay);
    void printVector();
    void setSpace_x(int a);
    void setSpace_y(int a);
    void pushToMoveVector(char o);
    void printMoveVector();
    bool checkIfInList(Board& B);

    static int move_counter; //public static varible for keeping moves.

};

int NPuzzle::move_counter = 0; //Init the static val

int main(int argc, char** argv){

    NPuzzle Game;//Game started.
    string board_name;
    int board_size;
    char option;
    string l_board_name;

    srand(time(NULL));    
    
    //Gameconfig set to true (classic npuzzle)
    if(argc==1){

        Game.setGameConfiguration(true);

        cout << "Please enter the problem size" << endl;
        cin >> board_size;
        cout << "Your initial random board is" << endl;

        Game.setSpace_x(board_size-1);
        Game.setSpace_y(board_size-1);

        Game.setSize(board_size, board_size); 
        Game.shuffle(board_size*board_size);
        Game.print();      

    }

    //Gameconfig set to false (from file)
    else{

        Game.setGameConfiguration(false);
        cout << "Board initialized from " << argv[argc-1] << " is" << endl;
        board_size = Game.readFromFile(argv[argc-1]);   
        Game.print();

    }

    while(option != 'Q'){//This game loop will keep on going till the game finishes or user wishes to quit by pressing 'Q'.

        cout << "Your move: ";
        cin >> option;
        
        if(option == 'O'){
            cout << "Please give the name for .txt file (format: xxxxxx.txt):";
            cin >> board_name;

            Game.setGameConfiguration(false);
            board_size = Game.readFromFile(board_name); 
            Game.print();
        }

        else if(option == 'L'){

            if(Game.move('L')){
                NPuzzle::setMoveCounter(NPuzzle::getMoveCounter()+1);
                Game.print();
            }

            else{
                cout << "Illegal move, try again." << endl;        
            }

        }
    
        else if(option == 'R'){

            if(Game.move('R')){
                NPuzzle::setMoveCounter(NPuzzle::getMoveCounter()+1);
                Game.print();
            }

            else{
                cout << "Illegal move, try again." << endl;        
            }
        
        }
    
        else if(option == 'U'){

            if(Game.move('U')){
                NPuzzle::setMoveCounter(NPuzzle::getMoveCounter()+1);
                Game.print();
            }

            else{
                cout << "Illegal move, try again." << endl;        
            }
        
        }
    
        else if(option == 'D'){

            if(Game.move('D')){
                NPuzzle::setMoveCounter(NPuzzle::getMoveCounter()+1);
                Game.print();
            }

            else{
                cout << "Illegal move, try again." << endl;        
            }              
       
        }
    
        else if(option == 'I'){

            NPuzzle::setMoveCounter(NPuzzle::getMoveCounter()+1);
            Game.moveIntelligent();
            Game.print();

        }

        else if(option == 'S'){

            cout << "Shuffling current configuration..." << endl;
            Game.shuffle(board_size*board_size);
            Game.print();

        }

        else if(option == 'E'){
            cout << "Please give the name for .txt file (format: xxxxxx.txt):";
            cin >> l_board_name;

            Game.writeToFile(l_board_name);
        }

        else if(option == 'T'){

            Game.printReport();

        }

        else if(option == 'V'){

            Game.solvePuzzle();

        }

        else if(option == 'Q'){
            cout << "Quitting the game..." << endl;
        }

        else{
            cout << "Unknown move, try again!" << endl;
        }
    
    }

    return 0;
}

void NPuzzle::printVector(){
    for(int i=0; i<Boards.size(); i++){
        Boards[i].print();
        cout << endl;
    }
};

void NPuzzle::printMoveVector(){
    for(int i=0; i<last_plays.size(); i++){
        cout << last_plays[i] << " ";
    }    
    cout << endl;
};

void NPuzzle::Board::setLast_move(char p){
    last_move = p;
};

void NPuzzle::pushToMoveVector(char o){
    last_plays.push_back(o);
};

char NPuzzle::Board::getLast_move(){
    return last_move;
};

void NPuzzle::setSpace_x(int a){
    gameBoard.setSpace_x(a);
};

void NPuzzle::setSpace_y(int a){
    gameBoard.setSpace_y(a);
};

void NPuzzle::Board::setSpace_x(int a){
    space_x = a;
};

void NPuzzle::Board::setSpace_y(int a){
    space_y = a;
};


//NPuzzle::Board--------------------------------------------------------------------------------------------
inline int NPuzzle::Board::getRow() const{    return row;    }; 
inline int NPuzzle::Board::getColumn() const{    return column;    };
inline bool NPuzzle::Board::getGameConfiguration() const{    return game_configuration;    };         
inline int NPuzzle::Board::getSolvedBoardElement(int x, int y) const{    return temp_board[x][y];    };
inline int NPuzzle::Board::getBoardElement(int x, int y) const{    return board[x][y];    }; 

inline void NPuzzle::Board::setRow(int x){    row = x;    };
inline void NPuzzle::Board::setColumn(int x){    column = x;    };        
inline void NPuzzle::Board::setGameConfiguration(bool config){    game_configuration=config;    }; 

//NPuzzle::-------------------------------------------------------------------------------------------------
inline int NPuzzle::getMoveCounter(){    return move_counter;    };
inline vector<NPuzzle::Board> NPuzzle::getBoard(){    return Boards;    };

inline void NPuzzle::pushToBoardsVector(NPuzzle::Board& B){   Boards.push_back(B);    };
inline void NPuzzle::setMoveCounter(int m){    move_counter=m;    };    
inline void NPuzzle::setGameConfiguration(bool config){    gameBoard.setGameConfiguration(config);    };

//Helper Functions:
int NPuzzle::Board::string_parser(char x){
    if(x=='b'){
        return -1;
    }

    else if(x==' '){
        return -2;
    }

    else if(x=='0'){
        return 0;
    }

    else if(x=='1'){
        return 1;
    }

    else if(x=='2'){
        return 2;
    }

    else if(x=='3'){
        return 3;
    }

    else if(x=='4'){
        return 4;
    }

    else if(x=='5'){
        return 5;
    }

    else if(x=='6'){
        return 6;
    }

    else if(x=='7'){
        return 7;
    }

    else if(x=='8'){
        return 8;
    }

    else if(x=='9'){
        return 9;
    }

    return 0;
}

//Member Functions

void NPuzzle::printReport(){

        cout << NPuzzle::getMoveCounter() << " moves has been done for current configuration and the game is";

        if(gameBoard.isSolved()){
            cout << " done.";
        }
        else{
            cout << " not done.";
        }

        cout << endl;

}

void NPuzzle::shuffle(int n){

    int rand_number=0;
    bool checker = false;    

    reset();

    for(int i=0; i<n; i++){

        rand_number = rand()%4;

        if(rand_number == 0){
            checker = move('L');
        }

        else if(rand_number == 1){
            checker = move('R'); 
        }

        else if(rand_number == 2){
            checker = move('U'); 
        }

        else if(rand_number == 3){
            checker = move('D');  
        }

        if(checker == false){
            i--;
        }

    }

    Boards.push_back(gameBoard);

}

void NPuzzle::moveRandom(){

    int rand_num = 0;
    bool checker = false;

    while(!checker){

        rand_num = rand()%4;

        if(rand_num == 0){
            if(move('L')){
                checker = true;
            }        
        }

        else if(rand_num == 1){
            if(move('R')){
                checker = true;
            }             
        }

        else if(rand_num == 2){
            if(move('U')){
                checker = true;
            }             
        }

        else if(rand_num == 3){
            if(move('D')){
                checker = true;
            }             
        }                        

    }

}

bool NPuzzle::moveIntelligent(){

}

bool NPuzzle::checkIfInList(Board& B){

    bool checker=false;
    int counter=0;

        for(int x=0; x<Boards.size(); x++){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    if(Boards[x].getBoardElement(i,j) != B.getBoardElement(i,j)){
                        checker = true;    
                    }
                }
            }

            if(checker == false){
                return true;
            }

            checker = false;

        }    
 
    return false;
};

void NPuzzle::solvePuzzle(){

    int i = 0;
    int index = 0;
    bool x = false;

        while(!Boards[i].isSolved()){

            if(Boards[i].move('L')){

                    index++;

                    if(x != true){            
                        last_plays.push_back('L');
                        x = true;
                    }    

                    Boards.push_back(Boards[i]);


                    if(Boards[i].isSolved()){

                        Boards[i].print();
                        cout << "Algorithm succesfuly solved the puzzle." << endl;
                        
                        break;
                    }
                    
                    Boards[i].move('R');
            }

            if(Boards[i].move('R')){

                    index++;                

                    if(x != true){            
                        last_plays.push_back('R');
                        x = true;
                    }                                  
                    Boards.push_back(Boards[i]);


                    if(Boards[i].isSolved()){
                        Boards[i].print();                        
                        cout << "Algorithm succesfuly solved the puzzle." << endl;                    
                        break;
                    }
                    
                    Boards[i].move('L');                               
            }

            if(Boards[i].move('U')){

                    index++;                

                    if(x != true){            
                        last_plays.push_back('U');
                        x = true;
                    }                                  
                    Boards.push_back(Boards[i]);


                    if(Boards[i].isSolved()){   
                        Boards[i].print();                                                         
                        cout << "Algorithm succesfuly solved the puzzle." << endl;
                        break;
                    }
                   
                    Boards[i].move('D');         
            }

            if(Boards[i].move('D')){  

                    index++;                   
                        
                    if(x != true){            
                        last_plays.push_back('D');
                        x = true;
                    }                                    
                    Boards.push_back(Boards[i]);


                    if(Boards[i].isSolved()){  
                        Boards[i].print();                                                           
                        cout << "Algorithm succesfuly solved the puzzle." << endl;                    
                        break;
                    }
                    
                    Boards[i].move('U');     
            }

            x = false;
            cout << "Pushed " << index << " new boards to the vector." << endl;
            index = 0;
            i++;

        }

        cout << "Number of moves:" << i+1 << endl; 

}

void NPuzzle::Board::print(){

    if(game_configuration == true){

        for(int i=0; i<row; i++){
            for(int j=0; j<column; j++){
                if(board[i][j] != 0){
                    if(board[i][j] == -1){
                        cout << "   ";
                    }

                    else if(board[i][j] < 10){
                        cout << board[i][j] << "  ";
                    }

                    else{
                        cout << board[i][j] << ' ';
                    }
                }

                else{
                    cout << "   ";
                }
            }
            cout << endl;
        }

    }

    else{

        for(int i=0; i<MAX_BOARD_SIZE; i++){
            for(int j=0; j<MAX_BOARD_SIZE; j++){
                if(board[i][j] == 0){
                    cout << "00 ";                   
                }

                else if(board[i][j] == -1){
                    cout << "bb ";
                }
                
                else if(board[i][j] != 0 && board[i][j] < 10){
                    cout << "0" << board[i][j] << " ";
                }

                else{
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }

    }

    cout << endl;
}

void NPuzzle::print(){ //Defined in NPuzzle::Board
    return gameBoard.print();
}

int NPuzzle::Board::readFromFile(string text_name){

    string temp;
    int counter=0;
    int count2 = 0;

    ifstream FILE;
    FILE.open(text_name);
    
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            board[i][j]=0;
        }
    }       
    
    while(getline(FILE, temp)){
        counter = 0;

        for(long long unsigned i=0; i<temp.length(); i=i+3){

            if(string_parser(temp[i])!=-1 && string_parser(temp[i])!=-2){  

                if(temp[i]=='0' && temp[i+1]=='0'){
                    board[count2][counter] = 0;

                    counter++;
                }

                else if(temp[i]=='0'){
                    board[count2][counter] = string_parser(temp[i+1]);     
                    counter++;              
                }

                else{                   
                    board[count2][counter] = string_parser(temp[i])*10 + string_parser(temp[i+1]);
                    counter++;              
                }

            }

            else if(string_parser(temp[i]) == -1){
                space_x=counter;
                space_y=count2;                
                board[count2][counter] = -1;
                counter ++;
            }
        
        }

        count2++;      
    }

    counter = 1;

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            temp_board[j][i] = board[j][i];        
        }
    }

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(temp_board[i][j] != 0){
                temp_board[i][j] = counter;
                counter++;
            }     
        }
    }

    int max = 0;
    int m,x;

    for(int a=0; a<9; a++){
        for(int b=0; b<9; b++){
            if(temp_board[a][b] > max){
                m=a;
                x=b;
            }        
        }
    }

    setRow(9);
    setColumn(9);
    temp_board[m][x] = -1;

    FILE.close();

    return count2;
}

int NPuzzle::readFromFile(string text_name){ //Defined in NPuzzle::Board
    Boards.resize(1);
    return gameBoard.readFromFile(text_name);
}


void NPuzzle::Board::writeToFile(string text_name){

    ofstream FILE;
    FILE.open(text_name);

    if(game_configuration == true){

        for(int i=0; i<MAX_BOARD_SIZE; i++){
            for(int j=0; j<MAX_BOARD_SIZE; j++){
                if(board[j][i] != 0){
                    if(board[j][i] < 10){

                        if(board[j][i] == -1){
                            FILE << "   ";
                        }

                        else{
                            FILE << board[j][i] << "  ";
                        }

                    }

                    else{
                        FILE << board[j][i] << ' ';
                    }
                }


                else{
                    FILE << "   ";
                }
            }
            FILE << endl;
        }

    }

    else{

        for(int i=0; i<MAX_BOARD_SIZE; i++){
            for(int j=0; j<MAX_BOARD_SIZE; j++){
                if(board[i][j] == 0){
                    FILE << "00 ";                   
                }

                else if(board[i][j] == -1){
                    FILE << "bb ";
                }
                    
                else if(board[i][j] != 0 && board[i][j] < 10){
                    FILE << "0" << board[i][j] << " ";
                }

                else{
                    FILE << board[i][j] << " ";
                }
            }
            FILE << endl;
        }

    }

    FILE.close();
}


void NPuzzle::writeToFile(string text_name){ //Defined in NPuzzle::Board
    return gameBoard.writeToFile(text_name);
}

void NPuzzle::Board::reset(){
    
    int counter = 1;

    if(game_configuration == true){

        for(int i=0; i<MAX_BOARD_SIZE; i++){
            for(int j=0; j<MAX_BOARD_SIZE; j++){
                
                if(j<row && i<column){
                    board[i][j]=counter;
                    temp_board[i][j]=counter;
                    counter++;
                }

                else{
                    //0 stands for the borders of the board.
                    board[i][j]=0;
                    temp_board[i][j]=0;       
                }

            }
        }

        board[space_x][space_y] = -1;
        temp_board[space_x][space_y] = -1;        

    }

    else{

        for(int i=0; i<MAX_BOARD_SIZE; i++){
            for(int j=0; j<MAX_BOARD_SIZE; j++){
                
                if(board[j][i] != 0 && board[j][i] != -1){
                    board[j][i] = counter;
                    counter++;
                }

            }
        }

    }
    
}

void NPuzzle::reset(){ //Defined in NPuzzle::Board
    NPuzzle::setMoveCounter(0);
    gameBoard.reset();
    return;
}

void NPuzzle::Board::setSize(int r, int c){
    row = r;
    column = c;

    reset();
}

void NPuzzle::setSize(int r, int c){ //Defined in NPuzzle::Board
    return gameBoard.setSize(r,c);
}

bool NPuzzle::Board::LMove(){

    int temp=0;

    if(space_y - 1 >= 0){
        if(board[space_x][space_y-1] != 0){
            temp = board[space_x][space_y-1];
            board[space_x][space_y-1] = -1;
            board[space_x][space_y] = temp;

            space_y = space_y - 1;
            return true;
        }
    }

    return false;
}

bool NPuzzle::Board::RMove(){

    int temp=0;

    if(board[space_x][space_y+1] != 0){
        temp = board[space_x][space_y+1];
        board[space_x][space_y+1] = -1;
        board[space_x][space_y] = temp;
        
        space_y = space_y + 1;        
        return true;
    }

    return false;
}

bool NPuzzle::Board::UMove(){

    int temp=0;

    if(space_x - 1 >= 0){
        if(board[space_x-1][space_y] != 0){
            temp = board[space_x-1][space_y];
            board[space_x-1][space_y] = -1;
            board[space_x][space_y] = temp;

            space_x = space_x - 1;
            return true;            
        }
    }

    return false;

}

bool NPuzzle::Board::DMove(){

    int temp=0;

    if(board[space_x+1][space_y] != 0){
        temp = board[space_x+1][space_y];
        board[space_x+1][space_y] = -1;
        board[space_x][space_y] = temp;

        space_x = space_x + 1;
        return true;
    }

    return false;
    
}

bool NPuzzle::Board::move(char m){
    
    if(m == 'L'){
        return LMove();        
    }

    if(m == 'R'){
       return RMove();
    }

    if(m == 'U'){
        return UMove();
    }

    if(m == 'D'){
        return DMove();
    }

    return false;

}

bool NPuzzle::move(char m){ //Defined in NPuzzle::Board
    return gameBoard.move(m);
}

bool NPuzzle::Board::isSolved(){

    for(int i=0; i<MAX_BOARD_SIZE; i++){
        for(int j=0; j<MAX_BOARD_SIZE; j++){
            if(board[i][j] != temp_board[i][j]){
                return false;
            }
        }        
    }

    return true;
    
}



