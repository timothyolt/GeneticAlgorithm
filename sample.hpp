// Copyright 2017 timothyolt.

#ifndef GENETICALGORITM_SAMPLE_HPP_
#define GENETICALGORITM_SAMPLE_HPP_

#include <string>
#include <ostream>

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

  bool operator<(const sample &rhs) const;

  bool operator>(const sample &rhs) const;

  bool operator<=(const sample &rhs) const;

  bool operator>=(const sample &rhs) const;

  static unsigned int toUnsignedInt(const std::string &string);

  static double fitness(unsigned int value);

  friend std::ostream &operator<<(std::ostream &os, const sample &sample1);
};

#endif  // GENETICALGORITM_SAMPLE_HPP_
