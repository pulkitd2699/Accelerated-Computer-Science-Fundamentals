// Tower of Hanoi with C++
// There is a game, consisting of cubes and stacks, cubes are the plates that have to go from S -> D.
// Stacks are represented as vector

#include <bits/stdc++.h>
using namespace std;

// cube class
class Cube{
    // plates in tower of hanoi with 2 properties
    int length_;
    int color_;

    public:
        Cube(int length, int color);
        int getLength() const;
        void setLength(int length);
        int getVolume() const;
        int getSurfaceArea() const;
};

// stack class
class Stack{
    // A vector of cubes and operation to interact with top of stack
    vector<Cube> cubes_;

    public:
        void push_back(const Cube & cube);
        Cube removeTop(); // returns copy of the top cube
        Cube & peekTop();
        unsigned size() const;

        // an overloaded operator <<, allowing us to print the stack
        // via cout<<
        friend ostream& operator<<(ostream & os, const Stack & stack);
};

// game class
class Game{
    //consists of array of 3 stacks and initial satte (4 cubes in first stack)
    vector<Stack> stacks_;

    public:
        Game();
        void solve();
        void _move(unsigned start, unsigned end, Stack& source, Stack& target, Stack& spare);
        void _moveCube(Stack& source, Stack& target);
        
        friend ostream& operator<<(ostream &os, const Game & game);
};

//cube.cpp file
Cube :: Cube(int length, int color){
    length_ = length;
    color_ = color;
}

int Cube :: getLength() const{
    return length_;
}

int Cube :: getVolume() const{
    return length_ * length_ * length_;
}

int Cube :: getSurfaceArea() const {
    return 6 * length_ * length_;
}

void Cube :: setLength(int length){
    length_ = length;
}
// ends here --------------

//stack.cpp file
void Stack :: push_back(const Cube &cube){
    // errorneous situation
    if(size() > 0 and cube.getLength() > peekTop().getLength()){
        cerr << "A small cube cannot be placed on top of a larger cube" << endl;
        cerr << "Tried to add Cube(length="<< cube.getLength() << ")" << endl;
        cerr << "Current Stack: " <<  *this << endl;

        throw runtime_error("A smaller cube cannot be placed on top of a larger cube.");
    }

    cubes_.push_back(cube);
}

Cube Stack :: removeTop(){
    Cube cube = peekTop();
    cubes_.pop_back();
    return cube;
}

Cube & Stack :: peekTop(){
    return cubes_[cubes_.size() - 1];
}

unsigned Stack :: size() const{
    return cubes_.size();
}

ostream& operator<<(ostream & os, const Stack & stack){
    for(unsigned i=0; i<stack.size();i++){
        os << stack.cubes_[i].getLength() << " ";
    }
    os << endl;
    return os;
}
//ends here --------------

//game.cpp file which includes game class member functions definition
Game :: Game(){
    for(int i=0;i<3;i++){
        Stack stackOfCubes;
        stacks_.push_back(stackOfCubes);
    }

    //creating 4 cubes, placing each on the [0]th stack 1 top of another
    //color and number mapping -> blue(1), orange(2), purple(3), yellow(4)
    Cube blue(4, 1);
    stacks_[0].push_back(blue);

    Cube orange(3, 2);
    stacks_[0].push_back(orange);

    Cube purple(2, 3);
    stacks_[0].push_back(purple);

    Cube yellow(1, 4);
    stacks_[0].push_back(yellow);
}

ostream& operator<<(ostream & os, const Game & game){
    for(unsigned i=0;i<game.stacks_.size();i++){
        os << "Stack[" << i << "]: " << game.stacks_[i];
    }
    return os;
}

void Game :: _moveCube(Stack &source, Stack &target){
    Cube cube = source.removeTop();
    target.push_back(cube);
}

void Game :: _move(unsigned start, unsigned end, Stack &source, Stack &target, Stack &spare){
    //check if we are only moving one cube
    if(start == end){
        _moveCube(source, target);
        cout << *this << endl;
    }
    else{
        //follow move strategy
        _move(start+1, end, source, spare, target);
        _move(start, start, source, target, spare);
        _move(start+1, end, spare, target, source);
    }
}


void Game :: solve(){
    _move(0,stacks_[0].size()-1,stacks_[0],stacks_[2],stacks_[1]);
}
// ends here -----------------

int main() {
    //creating a game of TOH
    Game g;

    cout << "INITIAL GAME STATE : " << endl;
    cout << g << endl;

    g.solve();

    cout << "FINAL GAME STATE : " << endl;
    cout << g << endl;

    return 0;
}
