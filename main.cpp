// Copyright 2017 Timothy Oltjenbruns

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "sample.hpp"

const int candidates(6);
const int candidateSize(5);
const float keep(0.5f);
const float mutateRate(0.1f);

void printSamples(const std::vector<sample> &samples);

void crossover(std::vector<sample>& samples);

void mutate(std::vector<sample>& samples);

int main() {
  using std::cout;
  using std::endl;
  using std::setw;
  using std::left;

  srand((unsigned int) time(0));
  std::cout << "Genetic Algorithm!" << std::endl;
  std::vector<sample> samples(candidates);
  for (auto i(0); i < candidates; ++i) {
    std::string temp;
    // generate sample code
    for (auto j(0); j < candidateSize; ++j) {
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

  for (auto k(0); k < 100; ++k) {
    double avgFit(0);
    for (auto i(0); i < candidates; ++i)
      avgFit += samples[i].getFit();
    avgFit /= candidates;
    cout
      << "Gen " << setw(3) << left << k << ": "
      << " Avg fit: " << setw(10) << left
        << avgFit
      << " Max fit: " << setw(8) << left
        << std::max_element(samples.begin(), samples.end())->getFit()
      << " Min fit: " << setw(8) << left
        << std::min_element(samples.begin(), samples.end())->getFit()
      << endl;

    std::sort(samples.begin(), samples.end(), [](const sample a, const sample b) {return a > b; });
    crossover(samples);
    mutate(samples);
  }
  cout << "Gen 100: " << endl;
  printSamples(samples);

  return 0;
}

void printSamples(const std::vector<sample> &samples) {
  for (auto i(0); i < samples.size(); ++i)
    std::cout << samples[i] << std::endl;
}

void crossover(std::vector<sample>& samples) {
  std::vector<sample> results;
  for (auto i(0); i < (candidates * keep); ++i) {
    sample one = samples[(rand() % candidates) * keep];
    sample two = samples[(rand() % candidates) * keep];

    unsigned int cut((unsigned int) (rand() % candidateSize));

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
