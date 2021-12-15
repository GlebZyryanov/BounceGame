#pragma once

#include<SFML/Graphics.hpp>
class Animation
{
public: std::vector<sf::IntRect> frames, frames_reverse;
public: float ActualFrame, speed;
public: bool reverse, playAnimation;
public: sf::Sprite sprite;
public: Animation(sf::Texture& texture, int CordX, int CordY, int Width, int High, int Count, float Speed, int Step = 0) {
	speed = Speed;
	sprite.setTexture(texture);
	ActualFrame = 0;
	playAnimation = true;
	reverse = false;

	for (int i = 0; i < Count; i++) {
		frames.push_back(sf::IntRect(CordX + i * Step, CordY, Width, High));
		frames_reverse.push_back(sf::IntRect(CordX + i * Step+Width, CordY, -Width, High));
	}

}
public: void Mark(float time) {
	if (!playAnimation) {
		return;
	}
	ActualFrame = ActualFrame + speed * time;
	if (ActualFrame > frames.size()) {
		ActualFrame = ActualFrame - frames.size();
	}
	int i = ActualFrame;
	sprite.setTextureRect(frames[i]);
	if (reverse) {
		sprite.setTextureRect(frames_reverse[i]);
	}
}
};
class AnimationManage {
public:sf::String ActualAnim;
public: std::map<sf::String, Animation> ListofAnimation;
public: AnimationManage() { }
public: void Create(sf::String name, sf::Texture& texture, int CordX, int CordY, int Width, int High, int Count, float Speed, int Step = 0) {
	ListofAnimation[name] = Animation(texture, CordX, CordY, Width, High, Speed, Step);
	ActualAnim = name;
}
public: 
	void drawAnim(sf::RenderWindow& window, int CordX = 0, int CordY = 0) {
		ListofAnimation[ActualAnim].sprite.setPosition(CordX, CordY);
		window.draw(ListofAnimation[ActualAnim].sprite);
	}
};

