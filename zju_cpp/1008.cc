#include <iostream>

int n, count;
int mm[25][4];
int now_queue[25];
int used[25];


int if_can_move(int num, int next_square) {
  if ((num / n > 0 && mm[next_square][0] != mm[now_queue[num - n]][2]) ||
      (num % n > 0 && mm[next_square][3] != mm[now_queue[num - 1]][1]))
    return 0;
  return 1;
}

int move(int num) {
  if (num == n * n)
    return 1;

  for (int i = 0; i < count; i++) {
    if (used[i] > 0 && if_can_move(num, i)) {
      used[i]--;
      now_queue[num] = i;
      num++;
      if (move(num))
        return 1;
      used[i]++;
      num--;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int i, j, iter_count = 0;
  bool flag, if_success;

  while (std::cin >> n) {
    if (n == 0)
      break;
    iter_count++;
    count = 0;
    for (i = 0; i < n * n; i++)
      used[i] = 0;
    for (i = 0; i < n * n; i++) {
      for (j = 0; j < 4; j++)
        std::cin >> mm[count][j];

      flag = true;
      for (j = 0; j < count; j++) {
        if (mm[count][0] == mm[j][0] && mm[count][1] == mm[j][1] &&
            mm[count][2] == mm[j][2] && mm[count][3] == mm[j][3]) {
          used[j]++;
          flag = false;
          break;
        }
      }
      if (flag) {
        used[count]++;
        count++;
      }
    }
    if_success = move(0);
    if (iter_count > 1)
      std::cout << std::endl;
    std::cout << "Game " << iter_count << ": ";
    if (if_success) {
      std::cout << "Possible";
    } else {
      std::cout << "Impossible";
    }
    std::cout << std::endl;
  }
  return 0;
}
