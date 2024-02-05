#include <iostream>

int main() {
  std::cout << "请输入密码：" << std::flush;
  system("stty -echo");
  std::string password;
  std::cin >> password;
  system("stty echo");
  std::cout << std::endl;
  std::cout << "your input is " << password << std::endl;

  
  return 0;
}

