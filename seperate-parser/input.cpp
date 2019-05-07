#include <bits/stdc++.h>
using namespace std;

int main() {
	int x; cin >> x;
	int y = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < 16; j++) {
			y++;
			x--;
		}
	}
	cout << y << '\n';
}