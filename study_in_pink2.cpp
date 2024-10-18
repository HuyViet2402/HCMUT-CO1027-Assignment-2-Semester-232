#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

bool Type_canUse(ItemType type, Character* CHAR) {
    BaseItem* tempItem = nullptr;
    switch(type) {
        case MAGIC_BOOK:
            tempItem = new MagicBook();
            break;
        case ENERGY_DRINK:
            tempItem = new EnergyDrink();
            break;
        case FIRST_AID:
            tempItem = new FirstAid();
            break;
        case PASSING_CARD:
            tempItem = new PassingCard("dummmy");
            break;
        case EXCEMPTION_CARD:
            tempItem = new ExcemptionCard();
            break;
    }
    bool result = tempItem->canUse(CHAR, nullptr);
    delete tempItem;
    return result;
}

//      Config class      ////////////////////////////////////////////////////////////////////////
int Manhattan_Dis(Position P1, Position P2) {
    return abs(P1.getRow()-P2.getRow()) + abs(P1.getCol()-P2.getCol());
}
int sum_Manhattan_dis(Position W, Position S, Position to_compare) {
    return Manhattan_Dis(W, to_compare) + Manhattan_Dis(S, to_compare);
}
int count_ele_Arr(string to_count) {
    size_t find_num_element = to_count.find(",");
    int num_element = 0;
    while(find_num_element != string::npos) {
        num_element++;
        find_num_element = to_count.find(",", find_num_element+1);
    }
    return num_element;
}
Position* process_pos_array(string data, int num) {
    Position* arr = new Position[num]; 
    size_t find1, find2;
    int i = 0;
    find1 = data.find("(");
    find2 = data.find(")");
    while(find1 != string::npos && find2 != string::npos && i < num) {
        arr[i++].set_RC(data.substr(find1, find2-find1+1));
        find1 = data.find("(", find1+1);
        find2 = data.find(")", find2+1);
    }
    return arr;
}
Configuration::~Configuration() {
    delete[] arr_walls;
    delete[] arr_fake_walls;
}
Configuration::Configuration(const string & filepath) {
    ifstream config_file;
    config_file.open(filepath.c_str(), ifstream::in);
    string str_temp, str_temp1, str_temp2;
    while(!config_file.eof()) {
        getline(config_file, str_temp);
        int find_equal = str_temp.find("=");
        str_temp1 = str_temp.substr(0, find_equal);
        str_temp2 = str_temp.substr(find_equal + 1);

        if(str_temp1 == "MAP_NUM_ROWS") {
            stringstream ss(str_temp2);
            ss >> this->map_num_rows;
        } else if (str_temp1 == "MAP_NUM_COLS") {
            stringstream ss(str_temp2);
            ss >> this->map_num_cols;
        } else if(str_temp1 == "MAX_NUM_MOVING_OBJECTS") {
            stringstream ss(str_temp2);
            ss >> this->max_num_moving_objects;
        } else if(str_temp1 == "SHERLOCK_MOVING_RULE") {
            this->sherlock_moving_rule = str_temp2;
        } else if(str_temp1 == "SHERLOCK_INIT_POS") {
            this->sherlock_init_pos.set_RC(str_temp2);
        } else if(str_temp1 == "SHERLOCK_INIT_HP") {
            stringstream ss(str_temp2);
            ss >> this->sherlock_init_hp;
        } else if(str_temp1 == "SHERLOCK_INIT_EXP") {
            stringstream ss(str_temp2);
            ss >> this->sherlock_init_exp;
        } else if(str_temp1 == "WATSON_MOVING_RULE") {
            this->watson_moving_rule = str_temp2;
        } else if(str_temp1 == "WATSON_INIT_POS") {
            this->watson_init_pos.set_RC(str_temp2);
        } else if(str_temp1 == "WATSON_INIT_HP") {
            stringstream ss(str_temp2);
            ss >> this->watson_init_hp;
        } else if(str_temp1 == "WATSON_INIT_EXP") {
            stringstream ss(str_temp2);
            ss >> this->watson_init_exp;
        } else if(str_temp1 == "CRIMINAL_INIT_POS") {
            this->criminal_init_pos.set_RC(str_temp2);
        } else if(str_temp1 == "NUM_STEPS") {
            stringstream ss(str_temp2);
            ss >> this->num_steps;
        } else if(str_temp1 == "ARRAY_WALLS") {
            this->str_arr_walls = str_temp2;
            this->num_walls = count_ele_Arr(str_temp2);
            arr_walls = process_pos_array(str_temp2, this->num_walls);
        } else if(str_temp1 == "ARRAY_FAKE_WALLS") {
            this->str_arr_fake_walls = str_temp2;
            this->num_fake_walls = count_ele_Arr(str_temp2);
            arr_fake_walls = process_pos_array(str_temp2, this->num_fake_walls);
        }
    }
    config_file.close();
}
string Configuration::str() const{
    string result = "Configuration[\n";
    result += "MAP_NUM_ROWS=" + to_string(this->map_num_rows) + '\n';
    result += "MAP_NUM_COLS=" + to_string(this->map_num_cols) + '\n';
    result += "MAX_NUM_MOVING_OBJECTS=" + to_string(this->max_num_moving_objects) + '\n';
    result += "NUM_WALLS=" + to_string(this->num_walls) + '\n';
    result += "ARRAY_WALLS=" + this->str_arr_walls + '\n';
    result += "NUM_FAKE_WALLS=" + to_string(this->num_fake_walls) + '\n';
    result += "ARRAY_FAKE_WALLS=" + this->str_arr_fake_walls + '\n';
    result += "SHERLOCK_MOVING_RULE=" + this->sherlock_moving_rule + '\n';
    result += "SHERLOCK_INIT_POS=" + this->sherlock_init_pos.str() + '\n';
    result += "SHERLOCK_INIT_HP=" + to_string(this->sherlock_init_hp) + '\n';
    result += "SHERLOCK_INIT_EXP=" + to_string(this->sherlock_init_exp) + '\n';
    result += "WATSON_MOVING_RULE=" + this->watson_moving_rule + '\n';
    result += "WATSON_INIT_POS=" + this->watson_init_pos.str() + '\n';
    result += "WATSON_INIT_HP=" + to_string(this->watson_init_hp) + '\n';
    result += "WATSON_INIT_EXP=" + to_string(this->watson_init_exp) + '\n';
    result += "CRIMINAL_INIT_POS=" + this->criminal_init_pos.str() + '\n';
    result += "NUM_STEPS=" + to_string(this->num_steps) + '\n';
    result += "]";
    return result;
}
//Done config next do map related class
//      Position class      ////////////////////////////////////////////////////////////////////////
//Done 3.3
Position::Position(int r /*=0*/, int c /*=0*/) {
    this->r = r;
    this->c = c;
}
Position::Position ( const string & str_pos ) {
    int find_comma = str_pos.find(",");
    string num1 = str_pos.substr(1, find_comma-1);
    string num2 = str_pos.substr(find_comma+1, str_pos.size() - find_comma - 2);
    if(stoi(num1) < 0 || stoi(num2) < 0) {
        this->r = -1;
        this->c = -1;
    }
    else {
        this->r = stoi(num1);
        this->c = stoi(num2);
    }
}
int Position::getRow() const { return this->r; }
int Position::getCol() const { return this->c; }
void Position::setRow(int r) { this->r = r; }
void Position::setCol(int c) { this->c = c; }
string Position::str() const {
    string result = "";
    result = "(" + to_string(this->r) + "," + to_string(this->c) + ")";
    return result;
}
bool Position::isEqual(int in_r, int in_c) const {
    if(this->r == in_r && this->c == in_c) return true;
    return false;
}
bool Position::isEqual(const Position& in_Pos) const {
    if(this->r == in_Pos.getRow() && this->c == in_Pos.getCol()) return true;
    return false;
}
void Position::set_RC(string str_in) {
    int find_comma = str_in.find(",");
    string num1 = str_in.substr(1, find_comma-1);
    string num2 = str_in.substr(find_comma+1, str_in.size() - find_comma - 2);
    this->r = stoi(num1);
    this->c = stoi(num2);
}
const Position Position::npos = Position(-1,-1);
// Position::~Position() {

