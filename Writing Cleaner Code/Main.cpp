#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <random>

using namespace std;

/*** Tips for writing cleaner code by Gideon Hoogeveen ***/

/*
Topics:
reduce nesting.
side effects.
dependencies
Single responsibility
early returns.
returning booleans.
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>


using namespace std;

/*** Tips for writing cleaner code by Gideon Hoogeveen ***/

/* Booleans */
/* Boolean operators are < > <= >= && || */

bool is_odd_v1(int x) {
	//x % 2 == 0 produces a truth value (bool)
	if (x % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool is_odd_v2(int x) {
	//directly returns resulting truth value;
	return (x % 2 == 0);
}

//Actually just returns the other bool value
bool is_dead_v1(bool alive) {
	if (alive) {
		return false;
	}
	else {
		return true;
	}
}

//Is the same as
bool is_dead_v2(bool alive) {
	if (alive)
		return false;
	else
		return true;
}

//Is the same as
bool is_dead_v3(bool alive) {
	if (alive)
		return false;

	assert(!alive);
	//From now on you can assume !alive because else the function wouldve returned by now
	return true;
}

//Is the same as
bool is_dead_v4(bool alive) {
	return !alive; //just return the negation of bool input.
}

//boolean return can be stored in a variable to better understand the semantics of every step.
bool dead_and_odd_v1(bool alive, int x) {

	bool dead = is_dead_v4(alive);
	bool odd = is_odd_v2(x);

	return dead && odd;//Now it is really clear what the result of this function is.
}

//The shorter way of writing this is as follows.
//You can also see why proper naming of functions is important.
//The result value of your function is only as clear as the names of the functions is_dead_v4() and is_odd_v2()
bool dead_and_odd_v2(bool alive, int x) {
	return is_dead_v4(alive) && is_odd_v2(x);// is_dead && is_odd
}

bool random_bool() {
	return rand() > (RAND_MAX / 2);
}

bool download_assignment_from_blackboard() {
	cout << "downloading assignment from blackboard"<<endl;
	return random_bool();
}

bool make_assignment() {
	cout << "making assignment"<< endl;
	return random_bool();
}

string convert_assignment_to_pdf() {
	cout << "Converting assignment to pdf";
	if (random_bool())
		return "assignment.pdf";

	return "assignment.gif";
}

bool turn_assignment_in_before_deadline() {
	cout << "turning assignment in before deadline" << endl;
	return random_bool();
}

//A lot of people code like this.
//Nesting a lot of if else makes your code unreadable, hard to understand and very prone to errors.
//As an exercise, try to figure out what this code does. Use a Timer to measure how long it took.
bool make_homework_v1() {
	if (download_assignment_from_blackboard()) {
		if (make_assignment()) {
			string assignment = convert_assignment_to_pdf();
			if (assignment == "assignment.pdf") {
				if (turn_assignment_in_before_deadline()) {
					cout << "You did it! Well done!" << endl;
					return true;
				}
				else {
					cout << "To late. Deadline already over.... :'( "<< endl;
					return false;
				}
			}
			else {
				cout << "Not possible to succesfully create a pdf file."<< endl;
				return false;
			}
		}
		else {
			cout << "Assignment was way to hard and I did not went to all the Hoorcolleges." << endl;
			return false;
		}
	}
	else {
		cout << "Blackboard is down. Impossible to download assignment" << endl;
		return false;
	}
}

//To avoid deep nesting of if, else and else if statements there is a simple recipe you can follow.
//Do something -> It didn't work: STOP,  It worked: GO ON
//Again. measure how long it takes to understand this code.
bool make_homework_v2() {

	//Do something
	bool download_successfull = download_assignment_from_blackboard();
	
	if (!download_successfull) {
		//It didn't work: STOP
		cout << "Blackboard is down. Impossible to download assignment" << endl;
		return false;
	}
	//It worked: GO ON

	//Do Something
	bool succesfully_made_assignment = make_assignment();

	if (!succesfully_made_assignment) {
		//It didn't work: STOP
		cout << "Assignment was way to hard and I did not went to all the Hoorcolleges." << endl;
		return false;
	}
	//It worked: GO ON

	//etc.
	
	string assignment = convert_assignment_to_pdf();

	if (assignment != "assignment.pdf") {
		cout << "Not possible to succesfully create a pdf file." << endl;
		return false;
	}

	bool turned_in_succesfully = turn_assignment_in_before_deadline();

	if (!turned_in_succesfully) {
		cout << "To late. Deadline already over.... :'( " << endl;
		return false;
	}

	//We successfully made it through every step. That means we have made our homework successfully!!!
	cout << "You did it! Well done!" << endl;
	return true;
}
//We know followed a recipe. We made our homework Step by step. Every step is after the previous step.
//Now this also permits us to make our code even shorter.
bool make_homework_v3() {
	if (!download_assignment_from_blackboard()) {
		cout << "Blackboard is down. Impossible to download assignment" << endl;
		return false;
	}

	if (!make_assignment()) {
		cout << "Assignment was way to hard and I did not went to all the Hoorcolleges." << endl;
		return false;
	}

	if (convert_assignment_to_pdf() != "assignment.pdf") {
		cout << "Not possible to succesfully create a pdf file." << endl;
		return false;
	}

	if (!turn_assignment_in_before_deadline()) {
		cout << "To late. Deadline already over.... :'( " << endl;
		return false;
	}

	cout << "You did it! Well done!" << endl;
	return true;
}
/*Note that for every distinct step in the homework making process we used a function to do this step.
This function is abstract in comparison with the different steps. (The only thing this function does is describe the recipe)
This makes it way easier to reason over this function, because all details are put away in the different steps.
make_home_v3() only cares about which steps to take. Not how to take these steps.*/


/*Single Responsibility  (google it)*/

/* Every function/class/method should only have 1 reason to change.   <--- very good coding practice. believe me!
in other words: it should only have 1 taks/ do 1 thing.
If you look at our previous homework example. Try to describe in a very short sentence what it does.

Note: I did not follow this principle 100% in the previous example.
make_home_work_v3() makes you homework,  but also prints everything to the console.
printing to the console and doing the homework are 2 distinct things.
If you want to make your homework without printing to the console, you cannot use this function.
*/


/*Let's bake some pancakes. Eventhough this recipe makes perfect sense, it is very easy to lose yourself in the details.*/
void bake_pancakes_v1() {
	cout << "Take Milk from fridge" << endl;
	cout << "Take Eggs from fridge" << endl;
	cout << "Take flour from cabinet" << endl;
	cout << "Take bowl from cabinet" << endl;
	cout << "Put ingredients in bowl" << endl;
	cout << "Take whisk from cabinet" << endl;
	cout << "Mix ingredients with whish" << endl;
	cout << "Take cookking pan from cabinet" << endl;
	cout << "Put cooking pan on furnace" << endl;
	cout << "Turn on furnace" << endl;
	cout << "Pour dough in cooking pan" << endl;
	cout << "Wait till pancake is done on one side" << endl;
	cout << "Flip pancake acrobatic style." << endl;
	cout << "Wait till pancake is on other side" << endl;
	cout << "Take plate from cabinet" << endl;
	cout << "Put pancake on plate" << endl;
	cout << "Turn off furnace" << endl;
	cout << "Put Syrup on pancake" << endl;
	cout << "Eat pancake" << endl;
	//Although ultimately this function does 1 thing. (baking pancakes). It does a lot of different things to accomplish this task.
	//So many things you can't see in a second what all the steps are.
	//When reading it you easily get lost in the details.
	//What if we want to bake a pancake and not eat it? 
	//What if we want to make 2 pancakes? We do a lot of double work if we execute this function 2 times.
	//What is we want to make poffertjes? We already know how to make dough, but we can only turn it into pancakes now.
}

/*Let's try to make more abstract pancakes now*/

void gather_pancake_ingredients() {
	cout << "Take Milk from fridge" << endl;
	cout << "Take Eggs from fridge" << endl;
	cout << "Take flour from cabinet" << endl;
}

void make_dough() {
	cout << "Take bowl from cabinet" << endl;
	cout << "Put ingredients in bowl" << endl;
	cout << "Take whisk from cabinet" << endl;
	cout << "Mix ingredients with whish" << endl;
}

//We also need the furnace for cooking / baking potential other stuff.
void turn_furnace_on() {
	cout << "Turn on furnace" << endl;
}

void turn_furnace_off() {
	cout << "Turn off furnace" << endl;
}

void put_cooking_pan_on_furnace() {
	cout << "Take cookking pan from cabinet" << endl;
	cout << "Put cooking pan on furnace" << endl;
}

void actual_pancake_baking() {
	cout << "Pour dough in cooking pan" << endl;
	cout << "Wait till pancake is done on one side" << endl;
	cout << "Flip pancake acrobatic style." << endl;
	cout << "Wait till pancake is done on other side" << endl;
	cout << "Take plate from cabinet" << endl;
	cout << "Put pancake on plate" << endl;
}

void bake_pancake() {
	put_cooking_pan_on_furnace();
	turn_furnace_on();
	actual_pancake_baking();
	turn_furnace_off();
}


void eat_pancake() {
	cout << "Put Syrup on pancake" << endl;
	cout << "Eat pancake" << endl;
}

void bake_pancakes_v2() {
	gather_pancake_ingredients();
	make_dough();
	bake_pancake();
	eat_pancake();
}
//As you can see all functions individually are way easier to understand.
//One thing to note is that bake_pancake() is more abstract then i.e. make_dough();
//make_dough() cares about the details of making though. bake_pancake() does not care how everything is done. it just lists the steps
//required to bake a pancake.
/*
Yes, you now have a lot of functions and when programming for the first time it may seem this is a bad thing. This is not true!
Every function now has 1 reason to change. If you want to change the baking process, you now know exactly where to look.
If you want to change the dough making process, you now know where to look.
An other great benefit if Single Responsibility is that all functions are way more reusable.
What do you do if a function does 2 things and in your program you only want 1 of those 2 to be done?? You have a problem.
When those 2 things are split in 2 functions, you can just use the part you need.
*/

//Now we can make functions which bake multiple pancakes. (Not possible with the implementation we began with.)
void bake_multiple_pancakes(int x) {
	put_cooking_pan_on_furnace();
	turn_furnace_on();
	for (int i = 0; i < x; i++) {
		actual_pancake_baking();
	}
	turn_furnace_off();
}

void actually_bread_baking() {
	//Image this does something.
}

//We can make dough to bake bread
void bake_bread() {
	make_dough(); 
	actually_bread_baking();
}

//We can now eat a lot of pancakes which were baked by someone else.
void eat_lots_of_pancakes(int x) {
	for (int i = 0; i < x; i++) {
		eat_pancake();
	}
}

//We can now continiously turn the furnace on and off.
void turn_furnace_on_and_off(int x) {
	for (int i = 0; i < x; i++) {
		turn_furnace_on();
		turn_furnace_off();
	}
}


int bool_example() {
	cout << "1 is odd  v1:" << is_odd_v1(1) << " v2:" << is_odd_v2(1)<<endl;
	cout << "2 is odd  v1:" << is_odd_v1(2) << " v2:" << is_odd_v2(2) << endl;
	cout << "alive:true  is dead: v1:" << is_dead_v1(true) << " v2:" << is_dead_v2(true) << " v3:" << is_dead_v3(true) << " v4:" << is_dead_v4(true) << endl;
	cout << "alive:false  is dead: v1:" << is_dead_v1(false) << " v2:" << is_dead_v2(false) << " v3:" << is_dead_v3(false) << " v4:" << is_dead_v4(false) << endl;
	return 0;
}

int reduce_nesting_example() {
	/*Note: everytime you run make_homework() The function gives an other result, because it uses random numbers
	Normally this is bad practice, because you want a function to behave consistently and always give the same outcome given the same input*/
	cout << "making homework v1. making homework succeeded: (" << make_homework_v1() << ")" << endl;
	cout << "making homework v2. making homework succeeded: (" << make_homework_v2() << ")" << endl;
	cout << "making homework v3. making homework succeeded: (" << make_homework_v3() << ")" << endl;

	return 0;
}

int single_responsibility_example() {
	bake_pancakes_v2();
	return 0;
}


int main() {
	/*Turn examples on and off with comments*/
	bool_example();
	//reduce_nesting_example();
	//single_responsibility_example();
	cin.get();
}