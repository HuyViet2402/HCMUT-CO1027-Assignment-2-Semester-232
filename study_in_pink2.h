/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Robot;
class Character;
class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };
int Manhattan_Dis(Position P1, Position P2);
int sum_Manhattan_dis(Position W, Position S, Position to_compare);
BaseItem* Create_Reward(Robot* robot);
bool Type_canUse(ItemType type, Character* CHAR);

class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    // MapElement();
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
    friend class TestStudyInPink;
public:
    Path();
};

class Wall : public MapElement {
    friend class TestStudyInPink;
public:
    Wall();
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;
private:
    int req_exp;
public:
    FakeWall();
    FakeWall ( int in_req_exp );
    int getReqExp() const;
};

class Map {
    friend class TestStudyInPink;
private:
    int num_rows, num_cols;
    MapElement*** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls); //: num_rows(num_rows), num_cols(num_cols);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const;
    int get_num_rows();
    int get_num_cols();
};

class Position {
    friend class TestStudyInPink;
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    void set_RC(string str_in);
    string str() const;
    
    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position& in_Pos) const;
};

class MovingObject {
    friend class TestStudyInPink;
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    string getName() const;
};

class Character : public MovingObject{
    friend class TestStudyInPink;
protected:
    int hp, exp;
public:
    BaseBag* bag;
    Character(int index, const Position pos, Map * map, const string & name="");

    int get_hp() const;
    int get_exp() const;
    void change_hp(double diff);
    void change_exp(double diff);
    void check_and_set_hp();
    void check_and_set_exp();

    void setEXP(int tem);
};


bool check_and_set(int& hp_exp, int max);

class Sherlock : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    int next_move;
    string moving_rule;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    void move_to_criminal(Position crimnal_pos);
    
    // ...
};

class Watson : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    int next_move;
    string moving_rule;
    
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;

    
    // ...
};

class Criminal : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    Sherlock* sherlock;
    Watson* watson;
    Position prev_pos;
public:
    int steps_create_robot;
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getNextPosition();
    void move();
    string str() const;
    int distance_to_Criminal(Position to_Compare);
    Position getPrevPostion();
    // ...
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ArrayMovingObject {
    friend class TestStudyInPink;
private:
    // TODO
    MovingObject **arr_mv_objs;
    int count, capacity;
public:
    bool had_Robot;
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Configuration {
    friend class StudyPinkProgram;
    friend class TestStudyInPink;
private:
    // TODO
    int map_num_rows, map_num_cols, max_num_moving_objects, num_walls, num_fake_walls, sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp, num_steps;
    Position *arr_walls, *arr_fake_walls, sherlock_init_pos, watson_init_pos, criminal_init_pos;
    string sherlock_moving_rule, watson_moving_rule, str_arr_walls, str_arr_fake_walls;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Robot : public MovingObject{
    friend class TestStudyInPink;
protected:
    int create_Robot;
    Criminal* criminal;

    RobotType Type;
    BaseItem* item;
public:
    Robot(int index, const Position & init_pos, Map * map);
    virtual int getDistance(Character* WorS = nullptr) const = 0;
    RobotType getType();
    BaseItem* getReward();
};

class RobotC : public Robot{
    friend class TestStudyInPink;
public:
    RobotC( int index , const Position & init_pos , Map * map , Criminal * criminal );
    Position getNextPosition();
    void move();
    string str() const;
    int getDistance(Character* WorS = nullptr) const;
};

class RobotS : public Robot{
    friend class TestStudyInPink;
private:
    Sherlock * sherlock;
public:
    RobotS ( int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock );
    Position getNextPosition();
    void move();
    string str() const;
    int getDistance(Character* WorS = nullptr) const;
};

class RobotW : public Robot{
    friend class TestStudyInPink;
private:
    Watson * watson;
public:
    RobotW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson );
    Position getNextPosition();
    void move();
    string str() const;
    int getDistance(Character* WorS = nullptr) const;
};

class RobotSW : public Robot{
    friend class TestStudyInPink;
private:
    Sherlock * sherlock;
    Watson * watson;
public:
    RobotSW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Sherlock * sherlock , Watson * watson );
    Position getNextPosition();
    void move();
    string str() const;
    int getDistance(Character* WorS = nullptr) const;
};

