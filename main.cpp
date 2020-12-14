//----------TERMASUK----------
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

//sf:: ___
using namespace sf; //-[Namespace: Wilayah Deklaratif yg Menyediakan Cakupan utk Pengidentifikasi]

class Heart //-[Kelas: Blok Bangunan, Mengarah ke Pemrograman Berorientasi Objek]
{
public:
	Sprite shape; //-[Sprite: Gambar Dilayar Yang Dapat Bergerak]

	Heart(Texture * texture, Vector2u windowSize)
	{
		this->shape.setTexture(*texture); //Gambar
		this->shape.setScale(0.05f, 0.05f); //Ukuran
		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % int(windowSize.y - this->shape.getGlobalBounds().height)); //Letak
	}

	~Heart()
	{

	}
};

class Bullet //-[Kelas: Blok Bangunan, Mengarah ke Pemrograman Berorientasi Objek]
{
public:
	Sprite shape; //-[Sprite: Gambar Dilayar Yang Dapat Bergerak]

	Bullet(Texture* texture, Vector2f pos)
	{
		this->shape.setTexture(*texture); //Gambar
		this->shape.setScale(0.03f, 0.03f); //Ukuran
		this->shape.setPosition(pos); //Letak
	}

	~Bullet()
	{

	}
};

class Player //-[Kelas: Blok Bangunan, Mengarah ke Pemrograman Berorientasi Objek]
{
public:
	Sprite shape; //-[Sprite: Gambar Dilayar Yang Dapat Bergerak]
	Texture* texture;

	int HP; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]
	int HPMax; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]

	std::vector<Bullet> bullets; //-[Vector: Wadah Urutan yg Mewakili Larik, dpt Berubah dlm Ukuran]

	Player(Texture* texture)
	{
		this->HPMax = 100; //Nyawa
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture); //Gambar
		this->shape.setScale(0.3f, 0.3f); //Ukuran
	}

	~Player()
	{

	}
};

class Enemy //-[Kelas: Blok Bangunan, Mengarah ke Pemrograman Berorientasi Objek]
{
public:
	Sprite shape; //-[Sprite: Gambar Dilayar Yang Dapat Bergerak]

	int HP; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]
	int HPMax; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]

	Enemy(Texture* texture, Vector2u windowSize)
	{
		this->HPMax = rand() % 10 + 1; //Nyawa (in range 1 to 10)
		this->HP = this->HPMax;

		this->shape.setTexture(*texture); //Gambar
		this->shape.setScale(0.2f, 0.2f); //Ukuran
		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % int(windowSize.y - this->shape.getGlobalBounds().height)); //Letak
	}

	~Enemy()
	{
	}
};

int main()
{
	srand(time(NULL)); //Bilangan Acak Pseudo (Enemy Spawn Random)

	RenderWindow window(VideoMode(1920, 1080), "Whatchout My Bicycle", Style::Fullscreen); //Dimensi Layar
	window.setFramerateLimit(120); //FPS

	bool isFullscreen = true; //-[Bool: Memiliki Dua Nilai yg Mungkin, Benar/Salah]

	//----------TULISAN----------
	Font gameFont; //File Tulisan "Watchout My Bicycle"
	gameFont.loadFromFile("fonts/grounde/black-grounde.ttf");
	Font menuFont; //File Tulisan Menu
	menuFont.loadFromFile("fonts/hexgon/hexgonbold.ttf");
	Font wmFont; //File Tulisan Dev (RAVV)
	wmFont.loadFromFile("fonts/armed-traitorous.otf");
	Font ingameFont; //File Tulisan Dalam Game
	ingameFont.loadFromFile("fonts/punch-drunk.ttf");
	Font hintFont; //File Tulisan Hint
	hintFont.loadFromFile("fonts/bang-whack.ttf");

	//----------GAMBAR----------
	Texture themeTexture; //File Latar
	themeTexture.loadFromFile("textures/background/artboard.png");
	Texture playerTexture; //File Pemain
	playerTexture.loadFromFile("textures/object/bicycleremake.png");
	Texture enemyTexture; //File Musuh
	enemyTexture.loadFromFile("textures/object/enemy.png");
	Texture heartTexture; //File Hati
	heartTexture.loadFromFile("textures/object/fill-heart.png");
	Texture bulletTexture; //File Peluru
	bulletTexture.loadFromFile("textures/gun/ammo1.png");

	//----------GAMBAR PEMANDANGAN----------
	Texture tree1Texture; //File Pohon
	tree1Texture.loadFromFile("textures/landscape/deadtree.png");
	Texture tree2Texture; //File Pohon
	tree2Texture.loadFromFile("textures/landscape/tree1.png");
	Texture tree3Texture; //File Pohon
	tree3Texture.loadFromFile("textures/landscape/tree2.png");

	//----------INIT BACKGROUND----------
	Sprite background(themeTexture); //-[Sprite: Gambar Dilayar Yang Dapat Bergerak]

	//----------INIT USER INTERVIEW----------
	Text scoreTexture;
	scoreTexture.setFont(ingameFont); //Gaya Tulisan
	scoreTexture.setCharacterSize(25); //Ukuran
	scoreTexture.setFillColor(Color::Black); //Warna
	scoreTexture.setPosition(10.f, 1000.f); //Letak

	Text gameoverTexture;
	gameoverTexture.setFont(ingameFont); //Gaya Tulisan
	gameoverTexture.setCharacterSize(200); //Ukuran
	gameoverTexture.setFillColor(Color::Red); //Warna
	gameoverTexture.setPosition(0.f, 520.f); //Letak
	gameoverTexture.setString("YOU'RE DIE!");

	Text captionsWTexture;
	captionsWTexture.setFont(hintFont); //Gaya Tulisan
	captionsWTexture.setCharacterSize(25); //Ukuran
	captionsWTexture.setFillColor(Color::Black); //Warna
	captionsWTexture.setPosition(1300.f, 1000.f); //Letak
	captionsWTexture.setString("Press Keyword W For Moving the Player Upwards.");

	Text captionsSTexture;
	captionsSTexture.setFont(hintFont); //Gaya Tulisan
	captionsSTexture.setCharacterSize(25); //Ukuran
	captionsSTexture.setFillColor(Color::Black); //Warna
	captionsSTexture.setPosition(1300.f, 950.f); //Letak
	captionsSTexture.setString("Press Keyword S For Moving the Player Down.");

	Text captionsMCTexture;
	captionsMCTexture.setFont(hintFont); //Gaya Tulisan
	captionsMCTexture.setCharacterSize(25); //Ukuran
	captionsMCTexture.setFillColor(Color::Black); //Warna
	captionsMCTexture.setPosition(1300.f, 900.f); //Letak
	captionsMCTexture.setString("Click Left Mouse Button For Shooting.");

	//----------INIT PLAYER----------
	Player player(&playerTexture);

	int shootTimer = 30; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]
	int score = 0; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]

	Text hpTexture;
	hpTexture.setFont(ingameFont); //Gaya Tulisan
	hpTexture.setCharacterSize(25); //Ukuran
	hpTexture.setFillColor(Color::Black); //Warna
	hpTexture.setPosition(10.f, 970.f); //Letak

	//----------INIT SUARA----------
	SoundBuffer dorBuffer;
	Sound dorSound;

	dorSound.setBuffer(dorBuffer); //-[Buffer: Memungkinkan Program Mengontrol Buffer dari Aliran yg Diberikan.]

	if (!dorBuffer.loadFromFile("sound/effect/gun-out.wav")) //File Suara
	{
		std::cout << "Error loading Dor Sound Effect" << std::endl;
	}

	//----------INIT HATI----------
	int heartSpawnTimer = 0; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]
	std::vector<Heart> heart; //-[Vector: Wadah Urutan yg Mewakili Larik, dpt Berubah dlm Ukuran]

	//----------INIT MUSUH----------
	int enemySpawnTimer = 0; //-[Int: Jenis Integral yg Dapat Mewakili Bilangan Bulat]
	std::vector<Enemy> enemy; //-[Vector: Wadah Urutan yg Mewakili Larik, dpt Berubah dlm Ukuran]

	//============================================================
	//============================================================
	while (window.isOpen()) //Membuka Window
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close(); //Menutup Window
		}

		if (player.HP > 0) //Jika < 0 Maka Game Berhenti
		{
			//----------PEMBARUAN PLAYER----------
			if (Keyboard::isKeyPressed(Keyboard::W)) //Tekan W
				player.shape.move(0.f, -10.f); //Bergerak Keatas
			if (Keyboard::isKeyPressed(Keyboard::S)) //Tekan S
				player.shape.move(0.f, 10.f); //Bergerak Kebawah

			//if (Keyboard::isKeyPressed(Keyboard::A)) //Tekan A
				//player.shape.move(-10.f, 0.f); //(X,Y) //Bergerak Kekiri
			//if (Keyboard::isKeyPressed(Keyboard:D)) //Tekan D
				//player.shape.move(10.f, 0.f); //(X,Y) //Bergerak Kekanan

			//MENCAPAI BATAS BINGKAI
			if (player.shape.getPosition().y <= 0) //Saat Keatas
				player.shape.setPosition(player.shape.getPosition().x, 0.f); //Sudah Diatas
			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Saat Kebawah
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height); //Sudah Dibawah

			//if (player.shape.getPosition().x <= 0) //Saat Kekiri
				//player.shape.setPosition(0.f, player.shape.getPosition().y); //Sudah Dikiri
			//if (player.shape.getPosition().x >= window.getSize(). - player.shape.getGlobalBounds().width) //Saat Kekanan
				//player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y); //Sudah Dikanan

			hpTexture.setString("LIVES: " + std::to_string(player.HP) + "/" + std::to_string(player.HPMax)); //Tampilkan HP

			//----------PEMBARUAN KONTROL----------
			if (shootTimer < 30)
				shootTimer++;

			if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 30) //Tekan Kiri Mouse
			{
				player.bullets.push_back(Bullet(&bulletTexture, player.shape.getPosition())); //Menembak
				shootTimer = 0; //Mengulangi

				dorSound.play(); //Suara Tembakan
			}

			//----------PEMBARUAN PELURU----------
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				player.bullets[i].shape.move(30.f, 0.f); //Peluru Berpindah

				//KELUAR LAYAR
				if (player.bullets[i].shape.getPosition().x > window.getSize().x) //Saat Ditembak
				{
					player.bullets.erase(player.bullets.begin() + i); //Sudah Ditembak
					break; //stop
				}

				//TERKENA MUSUH
				for (size_t j = 0; j < enemy.size(); j++)
				{
					if (player.bullets[i].shape.getGlobalBounds().intersects(enemy[j].shape.getGlobalBounds())) //Saat Tertembak
					{
						if (enemy[j].HP <= 1)
						{
							score += enemy[j].HPMax; //Menambah Score
							enemy.erase(enemy.begin() + j); //Menghilangkan Musuh
						}
						else
							enemy[j].HP--; //Dapat Kerusakan

						player.bullets.erase(player.bullets.begin() + i); //Sudah Tertembak
						break; //stop
					}
				}
			}

			//----------PEMBARUAN HATI----------
			if (heartSpawnTimer < 1003)
				heartSpawnTimer++;

			//ADA HATI
			if (heartSpawnTimer > 1000)
			{
				heart.push_back(Heart(&heartTexture, window.getSize())); //Memunculkan Hati
				heartSpawnTimer = 0; //Mengulangi Waktu
			}

			//GERAK Hati
			for (size_t k = 0; k < heart.size(); k++)
			{
				heart[k].shape.move(-3.f, 0.f); //Hati Berpindah

				if (heart[k].shape.getPosition().x <= 0 - heart[k].shape.getGlobalBounds().width)
				{
					heart.erase(heart.begin() + k); //Hati Terkena Player
					break; //stop
				}

				if (heart[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					heart.erase(heart.begin() + k); //Player Terkena Hati
					player.HP++; //Menambah Heal
					break; //stop
				}
			}

			//----------PEMBARUAN MUSUH----------
			if (enemySpawnTimer < 103)
				enemySpawnTimer++;

			//MENGHIDUPKAN MUSUH
			if (enemySpawnTimer >= 100)
			{
				enemy.push_back(Enemy(&enemyTexture, window.getSize())); //Memunculkan Musuh
				enemySpawnTimer = 0; //Mengulangi Waktu
			}

			//GERAK MUSUH
			for (size_t i = 0; i < enemy.size(); i++)
			{
				enemy[i].shape.move(-3.f, 0.f); //Musuh Berpindah

				if (enemy[i].shape.getPosition().x <= 0 - enemy[i].shape.getGlobalBounds().width)
				{
					enemy.erase(enemy.begin() + i); //Musuh Terkena Player
					break; //stop
				}

				if (enemy[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemy.erase(enemy.begin() + i); //Player Terkena Musuh
					player.HP--; //Dapat Kerusakan
					break; //stop
				}
			}

			//----------PEMBARUAN USER INTERVIEW----------
			scoreTexture.setString("SCORE: " + std::to_string(score));
		}

		//----------LAYAR UTAMA----------
		window.clear();
		window.draw(background); //Latar Game
		window.draw(player.shape); //Player

		//UI
		window.draw(scoreTexture);
		window.draw(captionsWTexture);
		window.draw(captionsSTexture);
		window.draw(captionsMCTexture);

		window.draw(hpTexture);
		if (player.HP <= 0)
			window.draw(gameoverTexture);

		//PELURU
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		//HATI
		for (size_t k = 0; k < heart.size(); k++)
		{
			window.draw(heart[k].shape);
		}

		//MUSUH
		for (size_t i = 0; i < enemy.size(); i++)
		{
			window.draw(enemy[i].shape);
		}

		window.display();
	}

	return 0;
}