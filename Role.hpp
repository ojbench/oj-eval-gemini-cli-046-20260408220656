#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    //uncompleted, you should add code into this class
    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        //WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health,attack;
        bool alive,defensive;
        //you only need to define aliveNumber here.
        inline static int aliveNumber = 0;
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED（实例化）.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        //the function you need to implement or define is as follows.
        //(1) getAliveNumber
        static int getAliveNumber() {
            return aliveNumber;
        }
        //(2) Constructor
        Base(const std::string& name, const int health, const int attack)
            : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }
        virtual ~Base() {
            if (alive) {
                aliveNumber--;
            }
        }
        //(3) launch_attack
        virtual void launch_attack(Base* target) = 0;
        //(4) defend
        virtual void defend(bool flag) = 0;

        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }
    };

    class Fighter:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Caster*>(target)) {
            multiplier = 2;
        }
        int damage_to_target = 0;
        int damage_to_attacker = 0;
        if (!target->defensive) {
            damage_to_target = this->attack * multiplier;
        } else {
            damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            damage_to_attacker = target->attack;
        }
        
        target->health -= damage_to_target;
        this->health -= damage_to_attacker;
        
        if (target->health <= 0) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (this->health <= 0) {
            this->alive = false;
            Base::aliveNumber--;
        }
        
        if (!target->alive && !this->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
            std::cout << "Fighter " << this->name << " is killed\n";
        } else if (!target->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
        } else if (!this->alive) {
            std::cout << "Fighter " << this->name << " is killed\n";
        }
    }

    void Protector::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Fighter*>(target)) {
            multiplier = 2;
        }
        int damage_to_target = 0;
        int damage_to_attacker = 0;
        if (!target->defensive) {
            damage_to_target = this->attack * multiplier;
        } else {
            damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            damage_to_attacker = target->attack;
        }
        
        target->health -= damage_to_target;
        this->health -= damage_to_attacker;
        
        if (target->health <= 0) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (this->health <= 0) {
            this->alive = false;
            Base::aliveNumber--;
        }
        
        if (!target->alive && !this->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
            std::cout << "Protector " << this->name << " is killed\n";
        } else if (!target->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
        } else if (!this->alive) {
            std::cout << "Protector " << this->name << " is killed\n";
        }
    }

    void Caster::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Protector*>(target)) {
            multiplier = 2;
        }
        int damage_to_target = 0;
        int damage_to_attacker = 0;
        if (!target->defensive) {
            damage_to_target = this->attack * multiplier;
        } else {
            damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            damage_to_attacker = 0;
        }
        
        target->health -= damage_to_target;
        this->health -= damage_to_attacker;
        
        if (target->health <= 0) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (this->health <= 0) {
            this->alive = false;
            Base::aliveNumber--;
        }
        
        if (!target->alive && !this->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
            std::cout << "Caster " << this->name << " is killed\n";
        } else if (!target->alive) {
            std::string target_role = "";
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed\n";
        } else if (!this->alive) {
            std::cout << "Caster " << this->name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP
