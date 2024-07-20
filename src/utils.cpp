#include "utils.hpp"
#include <random>
#include <stdexcept>

#define INVALID_ARG_MSG                                                        \
  "Invalid range: 'start' must be less than or equal to 'end'"

namespace utils {

int rng(int start, int end) {
  if (start > end)
    throw std::invalid_argument(INVALID_ARG_MSG);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_int(start, end);

  int random_int = dis_int(gen);

  return random_int;
}

} // namespace utils
