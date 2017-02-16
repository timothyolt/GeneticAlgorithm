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
 private:
  std::string code;
  unsigned int value;
  double fit;

 public:
  sample();

  explicit sample(std::string code);

  const std::string &getCode() const;

  void setCode(const std::string &code);

  unsigned int getValue() const;

  double getFit() const;
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
  std::cout << "Generation 0"<< std::endl;
  printSamples(samples);

  for (auto k(0); k < 100; ++k) {
    std::sort(samples.begin(), samples.end(), [](sample a, sample b) { return b.getFit() < a.getFit(); });
    crossover(samples);
    mutate(samples);
    std::cout << "Generation " << k + 1 << std::endl;
    printSamples(samples);
  }

  return 0;
}

sample::sample() : code(""), value(0), fit(0) {}

sample::sample(std::string code) :
    code(code),
    value(toUnsignedInt(code)),
    fit(fitness(value)) {}

const std::string &sample::getCode() const {
  return code;
}

void sample::setCode(const std::string &code) {
  sample::code = code;
  value = toUnsignedInt(code);
  fit = fitness(value);
}

unsigned int sample::getValue() const {
  return value;
}

double sample::getFit() const {
  return fit;
}

void printSamples(const std::vector<sample> &samples) {
  for (int i(0); i < samples.size(); ++i) {
    std::cout << "Sample " << i << ": \tcode("
              << samples[i].getCode() << "), \tvalue("
              << samples[i].getValue() << "), \tfit("
              << samples[i].getFit() << ");" << std::endl;
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

    results.push_back(sample(one.getCode().substr(0, cut) + two.getCode().substr(cut, candidateSize - cut)));
    results.push_back(sample(two.getCode().substr(0, cut) + one.getCode().substr(cut, candidateSize - cut)));
  }
  std::copy(results.begin(), results.end(), samples.begin());
  return;
}

void mutate(std::vector<sample> &samples) {
  for (auto i(0); i < candidates; ++i) {
    if (((rand() % 10) / 10.0f) < mutateRate) {
      // choose element
      int index(rand() % candidateSize);
      std::string code(samples[i].getCode());
      code[index] = code[index] == '0' ? '1' : '0';
      samples[i].setCode(code);
    }
  }
  return;
}
