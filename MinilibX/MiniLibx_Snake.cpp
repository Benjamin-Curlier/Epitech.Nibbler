#include	"../Snake.hh"
#include	"graph.h"

MLXCore *core = NULL;
MLXWindow *w = NULL;
MLXImage *img = NULL;
MLXClean *clean_game = NULL;
MLXClean *clean_menu = NULL;
bool Ingame;
int pos;

void	init(int height, int width)
{
  core = mlx_init();
  w = mlx_window_create(core, 1218, 956, "Snake");
  clean_game = mlx_image_create(core, height, width + 30);
  clean_menu = mlx_image_create(core, 1218, 956);
  pos = 0;
}

void	close()
{
  if (img != NULL)
    mlx_image_destroy(img);
  mlx_image_destroy(clean_game);
  mlx_image_destroy(clean_menu);
  mlx_window_destroy(core, win);
  mlx_deinit(core);
}

void	gerekey(int keycode, char *touch)
{
  if (keycode == MLX_KEY_RIGHT)
    {
      *touch = '5';
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_LEFT)
    {
      *touch = '4';
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_DOWN && ingame == false)
    {
      *touch = '3';
      pos++;
      if (pos > 2)
	pos = 0;
      mlx_put_image_to_window(core, w, clean_menu, 0, 0);
      if (pos == 0)
	img = mlx_bitmap_read(core, "../Nibbler/menu_start.bmp");
      else if (pos == 1)
	img = mlx_bitmap_read(core, "../Nibbler/menu_option.bmp");
      else
	img = mlx_bitmap_read(core, "../Nibbler/menu_exit.bmp");
      mlx_put_image_to_window(core, w, img, 0, 0);
      img = mlx_image_destroy(img);
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_UP && ingame == false)
    {
      *touch = '2';
      pos--;
      if (pos < 0)
	pos = 2;
      mlx_put_image_to_window(core, w, clean_menu, 0, 0);
      if (pos == 0)
	img = mlx_bitmap_read(core, "../Nibbler/menu_start.bmp");
      else if (pos == 1)
	img = mlx_bitmap_read(core, "../Nibbler/menu_option.bmp");
      else
	img = mlx_bitmap_read(core, "../Nibbler/menu_exit.bmp");
      mlx_put_image_to_window(core, w, img, 0, 0);
      img = mlx_image_destroy(img);
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_ENTER && ingame == false)
    {
      *touch = '1';
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_ESC && ingame == false)
    {
      *touch = 'E';
      mlx_loop_stop(core);
    }
}

extern "C" void	getInput(char *touh)
{
  mlx_key_hook(w, &gerekey, touch);
  mlx_loop(core);
}

void	gerekey2(int keycode, char *touch, char *touch2)
{
  if (keycode == MLX_KEY_RIGHT)
    {
      *touch = '5';
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_LEFT)
    {
      *touch = '4';
      mlx_loop_stop(core);
    }
  if (keycode == MLX_KEY_C)
    {
      *touch2 = '5';
      mlx_loop_stop(core);
    }
  else if (keycode == MLX_KEY_W)
    {
      *touch2 = '4';
      mlx_loop_stop(core);
    }
}

extern "C" void	getInput(char *touh, char *touch2)
{
  mlx_key_hook(w, &gerekey2, touch, touch2);
  mlx_loop(core);
}

extern "C" bool			end(int height, int width)
{
  std::string end_message = "coucou";
  (void)height;
  (void)width;
  mlx_window_destroy(core, win);
  w = mlx_window_create(core, 1130, 705, "Snake Game Over");
  img = mlx_bitmap_read(core, "../Nibbler/gameover.bmp");
  mlx_put_image_to_window(core, w, img, 0, 0);
  img = mlx_image_destroy(img);
  mlx_write_text(core, win, 105, 490, "%s", end_message.c_str())
  sleep(3);
  mlx_window_destroy(core, win);
  return (false);
}

extern "C" bool menu(int height, int width)
{
  (void)height;
  (void)width;
  if (w == NULL)
    w = mlx_window_create(core, 1218, 956, "Snake");
  Ingame = false;
  img = mlx_bitmap_read(core, "../Nibbler/menu_start.bmp");
  mlx_put_image_to_window(core, w, img, 0, 0);
  img = mlx_image_destroy(img);
  return (false);
}

extern "C" bool			game(int height, int width, char *map,std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction)
{
  if (Ingame == false)
    {
      mlx_window_destroy(core, win);
      w = mlx_window_create(core, height * 45, width * 45 + 30, "Snake Game");
      Ingame = true;
    }
  mlx_put_image_to_window(core, w, clean_game, 0, 0);
  mlx_write_text(core, win, 10, 10, "Score : %d", 0);
  std::string	mlx_map = map;
  if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '4';
  else if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '5';
  else if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '6';
  else
    mlx_map[poshead->first + poshead->second * width] = '7';
  for (std::vector<std::pair<int, int> >::iterator it = *caca; it != *caca.end(); ++it)
    mlx_map[it->first + it->second * height] = '8';
  int a = 1;
  int i = -1;
  int x = 0;
  int y = 0;
  while (mlx_map[++i])
    {
      if (mlx_map[i] == '0')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/black.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '1')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/grey.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '2')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/yellow.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '3')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/red.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '4')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_up.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '5')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_right.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '6')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_left.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '7')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_down.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '8')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/green.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      x += 45;
      if (a % width == 0)
	{
	  y += 45;
	  x = 0;
	}
      a++;
    }
  return (false);
}

extern "C" bool			game_two_player(int height, int width, char *map,std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction,,std::vector<std::pair<int,int> > *caca2, std::pair<int,int> *poshead2, char direction2)
{
  if (Ingame == false)
    {
      mlx_window_destroy(core, win);
      w = mlx_window_create(core, height * 45, width * 45 + 30, "Snake Game");
      Ingame = true;
    }
  mlx_put_image_to_window(core, w, clean_game, 0, 0);
  mlx_write_text(core, win, 10, 10, "Score : %d", 0);
  std::string	mlx_map = map;
  if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '4';
  else if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '5';
  else if (direction == '0')
    mlx_map[poshead->first + poshead->second * width] = '6';
  else
    mlx_map[poshead->first + poshead->second * width] = '7';
  if (direction2 == '0')
    mlx_map[poshead2->first + poshead2->second * width] = '4';
  else if (direction2 == '0')
    mlx_map[poshead2->first + poshead2->second * width] = '5';
  else if (direction2 == '0')
    mlx_map[poshead2->first + poshead2->second * width] = '6';
  else
    mlx_map[poshead2->first + poshead2->second * width] = '7';
  for (std::vector<std::pair<int, int> >::iterator it = *caca; it != *caca.end(); ++it)
    mlx_map[it->first + it->second * height] = '8';
  for (std::vector<std::pair<int, int> >::iterator it = *caca2; it != *caca2.end(); ++it)
    mlx_map[it->first + it->second * height] = '8';
  int a = 1;
  int i = -1;
  int x = 0;
  int y = 0;
  while (mlx_map[++i])
    {
      if (mlx_map[i] == '0')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/black.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '1')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/grey.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '2')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/yellow.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '3')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/red.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '4')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_up.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '5')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_right.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '6')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_left.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '7')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/MLX_head_down.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      else if (mlx_map[i] == '8')
	{
	  img = mlx_bitmap_read(core, "../Nibbler/green.bmp");
	  mlx_put_image_to_window(core, w, img, x, y);
	  img = mlx_image_destroy(img);
	}
      x += 45;
      if (a % width == 0)
	{
	  y += 45;
	  x = 0;
	}
      a++;
    }
  return (false);
}
