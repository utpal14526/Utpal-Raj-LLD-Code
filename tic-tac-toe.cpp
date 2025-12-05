#include <iostream>
using namespace std;

enum Symbol {
    X,
    O,
    EMPTY
};

class Position {
public:
    int row, col;
    Position(int r, int c) {
        row = r;
        col = c;
    }
};

class Board {
public:
    Symbol board[3][3];

    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = Symbol::EMPTY;
            }
        }
    }

    bool isValidMove(Position* move) {
        int row = move->row;
        int col = move->col;

        return (row >= 0 && row < 3 &&
                col >= 0 && col < 3 &&
                board[row][col] == Symbol::EMPTY);
    }

    void makeMove(Position* pos, Symbol symbol) {
        board[pos->row][pos->col] = symbol;
    }

    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                Symbol symbol = board[i][j];
                switch (symbol) {
                case Symbol::X:
                    cout << " X ";
                    break;
                case Symbol::O:
                    cout << " O ";
                    break;
                default:
                    cout << " . ";
                }

                if (j < 2) cout << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};


class PlayerStrategy {
public:
    virtual Position* makeMove(Board* board) = 0;  
    virtual ~PlayerStrategy() {}
};


class HumanStrategy : public PlayerStrategy {
public:
    string playerName;

    HumanStrategy(string playerName) {
        this->playerName = playerName;
    }

    Position* makeMove(Board* board) override {
        while (true) {
            cout << "Enter your move, " << playerName << " (row col): ";
            int row, col;
            cin >> row >> col;

            Position* move = new Position(row, col);
            if (board.isValidMove(move)) {
                return move;
            }
            cout << "Invalid move! Try again.\n";
        }
    }
};


class Player {
public:
    Symbol symbol;
    PlayerStrategy* strategy;

    Player(Symbol symbol, PlayerStrategy* strategy) {
        this->symbol = symbol;
        this->strategy = strategy;
    }

    Position* makeMove(Board* board){
        return strategy->makeMove(board);
    }

    Symbol getSymbol(){
        return symbol;
    }
};


class GameState{
    public:
    virtual void next(GameContext* context, Player* player , bool hasWon)=0;
    virtual bool isGameOver()=0;
    virtual ~GameState()=0;
};

class XturnState: public GameState{

    public:

    void next(GameContext* gameContext,Player* player,bool hasWon){
        if(hasWon){
            // XTurn State to XWon State 
        }
        else{

        }
    }

    bool isGameOver(){
        return false;
    }

};
class OturnState: public GameState{
  public:

  bool isGameOver(){
    return false;
  }

//   void next

};

class XWinState: public GameState{
    public :

    bool isGameOver(){
        return true;
    }
};

class OWinState: public GameState{
    public:
     bool isGameOver(){
        return true;
    }
};


class GameContext{
    public:

    GameState* currState;
    GameContext(){
        currState=new XturnState();
    }

    GameState* getState(){
        return currState;
    }

    void next(Player* player,bool hasWon){
        currState->next(this,player,hasWon);
    }

    void setState(GameState* gameState){
        this->currState=gameState;
    }

    bool isGameOver(){
        return currState->isGameOver();
    }

};


class BoardGame {
public:
    virtual void play() {}
};

class TicTacToeGame : public BoardGame {
public:
    Board* board;
    Player* playerX;
    Player* playerO;
    Player* currentPlayer;
    GameContext* gameContext;

    TicTacToeGame(PlayerStrategy* xStrategy, PlayerStrategy* oStrategy) {
        board = new Board();
        playerX = new Player(Symbol::X, xStrategy);
        playerO = new Player(Symbol::O, oStrategy);
        currentPlayer = playerX;
    }


    void play(){

        do{
            // means yet the player didn;t win the match 
            board->displayBoard();

            Position* move=currentPlayer->makeMove(board);
            board->makeMove(move,currentPlayer->getSymbol());

            board.checkGameState(gameContext);  // isme ye jakr gameCOntext mai state change krega if X win hua call krr dega 
            switchPlayer();

        }while(!gameContext->isGameOver());

    }

    void switchPlayer(){
        currentPlayer=(currentPlayer==playerX)?playerO:playerX;
    }

    void announceWinner(){

        // Check from the GameContext the state if the state is XWinState or OWinState 
        

    }

};


int main() {

}
