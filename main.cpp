// Copyright (c) 2017 Timothy Oltjenbruns

#include <iostream>
#include <vector>
#include <cmath>

const int candidates(6);
const int candidateSize(5);

struct sample {
  std::string code;
  unsigned int value;
  double fit;

  sample();

  explicit sample(std::string code);
};

void printSamples(const std::vector<sample> &samples);

unsigned int toUnsignedInt(const std::string &string);

double fitness(unsigned int value);

int main() {
  srand((unsigned int) time(0));
  std::cout << "Genetic Algorithm!" << std::endl;
  std::vector<sample> samples(candidates);
  for (int i(0); i < candidates; ++i) {
    std::string temp;
    // generate sample code
    for (int j(0); j < candidateSize; ++j) {
      int chance(rand() % 100);
      if (chance >= 50)
        temp += "1";
      else
        temp += "0";
    }
    // evaluate fitness function
    samples[i] = sample(temp);
  }
  printSamples(samples);
  return 0;
}

void printSamples(const std::vector<sample> &samples) {
  for (int i(0); i < samples.size(); ++i) {
    std::cout << "Sample " << i << ": \tcode("
              << samples[i].code << "), \tvalue("
              << samples[i].value << "), \tfit("
              << samples[i].fit << ");" << std::endl;
  }
}

unsigned int toUnsignedInt(const std::string &string) {
  unsigned int output(0);
  for (unsigned int i(0); i < string.size(); ++i)
    output = (output << 1) + (string[i] - '0');
  return output;
}

double fitness(unsigned int value) {
  return pow(value, 2);
}

sample::sample() : code(""), value(0), fit(0) {}

sample::sample(std::string code) :
    code(code),
    value(toUnsignedInt(code)),
    fit(fitness(value)) {}
