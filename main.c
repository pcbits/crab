#include "main.h"

/**
 * Sets magic pink, makecol(255, 0, 255), to transparent for 8 bit color depth mode.
 */
void set_transparent_pixel(BITMAP *bmp)
{
    int y, x, c;
    for(y = 0; y < bmp->h; ++y)
    {
        for(x = 0; x < bmp->w; ++x)
        {
            c = getpixel(bmp, x, y);
            if(c == makecol(255, 0, 255))
            {
                putpixel(bmp, x, y, 0);
            }
        }
    }
}

void up()
{
    player.yspeed = -4;
}

void down()
{
    player.yspeed = 4;
}

void right()
{
    player.xspeed = 4;
}

void left()
{
    player.xspeed = -4;
}

void idle()
{
    player.xspeed = 0;
    player.yspeed = 0;
}

int collision (int x, int y)
{
    BLKSTR *blkdatapt;
    blkdatapt = MapGetBlockInPixels(x, y);
    if (blkdatapt->tl) {
            return 1;
    }
    return 0;
}

void move()
{
    int prevxoffset, prevyoffset, prevx, prevy;

    prevxoffset = xoffset;
    prevyoffset = yoffset;
    prevx = player.x;
    prevy = player.y;

    player.y += player.yspeed;
    player.x += player.xspeed;
    if(player.x < 0)
    {
        player.x = 0;
    }
    if(player.x > mapwidth*mapblockwidth-player.width)
    {
        player.x = mapwidth*mapblockwidth-player.width;
    }
    if(player.y < 0)
    {
        player.y = 0;
    }
    if(player.y > mapheight*mapblockheight-player.height)
    {
        player.y = mapheight*mapblockheight-player.height;
    }

    xoffset = (player.x+(player.width/2)) - (SCREEN_W/2);
    yoffset = (player.y+(player.height/2)) - (SCREEN_H/2);
    if (xoffset < 0)
    {
        xoffset = 0;
    }
    if (xoffset > (((mapwidth*mapblockwidth)-SCREEN_W)))
    {
        xoffset = (((mapwidth*mapblockwidth)-SCREEN_W));
    }
    if (yoffset < 0)
    {
        yoffset = 0;
    }
    if (yoffset > (((mapheight*mapblockheight)-SCREEN_H)))
    {
        yoffset = (((mapheight*mapblockheight)-SCREEN_H));
    }

    // prevent from walking on water.
    if (collision(player.x+(player.width/2), player.y+(player.height/2)))
    {
        xoffset = prevxoffset;
        yoffset = prevyoffset;
        player.x = prevx;
        player.y = prevy;
    }
}

int set_gfx(int depth)
{
    set_color_depth(depth);
    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) != 0)
    {
        if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 240, 0, 0) != 0)
        {
            if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 200, 0, 0) != 0)
            {
                return -1;
            }
        }
    }
    return 0;
}

void initialize_player()
{
    player.height = 18;
    player.width = 18;
    player.alive = 1;
    // Start in the center of the island map.
    player.x = mapwidth*mapblockwidth/2;
    player.y = mapheight*mapblockheight/2;
}

int initialize()
{
    if(allegro_init()!=0)
    {
        allegro_message("Error: Could not initialize program.\n");
        return 1;
    }
    install_keyboard();

    if(set_gfx(8) != 0)
    {
        if(set_gfx_mode(GFX_SAFE, 640, 480, 0, 0) != 0)
        {
            allegro_message("Error: Could not set graphics resolution.\n");
            allegro_exit();
            return 2;
        }
    }

    if(MapLoad("data/map.fmp") != 0)
    {
        allegro_message("Can't find map.fmp.\n");
        allegro_exit();
        return 3;
    }

    crab = load_bitmap("data/crab.bmp", NULL);
    if(!crab)
    {
        allegro_message("Error loading crab.bmp\n");
        allegro_exit();
        return 3;
    }
    set_transparent_pixel(crab);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    return 0;
}

void draw()
{
    MapDrawBG(buffer, xoffset, yoffset, 0, 0, SCREEN_W, SCREEN_H);
    draw_sprite(buffer, crab, (player.x-xoffset), (player.y-yoffset));
    /* textprintf_ex(buffer,font,0,0,WHITE,-1,
                  "Position = %d,%d, Player = %d,%d, Block = %d,%d",
                  xoffset, yoffset, player.x, player.y,
                  MapGetXOffset(player.x, player.y), MapGetYOffset(player.x, player.y)); */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void shutdown()
{
    destroy_bitmap(crab);
    destroy_bitmap(buffer);
    MapFreeMem();
    allegro_exit();
}

void process_keypressed()
{
    if (key[KEY_RIGHT])
    {
        right();
    }
    else if (key[KEY_LEFT])
    {
        left();
    }
    else if (key[KEY_UP])
    {
        up();
    }
    else if (key[KEY_DOWN])
    {
        down();
    }
    else
    {
        idle();
    }
}

int main()
{
    int rc = initialize();
    if(rc!=0)
    {
        return rc;
    }
    initialize_player();
    while(!key[KEY_ESC])
    {
        process_keypressed();
        move();
        draw();
        rest(20);
    }
    shutdown();
    return 0;
}
END_OF_MAIN()
