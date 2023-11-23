#pragma once
#include <iostream>
#include <array>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <memory>


namespace asc
struct Position
{
	float x{};
	float y{};
	Position() = default;
	Position(const float x, const float y) : x{ x }, y{ y } {}
};

class AlphaDegree
{
public:
	enum class Degree
	{
	black,
	smooth_black,
	black_grey,
	medium_black_grey,
	smooth_black_grey,
	low_black_grey,
	grey,
	low_white_grey,
	smooth_white_grey,
	medium_white_grey,
	white_grey,
	smooth_white,
	white,
	};

	AlphaDegree(Degree deg) : m_charDegree{ CharacterDegrees[static_cast<int>(deg)] } {}

	operator char() const { return m_charDegree; }

	static std::array<char, 13> CharacterDegrees;

private:
	char m_charDegree;
};

std::array<char, 13> AlphaDegree::CharacterDegrees{ ' ', '.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@' };


class Shape
{
public:
	Shape(float(width) = 0, float(height) = 0, Position position = { 0, 0 }, AlphaDegree::Degree color = AlphaDegree::Degree::white) :
		m_width{ width }, m_height{ height }, m_position{ position }, m_degree{ color }
	{}
	virtual ~Shape() = default;
	void move(const Position& direction)
	{
		m_position.x += direction.x;
		m_position.y += direction.y;
	};
	void setPosition(const Position& direction)
	{
		m_position.x = direction.x;
		m_position.y = direction.y;
	};
	void setColor(AlphaDegree::Degree degree) { m_degree = degree; };
	const Position& getPosition() const { return m_position; };
	const AlphaDegree& getColor() const { return m_degree; }
	float getHeight() const { return m_height; };
	float getWidth() const { return m_width; };

private:
	Position m_position;
	AlphaDegree m_degree;
	float m_height;
	float m_width;
};

bool intersection(const Shape& shape1, const Shape& shape2)
{
	float start1_x = shape1.getPosition().x, start1_y = shape1.getPosition().y;
	float end1_x = start1_x + shape1.getWidth(), end1_y = start1_y + shape1.getHeight();

	float start2_x = shape2.getPosition().x, start2_y = shape2.getPosition().y;
	float end2_x = start2_x + shape2.getWidth(), end2_y = start2_y + shape2.getHeight();

	return((start1_x > start2_x && start1_x < end2_x) || (start2_x > start1_x && start2_x < end1_x)) &&
		((start1_y > start2_y && start1_y < end2_y) || (start2_y > start1_y && start2_y < end1_y));

}

bool intersection(const Shape& shape, const Position& pos)
{
	float start1_x = shape.getPosition().x, start1_y = shape.getPosition().y;
	float end1_x = start1_x + shape.getWidth(), end1_y = start1_y + shape.getHeight();

	return((pos.x > start1_x && pos.x < end1_x)) && ((pos.y > start1_y && pos.y < end1_y));

}

void cls()
{
	HANDLE hOut{};
	COORD Position{};

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

class Window {
public:

	Window(int term_cols, int term_rows, const AlphaDegree::Degree& degree = AlphaDegree::Degree::black) :
		m_degree{ degree }, m_term_cols{ term_cols }, m_term_rows{ term_rows }
	{
		clear();
	}

	void display() const
	{
		for (int y = 0; y < m_term_rows; ++y) {
			for (int x = 0; x < m_term_cols; ++x)
				std::cout << m_state[m_term_cols * y + x];
		}
	}

	void draw(const Shape& shape)
	{
		for (int h = shape.getPosition().y; h < shape.getHeight() + shape.getPosition().y; ++h)
		{
			if (h >= m_term_rows)
				break;

			for (int w = shape.getPosition().x; w < shape.getWidth() + shape.getPosition().x; ++w) {
				if (w >= m_term_cols)
					break;
				m_state[m_term_cols * h + w] = shape.getColor();
			}
		}
	}

	void clear()
	{
		cls();
		for (int y = 0; y < m_term_rows; ++y) {
			for (int x = 0; x < m_term_cols; ++x)
				m_state[m_term_cols * y + x] = m_degree;
			m_state[m_term_cols * y + m_term_cols] = '\n';
		}
	};

	Window(const Window&) = delete;

private:
	AlphaDegree m_degree;
	int m_term_cols;
	int m_term_rows;
	std::unique_ptr<char[]> manager = std::make_unique<char[]>(m_term_rows * m_term_cols);
	char* m_state = manager.get();
};
}
