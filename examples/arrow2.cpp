#include <iostream>
#include <termios.h>

int main() {
  struct termios old_termios, new_termios;

  // Get the current terminal settings.
  tcgetattr(0, &old_termios);

  // Set the terminal to non-canonical mode.
  new_termios = old_termios;
  new_termios.c_lflag &= ~ICANON;
  tcsetattr(0, TCSANOW, &new_termios);

  // Read a single character from the input buffer.
  char c = std::cin.get();

  // Check if the character is a direction key.
  if (c == '\033') {
    // Read the next two characters from the input buffer.
    char c1 = std::cin.get();
    char c2 = std::cin.get();

    // Check if the next two characters are a direction key.
    if (c1 == '[' && (c2 == 'A' || c2 == 'B' || c2 == 'C' || c2 == 'D')) {
      // The character is a direction key.
      std::cout << "The direction key is " << c2 << std::endl;
    }
  }

  // Restore the original terminal settings.
  tcsetattr(0, TCSANOW, &old_termios);

  return 0;
}

