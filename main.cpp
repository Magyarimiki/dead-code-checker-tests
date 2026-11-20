#include <functional>

void foo() {}
void bar() {}
void testLambda(int x, std::function<void()> func) {}

void test1(bool x) {
  auto l = [&]() {
	x = true;
	};
  testLambda(1, l);
  if (x) {
	foo();
  }
  else {
	bar();
  }
}

void test2(bool x, bool y) {
  if (x) {
	if (y) {
	  foo();
	}
  }

  if (!x) {
	bar();
  }
}

void test3() {
  bool x = true;
  if (true == x || false) {
	int a = 1;
  }
  else {
	int b = 2; // unreachable
  }
}

void test4(bool x) {
  if (x) {
	x = false;
  }
  else {
	x = true;
  }

  if (x) {
	foo();
  }
  else {
	bar();
  }
}

void test5(bool x) {
  if (x) {
	foo();
  }

  if (!x) {
	bar();
  }
}

void test6(bool x) {
  if (x) {
	return;
  }

  if (x) {
	foo(); // unreachable
  }
}

void test7(bool x, bool y) {
  if (x && y) {
	foo();
  }

  if (x && !y) {
	bar();
  }
}

void test8(bool x) {
  // In the first branch, x becomes false.
  if (x) {
	x = false;
  }

  // If the first if was true, x is now false.
  // If the first if was false, x was already false.
  // Therefore, the second if is always false.
  if (x) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test9(bool x, bool y) {
  if (x) {
	y = true;
  }
  else {
	y = false;
  }

  // The value of y matches the value of x.
  if (x && !y) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test10(bool x, bool y) {
  if (x && y) {
	x = false;
  }

  // If x && y was true, x is now false.
  // If it was not true, then x && y still cannot be true
  // based on the original state? The analysis needs to check this.
  if (x && y) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test11(bool x) {
  if (x) {
	return;
  }

  // After the previous if, x is definitely false.
  if (!x) {
	foo();
  }
  else {
	bar(); // unreachable
  }
}

void test12(bool x, bool y) {
  if (x) {
	if (y) {
	  x = false;
	}
  }

  // We examine the combined effect of the inner condition and the modification.
  if (x && y) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test13(bool x, bool y) {
  if (x || y) {
	x = false;
  }

  if (x && y) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test14() {
  bool x = true;
  bool y = false;

  if (x) {
	y = true;
  }

  if (x && y) {
	x = false;
  }

  if (x) {
	foo(); // unreachable
  }
  else {
	bar();
  }
}

void test15(bool x) {
  if (x) {
	x = false;
  }
  else {
	x = true;
  }

  // We inverted the value of x in both branches.
  // Therefore, the result depends on the original value of x.
  if (x) {
	foo();
  }
  else {
	bar();
  }
}

void test16() {
  bool y = true;
  bool z = false;

  if (y || z) {
	foo();
  }
  else {
	bar(); // unreachable
  }
}

void test17(bool x) {
  if (x) {
	int a = 1;
  }
  else {
	int b = 2;
  }
}

void test18(bool x) {
  if (x) {
	if (x) {
	  int a = 1;
	}
	else {
	  int b = 2; // unreachable
	}
  }
  else {
	if (!x) {
	  int c = 3;
	}
	else {
	  int d = 4; // unreachable
	}
  }
}

void test19() {
  bool x = true;
  bool y = true;
  auto foobar = [&]() {
	x = true;
  };
  testLambda(1, foobar);

  if (!x) {
	int a = 1; // no warning; x is modified by lambda
  }
  if (!y) {
	int a = 1; // unreachable
  }
  x = false;
  if (x) {
	int b = 1; // unreachable
  }
  foobar();
  if (x) {
	int c = 1; // no warning; x is modified by lambda
  }
}

void test20() {
  bool flag1 = true;
  bool* ptr1 = &flag1;
  *ptr1 = false;
  if (flag1) {
	// unreachable
  }
}

int main() {
  bool z = false;
  bool y = true;
  int a, b;
  if (y || z) {
	a = 1;
  }
  else {
	b = 2; // unreachable
  }
  bool testBool = true;
  bool x = true;

  if (testBool && !x) {
	x = true;  // unreachable
  }
  else {
	x = false;
	x = false;
  }
  if (!x && testBool)
	return 1;
  else
	return 2;  // unreachable

  return 0;
}
