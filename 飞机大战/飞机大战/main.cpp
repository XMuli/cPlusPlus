#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

enum My {
	W = 640,
	H = 1000,
	BULLET_NUM = 15,
	ENEMY_NUM = 10,
	BIG,
	SMALL
};
struct plane {
	int x;
	int y;
	bool live;
	int w;
	int h;
	int hp;
	int type;
}player,bullet[BULLET_NUM],enemy[ENEMY_NUM];
IMAGE bk;
IMAGE img_role;
IMAGE img_bullet;
IMAGE img_enemy[2];
IMAGE img;
void loadImg() {
	loadimage(&bk, "./images/±³¾°.jpg");
	loadimage(&img_bullet, "./images/jet.jpg");
	loadimage(&img_enemy[1], "./images/´óµÐ1.jpg");
	loadimage(&img_role, "./images/Ö÷»ú.jpg");
	loadimage(&img_enemy[0], "./images/µÐ1.jpg");
	loadimage(&img, "./images/ikun.jpg");
}
void enemyHp(int i) {
	int flag = rand() % 10;
	if (flag>=0&&flag<=2) {
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].w = 83;
		enemy[i].h = 119;
	}
	else {
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].w = 68;
		enemy[i].h = 51;
	}
}
void shift() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live&&enemy[i].y>player.y) {
			putimage(0, 0, &img);
			mciSendString("close kun.mp3", 0, 0, 0);
			mciSendString("open ¼¦ÄãÌ«ÃÀ.mp3", 0, 0, 0);
			mciSendString("play ¼¦ÄãÌ«ÃÀ.mp3 repeat", 0, 0, 0);
		}
	}
}
void gameInit() {
	loadImg();
	player.x = W / 2;
	player.y = H - 120;
	player.live = true;
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].live = false;
		bullet[i].x = 0;
		bullet[i].y = 0;
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].live = false;
		enemyHp(i);
	}
	
}
void gameDraw() {
	loadImg();
	putimage(0, 0, &bk);
	putimage(player.x, player.y, &img_role, SRCINVERT);
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			putimage(bullet[i].x, bullet[i].y, &img_bullet, SRCINVERT);
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live) {
			if (enemy[i].type == BIG) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1], SRCINVERT  );
			}
			else {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0] , SRCINVERT);
			}
		}
	}
	shift();
}
void createBullet() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (!bullet[i].live) {
			bullet[i].x = player.x + 60;
			bullet[i].y = player.y;
			bullet[i].live = true;
			break;
		}
	}
}
void bulletMove(int speed) {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			bullet[i].y -= speed;
			if (bullet[i].y < 0) {
				bullet[i].live = false;
			}
		}
	}
}
bool Timer(int ms, int id) {
	static DWORD t[10];
	if (clock() - t[id] > ms) {

		t[id] = clock();
		return true;
	}

	return false;
}
void playerMove(int speed) {
	if (GetAsyncKeyState(VK_UP)) {
		if (player.y > 0) {
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		if (player.y < H-114) {
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		if (player.x > -57) {
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (player.x < W - 57) {
			player.x += speed;
		}
	}
	
	if (GetAsyncKeyState(VK_SPACE)&&Timer(100,1)) {
		createBullet();
	
	}
	
}
void createEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemy[i].live) {
			enemy[i].live = true;
			enemy[i].x = rand() % (W-58);
			enemy[i].y = 0;
			enemyHp(i);
			break;
		}
	}
}
void enemyMove(int speed) {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live) {
			enemy[i].y+=speed;
			if (enemy[i].y > H) {
				enemy[i].live = false;
			}
		}
	}
}

void playPlane() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemy[i].live) 
			continue;
		for (int j = 0; j < BULLET_NUM; j++) {
			if (!bullet[j].live)
				continue;
			if (bullet[j].x > enemy[i].x && bullet[j].x<enemy[i].x + enemy[i].w && bullet[j].y>enemy[i].y && bullet[j].y < enemy[i].y + enemy[i].h) {
				bullet[j].live = false;
				enemy[i].hp--;
			}
		}
		if (enemy[i].hp <= 0) {
			enemy[i].live = false;
		}
	}
}

int main() {
	initgraph(W,H);
	gameInit();
	mciSendString("open kun.mp3", 0, 0, 0);
	mciSendString("play kun.mp3 repeat", 0, 0, 0);
	BeginBatchDraw();
	while (1) {
		gameDraw();
		FlushBatchDraw();
		playerMove(1);
		bulletMove(3);
		if (Timer(500,0)) {
			createEnemy();
		}
		if (Timer(10, 2)) {
			enemyMove(1);
		}
		playPlane();
		
	}
	EndBatchDraw();
	return 0;
}