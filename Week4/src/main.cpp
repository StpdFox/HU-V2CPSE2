#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <algorithm>


int main() {
	const std::string fileName = "resources/bible.txt";
	std::ifstream input(fileName);
	input >> std::noskipws;
	std::istream_iterator<char> start(input), end;
	std::vector<char> characters(start, end);

	std::cout << "Aantal characters: " << characters.size() << std::endl;
	std::cout << "Aantal regels: " << (std::count(characters.begin(), characters.end(), '\n') + 1) << std::endl;
	std::cout << "Aantal alpha: " << std::count_if(characters.begin(), characters.end(), [](const char& c) {return isalpha(c); }) << std::endl;

	std::cout << "Before: " << std::endl;
	uint8_t i = 0;
	for (const auto& c : characters) {
		std::cout << c;

		if (i++ > 10) break;
	}

	std::for_each(characters.begin(), characters.end(), [](char& c) { if (c >= 'A' && c <= 'Z') { c += 'a' - 'A'; } });
	std::cout << std::endl << "After: " << std::endl;
	i = 0;
	for (const auto& c : characters) {
		std::cout << c;

		if (i++ > 10) break;
	}

	// Count letters
	std::cout << std::endl << "Counted letters: " << std::endl;
	std::array<uint32_t, 26> alpha = {0};
	std::for_each(characters.begin(), characters.end(), [&alpha](const char& c) { if (c >= 'a' && c <= 'z') { alpha[c - 'a'] += 1; } });
	for (uint8_t i = 0; i < alpha.size(); ++i) {
		std::cout << static_cast<char>('a' + i) << ": " << alpha[i] << std::endl;
	}

	// Count words
	std::map<std::string, size_t> words;
	std::string word = "";

	std::for_each(characters.begin(), characters.end(), [&words, &word, &i](const char& c) {
		if (isalpha(c)) { 
			word += c;
		} else if (word.size() > 0) {
			if (words[word] != NULL) {
				words[word] += 1;
			} else {
				words[word] = 1;
			}
			word = "";
		}
	});

	// Sort map
	std::map<size_t, std::string> sorted_words;
	std::for_each(words.begin(), words.end(), [&sorted_words](const auto& pair) {
		sorted_words[pair.second] = pair.first;
	});

	std::cout << std::endl << "Most words:" << std::endl;
	i = 0;
	for (auto it = sorted_words.rbegin(); it != sorted_words.rend(); ++it) {
		std::cout << it->second << " " << it->first << std::endl;
		
		if (i++ > 10) break;
	}

	std::cin.get();

    return 0;
}

