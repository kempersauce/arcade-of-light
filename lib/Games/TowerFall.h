#include <Game.h>
#include <Constants.h>
#include <Dot.h>
#include <DirPad.h>
#include <Display.h>
#include <Platform.h>

//game Concept
//Race to the bottom
//All players start at the top
//player dots fall until they hit abritrary point down the strip
//players stop moving relative to the strip
//obstacles begin rising up to player
//race continues until finish line flies up
//players stop the dots from rising when the hit a Platform


class TowerFallGame : Game
{

  public:
    DirPad* controls;
    Dot* player;
    SingleColorBG* backgroundColor;

    DirPadTest(Display* gameDisplay)
        : Game(gameDisplay)
    {
    }


  void setup(){
      for (int i = 0; i < NUM_FIREWORKS; i++)
      {

      }

  void loop(){
    controls->pollAll();

      if (controls->up->isPressed()){
        player.move(up);
      }
      if (controls->down->isPressed()){
        player.move(down);
      }
      if (controls->left->isPressed()){
        player.move(left);
      }
      if (controls->right->isPressed()){
        player.move(right);
      }
      if (controls->a->isPressed()){
        player.boost();
      }
      if (controls->b->isPressed()){
        player.changeColor();
      }

    backgroundColor->draw(display);
    player->draw(display);
    FastLED.show();
  }
};
