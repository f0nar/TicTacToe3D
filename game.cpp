#include "game.h"
#include "player.h"

Game::Game(Player *p1, Player *p2) : players(std::make_pair(p1,p2)), gameEnded(false), currPlayer(0)
{}

void Game::Play()
{
	auto writePos = GetCurrPlayer()->ChooseFieldPos(fSet);
	fSet.Set(writePos);
	CheckWinSequence(writePos.x, writePos.y);
	UpdatePlayer();
}  

bool Game::IsEnded()
{
	return gameEnded;
}

void Game::CheckWinSequence(std::size_t x, std::size_t y)
{
	auto field = fSet.GetTotalField();
	if(!gameEnded) gameEnded = CheckRow(x, y, field);
	if(!gameEnded) gameEnded = CheckCow(x, y, field);
	if(!gameEnded) gameEnded = CheckMajorDiagonal(x, y, field);
	if(!gameEnded) gameEnded = CheckMinorDiagonal(x, y, field);
}


Player *Game::GetCurrPlayer() const
{
    return currPlayer ? players.second : players.first;
}

void Game::UpdatePlayer()
{
    if(!gameEnded) currPlayer = currPlayer ? 0 : 1;
}

bool Game::CheckRow(const size_t wx, const size_t wy, const vvc &field)
{
    const auto c = field[wx][wy];
    auto fsize = field.size(), strlen = 1UL;
    for(auto curx = wx + 1; curx < fsize && c == field[curx][wy]; ++strlen, ++curx);
    for(int curx = wx - 1; curx >= 0 && c == field[curx][wy]; ++strlen, --curx);
    return strlen >= winLength ? true : false;
}

bool Game::CheckCow(const size_t wx, const size_t wy, const vvc &field)
{
    const auto c = field[wx][wy];
    auto fsize = field.size(), strlen = 1UL;
    for(auto cury = wy + 1; cury < fsize && c == field[wx][cury]; ++strlen, ++cury);
    for(int cury = wy - 1; cury >= 0 && c == field[wx][cury]; ++strlen, --cury);
    return strlen >= winLength ? true : false;
}

bool Game::CheckMajorDiagonal(const size_t wx, const size_t wy, const vvc &field)
{
    const auto c = field[wx][wy];
    auto fsize = field.size(), strlen = 1UL;
    for(auto curx = wx + 1, cury = wy + 1;
        curx < fsize && cury < fsize && c == field[curx][cury];
        ++strlen, ++curx, ++cury);
    for(int curx = wx - 1, cury = wy - 1;
        curx >= 0 && cury >= 0 && c == field[curx][cury];
        ++strlen, --curx, --cury);
    return strlen >= winLength ? true : false;
}

bool Game::CheckMinorDiagonal(const size_t wx, const size_t wy, const vvc &field)
{
    const auto c = field[wx][wy];
    auto fsize = field.size(), strlen = 1UL;
    for(int curx = wx + 1, cury = wy - 1;
        curx < fsize && cury >= 0 && c == field[curx][cury];
        ++strlen, ++curx, --cury);
    for(int curx = wx - 1, cury = wy + 1;
        curx >= 0 && cury < fsize && c == field[curx][cury];
        ++strlen, --curx, ++cury);
    return strlen >= winLength ? true : false;

}
