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
	auto fn9 = [&i7]{i7=i7<<1; };
	cout << "facet9: " << fn() << endl;


	/*
	capture list :
	[] : do not capture any local variables
	[var_list]: capture a list of variables seperated with ','  e.g.  [name, age, gender];
	[&]: implicit by reference capture list: any vars used in lambda are implicit in local vars 
	[=]: implicit by value capture list: any vars used in lambda are implicit in local vars
	[&, var_val_list]: (e.g.  [&, name, age, gender] )   var_val_list is value capture list; other varable is implicit by reference
	[=, var_ref_list]: (e.g.  [&, name, age, gender] )   var_ref_list is reference capture list; other varable is implicit by value
	*/
}


int main(int argc, char* argv[])
{
	FacetsOfLambda();
	return 0;
}

