//Edwin Arturo Salgado Santana A00842140
#include <iostream>
#include <vector>
//GameObject class
class GameObject {
protected:
    int instanceId;

public:
    GameObject(int id = 0) : instanceId(id) {}

    virtual ~GameObject() {}

    int getId() const {
        return instanceId;
    }
};
//Weapon class
class Weapon : public GameObject {
protected:
    std::string name;
    int baseDamage;

public:
    Weapon(std::string n, int dmg, int id = 0)
        : GameObject(id), name(n), baseDamage(dmg) {}

    virtual void attack() = 0; // método virtual puro

    int getDamage() const {
        return baseDamage;
    }

    std::string getName() const {
        return name;
    }

    virtual ~Weapon() {}
};

//Sword class
class Sword : public Weapon {
private:
    int sharpness;
public:
    Sword(std::string n = "Sword", int dmg = 20, int s=10)
        : Weapon(n, dmg), sharpness(s) {}

    void attack() override {
        std::cout << "Sword attack! Damage: " << baseDamage << std::endl;
    }
};

//Bow class
class Bow : public Weapon {
    public:
        Bow(std::string n = "Bow", int dmg = 15)
            :Weapon(n,dmg) {}
            
        void attack() override
        {
            std::cout << "Bow attack! Damage: " << baseDamage << std::endl;
        }
};

// Stats class
class Stats {
private:
    int health;
    int attackPoints;

public:
    Stats(int hp = 100, int atk = 10)
        : health(hp), attackPoints(atk) {}

    void modifyHealth(int val) {
        health += val;
    }

    int getHealth() const {
        return health;
    }

    int getAttackPoints() const {
        return attackPoints;
    }
};

//Potion class
class Potion : public GameObject {
private:
    std::string name;

public:
    Potion(std::string n = "Health Potion")
        : name(n) {}

    std::string getName() const {
        return name;
    }
};

//Class class
class Class {
private:
   std:: string name;

public:
    Class(std::string n = "Warrior")
        : name(n) {}

    std::string getName() const {
        return name;
    }
};
//SoulMark class
class SoulMark {
private:
    std::string mark;

public:
    SoulMark(std::string m = "Fire")
        : mark(m) {}

    std::string getMark() const {
        return mark;
    }
};

//Guild class
class Guild {
private:
    std::string name;

public:
    Guild(std::string n = "No Guild")
        : name(n) {}

    std::string getName() const {
        return name;
    }
};

//Hero class
class Hero : public GameObject {
private:
    Stats stats;
    Class* heroClass;
    SoulMark soulMark;
    Guild* guild;
    std::string name;
    Weapon* weapon;

public:
    Hero(
        std::string n,
        Class* c,
        Weapon* w,
        Guild *g
    )
        : name(n),
          heroClass(c),
          weapon(w) ,
          stats(100,100),
          guild(g),
          soulMark()
          {}

    void usePotion(Potion p) {
        std::cout << name << " used " << p.getName() << std::endl;
        stats.modifyHealth(30);
        std::cout << "Health increased to: "
             << stats.getHealth() << std::endl;
    }

    void takeDamage(int dmg) {
        stats.modifyHealth(-dmg);
        std::cout << name << " took "
             << dmg << " damage." << std::endl;
        std::cout << "Current HP: "
             << stats.getHealth() << std::endl;
    }

    void attack() {
        if (weapon) {
            weapon->attack();
        }
    }

    void showInfo() {
        std::cout << "====== HERO INFO ======" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Class: " << heroClass->getName() << std::endl;
        std::cout << "Guild: " << guild->getName() << std::endl;
        std::cout << "SoulMark: " << soulMark.getMark() << std::endl;
        std::cout << "Health: " << stats.getHealth() << std::endl;
        std::cout << "Attack: " << stats.getAttackPoints() << std::endl;

        if (weapon)
            std::cout << "Weapon: " << weapon->getName() << std::endl;
    }
    
    void setWeapon(Weapon* newWeapon) {
        weapon = newWeapon;
    }
    
  
    
};


int main()
{
    // =========================
    // Creating objects
    // =========================

    Weapon* sword = new Sword("Excalibur", 50, 5);
    Weapon* bow = new Bow("Longbow", 30);

    Potion* potion = new Potion("Mega Potion");

    Guild* guild = new Guild("Dragon Slayers");

    Class* heroClass = new Class("Knight");

    // Hero starts with sword
    Hero* hero = new Hero(
        "Arthur",
        heroClass,
        sword,
        guild
    );

    // =========================
    // GameObjects vector
    // =========================

    std::vector<GameObject*> objects;

    objects.push_back(sword);
    objects.push_back(bow);
    objects.push_back(potion);
    objects.push_back(hero);

    // =========================
    // Hero info
    // =========================

    hero->showInfo();

    // =========================
    // Hero attacks with sword
    // =========================

    std::cout << "\nHero attacks with sword:\n";
    hero->attack();

    // =========================
    // Hero changes weapon
    // =========================

    std::cout << "\nHero changes weapon to bow\n";

    hero->setWeapon(bow);

    hero->attack();

    // =========================
    // Hero uses potion
    // =========================

    std::cout << "\nHero drinks potion\n";

    hero->usePotion(*potion);

  

    delete sword;
    delete bow;
    delete potion;
    delete guild;
    delete heroClass;
    delete hero;

    return 0;
}