// Robot, BaseItem, BaseBag,...
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BaseItem {
    friend class TestStudyInPink;
protected:
    ItemType Item;
public:
    ItemType getType();
    virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use( Character * obj , Robot * robot ) = 0;
    virtual BaseItem* clone() const = 0;
    BaseItem* next_Item;
};
class ExcemptionCard : public BaseItem {
    friend class TestStudyInPink;
public:
    ExcemptionCard();
    ExcemptionCard* clone() const;
    bool canUse ( Character * obj , Robot * robot );
    void use( Character * obj , Robot * robot );
};

class PassingCard : public BaseItem {
    friend class TestStudyInPink;
private:
    string challenge;
public:
    PassingCard(string in_challenge);
    PassingCard* clone() const;
    bool canUse ( Character * obj , Robot * robot );
    void use( Character * obj , Robot * robot );
};

class MagicBook : public BaseItem {
    friend class TestStudyInPink;
public:
    MagicBook();
    MagicBook* clone() const;
    bool canUse ( Character * obj , Robot * robot );
    void use( Character * obj , Robot * robot );
};

class EnergyDrink : public BaseItem {
    friend class TestStudyInPink;
public:
    EnergyDrink();
    EnergyDrink* clone() const;
    bool canUse ( Character * obj , Robot * robot );
    void use( Character * obj , Robot * robot );
};

class FirstAid : public BaseItem {
    friend class TestStudyInPink;
public:
    FirstAid();
    FirstAid* clone() const;
    bool canUse ( Character * obj , Robot * robot );
    void use( Character * obj , Robot * robot );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BaseBag {
    friend class TestStudyInPink;
protected:
    BaseItem* head_item;
    int max_item, count_item;
    Character* obj;
public:
    BaseBag();
    virtual bool insert ( BaseItem * item ); 
    virtual BaseItem * get (); 
    virtual BaseItem * get( ItemType itemType ); 
    virtual string str () const ;
    virtual BaseItem* del_item();
    int getCount();
};

class SherlockBag : public BaseBag {
    friend class TestStudyInPink;
protected:
public:
    SherlockBag(Sherlock* in_sherlock);
};

class WatsonBag : public BaseBag {
    friend class TestStudyInPink;
protected:
public:
    WatsonBag(Watson* in_watson);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;

    bool SW_win;
public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    bool move_and_meet(MovingObject* obj_1, MovingObject* obj_2, string name_1, string name_2) {
        if(obj_1->getName() != name_1 && obj_1->getName() != name_2) 
            return false;

        if(obj_2->getName() != name_1 && obj_2->getName() != name_2) 
            return false;
        
        if(obj_1->getName() == obj_2->getName())
            return false;
        return obj_1->getCurrentPosition().isEqual(obj_2->getCurrentPosition());
    }
    ~StudyPinkProgram();
    void run(bool verbose) { //change run
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                if (isStop()) {
                    break;
                }
                MovingObject* obj_i = arr_mv_objs->get(i); //change get and isValid
                Position prev = obj_i->getCurrentPosition();
                // if(obj_i->getNextPosition().isEqual(Position::npos)) {
                //     obj_i->move();
                //     printInfo(istep, i, OUTPUT);
                //     continue;
                // }
                obj_i->move();
                for(int j = 0; j < arr_mv_objs->size(); j++) {
                    bool fixed = false;
                    MovingObject* obj_j = arr_mv_objs->get(j);
                    Robot* robot = dynamic_cast<Robot*>(obj_j);
                    if(robot == nullptr)
                        robot = dynamic_cast<Robot*>(obj_i);
                    
                    //sherlock meet robot//////////////////////////////////////////////////////////////////////////////
                    if(move_and_meet(obj_i, obj_j, "Sherlock", "RobotS")) {
                        bool excemption = Type_canUse(EXCEMPTION_CARD, sherlock);
                        BaseItem *toUse;
                        if(excemption) {
                            excemption = false;
                            toUse = sherlock->bag->get(EXCEMPTION_CARD);
                            if(toUse != nullptr) {
                                excemption = true;
                                toUse = sherlock->bag->del_item();
                                delete toUse;
                            }
                        }
                        if(sherlock->get_exp() > 400) {
                            sherlock->bag->insert(robot->getReward()->clone());
                        }
                        else if(!excemption){
                            sherlock->change_exp(-0.1 * sherlock->get_exp());
                            fixed = true;
                            sherlock->check_and_set_exp();
                            toUse = sherlock->bag->get();
                            if(toUse != nullptr) {
                                toUse->use(sherlock, nullptr);
                                delete toUse;
                            }
                        }
                        toUse = sherlock->bag->get();
                        if(toUse != nullptr) {
                            toUse->use(sherlock, nullptr);
                            fixed = true;
                            delete toUse;
                        }
                    }
                    else if(move_and_meet(obj_i, obj_j, "Sherlock", "RobotW")) {
                        sherlock->bag->insert(robot->getReward()->clone());
                        BaseItem* toUse = sherlock->bag->get();
                        if(toUse != nullptr) {
                            toUse->use(sherlock, nullptr);
                            fixed = true;
                            delete toUse;
                        }
                    }
                    else if(move_and_meet(obj_i, obj_j, "Sherlock", "RobotSW")) {
                        bool excemption = Type_canUse(EXCEMPTION_CARD, sherlock);
                        BaseItem *toUse;
                        if(excemption) {
                            excemption = false;
                            toUse = sherlock->bag->get(EXCEMPTION_CARD);
                            if(toUse != nullptr) {
                                excemption = true;
                                toUse = sherlock->bag->del_item();
                                delete toUse;
                            }
                        }
                        if(sherlock->get_exp() > 300 && sherlock->get_hp() > 335) {
                            sherlock->bag->insert(robot->getReward()->clone());
                        }
                        else if(!excemption){
                            sherlock->change_exp(-0.15 * sherlock->get_exp()); sherlock->change_hp(-0.15 * sherlock->get_hp());
                            fixed = true;
                            sherlock->check_and_set_exp(); sherlock->check_and_set_hp();
                        }
                        toUse = sherlock->bag->get();
                        if(toUse != nullptr) {
                            fixed = true;
                            toUse->use(sherlock, nullptr);
                            delete toUse;
                        }
                    }
                    else if(move_and_meet(obj_i, obj_j, "Sherlock", "RobotC")) {
                        if(sherlock->get_exp() > 500) {
                            this->SW_win = true;
                            this->sherlock->move_to_criminal(this->criminal->getCurrentPosition());
                            break;
                        }
                        else {
                            sherlock->bag->insert(robot->getReward()->clone());
                        }
                        BaseItem* toUse = sherlock->bag->get();
                        if(toUse != nullptr) {
                            toUse->use(sherlock, nullptr);
                            fixed = true;
                            delete toUse;
                        }
                    }
                    //watson meet robot//////////////////////////////////////////////////////////////////////////////
                    else if(move_and_meet(obj_i, obj_j, "Watson", "RobotS")) {

                    }
                    else if(move_and_meet(obj_i, obj_j, "Watson", "RobotW")) {
                        bool passing = Type_canUse(PASSING_CARD, watson);
                        BaseItem *toUse = watson->bag->get(PASSING_CARD);
                        if(passing && toUse) {
                            if(toUse != nullptr) {
                                toUse->use(watson, robot);
                                toUse = watson->bag->del_item();
                                delete toUse;
                                watson->bag->insert(robot->getReward()->clone()); 
                            }
                        }
                        else {
                            if(watson->get_hp() > 350) {
                                watson->bag->insert(robot->getReward()->clone());
                            }
                            else {
                                watson->change_hp(-0.05 * watson->get_hp());
                                fixed = true;
                                watson->check_and_set_hp();
                            }
                            toUse = watson->bag->get();
                            if(toUse != nullptr && toUse->getType() != PASSING_CARD) {
                                toUse->use(watson, nullptr);
                                fixed = true;
                                delete toUse;
                            }
                        }
                    }
                    else if(move_and_meet(obj_i, obj_j, "Watson", "RobotSW")) {
                        // continue here 2/5/2024
                        bool passing = Type_canUse(PASSING_CARD, watson);
                        BaseItem *toUse = watson->bag->get(PASSING_CARD);
                        if(passing && toUse) {
                            if(toUse != nullptr) {
                                toUse->use(watson, robot);
                                toUse = watson->bag->del_item();
                                delete toUse;
                                watson->bag->insert(robot->getReward()->clone()); 
                            }
                        }
                        else {
                            if(watson->get_exp() > 600 && watson->get_hp() > 165) {
                                watson->bag->insert(robot->getReward()->clone());
                            }
                            else {
                                watson->change_hp(-0.15 * watson->get_hp()); 
                                fixed = true;
                                watson->change_exp(-0.15 * watson->get_exp());
                                watson->check_and_set_hp(); 
                                watson->check_and_set_exp();
                            }
                            toUse = watson->bag->get();
                            if(toUse != nullptr && toUse->getType() != PASSING_CARD) {
                                toUse->use(watson, nullptr);
                                fixed = true;
                                delete toUse;
                            }
                        }
                    }
                    else if(move_and_meet(obj_i, obj_j, "Watson", "RobotC")) {
                        watson->bag->insert(robot->getReward()->clone());
                        BaseItem* toUse = watson->bag->get();
                        if(toUse != nullptr && toUse->getType() != PASSING_CARD) {
                            toUse->use(watson, nullptr);
                            fixed = true;
                            delete toUse;
                    }
                    //watson meet sherlock///////////////////////////////////////////////////////////////////////////////////////
                    else if(move_and_meet(obj_i, obj_j, "Watson", "Sherlock")) {
                        BaseItem* to_exchange = watson->bag->get(EXCEMPTION_CARD);
                        while(to_exchange) {
                            to_exchange = watson->bag->del_item();
                            sherlock->bag->insert(to_exchange->clone());
                            delete to_exchange;
                            to_exchange = watson->bag->get(EXCEMPTION_CARD);
                        }
                        to_exchange = sherlock->bag->get(PASSING_CARD);
                        while(to_exchange) {
                            to_exchange = sherlock->bag->del_item();
                            watson->bag->insert(to_exchange->clone());
                            delete to_exchange;
                            to_exchange = sherlock->bag->get(PASSING_CARD);
                        }
                    }
                    if (verbose && fixed) {
                        printStep(istep);
                    }
                    if (isStop()) {
                        break;
                    }
                }
                
                if (isStop()) {
                    break;
                }
                // check to create robot
                if(obj_i->getName() == "Criminal" && criminal->steps_create_robot == 0 && !prev.isEqual(criminal->getCurrentPosition())) {
                    if(arr_mv_objs->had_Robot) {
                        int dis_Wat = Manhattan_Dis(prev, watson->getCurrentPosition());
                        int dis_Sher = Manhattan_Dis(prev, sherlock->getCurrentPosition());
                        if(dis_Wat > dis_Sher) {
                            arr_mv_objs->add(new RobotS(arr_mv_objs->size(), prev, map, criminal, sherlock));
                        } else if(dis_Sher > dis_Wat) {
                            arr_mv_objs->add(new RobotW(arr_mv_objs->size(), prev, map, criminal, watson));
                        } else {
                            arr_mv_objs->add(new RobotSW(arr_mv_objs->size(), prev, map, criminal, sherlock, watson));
                        }
                    }   
                    else {
                        arr_mv_objs->add(new RobotC(arr_mv_objs->size(), prev, map, criminal));
                    }
                }
                //sherlock can meet robot and watson at the same time, 2 robot can stand on the same square
                //fight the robot which sherlock or watson meet first
                // At every element: move -> meet -> stop or not -> |||| can creat robot ? create robot (after 1 iteration of istep)
                }
            }
            if (verbose) {
                printStep(istep);
            }
            if (isStop()) {
                break;
            }
        }
        printResult();
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */