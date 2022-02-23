#include "harry.hpp"
#include "assets.hpp"


#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 120

using namespace blit;

Font font(font5x7);

int state;

struct GAME
{
    int state;
    int level[256][4];
};

GAME game;

struct PLAYER 
{
    int state;
    int sprite;
    int alpha;
    int fade;
    bool flip;
    int x;
    int y;
    int dx;
    int timer;
    int level;
    int start_x;
    bool hide;
    int hide_x;
};

PLAYER p;
int level_new[256][4]{
    {0,3,99,14}, {0,1,3,18}, {4,5,9,18}, {4,6,99,99}, {0,1,2,19}, {4,5,9,11}, {4,10,99,13}, {4,5,7,14}, {4,8,99,17}, {4,5,10,17}, {4,6,99,99}, {0,3,99,17}, {0,3,99,18}, {0,2,99,19}, {0,2,12,99}, 
    {0,2,99,14}, {4,5,7,18}, {4,5,10,18}, {4,6,99,99}, {0,3,99,18}, {4,5,9,18}, {4,6,99,99}, {0,1,2,18}, {4,5,9,19}, {4,5,6,99}, {0,1,2,16}, {4,5,7,19}, {4,5,10,11}, {4,10,99,13}, {4,5,7,14},
    {4,8,99,18}, {4,5,10,18}, {4,6,99,99}, {0,1,3,17}, {4,5,9,17}, {4,6,99,99}, {0,2,99,18}, {0,3,99,18}, {0,2,99,16}, {0,1,2,18}, {4,5,9,16}, {4,10,99,13}, {4,5,9,12}, {4,10,99,13}, {4,5,7,19},
    {4,5,10,12}, {4,10,99,13}, {4,5,7,18}, {4,5,10,16}, {4,10,99,13}, {4,5,9,12}, {4,10,99,13}, {4,5,7,18}, {4,5,10,18}, {4,6,99,99}, {0,1,2,19}, {4,5,9,12}, {4,10,99,13}, {5,7,99,17}, {4,5,10,17},
    {4,6,99,99}, {0,3,99,19}, {0,3,11,99}, {0,1,2,11}, {4,5,7,11}, {4,8,12,99}, {4,8,99,16}, {8,99,99,19}, {4,5,10,12}, {4,10,99,13}, {4,5,7,19}, {4,5,10,11}, {4,10,99,13}, {4,5,7,12}, {4,8,99,16},
    {4,8,99,18}, {4,5,10,16}, {4,10,99,13}, {4,5,9,11}, {4,10,99,13}, {4,5,7,16}, {4,8,99,18}, {4,5,10,14}, {4,10,99,13}, {4,5,9,18}, {4,5,6,99}, {0,2,99,14}, {0,3,99,17}, {4,5,9,17}, {4,6,99,99},
    {0,2,99,19}, {0,3,12,99}, {0,1,2,16}, {4,5,7,19}, {4,5,10,12}, {4,10,99,13}, {4,5,7,17}, {4,5,10,18}, {4,5,6,99}, {0,3,11,99}, {0,1,3,11}, {4,5,7,12}, {4,8,99,14}, {4,8,99,18}, {4,5,10,19},
    {4,5,6,99}, {0,1,3,12}, {4,5,7,14}, {8,99,99,18}, {4,5,10,19}, {4,5,6,99}, {0,1,3,14}, {4,5,7,17}, {4,5,10,18}, {4,5,6,99}, {0,3,99,16}, {0,1,3,19}, {4,5,9,12}, {4,10,99,13}, {4,5,7,18},
    {4,5,10,14}, {4,10,99,13}, {4,5,9,18}, {4,6,99,99}, {0,1,2,17}, {4,5,9,18}, {4,5,6,99}, {0,2,99,16}, {0,1,3,18}, {4,5,9,14}, {4,10,99,13}, {4,5,9,18}, {4,6,99,99}, {0,1,2,12}, {4,5,9,16},
    {4,10,99,13}, {4,5,9,14}, {4,10,99,13}, {4,5,9,19}, {4,5,6,99}, {0,1,2,12}, {4,5,7,16}, {4,8,99,19}, {4,5,10,11}, {4,10,99,13}, {4,5,7,16}, {4,8,99,19}, {4,5,10,12}, {4,10,99,13}, {4,5,7,18},
    {4,5,10,19}, {4,5,6,99}, {0,1,3,11}, {4,5,7,12}, {4,8,99,16}, {4,8,99,19}, {5,10,11,99}, {4,10,99,13}, {4,5,7,11}, {4,8,11,99}, {4,8,12,99}, {4,8,99,16}, {4,8,99,18}, {4,5,10,14}, {4,10,99,13},
    {4,5,9,19}, {4,5,6,99}, {0,1,2,14}, {4,5,7,18}, {5,10,99,19}, {4,5,6,99}, {0,1,3,16}, {4,5,7,18}, {4,5,10,16}, {4,10,99,13}, {4,5,9,14}, {4,10,99,13}, {4,5,9,18}, {4,5,6,99}, {0,2,12,99},
    {0,1,3,14}, {4,5,7,17}, {4,5,10,17}, {4,6,99,99}, {0,3,99,18}, {0,3,99,19}, {0,2,11,99}, {0,1,2,12}, {4,5,7,16}, {4,8,99,18}, {4,5,10,16}, {4,10,99,13}, {4,5,9,16}, {4,10,99,13}, {4,5,9,16},
    {4,10,99,13}, {4,5,9,11}, {4,10,99,13}, {4,5,7,11}, {4,8,12,99}, {4,8,99,14}, {4,8,99,18}, {5,10,99,18}, {4,6,99,99}, {0,1,3,18}, {4,5,9,14}, {4,10,99,13}, {4,5,9,17}, {4,6,99,99}, {0,2,99,18},
    {0,3,99,14}, {0,1,2,18}, {4,5,9,19}, {4,5,6,99}, {0,1,2,11}, {4,5,7,11}, {4,8,11,99}, {4,8,11,99}, {4,8,11,99}, {4,8,12,99}, {4,8,99,14}, {4,8,99,17}, {4,5,10,17}, {4,6,99,99}, {0,3,99,18},
    {0,3,99,16}, {0,1,2,19}, {4,5,9,11}, {4,10,99,13}, {4,5,7,12}, {4,8,99,14}, {4,8,99,17}, {4,5,10,18}, {4,5,6,99}, {0,3,12,99}, {0,1,3,16}, {4,5,7,18}, {4,5,10,14}, {4,10,99,13}, {4,5,9,17},
    {4,6,99,99}, {0,2,99,17}, {0,3,99,17}, {0,2,99,18}, {0,2,99,18}, {0,2,99,14}, {0,1,2,17}, {4,5,9,18}, {4,5,6,99}, {0,2,11,99}, {0,1,3,12}, {4,5,7,14}, {4,8,99,17}, {4,5,10,18}, {4,5,6,99}, {98,99,99,99}};
int level[256][4];

struct SCORE
{
    int netto;
    int bonus;
    int coin;
};

SCORE score;

int jump[20] {-1, -1, -1, -1, 0, -1, 0, -1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 2, 2};
int jump_sound = 0;

struct WATCH
{
    int s;
    int m;
};

WATCH watch;

struct INFO
{
    std::string txt1 = "";
    std::string txt2 = ""; 
    int fader = 0;
    int d_fade = 3;
    int counter = 0;
};

INFO info;

blit::Timer seconds;

struct TIMBER 
{
    int sprite[3] = {195, 195, 199};
    int ani = 0;
    int typ = 0;
    int x[3] = {142, 124, 106};
    int counter = 0;
    int timer;
}; 

TIMBER timber;

int timber_pos[5][3]
{{142, 124, 106}, {142, 106, 70}, {142, 128, 70}, {142, 128, 92}, {142, 106, 92}};

struct SCORPION 
{
    int sprite = 227;
    bool flip = false;
    int ani = 0;
    int x = 134;
    int dx = -1;
    int timer;
};

SCORPION scorpion;

struct LIANA
{
    float angle = 90;
    float dangle = .8f;
    int state = 0;
    int note = 0;
    int timer;
};

LIANA liana;

int liana_sound[6][2] 
{{300,40},{500,30},{600,12},{500,12},{600,12},{500,30}};

struct LAKE 
{
    int s = 32;
    int ds = -1;
    int timer;
};

LAKE lake;

struct CROC
{
    int sprite = 211;
    int dx = 0;
    int timer;
};

CROC croc;

struct ITEM
{
    int flip = false;
    int ani = 0;
    int timer;
}; 

ITEM snake;
ITEM fire;
ITEM gold;

void start()
{
    for (int t=0;t<256;t++)
    {
        for (int i=0;i<4;i++)
        {
            level[t][i] = level_new[t][i];
        }
    }

    p.state = 0;
    p.sprite = 48;
    p.alpha = 0;
    p.fade = 5;
    p.flip = false;
    p.x = 0;
    p.y = 54;
    p.dx = 0;
    p.level = 0;
    p.start_x = 0;
    p.hide = false;
    p.hide_x = 0;

    score.netto = 500;
    score.bonus = 0;
    score.coin = 0;
    state = 1;

    timber.counter = 0;

    watch.s = 0;
    watch.m = 30;// 30
    seconds.start();
}

void seconds_update(blit::Timer &t)
{
    watch.s--;
    if (watch.s < 0)
    {
        watch.s = 59;
        watch.m--;
        if (watch.m < 0) // Game over
        {
            seconds.stop();
            watch.m = 0;
            watch.s = 0;
            state = 2;
            channels[4].trigger_attack();               
        }
    }
}

