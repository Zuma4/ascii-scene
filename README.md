# ascii_scene
## !! The Library Is Highly Unstable !! 
very simple C++ header-only library to make drawing ASCII graphics on terminal an easier process

![example GIF](https://github.com/Zuma4/ASCII_SCENE/blob/main/ASCII_PONG_example.gif)


## Getting Started
```cpp
#include <ASCII_SCENE.h>

using namespace asc;

int main() {

	// main window
	// (AlphaDegree::Degree) is an enum for setting brightness for the screen
	// paramters: 1 - width of the terminal, 2 - height of the terminal, initial background brightness
	Window window{30, 120, AlphaDegree::Degree::black};

	// Shape is a class for drawing simple rectangular shapes
	Shape player1{ 4, 10 };
	Shape player2{ 4, 10 };

	// setting the position with the xy coordination system
	player2.setPosition({ term_cols - player2.getWidth(), 0 });


	// (AlphaDegree::Degree) can also be used to determine a shape brightness
	// parameters: 1 - width, 2 - height, 3 - Vector2 Position, 4 - brightness
	Shape ball{ 3, 2, {(term_cols / 2) - 2, 3}, AlphaDegree::Degree::white};

	// Vector2 is a class to represent an xy point, used for positioning shapes
	// ball movement represents the next move the ball will take
	Vector2 ball_movement = {3, -1};


	// creating borders
	// NW
	Shape bottom{ term_cols, 1, {0, term_rows - 1}, AlphaDegree::Degree::white };
	Shape top{ term_cols, 1, {0, 0}, AlphaDegree::Degree::white };

	// EW
	Shape colRight{ 1, term_rows, {0, 0}, AlphaDegree::Degree::low_white_grey };
	Shape colLeft{ 1, term_rows, {term_cols - 1, 0}, AlphaDegree::Degree::low_white_grey };


	//The main loop for drawing endlessly
	while(true)
	{

		// move is a function to add position to the current position of a shape 
		ball.move(ball_movement);

		// Intersection checks if two shapes have collided
		if (intersection(ball, bottom) || intersection(ball, top))
			ball_movement.y *= -1; // reversing the y movement
		if (intersection(ball, player1) || intersection(ball, player2))
			ball_movement.x *= -1;

		// deciding which player to move
		Shape* playerToMove;
		// if the ball_movement x direction is going right
		if (ball_movement.x > 0)
			playerToMove = &player2;
		// if it's going left
		else
			playerToMove = &player1;


		// moving the chosen player according to the ball coordination
		// if the ball position is higher than the position of the player, move the player upward
		if (ball.getPosition().y > playerToMove->getPosition().y + playerToMove->getHeight() / 2 &&
			playerToMove->getPosition().y < term_rows - playerToMove->getHeight() - 1)
			playerToMove->move({ 0, 1 });

		// if the ball position is lower than player position, move the player accordingly
		else if (ball.getPosition().y < playerToMove->getPosition().y + playerToMove->getHeight() / 2 &&
			playerToMove->getPosition().y > 1)
			playerToMove->move({ 0, -1 });

		// completly clearing a screen with it's initial color
		window.clear();

		// drawing shapes
		// NS corners
		window.draw(bottom);
		window.draw(top);

		// EW corners
		window.draw(colLeft);
		window.draw(colRight);

		// drawing both player
		window.draw(player1);
		window.draw(player2);

		// drawing the ball
		window.draw(ball);

		// displaying the state of the window
		window.display();
	}

	return 0;
}