// }
//      MapElement class      ////////////////////////////////////////////////////////////////////////
MapElement::MapElement(ElementType in_type) : type(in_type) {
    
}
MapElement::~MapElement() {

}
ElementType MapElement::getType() const {
    return this->type;
}

// MapElement::MapElement() {}


Path::Path() : MapElement(PATH) {
    
}

Wall::Wall() : MapElement(WALL) {
}

FakeWall::FakeWall() : MapElement(FAKE_WALL) {
}

FakeWall::FakeWall(int in_req_exp) : MapElement(FAKE_WALL) {
    req_exp = in_req_exp;
}

int FakeWall::getReqExp() const{
    return this->req_exp;
}
//Done 3.1
//      Map class      ////////////////////////////////////////////////////////////////////////
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols) {
    map = new MapElement**[num_rows];
    for(int i = 0; i < num_rows; i++) {
        map[i] = new MapElement*[num_cols];
        for(int j = 0; j < num_cols; j++) {
            map[i][j] = new Path();
        }
    }
    for(int i = 0; i < num_walls; i++) {
        delete map[array_walls[i].getRow()][array_walls[i].getCol()];
        map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
    }
    for(int i = 0; i < num_fake_walls; i++) {
        delete map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()];
        map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = new FakeWall((array_fake_walls[i].getRow() * 257 + array_fake_walls[i].getCol() * 139 + 89)%900 + 1 );
    }
}
Map::~Map() {
    // for(int i = 0; i < this->num_rows; i++) {
    //     for(int j = 0; j < this->num_cols; j++) {
    //         delete map[i][j];
    //     }
    //     delete [] map[i];
    // }
    // delete [] map; //here check again tomorrow done
    // Comment destructor, redo it again if neccessary
} //done 3.2

