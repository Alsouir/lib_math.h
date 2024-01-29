#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = s21_fabs(x);
  int flag = 0;
  if (x < 0) {
    flag = 1;
  }
  y = s21_fabs(y);
  if (x != x || y != y || y == 0) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF || y == -S21_INF) {
    result = S21_NAN;
  } else {
    while (result >= y) {
      result -= y;
    }
  }
  if (flag == 1) {
    result *= -1;
  }
  return result;
}

long double s21_fabs(double x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double s21_atan(double x) {
  long double copy_x = x;
  long double result = copy_x;
  if (x != x) {
    result = S21_NAN;
  } else if (x >= S21_INF) {
    result = S21_PI / 2;
  } else if (x <= -S21_INF) {
    result = -S21_PI / 2;
  } else if (x == 1) {
    result = S21_PI / 4;
  } else if (x == -1) {
    result = -S21_PI / 4;
  } else if (x < 1.0 && x > -1.0) {
    long double result_degree_x = 1;
    long double degree_x = 1;
    long double result_degree_1 = 1;
    for (int i = 2; i < 2500; i++) {
      degree_x = 2 * i - 1;
      result_degree_x = s21_pow(copy_x, degree_x);
      result_degree_1 = s21_pow(-1, i - 1);

      result = result + result_degree_1 * (result_degree_x) / degree_x;
    }
  } else {
    copy_x = 1 / copy_x;
    result = S21_PI * s21_sqrt(x * x) / (2 * x) - copy_x;
    long double result_degree_x = 1;
    long double degree_x = 1;
    long double result_degree_1 = 1;
    for (int i = 2; i < 2500; i++) {
      degree_x = 2 * i - 1;
      result_degree_x = s21_pow(copy_x, degree_x);
      result_degree_1 = s21_pow(-1, i);
      result = result + result_degree_1 * (result_degree_x) / degree_x;
    }
  }
  return result;
}

long double s21_acos(double x) {
  long double result = 0;
  if (x < -1 || x > 1) {
    result = S21_NAN;
  } else {
    result = S21_PI / 2.0 - s21_asin(x);
    ;
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = 0;
  if (x < 0) {
    result = S21_NAN;
  } else {
    result = s21_pow(x, 0.5);
  }
  return result;
}

long double s21_cos(double x) {
  long double result = 0;
  if (x == S21_INF || x == -S21_INF) {
    result = S21_NAN;
  } else {
    long double copy_x = x;
    while (copy_x > S21_PI || copy_x < -S21_PI) {
      if (copy_x > S21_PI) {
        copy_x = copy_x - 2.0 * S21_PI;
      } else {
        copy_x = copy_x + 2.0 * S21_PI;
      }
    }
    result = s21_sin(S21_PI / 2.0 - copy_x);
  }

  return result;
}

int s21_abs(int x) {
  if (x < 0) {
    x = x * -1;
  }
  return x;
}

long double s21_asin(double x) {
  long double result = x;
  if (x < 1 && x > -1) {
    long double copy_x = x;
    long double factorial_2n = 1;
    long double factorial_n = 1;
    long double num_factorian_n = 1;
    long double number_4 = 1;
    for (int i = 3; i < 1000 && factorial_2n > 0; i = i + 2) {
      copy_x = copy_x * x * x;  //
      number_4 = number_4 * 4;
      factorial_n = factorial_n * num_factorian_n;
      num_factorian_n++;
      factorial_2n = factorial_2n * (i - 1) * (i - 2);
      result = result + (copy_x * factorial_2n) /
                            (i * factorial_n * factorial_n * number_4);
    }
  } else if (x == 1) {
    result = S21_PI / 2;
  } else if (x == -1) {
    result = -S21_PI / 2;
  }

  else {
    result = S21_NAN;
  }
  return result;
}

long double s21_ceil(double x) {
  long double result = 0;
  if (x == S21_INF || x == -S21_INF ||
      x != x)  // x != x, для ситуаций x = NaN, NaN не равен ничему
  {
    result = x;
  } else {
    result = find_integer_part_in_fraction(x);
    if (x < 0) {
      result = result * -1;
    } else if (x - result > S21_ZERO_DOUBLE)  // ???
    {
      result = result + 1;
    }
  }
  return result;
}

long double find_integer_part_in_fraction(double x) {
  long double copy_x = x;
  long double result = 0;
  if (copy_x < 0) {
    copy_x = copy_x * -1.0;
  }
  int count_digits = 0;
  while (copy_x >= 1) {
    copy_x = copy_x / 10;
    count_digits++;
  }
  for (int i = 0; i < count_digits; i++) {
    copy_x = copy_x * 10;
    result = result * 10 + (int)(copy_x);
    copy_x = copy_x - (int)(copy_x);
  }
  return result;
}

long double s21_floor(double x) {
  long double result = 0;
  if (x != x)  // x != x, для ситуаций x = NaN, NaN не равен ничему
  {
    result = x;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (x == -S21_INF) {
    result = -S21_INF;
  } else {
    long int integer_x = (long int)x;
    if (x < 0 && x - integer_x != 0) {
      result = (double)integer_x - 1;
    } else {
      result = (double)integer_x;
    }
  }
  return result;
}

long double s21_exp(double x) {
  bool need_divided = false;
  if (x < 0) {
    x = x * -1.0;
    need_divided = true;
  }
  long double x_to_power = x;
  long double result = 1.0 + x;
  long double factorial = 1;
  for (int i = 2; i < 1000; i++) {
    factorial = factorial * i;
    x_to_power = x_to_power * x;
    result = result + x_to_power / factorial;
  }

  if (need_divided == true && result != 0) {
    result = 1.0 / result;
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0;
  // long double copy_x = x;
  if (x < 0 || x != x) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (x == 1) {
    result = 0;
  } else if (x == 0) {
    result = -S21_INF;
  } else {
    int ex_pow = 0;
    for (; x >= S21_EXP; x /= S21_EXP, ex_pow++)
      ;
    int i;
    for (i = 0; i < 100; i++) {
      result = result + 2 * (x - s21_exp(result)) / (x + s21_exp(result));
    }
    result = result + ex_pow;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (exp == 0) {
    result = 1;
  } else if (base == 1) {
    result = 1;
  } else if (exp != exp || base != base) {
    result = S21_NAN;
  } else if (base == 0) {
    result = 0;
    if (exp < 0) {
      result = S21_INF;
    }
  } else if (base == S21_INF || base == -S21_INF) {
    result = base;
    if (exp < 0) {
      result = 0;
    }
  } else if (exp == S21_INF || exp == -S21_INF) {
    if (base == 1 || base == -1) {
      result = 1;
    } else if (base > 1 && exp == S21_INF) {
      result = S21_INF;
    } else if (base > 1 && exp == -S21_INF) {
      result = 0;
    } else if (base > 0 && base < 1 && exp == S21_INF) {
      result = 0;
    } else if (base > 0 && base < 1 && exp == -S21_INF) {
      result = S21_INF;
    } else if (base < 0 && base > -1 && exp == S21_INF) {
      result = 0;
    } else if (base < 0 && base > -1 && exp == -S21_INF) {
      result = -S21_INF;
    } else if (base < -1 && exp == S21_INF) {
      result = -S21_INF;
    } else if (base < -1 && exp == -S21_INF) {
      result = 0;
    }
  } else {
    long double copy_exp = exp;
    bool need_divided = false;

    if (exp < 0) {
      copy_exp = -1 * exp;
      need_divided = true;
    }

    while (copy_exp >= 1) {
      result = result * base;
      copy_exp = copy_exp - 1;
    }

    if (copy_exp > S21_ZERO_DOUBLE)
      result = result * s21_exp(copy_exp * s21_log(base));

    if (need_divided == true && result != 0) {
      result = 1.0 / result;
    } else if (need_divided == true && result == 0) {
      result = S21_INF;
    }
  }
  return result;
}

long double s21_sin(double x) {
  long double result = 0;
  long double copy_x = x;
  if (x == S21_INF || x == -S21_INF || x != x) {
    result = S21_NAN;
  } else {
    long double processed_x = x;
    /*if (x < 0) {
      processed_x = -x;
    }*/
    if (processed_x > 2 * S21_PI) {
      copy_x = processed_x - 2 * S21_PI * (int)(processed_x / (2 * S21_PI));
    } else if (processed_x < -2 * S21_PI) {
      copy_x = processed_x + 2 * S21_PI * (int)(-processed_x / (2 * S21_PI));
    }
    processed_x = copy_x;
    result = copy_x;
    long double factorial = 1;
    bool is_sum = false;
    for (int i = 2; i < 1000; i++) {
      copy_x = copy_x * processed_x;
      factorial = factorial * i;
      if (i % 2 == 1 && is_sum == true) {
        result = result + copy_x / factorial;
        is_sum = false;
      } else if (i % 2 == 1 && is_sum == false) {
        result = result - copy_x / factorial;
        is_sum = true;
      }
    }
    /*if (x < 0) {
      result = result * -1;
    }*/
  }
  return result;
}

long double s21_tan(double x) {
  long double result;
  if (x == S21_PI / 2) {
    result = 16331239353195369.755859;
  } else if (x == -S21_PI / 2) {
    result = -16331239353195369.755859;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}
