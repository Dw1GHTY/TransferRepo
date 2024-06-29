#pragma once
class Game
{
private:
	static int status;
	int moveCounter;

public:
	Game();
	
	void StartGame();
	void EndGame();

	int inline getStatus() { return status; }
	void inline setStatus(int status_) { status = status_; }


	~Game();

};