void ScoreUpdate()
{
    if (score.bonus > 0)
    {
        score.netto++;
        score.bonus--;
    }
    else if (score.bonus < 0)
    {
        if (score.netto > 0)
        {
            score.netto--;
            score.bonus++;
        }
        else
        {
            score.bonus = 0;
        }
    }
}

void TimberReset()
{
    for (int t = 0; t < 3; t++) // timber auf Ausgangsposition
    {
        timber.x[t] = timber_pos[timber.counter][t];
        timber.sprite[t] = 195;
        if (timber.x[t] < 107)
        {
            timber.sprite[t] = 199;
        }
    } 
}

void NewLevel(int dl)
{
    if (p.y > 55)
    {
        dl = dl * 3;
    }
    p.level += dl;
    if (p.level < 0)
    {
        p.level += 255;
    }
    else if (p.level > 254)
    {
        p.level -= 255;
    }
    p.start_x = p.x;

    timber.counter += dl;
    if (timber.counter < 0)
    {
        timber.counter += 5;
    }
    else if (timber.counter > 4)
    {
        timber.counter -= 5;
    }

    TimberReset();
    lake.s = 32;
    lake.ds = -1;

    scorpion.x = 70 + (rand() % 70);
}

void RunAni()
{
    p.timer++;
    if (p.timer == 3)
    {
        p.timer = 0;
        p.x += p.dx;
        p.sprite++;
        if (p.sprite > 15)
        {
            p.sprite = 0;
        }
        if (p.sprite == 5 || p.sprite == 13)
        {
            channels[1].trigger_attack();
        }
    }   
}

void PlayerControl()
{ 
    if (p.state == 0) // stehen & laufen
    {
        if (buttons & Button::DPAD_LEFT || joystick.x < 0)
        {
            p.flip = true;
            p.dx = -1;
            if (p.x < -1)
            {
                p.x = 152;
                NewLevel(-1);
            }
            RunAni();
        }
        else if (buttons & Button::DPAD_RIGHT || joystick.x > 0)
        {
            p.flip = false;
            p.dx = 1;
            if (p.x > 153)
            {
                p.x = 0;
                NewLevel(1);
            }
            RunAni();
        }
        else
        {
            p.sprite = 48;
            p.dx = 0;
            p.timer = 0;
        }
        if (buttons.pressed & Button::A) // jump
        {
            p.state = 1;
            p.sprite = 16;
            jump_sound = 300;
            channels[0].decay_ms = 240;
            channels[0].trigger_attack();
        }
    }

    else if (p.state == 1) //jump
    {
        p.timer--;
        if (p.timer < 1)
        {
            p.timer = 3;
            p.x += p.dx;
            if (p.x < -1)
            {
                p.x = 154;
                NewLevel(-1);
            }
            else if (p.x > 153)
            {
                p.x = -2;
                NewLevel(1);
            }
            p.y += jump[p.sprite - 16];
            p.sprite++;
            if (p.sprite == 35)
            {
                p.sprite = 48;
                p.state = 0;
                p.timer = 0;
            }

        }
        jump_sound += 10;
        channels[0].frequency = jump_sound;  
    }
    else if (p.state == 2) //climb
    {
        p.timer++;
        if (p.timer == 9)
        {
            p.timer = 0;
            if (buttons & Button::DPAD_DOWN || joystick.y > 0) // down
            {
                p.y++;
                if (p.y == 86)
                {
                    p.sprite = 64;
                    p.state = 0;
                }
                else
                {
                    p.sprite++;
                    if (p.sprite == 64)
                    {
                        p.sprite = 58;
                    }
                }
            }
            else if (buttons & Button::DPAD_UP || joystick.y < 0 || buttons & Button::DPAD_LEFT || joystick.x < 0 || buttons & Button::DPAD_RIGHT || joystick.x > 0) // up
            {
                p.y--;
                p.sprite--;
                if (p.y == 54)
                {
                    p.sprite = 48;
                    p.x -= (p.dx * 5);
                    p.state = 0;
                }
                else if (p.y == 59)
                {
                    p.sprite = 57;
                } 
                else if (p.y > 59)
                {
                    if (p.sprite == 57)
                    {
                        p.sprite = 63;
                    } 
                }
            }      
        }
        if (p.y > 57)
        {
            if (buttons & Button::DPAD_RIGHT || joystick.x > 0)
            {
                p.flip = true;
                p.dx = -1;
            } 
            else if (buttons & Button::DPAD_LEFT || joystick.x < 0)
            {
                p.flip = false;
                p.dx = 1;
            }
        }
    }
    else if (p.state == 5) // fall
    {
        p.timer++;
        if (p.timer == 2)
        {
            p.timer = 0;
            p.y++;
            if (p.y == 86)
            {
                channels[2].trigger_attack();
                score.bonus -= 100;
                p.sprite = 48;
                p.state = 6;
            }
        }
    }
    else if (p.state == 6) // stand up
    {
        p.timer++;
        if (p.timer == 12)
        {
            p.timer = 0;
            p.sprite++;
            if (p.sprite == 52)
            {
                p.sprite = 48;
                p.state = 0;
            }
        }
    }
    else if (p.state == 9) // win
    {
        jump_sound += 10;
        channels[0].frequency = jump_sound;  

        int res_s = (watch.m * 60) + watch.s;
        if (res_s > 0)
        {
            watch.s--;
            if (watch.s < 0)
            {
                watch.s = 59;
                watch.m--;
            }
            score.bonus += 5;        
        }  

        p.timer++;
        if (p.timer == 3)
        {
            p.timer = 0;
            p.y += jump[p.sprite - 16];
            p.sprite++;
            if (p.sprite == 35)
            {
                if (score.bonus > 0)
                {
                    p.sprite = 16;
                    p.flip = !p.flip;
                    jump_sound = 300;
                    channels[0].decay_ms = 300;
                    channels[0].trigger_attack();
                }
                else
                {
                    p.sprite = 48;
                    p.timer = 0;
                    info.txt1 = "CONGRATULATION!";
                    info.txt2 = info.txt1;
                    state = 3;          
                }
            }
        }
    }
}

void PlayerRender()
{
    screen.alpha = p.alpha;
    screen.sprite(p.sprite, Point(p.x, p.y), p.flip);
    screen.sprite(p.sprite + 64, Point(p.x, p.y + 8), p.flip);
    screen.alpha = 255;
}

void LadderUpdate(bool hole)
{
    if (p.state == 0)
    {
        if (p.y == 54) // obere Ebene
        {
            if (hole)
            {
                if ((p.x < 44 && p.x > 36) || (p.x < 116 && p.x > 108)) // sturz 2, 3
                {
                    p.sprite = 35;
                    p.state = 5;  
                }
            }
            if(p.x < 82 && p.x > 70) 
            {
                if (p.x < 80 && p.x > 72) // sturz
                {
                    p.sprite = 35;
                    p.state = 5;  
                }
                else if (buttons & Button::DPAD_DOWN || joystick.y > 0) // runter klettern
                {
                    p.x = 76;
                    p.y = 55;
                    if (p.flip)
                    {
                        p.dx = -1;
                    }
                    else 
                    {
                        p.dx = 1;
                    }
                    p.sprite = 52;
                    p.state = 2; 
                } 
            }
        }
        else // untere Ebene
        {
            if (p.x < 82 && p.x > 70 && (buttons & Button::DPAD_UP || joystick.y < 0)) // hoch klettern
            {
                p.x = 76;
                p.y = 85;
                if (p.flip)
                {
                    p.dx = -1;
                }
                else 
                {
                    p.dx = 1;
                }
                p.sprite = 58;
                p.state = 2;  
            } 
        }
    }
}

void LadderRender()
{
    screen.sprite(Rect(1, 11, 1, 5), Point(76, 64)); // Leiter
}

void HoleRender()
{
    screen.sprite(178, Point(40, 64)); // Loch links
    screen.sprite(178, Point(112, 64), true); // Loch rechts
}

void TimberUpdate(int number)
{
    if (p.y < 67 && p.y > 51) //63 Collision
    {
        for (int i = 0; i < number; i++)
        {
            if (p.x < (timber.x[i] + 3) && p.x > (timber.x[i] - 4)) 
            {
                if (p.y < 63)
                {
                    score.bonus -= 150;
                    if (number == 1)
                    {
                        timber.typ = 99;
                    }
                    else
                    {
                        timber.typ = level[p.level][3] - 1;
                    }
                    state = 2; // Died
                    channels[4].trigger_attack();
                }
                else
                {
                    p.hide = true;
                    p.hide_x = timber.x[i];
                }
                break;   
            }
        }
    }
}

void Timber2Update(int number)
{
    timber.timer++;
    if (timber.timer > 2)
    {
        timber.timer = 0;
        for (int i = 0; i < number; i++)
        {
            timber.x[i]--;
            if (timber.x[i] < -8)
            {
                timber.sprite[i] = 195;
                timber.x[i] = 156;
            }
            else if (timber.x[i] == 53 || timber.x[i] == 106)
            {
                timber.sprite[i] += 4;
            }
        }
        timber.ani++;
        if (timber.ani > 3)
        {
            timber.ani = 0;
        }
    }
}

void TimberRender(int number)
{
    for (int i = 0; i < number; i++)
    {
        screen.sprite(timber.sprite[i] + timber.ani, Point(timber.x[i], 63));
    }  
}

void WallUpdate(int x, bool flip)
{
    if (p.y > 68) // Collision
    {
        if ((flip == true && p.x < x + 8 && p.x > x) || (flip == false && p.x < x && p.x > x - 8))
        {
            p.hide = true;
            p.hide_x = x;
        }
        if (p.x < (x + 5) && p.x > (x - 5))
        {
            p.x -= p.dx;
        }
    }
}

