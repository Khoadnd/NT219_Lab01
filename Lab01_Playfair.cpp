#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>

const std::string cmenu = "1. Encrypt\n2. Decrypt\n3. Exit\n";

const std::vector<char> _Alphabet = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const std::vector<char> gen_key(std::string _key);
const std::string Decrypt(const std::string _secret, const std::string _key);
const std::string Encrypt(const std::string _plaintext, const std::string _key);

const auto Removespace = [](const std::string _string) -> const std::string {
  return std::regex_replace(_string, std::regex("\\s+"), "");
};

const auto ToUpperString = [](const std::string _string) -> const std::string {
  std::string result = "";
  for (auto c : _string)
    result += toupper(c);
  return result;
};

int main() {
  std::cout << cmenu;

  int choice = 0;
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
    std::vector<char> key_vec = gen_key(ToUpperString(Removespace(key)));
    int count = 1;
    for (auto i : key_vec) {
      std::cout << i << " ";
      if (count++ % 5 == 0)
        std::cout << std::endl;
    }
    std::cout << "Encrypted: " << Encrypt(plaintext, key) << std::endl;
  } break;

  case 2: {
    std::string ciphertext;
    std::string key;
    std::cout << "Enter ciphertext: ";
    std::getline(std::cin, ciphertext);
    std::cout << "Enter key: ";
    std::getline(std::cin, key);
    std::vector<char> key_vec = gen_key(ToUpperString(Removespace(key)));
    int count = 1;
    for (auto i : key_vec) {
      std::cout << i << " ";
      if (count++ % 5 == 0)
        std::cout << std::endl;
    }
    std::cout << "Decrypted: " << Decrypt(ciphertext, key) << std::endl;
  } break;

  default:
    break;
  }

  return 0;
}

const std::string Divide(std::string _s) {
  std::string result = "";
  for (int i = 0; i < _s.length(); i += 2)
    if (_s[i] == _s[i + 1]) {
      result += _s[i];
      result += "X";
      result += _s[i + 1];
    } else {
      result += _s[i];
      result += _s[i + 1];
    }

  if (_s.length() % 2)
    result.pop_back();
  if (result.length() % 2)
    result += "X";

  return result;
}

template <typename ForwardIterator>
ForwardIterator remove_duplicates(ForwardIterator first, ForwardIterator last) {
  auto new_last = first;

  for (auto current = first; current != last; ++current) {
    if (std::find(first, new_last, *current) == new_last) {
      if (new_last != current)
        *new_last = *current;
      ++new_last;
    }
  }

  return new_last;
}

const std::vector<char> gen_key(std::string _key) {
  std::vector<char> key_matrix;

  // Them key vao key_matrix
  std::for_each(_key.begin(), _key.end(),
                [&key_matrix](char &c) { key_matrix.push_back(c); });

  key_matrix.erase(remove_duplicates(key_matrix.begin(), key_matrix.end()),
                   key_matrix.end());

  // Them bang chu cai vao matrix
  key_matrix.insert(key_matrix.end(), _Alphabet.begin(), _Alphabet.end());

  // xoa cac ky tu lap lai
  // std::remove_if(
  //     key_matrix.begin() + _key.length(), key_matrix.end(),
  //     [&_key](char &c) { return _key.find(c) != std::string::npos; });

  key_matrix.erase(remove_duplicates(key_matrix.begin(), key_matrix.end()),
                   key_matrix.end());

  // resize 5x5
  key_matrix.resize(25);
  return key_matrix;
}

const std::string Encrypt(const std::string _plaintext,
                          const std::string _key) {
  std::string result;
  std::string plainttext = Divide(ToUpperString(Removespace(_plaintext)));
  std::string key = ToUpperString(Removespace(_key));
  std::replace(plainttext.begin(), plainttext.end(), 'J', 'K');
  std::replace(key.begin(), key.end(), 'J', 'K');

  std::vector<char> key_matrix = gen_key(key);

  for (auto i = 0; i < plainttext.length(); i += 2) {
    int pos1 = std::distance(
        key_matrix.begin(),
        std::find(key_matrix.begin(), key_matrix.end(), plainttext[i]));
    int pos2 = std::distance(
        key_matrix.begin(),
        std::find(key_matrix.begin(), key_matrix.end(), plainttext[i + 1]));

    // same row
    if ((int)(pos1 / 5) == (int)(pos2 / 5)) {
      result += key_matrix[(((int)(pos1 / 5) * 5) + (pos1 + 1) % 5) % 25];
      result += key_matrix[(((int)(pos2 / 5) * 5) + (pos2 + 1) % 5) % 25];
      continue;
    }

    // same col
    if (pos1 % 5 == pos2 % 5) {
      result += key_matrix[((((int)(pos1 / 5) + 1) * 5) + (pos1 % 5)) % 25];
      result += key_matrix[((((int)(pos2 / 5) + 1) * 5) + (pos2 % 5)) % 25];
      continue;
    }

    // rectangle
    result += key_matrix[(((int)(pos1 / 5) * 5) + (pos2 % 5)) % 25];
    result += key_matrix[(((int)(pos2 / 5) * 5) + (pos1 % 5)) % 25];
  }
  return result;
}

const std::string Decrypt(const std::string _secret, const std::string _key) {
  std::string result;
  std::string secret = Divide(ToUpperString(Removespace(_secret)));
  std::string key = ToUpperString(Removespace(_key));
  std::replace(key.begin(), key.end(), 'J', 'I');

  std::vector<char> key_matrix = gen_key(key);

  for (auto i = 0; i < secret.length(); i += 2) {
    int pos1 = std::distance(
        key_matrix.begin(),
        std::find(key_matrix.begin(), key_matrix.end(), secret[i]));
    int pos2 = std::distance(
        key_matrix.begin(),
        std::find(key_matrix.begin(), key_matrix.end(), secret[i + 1]));

    // same row
    if ((int)(pos1 / 5) == (int)(pos2 / 5)) {
      result +=
          key_matrix[((((int)(pos1 / 5) * 5) + (pos1 - 1) % 5) + 25) % 25];
      result +=
          key_matrix[((((int)(pos2 / 5) * 5) + (pos2 - 1) % 5) + 25) % 25];
      continue;
    }

    // same col
    if (pos1 % 5 == pos2 % 5) {
      result +=
          key_matrix[(((((int)(pos1 / 5) - 1) * 5) + (pos1 % 5)) + 25) % 25];
      result +=
          key_matrix[(((((int)(pos2 / 5) - 1) * 5) + (pos2 % 5)) + 25) % 25];
      continue;
    }

    // rectangle
    result += key_matrix[((((int)(pos1 / 5) * 5) + (pos2 % 5)) + 25) % 25];
    result += key_matrix[((((int)(pos2 / 5) * 5) + (pos1 % 5)) + 25) % 25];
  }

  return result;
}
