#include "random_utils.h"

namespace albinjohansson::wanderer {

bool RandomUtils::get_bool() {
  return get_int(0, 99) < 50;
}

}
