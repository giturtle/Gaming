


#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//定义棋盘为 3 * 3
#define ROW 3
#define COL 3
char g_board[ROW][COL];

//对于全局变量，没显式初始化，就会默认初始化为 0 
void menu() {
	while (1) {
		printf("         三子棋\n");
		printf("-----------------------\n");
		printf("1.开始游戏  0.退出游戏\n");
		printf("-----------------------\n");
		int a = 0;
		scanf("%d", &a);//接受玩家选择指令
		if (a == 1) {
			break;
		}
		else {
			printf("\n输入有误,请根据选项数字重新输入!\n");
			printf("\n");
			continue;
		}
	}
}



//1.进行棋盘的初始化
void Init() {
	srand((unsigned int)time(0));//设置随机种子
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			g_board[row][col] = ' ';//未下子用空格表示
		}
	}
}

//打印棋盘
void Print() {
	printf("|---|---|---|\n");
	for (int row = 0; row < ROW; ++row) {
		printf("| %c | %c | %c |\n", g_board[row][0],
			g_board[row][1], g_board[row][2]);
		printf(" ---|---|--- \n");
	}
}

//玩家落子回合
void PlayerMove() {
	printf("请玩家落子！\n");
	while (1) {
		printf("请输入坐标(row col):\n");
		int row, col;
		scanf("%d %d", &row, &col);
		//判断输入参数是否合法
		if (row < 0 || row >= ROW || col < 0 || col >= COL) {
			printf("输入的坐标非法，请重新输入！\n");
			continue;
		}
		if (g_board[row][col] != ' ') {
			printf("当前位置已经有子，请重新输入！\n");
			continue;
		}
		g_board[row][col] = 'x';//完成元素的更迭,直观上来看就是"落子"了
		break;
	}
}

//电脑落子回合
void ComputerMove() {
	printf("请电脑落子!\n");
	while (1) {
		//电脑"随机下"
		int row = rand() % ROW;
		int col = rand() % ROW;
		if (g_board[row][col] != ' ') {
			continue;
		}
		g_board[row][col] = 'o';
		break;
	}
}

//判断棋盘是否全部填满的函数
int Isfull() {
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			if (g_board[row][col] == ' ') {
				return 0;
			}
		}
	}
	return 1;
}
char CheckWinner() {
	//检查行列斜线是否可以连成三个
	//行
	for (int row = 0; row < ROW; ++row) {
		if (g_board[row][0] == g_board[row][1] &&
			g_board[row][0] == g_board[row][2] &&
			g_board[row][0] != ' ') {
			return g_board[row][0];
		}
	}
	//列
	for (int col = 0; col < COL; ++col) {
		if (g_board[0][col] == g_board[1][col] &&
			g_board[0][col] == g_board[2][col] &&
			g_board[0][col] != ' ') {
			return g_board[0][col];
		}
	}
	//斜  两条对角线
	if (g_board[0][0] == g_board[1][1] &&
		g_board[0][0] == g_board[2][2] &&
		g_board[0][0] != ' ') {
		return g_board[0][0];
	}
	if (g_board[0][2] == g_board[1][1] &&
		g_board[0][2] == g_board[2][0] &&
		g_board[0][2] != ' ') {
		return g_board[0][2];
	}
	//判断和棋情况
	if (Isfull()) {
		//如果填满了 返回和棋
		return 'q';
	}
	//如若没填满  返回 胜负未分
	return ' ';
}

//游戏逻辑主体
int main() {
	menu();//1.先打印菜单函数,让玩家选择
	Init();//2.玩家选择开始,初始化棋盘
	Print();//3.打印棋盘
	char winner;//4.判断胜者
	while (1) {

		//winner -> x 玩家胜
		//winner -> o 电脑胜
		//winner -> ' '胜负未分
		//winner -> q 和棋

		//5.玩家落子，判定是否游戏结束
		PlayerMove();
		winner = CheckWinner();
		if (winner != ' ') {
			//如果CheckWinner函数返回了 胜负未分 则跳出循环,跳出玩家落子阶段
			break;
		}
		Print();//打印更新后的棋盘

		//6.电脑落子，判定是否游戏结束
		ComputerMove();
		winner = CheckWinner();
		if (winner != ' ') {
			break;
		}
		Print();
	}
	if (winner == 'x') {
		printf("玩家胜\n");
		Print();
	}
	else if (winner == 'o') {
		printf("电脑胜\n");
		Print();
	}
	else {
		printf("和棋\n");
		Print();
	}
	system("pause");
	return 0;
}
