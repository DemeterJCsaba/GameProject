#include "MultiPlayerState.h"
#include "Player.h"
#include"Utility.h"

using namespace std;

MultiPlayerState::MultiPlayerState():
	m_Client(
		ClientSide(
			"127.0.0.1", 
			10013,
			new NewPlayer(this),
			new DeletePlayer(this),
			new UpdatePlayer(this)
		)
	)
{}

MultiPlayerState::~MultiPlayerState()
{
	m_Client.disconnect();
}

void MultiPlayerState::newPlayer(std::string str)//ip
{
	vector<string> parts = Utility::split(str, '/');
	m_Layer3DDynamic.addModel(str,new Player());
}

void MultiPlayerState::deletePlayer(std::string str)//ip
{
	m_Layer3DDynamic.removeModel(str);
}

void MultiPlayerState::updatePlayer(std::string str)//ip + BC + data
{
	vector<string> parts = Utility::split(str, ClientSide::BREAK_CHAR);
	Player* p = (Player*)m_Layer3DDynamic.getModel(parts[0]);
	if (p == nullptr) {
		p = new Player();
		m_Layer3DDynamic.addModel(parts[0],p);
	}
	vector<string> objects = Utility::split(parts[1], ';');
	vector<string> elemnts;
	if (objects.size() == 7) {//utolso ures
		elemnts = Utility::split(objects[0], ':');
		float health = stof(elemnts[1]);
		p->setHealth(health);

		elemnts = Utility::split(objects[1], ':');
		vec3 pos = vec3(stof(elemnts[1]), stof(elemnts[2]), stof(elemnts[3]));
		p->setPosition(pos);

		elemnts = Utility::split(objects[2], ':');
		vec3 rot = vec3(stof(elemnts[1]), stof(elemnts[2]), stof(elemnts[3]));
		p->setRotation(rot);

		elemnts = Utility::split(objects[3], ':');
		vec3 scale = vec3(stof(elemnts[1]), stof(elemnts[2]), stof(elemnts[3]));
		p->setScale(scale);

		elemnts = Utility::split(objects[4], ':');
		vec3 mot = vec3(stof(elemnts[1]), stof(elemnts[2]), stof(elemnts[3]));
		p->setMotion(mot);

		elemnts = Utility::split(objects[5], ':');
		vec3 color = vec3(stof(elemnts[1]), stof(elemnts[2]), stof(elemnts[3]));
		p->setColor(color);
	}
}

void MultiPlayerState::NewPlayer::run(string str)
{
	s->newPlayer(str);
}
void MultiPlayerState::DeletePlayer::run(string str)
{
	s->deletePlayer(str);
}
void MultiPlayerState::UpdatePlayer::run(string str)
{
	s->updatePlayer(str);
}

void MultiPlayerState::update() {
	SinglePlayerState::update();

	Player* p = (Player*)m_Layer3DDynamic.getModel("Player");
	m_Client.addMsg(p->toMyson());
}
