#include <iostream>
#include "string.h"
using namespace std;
int main()
{
	wg::String s1("hello");
	s1.PushBack(' ');
	s1.PushBack('w');
	cout << s1 << endl;

	return 0;
}