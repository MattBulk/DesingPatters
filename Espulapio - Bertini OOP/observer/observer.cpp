#include "observer.h"

#include <list>

class GameCharacter {
public:
    GameCharacter() {}
    virtual ~GameCharacter() {}

    void move(int x, int y) {
        posX += x;
        posY += y;
    }

    int getPosX() const {
        return(posX);
    }

    void setPosX(int posX) {
        this->posX = posX;
    }

    int getPosY() const {
        return(posY);
    }

    void setPosY(int posY) {
        this->posY = posY;
    }

private:
 int posX, posY;
};


class Display {
public:
    virtual ~Display() { }

    virtual void draw() = 0;
};


class VideogameMapView : public Display {
public:
    VideogameMapView(GameCharacter *gc) {
        this->subject = gc;
    }

    virtual void draw() override {
        print("posX ", x);
        print("posY ", y);
    }

private:
    int x, y;

    GameCharacter *subject;
};

class MiniMapView : public Display {
public:
    MiniMapView(GameCharacter *gc) {
        this->subject = gc;
    }

    virtual void draw() override {
        print("posX ", x);
        print("posY ", y);
    }

private:
    int x, y;
    bool visible;

    GameCharacter *subject;
};

// 3.1 Observer pull

class Observer {
public:
    virtual ~Observer() {}

    virtual void update() = 0;

    virtual void attach() = 0;      // pull cannot need parameters
    virtual void detach() = 0;
};

class Subject {
public:
    virtual ~Subject() {}

    virtual void subscribe(Observer *ob) = 0;
    virtual void unsubscribe(Observer *ob) = 0;

    virtual void notify() = 0;
};

class GameCharacterC : public Subject {
public:
    GameCharacterC() {
        posX = posY = 0;
    }
    virtual ~GameCharacterC() {

    }

    void move(int x, int y) {
        posX += x;
        posY += y;
        notify();
    }

    virtual void subscribe(Observer *ob) override {
        observers.push_back(ob);
    }

    virtual void unsubscribe(Observer *ob) override {
        observers.remove(ob);
    }

    virtual void notify() override {
        for(auto &&note : observers) {
            note->update();
        }
    }

    int getPosX() const {
        return(posX);
    }

    void setPosX(int posX) {
        this->posX = posX;
        notify();
    }

    int getPosY() const {
        return(posY);
    }

    void setPosY(int posY) {
        this->posY = posY;
        notify();
    }

private:
 int posX, posY;
 std::list<Observer *> observers;

};

class VideogameMapViewC : public Observer, public Display {
public:
    VideogameMapViewC(GameCharacterC *gc) {
        this->subject = gc;
        attach();
    }

    ~VideogameMapViewC() {
        detach();
    }

    virtual void draw() override {
        print("Video posX ", x);
        print("Video posY ", y);
    }

    virtual void update() override {
        this->x = subject->getPosX();
        this->y = subject->getPosY();
        draw();
    }

    virtual void attach() {
        subject->subscribe(this);
    }

    virtual void detach() {
        subject->unsubscribe(this);
    }
private:
    int x, y;

    GameCharacterC *subject;
};

void observerPullExample() {
 
    GameCharacterC *hero = new GameCharacterC();
    VideogameMapViewC map(hero);

    hero->move(100, 100);
    map.detach();
    hero->move(200, 200);
}

// 3.2 Observer push
class Observer2 {
public:
    virtual ~Observer2() {}

    virtual void update(int x, int y) = 0;

    virtual void attach() = 0;      // pull cannot need parameters
    virtual void detach() = 0;
};

class Subject2 {
public:
    virtual ~Subject2() {}

    virtual void subscribe(Observer2 *ob) = 0;
    virtual void unsubscribe(Observer2 *ob) = 0;

    virtual void notify() = 0;
};

class GameCharacter2 : public Subject2 {
public:
    GameCharacter2() {
        posX = posY = 0;
    }
    virtual ~GameCharacter2() {

    }

    void move(int x, int y) {
        posX += x;
        posY += y;
        notify();
    }

    virtual void subscribe(Observer2 *ob) override {
        observers.push_back(ob);
    }

    virtual void unsubscribe(Observer2 *ob) override {
        observers.remove(ob);
    }

    virtual void notify() override {
        for(auto &&note : observers) {
            note->update(posX, posY);
        }
    }

