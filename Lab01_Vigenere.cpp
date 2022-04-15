#include <iostream>
#include <string>

const std::string cMenu = (std::string) "1. Encrypt\n2. Decrypt\n3. Exit\n";

const std::string Encrypt(const std::string, const std::string);
const std::string Decrypt(const std::string, const std::string);

int main() {
  int choice = 0;
  std::cout << cMenu;
  std::cin >> choice;
  std::cin.ignore();
  switch (choice) {
  case 1: {
    std::string plaintext;
    std::string key;
    std::cout << "Enter plaintext: ";
    std::getline(std::cin, plaintext);
    std::cout << "Enter key: ";
    std::getline(std::cin, key);
    std::cout << "Encrypted: " << Encrypt(plaintext, key) << std::endl;
  } break;

  case 2: {
    std::string ciphertext;
    std::string key;
    std::cout << "Enter ciphertext: ";
    std::getline(std::cin, ciphertext);
    std::cout << "Enter key: ";
    std::getline(std::cin, key);
    std::cout << "Decrypted: " << Decrypt(ciphertext, key) << std::endl;
  } break;

  default:
    break;
  }
  return 0;
}

const std::string Encrypt(const std::string _plainttext,
                          const std::string _key) {
  std::string ciphertext = "";
  std::string plainttext = _plainttext;
  std::string key = _key;

  while (plainttext.length() > key.length())
    key.append(key);

  for (auto &c : plainttext)
    c = toupper(c);
  for (auto &c : key)
    c = toupper(c);

  for (int i = 0; i < plainttext.length(); i++)
    ciphertext += (plainttext[i] + key[i]) % 26 + 'A';

  return ciphertext;
}

const std::string Decrypt(const std::string _secret, const std::string _key) {
  std::string plaintext = "";
  std::string secret = _secret;
  std::string key = _key;

  while (secret.length() > key.length())
    key.append(key);

  for (auto &c : secret)
    c = toupper(c);
  for (auto &c : key)
    c = toupper(c);

  for (int i = 0; i < secret.length(); i++)
    plaintext += (secret[i] - key[i] + 26) % 26 + 'A';

  return plaintext;
}