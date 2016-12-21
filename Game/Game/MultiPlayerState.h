#pragma once
#include "SinglePlayerState.h"
#include"ClientSide.h"
#include"StringRunnable.h"
class MultiPlayerState :
	public SinglePlayerState
{
private:
	class NewPlayer :public StringRunnable
	{
	private:
		MultiPlayerState* s;
	public:
		NewPlayer(MultiPlayerState* s) :s(s) {}
		void run(string);
	};
	class DeletePlayer :public StringRunnable
	{
	private:
		MultiPlayerState* s;
	public:
		DeletePlayer(MultiPlayerState* s) :s(s) {}
		void run(string);
	};
	class UpdatePlayer :public StringRunnable
	{
	private:
		MultiPlayerState* s;
	public:
		UpdatePlayer(MultiPlayerState* s) :s(s) {}
		void run(string);
	};
private:
	ClientSide m_Client;
public:
	MultiPlayerState();
	~MultiPlayerState();

	void update();
private:
	void newPlayer(std::string);
	void deletePlayer(std::string);
	void updatePlayer(std::string);
};

