// Copyright 2017 timothyolt.

#include <cmath>
#include "sample.hpp"

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

bool sample::operator<(const sample &rhs) const {
  return fit < rhs.fit;
}

bool sample::operator>(const sample &rhs) const {
  return rhs < *this;
}

bool sample::operator<=(const sample &rhs) const {
  return !(rhs < *this);
}

bool sample::operator>=(const sample &rhs) const {
  return !(*this < rhs);
}

unsigned int sample::toUnsignedInt(const std::string &string) {
  unsigned int output(0);
  for (auto i(0); i < string.size(); ++i)
    output = (output << 1) + (string[i] - '0');
  return output;
}

double sample::fitness(unsigned int value) {
  return pow(value, 2);
}

std::ostream &operator<<(std::ostream &os, const sample &sample1) {
  os << "code: " << sample1.code << " value: " << sample1.value << " fit: " << sample1.fit;
  return os;
}