void WallRender(int x, bool flip)
{
    screen.sprite(Rect(2, 12, 1, 4), Point(x, 72), flip);
}

void ScorpionUpdate()
{
    scorpion.timer++;
    if (scorpion.timer > 10)
    {
        scorpion.timer = 0;
        scorpion.x += scorpion.dx;
        if (scorpion.x == 0 || scorpion.x == 153)
        {
            scorpion.dx = -scorpion.dx;
            scorpion.flip = !scorpion.flip;
        }
        else if (p.y > 62)
        {
            if (p.x > scorpion.x + 8)
            {
                scorpion.dx = 1;
                scorpion.flip = true;
            }
            else if (p.x < scorpion.x - 8)
            {
                scorpion.dx = -1;
                scorpion.flip = false;
            }
        }
        scorpion.ani++;
        if (scorpion.ani > 3)
        {
            scorpion.ani = 0;
        }
    }
    
    if (p.y > 82 && p.x < scorpion.x + 6 && p.x > scorpion.x - 6) // Collision
    {
        score.bonus -= 250;
        state = 2; // Died 
        channels[4].trigger_attack();  
    }
}

void ScorpionRender()
{
    screen.sprite(scorpion.sprite + scorpion.ani, Point(scorpion.x, 95), scorpion.flip);
}

void LianaUpdate()
{
    liana.angle+=liana.dangle;
    if (liana.angle <= 25 || liana.angle >= 155)
    {
        liana.dangle =- liana.dangle;
        if (p.state == 3)
        {
            p.flip = !p.flip;
            p.dx = -p.dx;
        }

    }
    if (liana.note > 0) {
        channels[0].frequency = liana_sound[liana.note - 1][0];
        liana.timer++;
        if (liana.timer > liana_sound[liana.note - 1][1]) {
            liana.timer = 0;
            liana.note++;
            if (liana.note > 6){
                liana.note = 0;
            }
        } 
    }

    if (p.state == 1 && p.x < (80 + cosf(liana.angle * pi / 180) * 40) && p.x > (73 + cosf(liana.angle * pi / 180) * 40) && p.y < (45 + abs(sinf(liana.angle * pi / 180) * 10)))
    {
        p.sprite = 36;
        liana.note = 1;
        liana.timer = 0;
        channels[0].frequency = 200;
        channels[0].decay_ms = 1800;
        channels[0].trigger_attack();
        p.state = 3;
        if (liana.dangle > 0)
        {
            p.flip = true;
            p.dx = -1;
        }
        else
        {
            p.flip = false;
            p.dx = 1;
        }
    }
    else if (p.state == 3)
    {
        p.x = 76 + cosf(liana.angle * pi / 180) * 40;
        p.y = 39 + abs(sinf(liana.angle * pi / 180) * 10);

        if (buttons.pressed & Button::A)
        {
            p.sprite = 26;
            p.y = 48;
            p.state = 4;
            jump_sound = 300;
            channels[0].decay_ms = 200;
            channels[0].trigger_attack();
        }
    }
    else if (p.state == 4) // Absprung
    {
        p.timer--;
        if (p.timer < 1)
        {
            p.timer = 3;
            p.x += p.dx;
            p.y += jump[p.sprite - 16];
            p.sprite++;
            if (p.sprite == 35)
            {
                p.sprite = 48;
                p.state = 0;
                p.timer = 0;
            }
        }
        jump_sound += 10;
        channels[0].frequency = jump_sound;  
    }
}

void LianaRender()
{
    screen.pen = Pen(194, 195, 199);
    screen.line(Point(80 + cosf(liana.angle * pi / 180) * 20, 32), Point(80 + cosf(liana.angle * pi / 180.0f) * 40, 48 + abs(sinf(liana.angle * pi / 180) * 10)));
}

void LakeUpdate()
{
    if (p.y == 54)
    {
        if (lake.s > 0 and p.x < 77 + lake.s && p.x > 75 - lake.s) // sinking
        {
            score.bonus -= 250;
            p.sprite = 37;
            p.state = 7;
            state = 2; 
        }
    }
}

void Lake2Update()
{
    lake.timer++;
    if (lake.timer > 200)
    {
        lake.s += lake.ds;
        if (lake.s <= 0 || lake.s >= 32)
        {
            lake.ds = -lake.ds;
            lake.timer = 0;
        }
    }
}

void LakeRender(int y)
{
    screen.stretch_blit(screen.sprites,Rect(56, y, 8, 8), Rect(80 - lake.s, 64, 2 * lake.s, 8));
}

void CrocUpdate()
{
    croc.timer++;
    if(croc.timer > 275)
    {
        croc.timer = 0;
        if (croc.sprite == 211)
        {
            croc.sprite = 212;
            croc.dx = 6;
        }
        else
        {
            croc.sprite = 211;
            croc.dx = 0;
        }
    }

    if (p.y == 54)
    {
        if ((p.x < 53 + croc.dx && p.x > 43) || (p.x < 71 + croc.dx && p.x > 63) || (p.x < 89 + croc.dx && p.x > 81) || (p.x < 109 && p.x > 99)) // Harry died
        {
            if ((p.x < 53 + croc.dx && p.x > 43) || (p.x < 71 + croc.dx && p.x > 63) || (p.x < 89 + croc.dx && p.x > 81) || (p.x < 109 && p.x > 99)) // Harry died
            {
                score.bonus -= 250;
                if ((p.x < 59 && p.x > 52) || (p.x < 77 && p.x > 70) || (p.x < 95 && p.x > 88)) 
                {
                    state = 2;
                    channels[4].trigger_attack();
                }
                else // sinking
                {
                    p.sprite = 37;
                    p.state = 7;
                    state = 2;
                }
            }
        }
    }
}

void CrocRender()
{
    screen.stretch_blit(screen.sprites,Rect(56, 112, 8, 8), Rect(48, 64, 64, 8));
    for (int i = 57; i < 95; i += 18)
    {
        screen.sprite(croc.sprite, Point(i, 65));
        screen.sprite(213, Point(i + 8, 65));
    }
}

void SnakeUpdate()
{
    snake.timer++;
    if (snake.timer > 25)
    {
        snake.timer = 0;
        snake.ani++;
        if (snake.ani > 1)
        {
            snake.ani = 0;
        }
    }

    if (p.x < 142 && p.x > 130 && p.y < 55 && p.y > 51) // Collision
    {
        {
            state = 2; // Died
            score.bonus -= 250;
            channels[4].trigger_attack();
        }
    }
}

void SnakeRender()
{
    if (p.x > 136)
    {
        screen.sprite(243 + snake.ani , Point(136, 63), true);
    }
    else
    {
        screen.sprite(243 + snake.ani , Point(136, 63));
    }

}

void FireUpdate()
{
    fire.timer++;
    if (fire.timer > 3)
    {
        fire.timer = 0;
        fire.ani = (rand() % 3);
    }

    if (p.x < 142 && p.x > 130 && p.y < 55 && p.y > 51) // Collision
    {
        {
            state = 2; // Died
            score.bonus -= 250;
            channels[4].trigger_attack();
        }
    }
}

void FireRender()
{
    screen.sprite(215 + fire.ani , Point(136, 63));
}

void GoldUpdate()
{
    gold.timer++;
    if (gold.timer > 9)
    {
        gold.timer = 0;
        gold.ani++;
        if (gold.ani > 3)
        {
            gold.ani = 0;
        }
    }

    if (p.x < 142 && p.x > 130 && p.y < 55 && p.y > 51) // Collision
    {
        score.bonus += 500;
        level[p.level][3] = 99;
        score.coin++;
        channels[3].trigger_attack();
        if (score.coin == 32) // 32
        {
            seconds.stop();
            p.sprite = 16;
            p.y = 54;
            p.timer = 0;
            p.state = 9; // Win
            jump_sound = 300;
            channels[0].decay_ms = 300;
            channels[0].trigger_attack();
        }
    }
}

void GoldRender()
{
    screen.sprite(218 + gold.ani , Point(136, 63));
}

void InfoUpdate()
{
    info.fader += info.d_fade;
    if (info.fader < 1 || info.fader > 254)
    {
        info.d_fade = -info.d_fade;
        if (info.fader == 0)
        {
            info.txt1 == info.txt2? info.txt1 = "PRESS A TO SKIP": info.txt1 = info.txt2;
        }
    }
    if (buttons.released & Button::A)
    {
        state = 0;
    }
}

