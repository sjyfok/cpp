#include <iostream>
using namespace std;

// �ڴ˴�������Ĵ���
class Animal
{
public:
	virtual ~Animal()
	{
		
	}
	static int number;
};




class  Dog : public Animal
{
public:
	Dog()
	{
		Animal::number++;
		number++;
	}
	~Dog()
	{
		number--;
		Animal::number--;
	}
	static int number;
};

class Cat : public Animal
{
public:
	Cat()
	{
		Animal::number++;
		number++;
	}
	~Cat()
	{
		number--;
		Animal::number--;
	}
	static int number;
};

int Animal::number = 0;
int Cat::number = 0;
int Dog::number = 0;

void print() {
	cout << Animal::number << " animals in the zoo, " << Dog::number << " of them are dogs, " << Cat::number << " of them are cats" << endl;
}



int main() {
	print();
	Dog d1, d2;
	Cat c1;
	print();
	Dog* d3 = new Dog();
	Animal* c2 = new Cat;
	Cat* c3 = new Cat;
	print();
	delete c3;
	delete c2;
	delete d3;
	print();
}