#include <ASCII_SCENE.h>

using namespace asc;

int main() {
	Window window{AlphaDegree::Degree::black};
	Shape player1{ 4, 10 };

	Shape player2{ 4, 10 };
	player2.setPosition({ term_cols - player2.getWidth(), 0 });

	Shape ball{ 3, 2, {(term_cols / 2) - 2, 3}, AlphaDegree::Degree::white};
	Position ball_movement = {3, -1};

	Shape bottom{ term_cols, 1, {0, term_rows - 1}, AlphaDegree::Degree::white };
	Shape top{ term_cols, 1, {0, 0}, AlphaDegree::Degree::white };

	Shape colRight{ 1, term_rows, {0, 0}, AlphaDegree::Degree::low_white_grey };
	Shape colLeft{ 1, term_rows, {term_cols - 1, 0}, AlphaDegree::Degree::low_white_grey };

	while(true)
	{
		
		ball.move(ball_movement);
		
		if (intersection(ball, bottom) || intersection(ball, top))
			ball_movement.y *= -1;
		if (intersection(ball, player1) || intersection(ball, player2))
			ball_movement.x *= -1;

		Shape* playerToMove;
		if (ball_movement.x > 0)
			playerToMove = &player2;
		else
			playerToMove = &player1;

		if (ball.getPosition().y > playerToMove->getPosition().y + playerToMove->getHeight() / 2 &&
			playerToMove->getPosition().y < term_rows - playerToMove->getHeight() - 1)
			playerToMove->move({ 0, 1 });

		else if (ball.getPosition().y < playerToMove->getPosition().y + playerToMove->getHeight() / 2 &&
			playerToMove->getPosition().y > 1)
			playerToMove->move({ 0, -1 });

		window.clear();

		window.draw(bottom);
		window.draw(top);

		window.draw(colLeft);
		window.draw(colRight);

		window.draw(player1);
		window.draw(player2);

		window.draw(ball);

		window.display();
	}

	return 0;
}
