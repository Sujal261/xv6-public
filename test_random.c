#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  uint random_num;
  random_num = getrandom();
  printf(1, "%d\n", random_num);
  exit();
}