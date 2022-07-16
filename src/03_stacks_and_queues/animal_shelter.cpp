// Animal Shelter: An animal shelter, which holds only dogs and cats, operates
// on a strictly "first in, first out" basis. People must adopt either the
// "oldest" (based on arrival time) of all animals at the shelter, or they can
// select whether they would prefer a dog or a cat (and will receive the oldest
// animal of that type). They cannot select which specific animal they would
// like. Create the data structures to maintai n this system and implement
// operations such as enqueue, dequeueAny, dequeueDog, and dequeueCat. You may
// use the built-in LinkedList data structure.

#include <list>
#include <memory>
#include <string>

// Solution
// ------------------------------------------------------------------------------------------------

enum class AnimalType { kUnknown, kDog, kCat };

class Animal {
 public:
  explicit Animal(const std::string &n) : name(n), type(AnimalType::kUnknown) {}
  virtual ~Animal() {}

  void setOrder(int o) { order = o; }
  int getOrder() { return order; }

  AnimalType getType() { return type; }

  const std::string &getName() { return name; }

  /* Compare orders of animals to return the older item. */
  bool isOlderThan(Animal a) { return order < a.getOrder(); }

 protected:
  std::string name;
  AnimalType type;

 private:
  int order;
};

class Dog : public Animal {
 public:
  Dog(const std::string &n) : Animal(n) { type = AnimalType::kDog; }
};

class Cat : public Animal {
 public:
  Cat(const std::string &n) : Animal(n) { type = AnimalType::kCat; }
};

class AnimalQueue {
 public:
  void enqueue(std::shared_ptr<Animal> a) {
    /* Order is used as a sort of timestamp, so that we can compare the
     * insertion order of a dog to a cat. */
    a->setOrder(order);
    order++;

    if (a->getType() == AnimalType::kDog) {
      dogs.push_front(std::dynamic_pointer_cast<Dog>(a));
    } else if (a->getType() == AnimalType::kCat) {
      cats.push_front(std::dynamic_pointer_cast<Cat>(a));
    }
  }

  std::shared_ptr<Dog> dequeueDog() {
    auto d = dogs.back();
    dogs.pop_back();
    return d;
  };

  std::shared_ptr<Cat> dequeueCat() {
    auto c = cats.back();
    cats.pop_back();
    return c;
  };

  std::shared_ptr<Animal> dequeueAny() {
    /* Look at tops of dog and cat queues, and pop the queue with the oldest
     * value. */
    if (dogs.size() == 0) {
      return dequeueCat();
    } else if (cats.size() == 0) {
      return dequeueDog();
    }
    auto dog = dogs.back();
    auto cat = cats.back();
    if (dog->isOlderThan(*cat)) {
      return dequeueDog();
    } else {
      return dequeueCat();
    }
  }

 private:
  std::list<std::shared_ptr<Dog>> dogs;
  std::list<std::shared_ptr<Cat>> cats;
  int order = 0;  // acts as timestamp
};

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(AnimalShelterTest, Trivial) {
  AnimalQueue animals;
  animals.enqueue(std::make_shared<Dog>("dog_1"));
  animals.enqueue(std::make_shared<Dog>("dog_2"));
  animals.enqueue(std::make_shared<Cat>("cat_1"));
  animals.enqueue(std::make_shared<Dog>("dog_3"));
  animals.enqueue(std::make_shared<Cat>("cat_2"));
  animals.enqueue(std::make_shared<Cat>("cat_3"));
  auto any = animals.dequeueAny();
  EXPECT_EQ(any->getName(), "dog_1");
  auto cat = animals.dequeueCat();
  EXPECT_EQ(cat->getName(), "cat_1");
  auto dog = animals.dequeueDog();
  EXPECT_EQ(dog->getName(), "dog_2");
}