    int getPosX() const {
        return(posX);
    }

    void setPosX(int posX) {
        this->posX = posX;
        notify();
    }

    int getPosY() const {
        return(posY);
    }

    void setPosY(int posY) {
        this->posY = posY;
        notify();
    }

private:
 int posX, posY;
 std::list<Observer2 *> observers;

};

class VideogameMapView2 : public Observer2, public Display {
public:
    VideogameMapView2(GameCharacter2 *gc) {
        this->subject = gc;
        attach();
    }

    ~VideogameMapView2() {
        detach();
    }

    virtual void draw() override {
        print("Video posX ", x);
        print("Video posY ", y);
    }

    virtual void update(int x, int y) override {
        this->x = x;
        this->y = y;
        draw();
    }

    virtual void attach() {
        subject->subscribe(this);
    }

    virtual void detach() {
        subject->unsubscribe(this);
    }
private:
    int x, y;

    GameCharacter2 *subject;
};

void observerPushExample() {
    GameCharacter2 *hero = new GameCharacter2();
    VideogameMapView2 map(hero);

    hero->move(100, 100);
    map.detach();
    hero->move(200, 200);    
}

// 3.3 Observer Multi
class SubjectMulti;
class ObserverMulti {
public:
    virtual ~ObserverMulti() {}

    virtual void update(SubjectMulti *theChangedSubject) = 0;

    virtual void attach() = 0;      // pull cannot need parameters
    virtual void detach() = 0;
};

class SubjectMulti {
public:
    virtual ~SubjectMulti() {}

    virtual void subscribe(ObserverMulti *ob) = 0;
    virtual void unsubscribe(ObserverMulti *ob) = 0;

    virtual void notify() = 0;
};

class GameCharacterM : public SubjectMulti {
public:
    GameCharacterM(const std::string &name) {
        this->name = name;
        posX = posY = 0;
    }
    virtual ~GameCharacterM() {

    }

    void move(int x, int y) {
        posX += x;
        posY += y;
        notify();
    }

    virtual void subscribe(ObserverMulti *ob) override {
        observers.push_back(ob);
    }

    virtual void unsubscribe(ObserverMulti *ob) override {
        observers.remove(ob);
    }

    virtual void notify() override {
        for(auto &&note : observers) {
            note->update(this);
        }
    }

    int getPosX() const {
        return(posX);
    }

    void setPosX(int posX) {
        this->posX = posX;
        notify();
    }

    int getPosY() const {
        return(posY);
    }

    void setPosY(int posY) {
        this->posY = posY;
        notify();
    }

    std::string getName() const {
      return(name);
    }

private:
    std::string name;
    int posX, posY;
    std::list<ObserverMulti *> observers;

};

class VideogameMapViewM : public ObserverMulti, public Display {
public:
    VideogameMapViewM(GameCharacterM *gc) {
        this->subject = gc;
        attach();
    }

    ~VideogameMapViewM() {
        detach();
    }

    virtual void draw() override {
        print("Video posX ", x);
        print("Video posY ", y);
    }

    virtual void update(SubjectMulti *subject) override {
        GameCharacterM *sub = static_cast<GameCharacterM*>(subject);
        this->x = sub->getPosX();
        this->y = sub->getPosY();
        draw();
    }

    virtual void attach() {
        subject->subscribe(this);
    }

    virtual void detach() {
        subject->unsubscribe(this);
    }
private:
    int x, y;
    GameCharacterM *subject;
};

class VideogameUI : public ObserverMulti, public Display {
public:
    VideogameUI(GameCharacterM *gc) {
        this->subject = gc;
        attach();
    }

    ~VideogameUI() {
        detach();
    }

    virtual void draw() override {
        print("GameCharacter name ", name);
    }

    virtual void update(SubjectMulti *subject) override {
        GameCharacterM *sub = static_cast<GameCharacterM*>(subject);

        this->name = sub->getName();
        draw();
    }

    virtual void attach() {
        subject->subscribe(this);
    }

    virtual void detach() {
        subject->unsubscribe(this);
    }
private:
    std::string name;
    GameCharacterM *subject;
};


void observerMultiExample() {
    GameCharacterM *hero = new GameCharacterM("Player1");
    VideogameMapViewM map(hero);
    VideogameUI ui(hero);

    hero->move(100, 100);
    map.detach();
    hero->move(200, 200);


}