bool Map::isValid ( const Position & pos , MovingObject * mv_obj ) const {
    if(pos.getCol() < 0 || pos.getRow() < 0) return false;
    if(map[pos.getRow()][pos.getCol()]->getType() == WALL) return false;
    if(map[pos.getRow()][pos.getCol()]->getType() == PATH) return true;
    if(mv_obj->getName() == "Watson" && map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL) {
        Character* temp_w = dynamic_cast<Character*>(mv_obj);
        FakeWall* temp_fw = dynamic_cast<FakeWall*>(map[pos.getRow()][pos.getCol()]);
        if(temp_w->get_exp() <= temp_fw->getReqExp()) return false;
        else return true;
    }
    return true;
}

int Map::get_num_cols() {return this->num_cols;}
int Map::get_num_rows() {return this->num_rows;}

//      MovingObject class      ////////////////////////////////////////////////////////////////////////
MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name /*=""*/) {
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}
MovingObject::~MovingObject() {

}
Position MovingObject::getCurrentPosition() const {
    return pos;
}

string MovingObject::getName() const {return this->name;}

//      Sherlock class      ////////////////////////////////////////////////////////////////////////
Character::Character(int index, const Position pos, Map * map, const string & name /*=""*/) :  MovingObject(index, pos, map, name){

}
int Character::get_hp() const {
    return this->hp;
}
int Character::get_exp() const {
    return this->exp;
}
void Character::change_hp(double diff) {
    diff += 0.999;
    this->hp = this->hp + diff;
}
void Character::change_exp(double diff) {
    diff += 0.999;
    this->exp = this->exp + diff;
}


void Character::check_and_set_hp() { //to check and set hp and exp
    if (this->hp < 0) {
        this->hp = 0; 
    }
    if(this->hp > 500) this->hp = 500;
}
void Character::check_and_set_exp() { //to check and set hp and exp
    if (this->exp < 0) {
        this->exp = 0; 
    }
    if(this->exp > 900) this->exp = 900;
}
Sherlock::Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : Character(index, init_pos, map, "Sherlock"){
    this->moving_rule = moving_rule;
    this->hp = init_hp;
    this->exp = init_exp;
    this->next_move = 0;
    this->bag = new SherlockBag(this);
    this->name = "Sherlock";
}
Position Sherlock::getNextPosition() {
    this->next_move %= this->moving_rule.size();

    char current_move = this->moving_rule[this->next_move];
    Position up(this->pos.getRow()-1, this->pos.getCol());
    Position left(this->pos.getRow(), this->pos.getCol()-1);
    Position down(this->pos.getRow()+1, this->pos.getCol());
    Position right(this->pos.getRow(), this->pos.getCol()+1);

    if(current_move == 'U' && up.getRow() >= 0 && this->map->isValid(up, this)) 
        return up;
    else if(current_move == 'L' && left.getCol() >= 0 && this->map->isValid(left, this))
        return left;
    else if(current_move == 'D' && down.getRow() < this->map->get_num_rows() && this->map->isValid(down, this))
        return down;
    else if(current_move == 'R' && right.getCol() < this->map->get_num_cols() && this->map->isValid(right, this))
        return right;
    return Position::npos;
}
void Sherlock::move() {
    Position next = this->getNextPosition();
    this->next_move++;
    if(next.getCol() != -1 && next.getRow() != -1 && this->exp > 0) this->pos = next;
}
string Sherlock::str() const{
    string result = "Sherlock[index=" + to_string(this->index) + ";pos=" + this->pos.str() + ";moving_rule=" + this->moving_rule + "]";
    return result;
}
void Sherlock::move_to_criminal(Position crimnal_pos) {
    this->pos = crimnal_pos;
}
//      Watson class      ////////////////////////////////////////////////////////////////////////
Watson::Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) :  Character(index, init_pos, map, "Watson"){
    this->moving_rule = moving_rule;
    this->hp = init_hp;
    this->exp = init_exp;
    this->next_move = 0;
    this->bag = new WatsonBag(this);
    this->name = "Watson";
}
Position Watson::getNextPosition() {
    this->next_move %= this->moving_rule.size();

    char current_move = this->moving_rule[this->next_move];
    Position up(this->pos.getRow()-1, this->pos.getCol());
    Position left(this->pos.getRow(), this->pos.getCol()-1);
    Position down(this->pos.getRow()+1, this->pos.getCol());
    Position right(this->pos.getRow(), this->pos.getCol()+1);
    if(current_move == 'U' && up.getRow() >= 0 && this->map->isValid(up, this)) 
        return up;
    else if(current_move == 'L' && left.getCol() >= 0 && this->map->isValid(left, this))
        return left;
    else if(current_move == 'D' && down.getRow() < this->map->get_num_rows() && this->map->isValid(down, this))
        return down;
    else if(current_move == 'R' && right.getCol() < this->map->get_num_cols() && this->map->isValid(right, this))
        return right;
    return Position::npos;
}

void Watson::move() {
    Position next = this->getNextPosition();
    this->next_move++;
    if(next.getCol() != -1 && next.getRow() != -1 && this->exp > 0) this->pos = next;
}
string Watson::str() const{
    string result = "Watson[index=" + to_string(this->index) + ";pos=" + this->pos.str() + ";moving_rule=" + this->moving_rule + "]";
    return result;
}


//Done 3.4 3.5 3.6 Not yet done isvalid // do robot next
//      Criminal class      ////////////////////////////////////////////////////////////////////////
Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson) :  Character(index, init_pos, map, "Criminal"){
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->sherlock = sherlock;
    this->watson = watson;
    steps_create_robot = 0;
    prev_pos = Position::npos;
    this->name = "Criminal";
}
int Criminal::distance_to_Criminal(Position to_compare) {
    int Sher_Dis = abs(this->sherlock->getCurrentPosition().getRow() - to_compare.getRow()) + abs(this->sherlock->getCurrentPosition().getCol() - to_compare.getCol());
    int Wat_Dis = abs(this->watson->getCurrentPosition().getRow() - to_compare.getRow()) + abs(this->watson->getCurrentPosition().getCol() - to_compare.getCol());
    return Sher_Dis + Wat_Dis;
}
Position Criminal::getNextPosition() {
    int max = -1;
    Position result;

    // Define the possible moves in the R, D, L, U directions
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 0; i < 4; i++) {
        int newRow = this->pos.getRow() + directions[i][0];
        int newCol = this->pos.getCol() + directions[i][1];
        // Check if the new position is within the map boundaries and is valid
        if (newRow >= 0 && newRow < this->map->get_num_rows() && newCol >= 0 && newCol < this->map->get_num_cols() 
            && this->map->isValid(Position(newRow, newCol), this)) {
            int curr_dis = distance_to_Criminal(Position(newRow, newCol));
            if (max <= curr_dis) {
                max = curr_dis;
                result = Position(newRow, newCol);
            }
        }
    }
    if (max != -1) return result;
    
    return Position::npos;
}

void Criminal::move() {
    Position next = this->getNextPosition();
    if(!next.isEqual(Position::npos)) {
        steps_create_robot = (steps_create_robot+1)%3;
        this->prev_pos = this->pos;
        this->pos = next;
    }
}
string Criminal::str() const {
    string result = "Criminal[index=" + to_string(this->index) + ";pos=" + this->pos.str() + "]";
    return result;
}
Position Criminal::getPrevPostion() {
    return this->prev_pos;
}
//Done 3.7
//      ArrayMovingObject class      ////////////////////////////////////////////////////////////////////////
ArrayMovingObject::ArrayMovingObject(int capacity) {
    had_Robot = false;
    this->arr_mv_objs = new MovingObject*[capacity];
    for(int i =0; i < capacity; i++) {
        this->arr_mv_objs[i] = nullptr;
    }
    count = 0;
    this->capacity = capacity;
}
ArrayMovingObject::~ArrayMovingObject() {
    // for(int i = 0; i < capacity; i++) {
    //     if(this->arr_mv_objs[i]) delete this->arr_mv_objs[i];
    // }
    // delete [] this->arr_mv_objs;
}
bool ArrayMovingObject::isFull() const {
    return (count == capacity);
}
bool ArrayMovingObject::add(MovingObject * mv_obj) {
    if(this->isFull()) return false; 
    if(mv_obj->getName() == "RobotC" || mv_obj->getName() == "RobotS" || mv_obj->getName() == "RobotW" || mv_obj->getName() == "RobotSW") had_Robot = true;
    this->arr_mv_objs[this->count++] = mv_obj;
    return true;
}
string ArrayMovingObject::str () const {
    string result = "ArrayMovingObject[count=" + to_string(this->count) + ";capacity=" + to_string(this->capacity);
    if(this->count > 0) result += ";";
    int c = 0;
    for(int i = 0; i < capacity; i++) {
        if(this->arr_mv_objs[i]) {
            result += this->arr_mv_objs[i]->str();
            c++;
        }
        if(c < count) result += ";";
    }
    result += "]";
    return result;
}
MovingObject* ArrayMovingObject::get(int index) const {
    if(index >= count || index < 0) return nullptr;
    
    return this->arr_mv_objs[index];
}
int ArrayMovingObject::size() const {
    return this->count;
}
//HERE CONTINUE WITH ARRAY THEN ROBOT
//      ROBOT class      ////////////////////////////////////////////////////////////////////////

BaseItem* Create_Reward(Robot* robot) {
    int p = robot->getCurrentPosition().getCol() * robot->getCurrentPosition().getRow();

    while (p > 9) {
        int sum = 0;
        while(p != 0) {
            sum += p%10;
            p/=10;
        }
        p = sum;
    }
    if(p == 0 || p == 1) return new MagicBook();
    if(p == 2 || p == 3) return new EnergyDrink();
    if(p == 4 || p == 5) return new FirstAid();
    if(p == 6 || p == 7) return new ExcemptionCard();
    if(p == 8 || p == 9) {
        string challenge;
        int t = (robot->getCurrentPosition().getRow()*11 + robot->getCurrentPosition().getCol())%4;
        if(t == 0) challenge = "RobotS";
        else if(t == 1) challenge = "RobotC";
        else if(t == 2) challenge = "RobotSW";
        else if(t == 3) challenge = "all";
        return new PassingCard(challenge);
    }
    return nullptr;
}
Robot::Robot(int index, const Position & init_pos, Map * map) : MovingObject(index, init_pos, map) {
    this->item = Create_Reward(this);
}
RobotType Robot::getType() {
    return Type;
}
BaseItem* Robot::getReward() {
    return this->item;
}
RobotC::RobotC( int index , const Position & init_pos , Map * map , Criminal * criminal ) : Robot(index, init_pos, map) {
    this->criminal = criminal;
    this->Type = C;
    this->name = "RobotC";
}

Position RobotC::getNextPosition() {
    return this->criminal->getPrevPostion();
}
void RobotC::move() {
    this->pos = this->getNextPosition();
}
string RobotC::str() const {
    string result = "";
    result += "Robot[pos=";
    result += this->pos.str();
    result += ";type=C;dist=]";
    return result;
}
int RobotC::getDistance(Character* WorS) const{
    if(WorS == nullptr) return -1;
    return Manhattan_Dis(WorS->getCurrentPosition(), this->pos);
}
RobotS::RobotS ( int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock ) : Robot(index, init_pos, map) {
    this->criminal = criminal;
    this->sherlock = sherlock;
    this->Type = S;
    this->name = "RobotS";
}

Position RobotS::getNextPosition() {
    int min = 90000000;
    Position result;

    // Define the possible moves in the U, R, D, L directions
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // D, L, U, R
    //int directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int newRow = this->pos.getRow() + directions[i][0];
        int newCol = this->pos.getCol() + directions[i][1];

        // Check if the new position is within the map boundaries and is valid
        if (newRow >= 0 && newRow < this->map->get_num_rows() && newCol >= 0 && newCol < this->map->get_num_cols() 
            && this->map->isValid(Position(newRow, newCol), this)) {

            int curr_dis = Manhattan_Dis(Position(newRow, newCol), this->sherlock->getCurrentPosition());

            // Update the maximum distance and result if the new maximum distance is greater
            if (min > curr_dis) {
                min = curr_dis;
                result = Position(newRow, newCol);
            }
        }
    }

    if (min != 90000000) return result;
    return Position::npos;
}

void RobotS::move() {
    Position next = this->getNextPosition();
    if(next.getCol() != -1 && next.getRow() != -1) this->pos = next;
}
string RobotS::str() const {
    string result = "";
    result += "Robot[pos=";
    result += this->pos.str();
    result += ";type=S;dist=";
    result += to_string(this->getDistance());
    result += "]";
    return result;
}
int RobotS::getDistance(Character* WorS) const {
    return Manhattan_Dis(this->pos, this->sherlock->getCurrentPosition());
}

RobotW::RobotW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson ) : Robot(index, init_pos, map){
    this->criminal = criminal;
    this->watson = watson;
    this->Type = W;
    this->name = "RobotW";
}

Position RobotW::getNextPosition() {
    int min = 90000000;
    Position result;

    // Define the possible moves in the U, R, D, L directions
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // D, L, U, R
    // int directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int newRow = this->pos.getRow() + directions[i][0];
        int newCol = this->pos.getCol() + directions[i][1];

        // Check if the new position is within the map boundaries and is valid
        if (newRow >= 0 && newRow < this->map->get_num_rows() && newCol >= 0 && newCol < this->map->get_num_cols() 
            && this->map->isValid(Position(newRow, newCol), this)) {

            int curr_dis = Manhattan_Dis(Position(newRow, newCol), this->watson->getCurrentPosition());

            // Update the maximum distance and result if the new maximum distance is greater
            if (min > curr_dis) {
                min = curr_dis;
                result = Position(newRow, newCol);
            }
        }
    }

    if (min != 90000000) return result;
    return Position::npos;
}

void RobotW::move() {
    Position next = this->getNextPosition();
    if(next.getCol() != -1 && next.getRow() != -1) this->pos = next;
}
string RobotW::str() const {
    string result = "";
    result += "Robot[pos=";
    result += this->pos.str();
    result += ";type=W;dist=";
    result += to_string(this->getDistance());
    result += "]";
    return result;
}
int RobotW::getDistance(Character* WorS) const {
    return Manhattan_Dis(this->pos, this->watson->getCurrentPosition());
}
RobotSW::RobotSW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock , Watson * watson ) : Robot(index, init_pos, map) {
    this->criminal = criminal;
    this->watson = watson;
    this->sherlock = sherlock;
    this->Type = SW;
    this->name = "RobotSW";
}

Position RobotSW::getNextPosition() {
    int min = 90000000;
    Position result;

    // Define the possible moves in the UU, UR, RR, RD, DD, DL, LL, LU directions
    int directions[8][2] = {{-2, 0}, {-1, 1}, {0, 2}, {1, 1}, {2, 0}, {1, -1}, {0, -2}, {-1, -1}};
    //int directions[8][2] = {{2, 0}, {1, -1}, {0, -2}, {-1, -1}, {-2, 0}, {-1, 1}, {0, 2}, {1, 1}};
    for (int i = 0; i < 8; i++) {
        int newRow = this->pos.getRow() + directions[i][0];
        int newCol = this->pos.getCol() + directions[i][1];

        // Check if the new position is within the map boundaries and is valid
        if (newRow >= 0 && newRow < this->map->get_num_rows() && newCol >= 0 && newCol < this->map->get_num_cols() 
            && this->map->isValid(Position(newRow, newCol), this)) {

            int curr_sum_dis = sum_Manhattan_dis(this->watson->getCurrentPosition(), this->sherlock->getCurrentPosition(), Position(newRow, newCol));

            // Update the maximum distance and result if the new maximum distance is greater
            if (min > curr_sum_dis) {
                min = curr_sum_dis;
                result = Position(newRow, newCol);
            }
        }
    }

    if (min != 90000000) return result;
    return Position::npos;
}

