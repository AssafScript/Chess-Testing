#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "logic.cpp"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(780, 780), "SFML works!");
	gameLogic logic;
	sf::Texture boardTxt , validDottxt;
	sf::Texture pawnBtxt, knightBtxt, rookBtxt, kingBtxt, queenBtxt, bishopBtxt;
	sf::Texture pawnWtxt, knightWtxt, rookWtxt, kingWtxt, queenWtxt, bishopWtxt;
	if (boardTxt.loadFromFile("assets/board1.png") == false)
		cout << "Failed to load board\n";
	if (pawnBtxt.loadFromFile("assets/B_Pawn.png") == false)
		cout << "Failed to load black pawn\n";
	if (knightBtxt.loadFromFile("assets/B_Knight.png") == false)
		cout << "Failed to load black knight\n";
	if (rookBtxt.loadFromFile("assets/B_Rook.png") == false)
		cout << "Failed to load black rook\n";
	if (kingBtxt.loadFromFile("assets/B_King.png") == false)
		cout << "Failed to load black King\n";
	if (queenBtxt.loadFromFile("assets/B_Queen.png") == false)
		cout << "Failed to load black Queen\n";
	if (bishopBtxt.loadFromFile("assets/B_Bishop.png") == false)
		cout << "Failed to load black Bishop\n";
	if (pawnWtxt.loadFromFile("assets/W_Pawn.png") == false)
		cout << "Failed to load white pawn\n";
	if (knightWtxt.loadFromFile("assets/W_Knight.png") == false)
		cout << "Failed to load white knight\n";
	if (rookWtxt.loadFromFile("assets/W_Rook.png") == false)
		cout << "Failed to load white rook\n";
	if (kingWtxt.loadFromFile("assets/W_King.png") == false)
		cout << "Failed to load white King\n";
	if (queenWtxt.loadFromFile("assets/W_Queen.png") == false)
		cout << "Failed to load white Queen\n";
	if (bishopWtxt.loadFromFile("assets/W_Bishop.png") == false)
		cout << "Failed to load white Bishop\n";
	if (validDottxt.loadFromFile("assets/valid.png") == false)
		cout << "Failed to load Dot\n";
	sf::Sprite board , validDot;
	validDot.setTexture(validDottxt);
	board.setTexture(boardTxt);
	board.setScale(6, 6);
	bool validPoints[8][8] = {};
	int lastPieceX = 0, lastPieceY = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int mouseY = sf::Mouse::getPosition(window).x/97;
				int mouseX = sf::Mouse::getPosition(window).y/97;
				cout << mouseX << " " << mouseY << endl;
				if (logic.chessBoard[mouseX][mouseY] != '.')
				{
					lastPieceX = mouseX;
					lastPieceY = mouseY;
					for (int i = 0; i < 8; i++){
						for (int j = 0; j < 8; j++) {
							if (i == mouseX && j == mouseY) continue;
							if (logic.Valid(mouseX, mouseY, i, j))
							{
								validPoints[i][j] = 1;
							}
						}
					}
				}
				else if (validPoints[mouseX][mouseY] == true)
				{
					logic.movePiece(lastPieceX, lastPieceY, mouseX, mouseY);
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							validPoints[i][j] = 0;
					logic.black = !logic.black;
				}
				else
				{
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							validPoints[i][j] = 0;
				}
			}
		}
		window.clear();
		window.draw(board);
		for (int i = 0; i < 780; i += 97) {
			for (int j = 0; j < 780; j += 97) {
				sf::Sprite piece;
				if (logic.chessBoard[i / 97][j / 97] == 'p')
					piece.setTexture(pawnWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'k')
					piece.setTexture(kingWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'b')
					piece.setTexture(bishopWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'r')
					piece.setTexture(rookWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'q')
					piece.setTexture(queenWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'n')
					piece.setTexture(knightWtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'P')
					piece.setTexture(pawnBtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'K')
					piece.setTexture(kingBtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'B')
					piece.setTexture(bishopBtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'R')
					piece.setTexture(rookBtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'Q')
					piece.setTexture(queenBtxt);
				else if (logic.chessBoard[i / 97][j / 97] == 'N')
					piece.setTexture(knightBtxt);
				piece.setScale(2.85, 2.85);
				piece.setPosition(j, i);
				window.draw(piece);
				if (validPoints[i / 97][j / 97] == true)
					piece.setTexture(validDottxt);
				piece.setScale(2.85, 2.85);
				piece.setPosition(j, i);
				window.draw(piece);
			}
		}
		window.display();
	}
	return 0;
}