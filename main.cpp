// Copyright (c) 2017 Timothy Oltjenbruns

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const int candidates(6);
const int candidateSize(5);
const float keep(0.5f);
const float mutateRate(0.1f);

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

void crossover(std::vector<sample>& samples);

void mutate(std::vector<sample>& samples);

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
  std::cout << "Sorted: " << std::endl;
  printSamples(samples);
  std::sort(samples.begin(), samples.end(), [](sample a, sample b) { return b.fit < a.fit; });
  std::cout << "Sorted: " << std::endl;
  printSamples(samples);
  crossover(samples);
  std::cout << "Crossover: " << std::endl;
  printSamples(samples);
  mutate(samples);
  std::cout << "Mutate: " << std::endl;
  printSamples(samples);

  return 0;
}

sample::sample() : code(""), value(0), fit(0) {}

sample::sample(std::string code) :
    code(code),
    value(toUnsignedInt(code)),
    fit(fitness(value)) {}

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

void crossover(std::vector<sample>& samples) {
  std::vector<sample> results;
  for (auto i(0); i < (candidates * keep); ++i) {
    sample one = samples[(rand() % candidates) * keep];
    sample two = samples[(rand() % candidates) * keep];

    int cut((rand() % candidateSize));

    results.push_back(sample(one.code.substr(0, cut) + two.code.substr(cut, candidateSize - cut)));
    results.push_back(sample(two.code.substr(0, cut) + one.code.substr(cut, candidateSize - cut)));
  }
  std::copy(results.begin(), results.end(), samples.begin());
  return;
}

void mutate(std::vector<sample> &samples) {
  for (auto i(0); i < candidates; ++i) {
    if (((rand() % 10) / 10.0f) < mutateRate) {
      // choose element
      int index(rand() % candidateSize);
      samples[i].code[index] = (samples[i].code[index] == '0' ? '1' : '0');
    }
  }
  return;
}