void RobotSW::move() {
    Position next = this->getNextPosition();
    if(next.getCol() != -1 && next.getRow() != -1) this->pos = next;
}
string RobotSW::str() const {
    string result = "";
    result += "Robot[pos=";
    result += this->pos.str();
    result += ";type=SW;dist=";
    result += to_string(this->getDistance());
    result += "]";
    return result;
}
int RobotSW::getDistance(Character* WorS) const {
    return sum_Manhattan_dis(this->watson->getCurrentPosition(), this->sherlock->getCurrentPosition(), this->pos);
}
// 19.04.2024 done robot
//      3.11 Item class      ////////////////////////////////////////////////////////////////////////
// not yet done item, do bag next then return to item
ItemType BaseItem::getType() {
    return Item;
}
ExcemptionCard::ExcemptionCard() {
    this->Item = EXCEMPTION_CARD;
    this->next_Item = nullptr;
}
bool ExcemptionCard::canUse(Character * obj , Robot * robot) {
    if(obj->getName() == "Sherlock" && obj->get_hp() % 2 != 0) return true;
    return false;
}
void ExcemptionCard::use(Character * obj , Robot * robot) {
    
}
PassingCard::PassingCard(string in_challenge) : challenge(in_challenge) {
    this->Item = PASSING_CARD;
    this->next_Item = nullptr;
}
bool PassingCard::canUse(Character * obj , Robot * robot) {
    if(obj->getName() == "Watson" && obj->get_hp() % 2 == 0) return true;
    return false;
}
void PassingCard::use(Character * obj , Robot * robot) {
    if(this->challenge != "all") {
        if(this->challenge != robot->getName()) {
            obj->change_exp(-50);
        }
    }
}

MagicBook::MagicBook() {
    this->Item = MAGIC_BOOK;
    this->next_Item = nullptr;
}
bool MagicBook::canUse(Character * obj , Robot * robot) {
    if(obj->get_exp() <= 350) return true;
    return false;
}
void MagicBook::use(Character * obj , Robot * robot) {
    obj->change_exp(0.25 * obj->get_exp());
}

EnergyDrink::EnergyDrink() {
    this->Item = ENERGY_DRINK;
    this->next_Item = nullptr;
}
bool EnergyDrink::canUse(Character * obj , Robot * robot) {
    if(obj->get_hp() <= 100) return true;
    return false;
}
void EnergyDrink::use(Character * obj , Robot * robot) {
    obj->change_hp(0.20 * obj->get_hp());
}

FirstAid::FirstAid() {
    this->Item = FIRST_AID;
    this->next_Item = nullptr;
}
bool FirstAid::canUse(Character * obj , Robot * robot) {
    if(obj->get_hp() <= 100 || obj->get_exp() <= 350) return true;
    return false;
}
void FirstAid::use(Character * obj , Robot * robot) {
    obj->change_hp(0.50 * obj->get_hp());
}
EnergyDrink* EnergyDrink::clone() const {
    return new EnergyDrink(*this);
}
FirstAid* FirstAid::clone() const {
    return new FirstAid(*this);
}
MagicBook* MagicBook::clone() const {
    return new MagicBook(*this);
}
PassingCard* PassingCard::clone() const {
    return new PassingCard(*this);
}
ExcemptionCard* ExcemptionCard::clone() const {
    return new ExcemptionCard(*this);
}
//done item 25/4

