#include <iostream>

int n, count;
int mm[25][4];
int used[25];
int now_queue[25];


int if_can_move(int height, int width, int num, int beyond_num, int action, int next_square) {
  if (num == 0)
    return 1;
  if (mm[now_queue[num - 1]][action] != mm[next_square][(action + 2) % 4])
    return 0;
  if (beyond_num > 1) {
    int c_square_idx = num - 1;
    if (action % 2 == 0) {
      c_square_idx -= ((width - 1) * 2 + height * 2 - 3);
    } else {
      c_square_idx -= ((height - 1) * 2 + width * 2 - 3);
    }
    if (c_square_idx >= 0 && c_square_idx < num &&
        mm[next_square][(action + 1) % 4] != mm[now_queue[c_square_idx]][(action - 1) % 4])
      return 0;
  }
  return 1;
}

int move(int height, int width, int num, int beyond_num, int action) {
  if (num == n * n)
    return 1;

  int next_height, next_width, next_beyond_num;
  next_height = height;
  next_width = width;
  if ((action % 2 == 0 && beyond_num == height) ||
     (action % 2 == 1 && beyond_num == width)) {
    next_beyond_num = 1;
    if (action % 2 == 0) {
      next_height++;
    } else {
      next_width++;
    }
  } else {
    next_beyond_num = beyond_num + 1;
  }
  int next_action = action;
  if (beyond_num == 1) {
    next_action++;
    next_action %= 4;
  }
  bool can_move;
  for (int i = 0; i < count; i++) {
    if (used[i] > 0) {
      can_move = if_can_move(height, width, num, beyond_num, action, i);
      if (can_move == 1){
        used[i]--;
        now_queue[num] = i;
        num++;
        if (move(next_height, next_width, num, next_beyond_num, next_action))
          return 1;
        used[i]++;
        num--;
      }
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
    if_success = move(0, 0, 0, 0, 0);
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
