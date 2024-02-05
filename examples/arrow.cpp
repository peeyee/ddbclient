#include <iostream>

int main() {
  char c[3];

  // Read the first three characters from the input buffer.
  std::cin.read(c, 3);

  // Check if the first three characters are a direction key.
  if (c[0] == '\033' && c[1] == '[' && (c[2] == 'A' || c[2] == 'B' || c[2] == 'C' || c[2] == 'D')) {
    // The first three characters are a direction key.
    std::cout << "The direction key is " << c[2] << std::endl;
  } else {
    // The first three characters are not a direction key.
    std::cout << "The first three characters are not a direction key." << std::endl;
  }

  return 0;
}

