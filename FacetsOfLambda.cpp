#include<vector>
#include<string>
#include<iostream>
#include <algorithm>
using namespace std;
//[capture list] (parameter list) -> return type  { function body }
//here is a list of different ways to use lambda

void FacetsOfLambda(void)
{
	//1 basic use no arguement
	auto fn = []{return 42; };

	cout << "facet1: " << fn() << endl;

	//2 with arglist
	auto fn2 = [](int a, int b){return a + b; };

	cout << "facet2: " << fn2(42, 42) << endl;


	//3 with arglist, a swap
	auto fn3 = [](int &a, int &b){a = a^b; b = a^b; a = a^b; };
	int i = 10, j = 21;
	fn3(i, j);
	//print out : facet3: i:21 j:10 
	cout << "facet3: " << "i:" << i << " j:" << j << endl;

	//4 embedded in STL functions：
	vector<string>text = { "a", "quick", "fox", "jump", "over", "the", "lazy", "dog" };
	stable_sort(text.begin(), text.end(), [](const string a, const string b){return a.size() < b.size(); });
	cout << "facet4: ";
	for (auto i : text) cout << i<<" ";
	cout << endl;
	
	/*
	another way to out put a container like this
	cout << "facet4: ";
	for (auto i : text) cout << i<<" ";
	cout << endl;
	*/
	//5 for_each loop to print a container
	text = { "a", "quick", "fox", "jump", "over", "the", "lazy", "dog" };
	cout << "facet5: ";
	for_each(text.begin(), text.end(), [](const string &s){cout << s << " "; });
	//C++14: for_each(text.begin(), text.end(), [](auto s){cout << s << " "; });

	//6 find how many word in a text with length >3
	stable_sort(text.begin(), text.end(), [](const string a, const string b){return a.size() < b.size(); });
	auto it = find_if(text.begin(), text.end(), [](const string &s){return s.size() > 3; });
	auto count = text.end() - it;
	cout << endl << "facet6: " << count << endl;


	//7 capture list to access local vars
	int i7 = 42;
	auto fn7 = [i7]{return i7; };
	cout << "facet7: " << fn() << endl;
	 
	//8 revisit 6: find how many word in a text with length >3 
	//with access to local variable with capture list:
	int w = 3;
	it = find_if(text.begin(), text.end(), [w](const string &s){return s.size() > w; });
	cout << endl << "facet8: " << count << endl;

	//9 change local vars with reference in capture list
	int i9 = 42;
	auto fn9 = [&i9]{return ++i9; };     //ret 43
	cout << "facet9: " <<"i9= "<<i9<<"  fn9: "<< fn9() << endl;  // output 43

	i9 = 21;
	cout << "facet9: " << fn9() << endl;  //output 22

	//10change local vars with reference in capture list
	//auto fn10 = [i7]{i7 = i7 << 1; }; //this wont compile
	auto i10 = 42;
	auto fn10 = [i10]{return i10; };
	cout << "facet10: " << fn10() << endl;  //not changed
	i10 = 21;
	cout << "facet10: " << fn10() << endl;  //still output 42...!!

	//11 value capture list in loop
	int i11=0;
	auto fn11 = [i11]{cout<<" i11 "<< i11<<" "; };
	auto m11 = { 1, 2, 3, 4 };
	//ops, all print out 0!
	for (auto i : m11) { i11 = i; fn11(); }
	//output: i11 0  i11 0  i11 0  i11 0
	cout << endl;


	/*
	capture list recap:
	[] : do not capture any local variables
	[var_list]: capture a list of variables seperated with ','  e.g.  [name, age, gender];
	[&]: implicit by reference capture list: any vars used in lambda are implicit in local vars 
	[=]: implicit by value capture list: any vars used in lambda are implicit in local vars
	[&, var_val_list]: (e.g.  [&, name, age, gender] )   var_val_list is value capture list; other varable is implicit by reference
	[=, var_ref_list]: (e.g.  [=, &name, &age, &gender] )   var_ref_list is reference capture list; other varable is implicit by value
	*/


	//12 using [=]
	int i12 = 0;
	auto fn12 = [=]{cout  << " i12 " << i12 << " "; };
	auto m12 = { 1, 2, 3, 4 };
	//ops, all print out 0!
	for (auto i : m11) { i12 = i; fn12(); }
	cout << endl;
	// output :  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0
	
	//13 using [&]
	int i13 = 0;
	auto fn13 = [&]{cout << " i13 " << i13 << " "; };
	auto m13 = { 1, 2, 3, 4 };
	//ops, all print out 0!
	for (auto i : m11) { i13 = i; fn13(); }
	cout << endl;
	// output :  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0  i11 0


	//14:  [&, var_val_list]
	int age = 14;
	string name{ "ray" };
	char gender{'M'};
	
	// this wont compile:  auto fn14 = [&, gender]{age++; gender = 'F'; };
	auto fn14 = [&, gender]{ ++age; cout << "facet14" << "age: " << age << "gender: " << gender << endl; };
	cout << "what is age now?  it is:" << age << endl;
	//output what is age now?  it is:14


	//15:  [=, var_ref_list]

	// this wont compile:  auto fn14 = [=, gender]{age++; gender = 'F'; }; //you can not change age now
	auto fn15 = [=, &gender, &name]{ gender = 'F'; name = "Jean"; };
	fn15();
	cout << "facet15" << " gender: " << gender << "name: " << name << endl;
	//output what is age now?  it is:14

}


int main(int argc, char* argv[])
{
	FacetsOfLambda();
	return 0;
}

