#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const std::string menu = "1. Encrypt\n2. Decrypt\n3. Exit\n";

std::string Encrypt(std::string, int);
std::string Decrypt(std::string, int);
std::string Decrypt(std::string); // brute force

void Choice1();
void Choice2();

int main() {
  int choice = 0;
  std::cout << menu;
  std::cin >> choice;
  std::cin.ignore();
  switch (choice) {
  case 1:
    Choice1();
    break;

  case 2:
    Choice2();
    break;

  case 3:
    exit(0);
    break;

  default:
    break;
  }

  return 0;
}

std::string Decrypt(std::string secret) {
  std::string decryptedData = "";
  for (int i = 1; i < 26; i++)
    decryptedData.append("k = " + std::to_string(i) + ": " +
                         Encrypt(secret, 26 - i) + "\n\n");
  return decryptedData;
}

std::string Decrypt(std::string secret, int key) {
  return Encrypt(secret, 26 - key);
}

std::string Encrypt(std::string plaintext, int key) {
  std::string ciphertext = "";
  for (int i = 0; i < plaintext.length(); i++) {
    if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
      ciphertext += (plaintext[i] - 'a' + key) % 26 + 'a';
    } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
      ciphertext += (plaintext[i] - 'A' + key) % 26 + 'A';
    } else {
      ciphertext += plaintext[i];
    }
  }
  return ciphertext;
}

void Choice1() {
  std::string plaintext;
  int key = 0;

  std::cout << "Enter plaintext: ";
  std::getline(std::cin, plaintext);

  std::cout << "Enter key: ";
  std::cin >> key;

  std::cout << "Ciphertext: " << Encrypt(plaintext, key) << "\n";
}

void Choice2() {
  int key;
  int choice;
  std::fstream fs;
  std::string secret;
  std::stringstream ss;

  std::cout << "1. Brute force\n2. Known key\n";
  std::cin >> choice;

  switch (choice) {

  case 1: {
    std::cout << "Secret readed in file secret.txt, decrypted message in "
                 "decrypted.txt\n";

    fs.open("secret.txt", std::fstream::in);
    ss << fs.rdbuf();
    fs.close();
    secret = ss.str();

    std::cout << "Secret is: " << secret
              << "\nThe decoded message are stored in decrypted.txt";
    fs.open("decrypted.txt", std::fstream::out);
    fs << Decrypt(secret);
    fs.close();
  } break;

  case 2: {
    std::cout << "Enter key: ";
    std::cin >> key;

    fs.open("secret.txt", std::fstream::in);
    ss << fs.rdbuf();
    fs.close();
    secret = ss.str();

    fs.open("decrypted.txt", std::fstream::out);
    std::string decryptedMSG = Decrypt(secret, key);
    std::cout << "Decrypted message using key " << key
              << " is: " << decryptedMSG;
    std::cout << "\nThe decrypted message are stored in decrypted.txt";
    fs << decryptedMSG;
    fs.close();

  } break;

  default:
    break;
  }
}