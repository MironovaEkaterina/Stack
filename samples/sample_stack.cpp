#include "StackQueue.h"
#include <string>

char bracket_pair(char bracket) {
	switch (bracket) {
	case '}':return '{';
	case ')':return '(';
	case ']':return '[';
	}

}

int main(int argc, char** argv){
	if (argc > 1) {
		std::string s(argv[1]);
		Stack<char> stack;
		char* rez = "Brackets are correct";
		for (int i = 0; i < s.size(); i++) {
			if ((s[i] == '{') || (s[i] == '(') || (s[i] == '['))
				stack.push(s[i]);
			if ((s[i] == '}') || (s[i] == ')') || (s[i] == ']'))
				if (stack.empty() != 0) {
					rez = "Brackets are not correct";
					break;
				}
				else
					if (stack.top() == bracket_pair(s[i]))
						stack.pop();
					else {
						rez = "Brackets are not correct";
						break;
					}
		}
		if (stack.empty()!=1) rez = "Brackets are not correct";
		std::cout << rez;
	}
	return 0;
}