#ifndef DEF_H
#define DEF_H

#define CENTER_SCREEN_X 325

// Nb levels
#define LEVEL_MAX	2

//Taille de la map
#define MAX_MAP_X	200 //400
#define MAX_MAP_Y	15 //150

//Nb plateformes/Monstres Max
#define PLATEFORMS_MAX	50
#define MONSTERS_MAX	50

//Taille d'un monstre
#define MONSTER_WIDTH			40
#define MONSTER_HEIGTH			50
#define MONSTER_JUMP_WIDTH		37
#define MONSTER_JUMP_HEIGTH		56
#define MONSTER_SPEED_WIDTH		44
#define MONSTER_SPEED_HEIGTH	37
#define MONSTER_LIFE_WIDTH		64
#define MONSTER_LIFE_HEIGTH		59

//Nb Tiles par Monstres
#define MAX_FRAME_MONSTER			8
#define MAX_FRAME_MONSTER_JUMP		5
#define MAX_FRAME_MONSTER_SPEED		6
#define MAX_FRAME_MONSTER_LIFE		5

//Taille de notre player
#define PLAYER_WIDTH	42
#define PLAYER_HEIGTH	54

//Vitesse de déplacement en pixels du sprite
#define PLAYER_SPEED	4

// Etats
#define IDLE	0
#define WALK	1
#define JUMP	2
#define DEAD	4
#define BOUNCE	5

// Directions
#define RIGHT	1
#define LEFT	2
#define UP		3
#define DOWN	4

//Vitesse de déplacement en pixels des plateformes
#define PLATEFORM_SPEED	2

//Frame constante
#define TIME_BETWEEN_2_FRAMES_PLAYER	4
#define TIME_BETWEEN_2_FRAMES			20

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED	0.6
#define MAX_FALL_SPEED	15
#define JUMP_HEIGHT		10

// Taille de la fenêtre : 800x480 pixels
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	480

//Constantes pour les limites de la caméra avant scrolling
#define LIMITE_X	400
#define LIMITE_Y	220
#define LIMITE_W	100
#define LIMITE_H	80

//Enum pour les boutons (input)
enum { up, down, right, left, attack, jump, enter };

//Taille d'un tile
#define TILE_SIZE	32

//Tiles solide
#define BLANK_TILE	13 //99

//Tiles traversables
#define TILE_TRAVERSABLE	28 //80

//Tiles spéciales
//#define TILE_CHECKPOINT	23
#define TILE_RESSORT	23
#define TILE_PIKES		31
#define TILE_MONSTRE	24

//Tiles plateformes mobiles
#define TILE_PLATEFORM		21
#define TILE_PLATEFORM_UP	22

#endif