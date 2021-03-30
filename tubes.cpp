/*
IDENTITAS:
Nama Anggota 	: 	
1. Hafidz Nur Rahman Ghozali		(16520186)
2. Malik Akbar Hashemi Rafsanjani	(16520299)
Topik			: Tugas Besar URO divisi programming
Deskripsi Tugas :
	Program robot yang dapat digerakkan ke kanan, kiri, maju, dan mundur, 
	juga mampu mengkalkulasi jarak antara robot dan musuh kecoak
	serta mampu menembak kecoak mutan tersebut
*/

#include <iostream>
#include <math.h>
using namespace std;

typedef struct {
	int x;
	int y;
} Titik ;

bool validBergerak(Titik posisiRobot, Titik posisiKecoa, char pilihan);

char masukan(Titik posisi, Titik posisiKecoa) {
	/* Menerima input user dan validasi */

	char pilihan;
	bool lanjut;

	lanjut = false;

	while (!lanjut) {
		lanjut = true;
		
		cout << "Ketik 'a' untuk attack, 'f' untuk forward, 'b' untuk backward, 'l' untuk left, 'r' untuk right, 's' untuk stop"<< endl;
		cin >> pilihan;

		if (pilihan == 'a'){
			lanjut = true;
		} else if (validBergerak(posisi, posisiKecoa, pilihan)) {
			lanjut = true;
		} else {
			cout << "Masukan invalid, robot tidak dapat melakukan perintah yang diberikan" << endl;
			lanjut = false;
		}
	}
	return pilihan;
}

bool validBergerak(Titik posisiRobot, Titik posisiKecoa, char pilihan){
	if (pilihan == 'f' && (posisiRobot.y + 1 != posisiKecoa.y)){
		return true;
	} else if (pilihan == 'r' && (posisiRobot.x + 1 != posisiKecoa.x)){
		return true;
	} else if (pilihan == 'b' && posisiRobot.y > 0 && (posisiRobot.y - 1) != posisiKecoa.y) {
		return true;
	} else if (pilihan == 'l' && posisiRobot.x > 0 && (posisiRobot.x - 1) != posisiKecoa.x) {
		return true;
	} else if (pilihan == 's') {
		return true;
	} else {
		return false;
	}
}

Titik bergerak(Titik posisi, char pilihan) {
	/* Bergerak */

	if (pilihan == 'f') {
		posisi.y += 1;
	} else if (pilihan == 'b') {
		posisi.y -= 1;
	} else if (pilihan == 'l') {
		posisi.x -= 1;
	} else if (pilihan == 'r') {
		posisi.x += 1;
	} else if (pilihan == 's') {
		posisi.x = -999;
	}

	return posisi;
}

Titik dropKecoa(Titik posisiRobot){
	Titik posisiKecoa;
	while (true) {
		posisiKecoa.x = rand() % 40;
		posisiKecoa.y = rand() % 40;
	
		if (posisiKecoa.x != posisiRobot.x && posisiKecoa.y != posisiRobot.y){
			break;
		}
	}
	return posisiKecoa;
}

int nyawa(int health, bool terserang) {
	/* Update Nyawa */

	int pengurangNyawa;
	
	pengurangNyawa = 1; // Bisa diubah

	if (terserang) {
		health -= pengurangNyawa;
	}
	return health;
}

float hitungJarak(Titik robot, Titik kecoa){
	float jarak, jarakx, jaraky;
	jarakx = robot.x - kecoa.y;
	jaraky = robot.y - kecoa.y;
	jarak = sqrt(jarakx*jarakx + jaraky*jaraky);

	return jarak;
}

bool bisaSerang( Titik posisi, Titik posisiKecoa, float jarakMax){
	if (hitungJarak(posisi, posisiKecoa) < jarakMax){
		return true;
	} else{
		cout << "Jarak terlalu jauh, robot tidak bisa menembak dan harus bergerak" << endl;
		return false;
	}
}

void info(Titik posisiRobot, Titik posisiKecoa, int health){
	/* Menampilkan info ke layar */
	/* Posisi kecoak belum ditampilkan */

	cout << "Posisi robot : ("<<posisiRobot.x<<","<<posisiRobot.y<<")"<<endl;
	cout << "Nyawa robot : "<<health<<endl;
	cout << "Posisi kecoa : ("<<posisiKecoa.x<<","<<posisiKecoa.y<<")"<<endl;
}

void intro(Titik posisiRobot, Titik posisiKecoa, int health){
	cout << "Selamat datang dalam program Urang Robot Orang"<<endl;
	cout <<endl;
	/* Intronya diubah wae mangga wkwk aku bingung */
	cout << "Posisi awal robot : (" << posisiRobot.x << "," << posisiRobot.y << ")" << endl;
	cout << "Nyawa awal robot : " << health <<endl;
	cout << "Posisi awal kecoa : (" << posisiKecoa.x << "," << posisiKecoa.y << ")" << endl;
}

void outro(int countKecoa){
	cout<<"Robot telah membunuh kecoa sebanyak : " << countKecoa<<endl;
	cout<< "Program selesai. Terima kasih"<<endl;
	/* Outro ne diubah yo wkwkw aku bingung*/
}

Titik totalBergerak(Titik posisiRobot, Titik posisiKecoa, char inp){
	while (!validBergerak(posisiRobot, posisiKecoa, inp)){
		cout << "Masukan invalid, robot tidak dapat bergerak ke arah yang dipilih" << endl;
		cout << "Ketik 'f' untuk forward, 'b' untuk backward, 'l' untuk left, 'r' untuk right, 's' untuk stop"<< endl;
		cin >> inp;
	}
	return bergerak(posisiRobot, inp);
}

bool diserang(Titik posisiRobot, Titik posisiKecoa) {
	if (hitungJarak(posisiRobot, posisiKecoa) < 5) {
		return true;
	} else {
		return false;
	}
}

int main() {
	char inp;	
	Titik posisiRobot, posisiKecoa;
	int health, countKecoa;
	bool terserang;
	float jarakMax = 10;

	posisiRobot.x = 0;
	posisiRobot.y = 0;
	health = 10; /* Nyawa awal bisa diubah*/
	countKecoa = 0;

	posisiKecoa = dropKecoa(posisiRobot);

	intro(posisiRobot, posisiKecoa, health);

	while (true) {
		inp = masukan(posisiRobot, posisiKecoa);
		if (inp == 's') {
			break; /* Terminasi Program */
		} else if (inp == 'a') {
			/* Menyerang */
			if (bisaSerang(posisiRobot, posisiKecoa, jarakMax)) {
				countKecoa += 1;
				cout << "Kecoa " << countKecoa << " telah berhasil dibunuh"<<endl;
				posisiKecoa = dropKecoa(posisiRobot);
			} else {
				cout << "Ketik 'f' untuk forward, 'b' untuk backward, 'l' untuk left, 'r' untuk right, 's' untuk stop"<< endl;
				cin >> inp;

				posisiRobot = totalBergerak(posisiRobot, posisiKecoa, inp);
				if (posisiRobot.x == -999) {
					break;
				}
			}
		} else {
			posisiRobot = totalBergerak(posisiRobot, posisiKecoa, inp);
			if (posisiRobot.x == -999) {
				break;
			}
		}

		terserang = diserang(posisiRobot, posisiKecoa);
		health = nyawa(health, terserang);

		info(posisiRobot, posisiKecoa, health);
	}
	outro(countKecoa);

	return 0;
}
