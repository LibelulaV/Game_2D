#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

#include <list>
#include <stdlib.h>
#include <time.h>

#define		GLFW_KEY_W		87
#define 	GLFW_KEY_S		83
#define 	GLFW_KEY_A		65
#define 	GLFW_KEY_D		68
#define 	GLFW_KEY_SPACE	32

#define		ASTEROID_DIM	40
#define		MISSILE_R		2

#define		MAX_ASTEROIDS	5

struct TMissile {
	int x;
	int y;
	int angle;
	int radius;
	int speed;

	TMissile(int x, int y, int radius, int angle, int speed) {
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->angle = angle;
		this->speed = speed; 
	}
};

static std::list<TMissile *> missiles;
static std::list<TMissile *>::const_iterator it_missiles;

struct TAsteroid{
	int x;
	int y;
	int speedx;
	int speedy;
	int r; 
	int g; 
	int b; 

	TAsteroid(int x, int y, int speedx, int speedy) {
		this->x = x;
		this->y = y;
		this->speedx = speedx;
		this->speedy = speedy;
		this->r = rand() % 254 + 1; 
		this->g = rand() % 254 + 1;
		this->b = rand() % 254 + 1;
	}
};

static std::list<TAsteroid *> asteroids;
static std::list<TAsteroid *>::const_iterator it_asteroids;

void initAsteroids() {
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		TAsteroid * asteroid = new TAsteroid(rand() % 750, rand() % 550, rand() % 100 + 100, rand() % 100 + 100);
		asteroids.push_front(asteroid);
	}
}

struct TSpaceship {
	int x; 
	int y; 
	int angle; 
	int height; 
	int width; 
	int rotateSpeed; 
	int speed; 

	TSpaceship(int x, int y, int width, int height, int angle) {
		this->x = x; 
		this->y = y; 
		this->height = height; 
		this->width = width; 
		this->angle = angle; 
		this->rotateSpeed = 150; 
		this->speed = 200; 
	}
};

void drawSpaceship(TSpaceship polygon1) {
	Renderer::Instance().PushMatrix(); 
	Renderer::Instance().TranslateMatrix(polygon1.x, polygon1.y, 0);
	Renderer::Instance().RotateMatrix(polygon1.angle, 0, 0, -1); 
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().DrawTriangle(-polygon1.width / 2, -polygon1.height / 2, polygon1.width, polygon1.height);
	Renderer::Instance().PopMatrix();
}

void drawAsteroids() {
	it_asteroids = asteroids.begin(); 
	while (it_asteroids != asteroids.end()) {
		Renderer::Instance().SetColor((*it_asteroids)->r, (*it_asteroids)->g, (*it_asteroids)->b, 255);
		Renderer::Instance().DrawRect((*it_asteroids)->x, (*it_asteroids)->y, ASTEROID_DIM, ASTEROID_DIM);
		it_asteroids++;
	}
}

void drawMissiles() {
	it_missiles = missiles.begin();
	while (it_missiles != missiles.end()) {
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawEllipse((*it_missiles)->x, (*it_missiles)->y, (*it_missiles)->radius, (*it_missiles)->radius);
		it_missiles++;
	}
}

void updateAsteroids() {
	it_asteroids = asteroids.begin();
	while (it_asteroids != asteroids.end()) {

		if ((*it_asteroids)->x <=0 || (*it_asteroids)->x + ASTEROID_DIM >= Screen::Instance().GetWidth())
			(*it_asteroids)->speedx *= -1;
		
		(*it_asteroids)->x += (*it_asteroids)->speedx * Screen::Instance().ElapsedTime();
	
		if ((*it_asteroids)->y <= 0 || (*it_asteroids)->y + ASTEROID_DIM >= Screen::Instance().GetHeight())
			(*it_asteroids)->speedy *= -1; 
		
		(*it_asteroids)->y += (*it_asteroids)->speedy * Screen::Instance().ElapsedTime();
		it_asteroids++;
	}
}

