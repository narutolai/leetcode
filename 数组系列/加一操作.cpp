// 给一个整数加1，放在数组里
// [ 1, 2, 3 ]
// 	[1, 2, 4]

// 	[9]
// 	[1, 0]

// 	[1, 9]
// 	[2, 0]
#include <iostream>
#include <vector>
	using namespace std;
int main(int argc, char const *argv[])
{

	vector<int> number = {9};
	int i = number.size() - 1;
	int sum = 10;
	while (sum == 10 && i >= 0)
	{
		sum = number[i] + 1;
		number[i] = sum % 10;
		i--;
	}

	if (sum == 10 && i == -1)
	{
		vector<int> result(number.size() + 1, 0);
		result[0] = 1;
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;
	}
	else
		for (int i = 0; i < number.size(); i++)
			cout << number[i] << endl;
	return 0;
}