void InfoRender()
{
    screen.alpha = info.fader;
    screen.pen = Pen(95, 87, 79);
    screen.text(info.txt1, minimal_font, Point(80,56), true, TextAlign::center_center);
    screen.pen = Pen(255, 241, 232);
    screen.text(info.txt1, minimal_font, Point(79,56), true, TextAlign::center_center);
    screen.alpha = 255;
}

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() 
{
    set_screen_mode(ScreenMode::lores);

    screen.sprites = Surface::load(asset_sprites);

    // Jump, Swing Sound
    channels[0].waveforms = Waveform::TRIANGLE; 
    channels[0].frequency = 0;
    channels[0].attack_ms = 5;
    channels[0].decay_ms = 0;
    channels[0].sustain = 0;
    channels[0].release_ms = 10;

    // Run Sound
    channels[1].waveforms = Waveform::SQUARE;
    channels[1].frequency = 200;
    channels[1].attack_ms = 10;
    channels[1].decay_ms = 30;
    channels[1].sustain = 0;
    channels[1].release_ms = 10;

    // Fall Sound
    channels[2].waveforms = Waveform::NOISE;
    channels[2].frequency = 600;
    channels[2].attack_ms = 5;
    channels[2].decay_ms = 250;
    channels[2].sustain = 0;
    channels[2].release_ms = 100;

    // Coin Sound
    channels[3].waveforms = Waveform::TRIANGLE;
    channels[3].frequency = 1800;
    channels[3].attack_ms = 5;
    channels[3].decay_ms = 250;
    channels[3].sustain = 0;
    channels[3].release_ms = 10;

    // Kill, end of time Sound
    channels[4].waveforms = Waveform::SQUARE;
    channels[4].frequency = 100;
    channels[4].attack_ms = 5;
    channels[4].decay_ms = 400;
    channels[4].sustain = 0;
    channels[4].release_ms = 50;

    seconds.init(seconds_update, 1000, -1);

    state = 0;
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) 
{
    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.clear();

    screen.alpha = 255;
    screen.mask = nullptr;

    if (state == 0) 
    {
        for (int i=0;i<120;i++)
        {
            screen.pen = Pen(250 - (i*2), 125 - i, 250 - (i*2));
            screen.rectangle(Rect(0,i,160,2));
        }
        screen.pen = Pen(29, 43, 83);
        screen.line(Point(81 + cosf(liana.angle * pi / 180) * 8, 20), Point(81 + cosf(liana.angle * pi / 180.0f) * 40, 71 + abs(sinf(liana.angle * pi / 180) * 10)));
        screen.pen = Pen(224, 224, 224);
        screen.line(Point(79 + cosf(liana.angle * pi / 180) * 8, 20), Point(79 + cosf(liana.angle * pi / 180.0f) * 40, 71 + abs(sinf(liana.angle * pi / 180) * 10)));
        screen.line(Point(80 + cosf(liana.angle * pi / 180) * 8, 20), Point(80 + cosf(liana.angle * pi / 180.0f) * 40, 71 + abs(sinf(liana.angle * pi / 180) * 10)));
        screen.sprite(Rect(14,14,2,2), Point(73 + cosf(liana.angle * pi / 180.0f) * 40, 65 + abs(sinf(liana.angle * pi / 180) * 10)), p.flip);
        screen.sprite(Rect(12,14,2,2), Point(72 + cosf(liana.angle * pi / 180.0f) * 40, 64 + abs(sinf(liana.angle * pi / 180) * 10)), p.flip);
        screen.sprite(Rect(0, 16, 13, 6), Point(31, 16));
        screen.pen = Pen(128, 128, 128);
        screen.text("PRESS X TO START", minimal_font, Point(80,104), true, TextAlign::center_center);
        screen.pen = Pen(240, 240, 240);
        screen.text("PRESS X TO START", minimal_font, Point(79,104), true, TextAlign::center_center);
    }
    else
    {
        screen.stretch_blit(screen.sprites,Rect(0, 104, 8, 13), Rect(0, 0, 160, 104)); // Hintergrund
        for (int i = 0; i < 160; i += 40)
        {
            screen.stretch_blit(screen.sprites,Rect(80, 112, 8, 8), Rect(16 + i, 42, 8, 22)); // Baumstamm
            screen.sprite(233, Point(12 + i, 34));
            screen.sprite(233, Point(20 + i, 34), true);
        }

        for (int i = 0; i < 4; i++)
        {
            switch(level[p.level][i])
            {
                case 0:
                    LadderRender();
                    break;
                case 1:
                    LadderRender();
                    HoleRender();
                    break;
                case 2:
                    WallRender(8, false);
                    break;
                case 3:
                    WallRender(144, true);
                    break;
                case 4:
                    ScorpionRender();
                    break;
                case 5:
                    LianaRender();
                    break;
                case 6:
                    CrocRender();
                    break;
                case 7: // Water
                case 8: 
                    LakeRender(112);
                    break;
                case 9: // Moor
                case 10: 
                    LakeRender(120);
                    break;
                case 11:
                    SnakeRender();
                    break;
                case 12:
                    FireRender();
                    break;
                case 13:
                    GoldRender();
                    break;
                case 14:
                case 15:
                case 16:
                    TimberRender(level[p.level][i] - 13);
                    break;
                case 17:
                case 18:
                case 19:
                    TimberRender(level[p.level][i] - 16);
                    break;
            }
        }

        PlayerRender();

        if (p.hide)
        {
            if (p.hide_x == 8)
            {
                WallRender(8, false);
            }
            else if (p.hide_x == 144)
            {
                WallRender(144, true);
            }
            else
            {
                screen.sprite(199 + timber.ani, Point(p.hide_x, 63));
            }
            p.hide = false;
        }

        for (int i = 0; i < 160; i += 40)
        {
            screen.stretch_blit(screen.sprites,Rect(64, 112, 8, 4), Rect(i, 32, 40, 4)); // Baum
            screen.stretch_blit(screen.sprites,Rect(0, 120, 8, 6), Rect(i, 72, 40, 6)); // Boden
            screen.stretch_blit(screen.sprites,Rect(0, 120, 8, 6), Rect(i, 104, 40, 6)); // Boden
        }        

        screen.sprite(192, Point(126, 20));
        std::string sec = std::to_string(watch.s);
        if (watch.s < 10)
        {
            sec = "0" + std::to_string(watch.s);
        }
        std::string min = std::to_string(watch.m);
        if (watch.m < 10)
        {
            min = "0" + std::to_string(watch.m);
        }
        screen.pen = Pen(95, 87, 79);
        screen.text(min + ":" + sec, font, Point(135,20));
        screen.text(std::to_string(score.netto), font, Point(6,5));
        screen.text(std::to_string(p.level + 1), font, Point(6,112));
        screen.pen = Pen(255, 241, 232);
        screen.text(min + ":" + sec, font, Point(134,20));
        screen.text(std::to_string(score.netto), font, Point(5,5));
        screen.text(std::to_string(p.level + 1), font, Point(5,112));

        screen.sprite(Rect(3, 11, 7, 1), Point(105, 5)); // Empty coin slot
        screen.sprite(Rect(3, 11, 7, 1), Point(105, 12)); // Empty coin slot
        for (int i = score.coin; i > 0; i--)
        {
            if (i < 17)
            {
                screen.sprite(176, Point(102 + (i * 3), 5));
            }
            else
            {
                screen.sprite(176, Point(54 + (i * 3), 12));
            }
        }

        if (state == 3)
        {
            InfoRender();
        }
    }
    screen.pen = Pen(0, 0, 0);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) 
{
    if (state == 0)
    {
        liana.angle+=liana.dangle;
        if (liana.angle <= 25 || liana.angle >= 155)
        {
            liana.dangle =- liana.dangle;
        }
        liana.dangle > 0? p.flip = true: p.flip = false;
        
        if (buttons.released & Button::A)
        {
            start();
            state = 2;
        }
    }
    else if (state == 1)
    {
        PlayerControl();
        ScoreUpdate();

        for (int i = 0; i < 4; i++)
        {
            switch(level[p.level][i])
            {
                case 0:
                    LadderUpdate(false);
                    break;
                case 1:
                    LadderUpdate(true);
                    break;
                case 2:
                    WallUpdate(8, false);
                    break;
                case 3:
                    WallUpdate(144, true);
                    break;
                case 4:
                    ScorpionUpdate();
                    break;
                case 5:
                    LianaUpdate();
                    break;
                case 6:
                    CrocUpdate();
                    break;
                case 7: // Water
                case 9: // Moor
                    lake.s = 32;
                    LakeUpdate();
                    break;
                case 8: // Water2
                case 10: // Moor2
                    Lake2Update();
                    LakeUpdate();
                    break;
                case 11:
                    SnakeUpdate();
                    break;
                case 12:
                     FireUpdate();
                     break;
                case 13:
                    GoldUpdate();
                    break;
                case 14:
                case 15:
                case 16:
                    TimberUpdate(level[p.level][i] - 13);
                    break;
                case 17:
                case 18:
                case 19:
                    Timber2Update(level[p.level][i] - 16);
                    TimberUpdate(level[p.level][i] - 16);
                    break;
            }
        }
    }
    else if (state == 2) // Harry died
    {
        ScoreUpdate();
        if (p.state == 7) // sinking
        {
            p.timer++;
            if (p.timer > 3)
            {
                p.timer = 0;
                p.sprite++;
                if (p.sprite == 48)
                {
                    p.alpha = 0;
                    p.fade = 5;
                    p.sprite = 48;
                    p.x = p.start_x;
                    if (p.x == 0)
                    {
                        p.flip = false;
                    }
                    else
                    {
                        p.flip = true;
                    }

                    TimberReset(); 
                    p.y = 54;
                    p.state = 0;            
                }
                jump_sound = 300;
                channels[0].decay_ms = 75;
                channels[0].frequency = 650 - ((p.sprite - 36) * 50);
                channels[0].trigger_attack();
            }
        }
        else // fadeing
        {
            p.alpha += p.fade;
            if (p.alpha == 0) // fade in
            {
                p.fade = 5;
                p.sprite = 48;
                p.x = p.start_x;
                if (p.x == 0)
                {
                    p.flip = false;
                }
                else
                {
                    p.flip = true;
                }
                 
                p.y = 54;
                p.state = 0; 

                if (timber.typ > 0) // delete timber
                {
                    level[p.level][3] = timber.typ;
                    timber.typ = 0;
                }
                TimberReset();           
                if (watch.m == 0 && watch.s == 0)
                {
                    info.txt1 = "time expired!";
                    info.txt2 = info.txt1;
                    state = 3;
                }                
            }
            else if (p.alpha == 255) // fade out
            {
                p.fade = -3;
                p.state = 0;
                state = 1;
            }
        }
    }
    else if (state == 3) // Info state
    {
        InfoUpdate();
    }
}