//      3.12 Bag class      ////////////////////////////////////////////////////////////////////////
BaseBag::BaseBag() {
    this->head_item = nullptr;
    this->count_item = 0;
}
SherlockBag::SherlockBag(Sherlock* in_sherlock) {
    this->head_item = nullptr;
    this->obj = in_sherlock;
    this->max_item = 13;
}
WatsonBag::WatsonBag(Watson* in_watson) {
    this->head_item = nullptr;
    this->obj = in_watson;
    this->max_item = 15;
}
int BaseBag::getCount() {
    return this->count_item;
}
bool BaseBag::insert ( BaseItem * item ) {
    if(this->count_item == this->max_item) return false;
    if(item == nullptr) {
        cout << "Error: nullptr\n" << endl;
        return false;
    }
    if(this->head_item == nullptr) this->head_item = item;
    else {
        item->next_Item = head_item;
        head_item = item;
    }
    this->count_item++;
    return true;
}
BaseItem* BaseBag::get() { //fix get and function run() again
    if(this->head_item == nullptr) return nullptr;
    if(this->head_item->canUse(this->obj, nullptr)) {
        this->count_item--;
        BaseItem* result = head_item;
        head_item = head_item->next_Item;
        result->next_Item = nullptr;
        return result;
    }
    BaseItem* curr = this->head_item->next_Item;
    BaseItem* prev = this->head_item;
    while(curr) {
        if(curr->canUse(this->obj, nullptr)) {
            prev->next_Item = curr->next_Item;
            // curr->next_Item = head_item;
            // head_item = curr;
            BaseItem* result = curr;
            result->next_Item = nullptr;
            this->count_item--;
            return result;
        }
        prev = curr;
        curr = curr->next_Item;
    }
    return nullptr;
}
BaseItem* BaseBag::get( ItemType itemType ) {
    if(this->head_item == nullptr) return nullptr;
    if(this->head_item->getType() == itemType) return head_item;
    
    BaseItem* curr = this->head_item->next_Item;
    BaseItem* prev = this->head_item;
    while(curr) {
        if(curr->getType() == itemType) {
            prev->next_Item = curr->next_Item;
            curr->next_Item = head_item;
            head_item = curr;
            return head_item;
        }
        prev = curr;
        curr = curr->next_Item;
    }
    return nullptr;
}
string BaseBag::str () const {
    string result = "Bag[count=";
    string type[5] = {"MagicBook", "EnergyDrink", "FirstAid", "ExcemptionCard", "PassingCard"};
    result += to_string(this->count_item);
    result += ";";
    BaseItem* traverse = this->head_item;
    while(traverse) {
        result += type[traverse->getType()];
        traverse = traverse->next_Item;
        if(traverse) result += ",";
    }
    result += "]";
    return result;
}
//here finish bag 
BaseItem* BaseBag::del_item() {
    if(head_item == nullptr) return nullptr;
    BaseItem* to_del = head_item;
    head_item = head_item->next_Item;
    this->count_item--;
    to_del->next_Item = nullptr;
    return to_del;
}
//      3.13 Program class      ////////////////////////////////////////////////////////////////////////
StudyPinkProgram::StudyPinkProgram(const string & config_file_path) {
    this->config = new Configuration(config_file_path);
    this->arr_mv_objs = new ArrayMovingObject(this->config->max_num_moving_objects);
    this->map = new Map(this->config->map_num_rows, this->config->map_num_cols, this->config->num_walls, this->config->arr_walls, this->config->num_fake_walls, this->config->arr_fake_walls);

    this->sherlock = new Sherlock(1, this->config->sherlock_moving_rule, this->config->sherlock_init_pos, this->map, this->config->sherlock_init_hp, this->config->sherlock_init_exp);
    this->watson = new Watson(2, this->config->watson_moving_rule, this->config->watson_init_pos, this->map, this->config->watson_init_hp, this->config->watson_init_exp);
    this->criminal = new Criminal(0,this->config->criminal_init_pos, this->map, this->sherlock, this->watson);

    this->arr_mv_objs->add(criminal);
    this->arr_mv_objs->add(sherlock);
    this->arr_mv_objs->add(watson);
    SW_win = false;

}

bool StudyPinkProgram::isStop () const {
    return (this->watson->get_hp() == 0 || this->sherlock->get_hp() == 0 || SW_win 
    || this->sherlock->getCurrentPosition().isEqual(this->criminal->getCurrentPosition()) || this->watson->getCurrentPosition().isEqual(this->criminal->getCurrentPosition()));
}

StudyPinkProgram::~StudyPinkProgram(){
    
}

//additional, delete after debug////////////////////////////
void Character::setEXP(int tem) {
    this->exp = tem;
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////