void updateMissiles() {
	it_missiles = missiles.begin();
	while (it_missiles != missiles.end()) {

		(*it_missiles)->x += (*it_missiles)->speed * Screen::Instance().ElapsedTime() * DegCos((*it_missiles)->angle);
		(*it_missiles)->y += (*it_missiles)->speed * Screen::Instance().ElapsedTime() * -DegSin((*it_missiles)->angle);

		if ((*it_missiles)->x - (*it_missiles)->radius <= 0 || (*it_missiles)->x + (*it_missiles)->radius >= Screen::Instance().GetWidth() ||
			(*it_missiles)->y - (*it_missiles)->radius <= 0 || (*it_missiles)->y + (*it_missiles)->radius >= Screen::Instance().GetHeight()) {
			delete *(it_missiles);
			it_missiles = missiles.erase(it_missiles); 
		}
		else 
			it_missiles++;
	}
}

bool checkPlayerAsteroidsCollitions(TSpaceship polygon1) {
	it_asteroids = asteroids.begin();
	bool game_over = false; 
	while (it_asteroids != asteroids.end() && !game_over) {
		
		// COLLITIONS
		/*int left_x = (*it_asteroids)->x;
		int right_x = (*it_asteroids)->x + ASTEROID_DIM;
		
		int up_y = (*it_asteroids)->y;
		int down_y = (*it_asteroids)->y + ASTEROID_DIM;*/

		/*if (((polygon1.x + polygon1.width / 2 >= right_x && polygon1.x + polygon1.width / 2 <= left_x) || 
			(polygon1.x - polygon1.width / 2 >= right_x && polygon1.x - polygon1.width / 2 <= left_x)) &&
			((polygon1.y + polygon1.height / 2 >= up_y && polygon1.y + polygon1.height / 2 <= down_y) || 
			(polygon1.y - polygon1.height / 2 >= up_y && polygon1.y - polygon1.height / 2 <= down_y)))*/

		int centerx = (*it_asteroids)->x + ASTEROID_DIM /2; 
		int centery = (*it_asteroids)->y + ASTEROID_DIM / 2;

		int dist = Distance(centerx, centery, (*it_asteroids)->x, (*it_asteroids)->y); 
		
		if (dist + polygon1.height / 2 >= Distance(centerx,centery, polygon1.x, polygon1.y))
			game_over = true; 
		else 
			it_asteroids++;
	}
	return game_over; 
}

void checkMissilesAsteroidsCollitions() {

}

int main(int argc, char* argv[]) {

	Screen& screen = Screen::Instance();
	screen.Open(800, 600, false); 

	bool game_over = false; 

	srand(time(NULL)); 

	initAsteroids(); 
	
	TSpaceship polygon1 = TSpaceship(screen.GetWidth()/2, screen.GetHeight()/2, 20, 20, 0); 

	while ((screen.IsOpened()) && (!screen.KeyPressed(GLFW_KEY_ESC)) && !game_over) {

		if (screen.KeyPressed(GLFW_KEY_LEFT)) 
			polygon1.angle++; 
		else if (screen.KeyPressed(GLFW_KEY_RIGHT)) 
			polygon1.angle -= screen.ElapsedTime() * polygon1.rotateSpeed;
		else if (screen.KeyPressed(GLFW_KEY_W)) 
			polygon1.y -= screen.ElapsedTime() * polygon1.speed;
		else if (screen.KeyPressed(GLFW_KEY_S))
			polygon1.y += screen.ElapsedTime() * polygon1.speed;
		else if (screen.KeyPressed(GLFW_KEY_A))
			polygon1.x -= screen.ElapsedTime() * polygon1.speed;
		else if (screen.KeyPressed(GLFW_KEY_D))
			polygon1.x += screen.ElapsedTime() * polygon1.speed;
		else if (screen.KeyPressed(GLFW_KEY_SPACE)) {
			TMissile * missile = new TMissile(polygon1.x, polygon1.y, MISSILE_R, polygon1.angle -90, 300);
			missiles.push_front(missile); 
		}

		if (polygon1.x - polygon1.width / 2 <= 0 || polygon1.x + polygon1.width / 2 >= screen.GetWidth() || 
			polygon1.y - polygon1.height / 2 <= 0 || polygon1.y + polygon1.height / 2 >= screen.GetHeight() || checkPlayerAsteroidsCollitions(polygon1)) {
			game_over = true; 
		}

		drawSpaceship(polygon1); 
		drawAsteroids(); 
		drawMissiles(); 

		//checkMissilesAsteroidsCollitions();

		updateAsteroids(); 
		updateMissiles(); 

		// Refrescamos la pantalla
		screen.Refresh();

		// Limpiar pantalla
		Renderer::Instance().Clear(0, 0, 0);
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}