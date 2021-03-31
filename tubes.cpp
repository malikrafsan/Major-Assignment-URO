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
#include <stdlib.h>
using namespace std;

typedef struct {
	int x;
	int y;
} Titik ;

/* fungsi mengecek apakah posisi robot sama dengan posisi kecoa */
bool isSame(Titik posisiRobot, Titik posisiKecoa){
	if (posisiKecoa.x == posisiRobot.x && posisiKecoa.y == posisiRobot.y) return true;
	else return false; 
}

/* fungsi mengecek apakah robot bisa bergerak sesuai dengan perintah yang dimasukkan atau tidak */
bool validBergerak(Titik posisiRobot, Titik posisiKecoa, char pilihan){
	if (pilihan == 'f' && (posisiRobot.y + 1 != posisiKecoa.y)){
		return true;
	} else if (pilihan == 'r' && !isSame(posisiRobot, posisiKecoa)){
		return true;
	} else if (pilihan == 'b' && posisiRobot.y > 0 && !isSame(posisiRobot, posisiKecoa)) {
		return true;
	} else if (pilihan == 'l' && posisiRobot.x > 0 && !isSame(posisiRobot, posisiKecoa)) {
		return true;
	} else if (pilihan == 's') {
		return true;
	} else {
		return false;
	}
}

/* fungsi menerima masukan pilihan bergerak untuk robot */
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

/* fungsi bergerak bagi robot.
memerlukan parameter posisi awal robot dan pilihan pergerakan
kemudian mengembalikan posisi robot setelah bergerak */
Titik bergerak(Titik posisi, char pilihan) {

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

/* fungsi penentuan titik munculnya kecoa secara random */
Titik dropKecoa(Titik posisiRobot){
	Titik posisiKecoa;
	while (true) {
		posisiKecoa.x = rand() % 25;
		posisiKecoa.y = rand() % 25;
	
		if (!isSame(posisiRobot, posisiKecoa)) break;
	}
	return posisiKecoa;
}

/* fungsi mengupdate nyawa robot */
int nyawa(int health, bool terserang) {
	int pengurangNyawa;
	pengurangNyawa = 1; // Bisa diubah
	if (terserang) {
		health -= pengurangNyawa;
	}
	return health;
}

/* fungsi untuk menghitung jarak antara kecoa dan robot. 
memerlukan parameter posisi robot dan kecoa dan mengembalikan jarak antara keduanya */
float hitungJarak(Titik robot, Titik kecoa){
	float jarak, jarakx, jaraky;
	jarakx = robot.x - kecoa.y;
	jaraky = robot.y - kecoa.y;
	jarak = sqrt(jarakx*jarakx + jaraky*jaraky);

	return jarak;
}

/* fungsi validasi apakah robot bisa menyerang atau tidak.
memerlukan parameter posisi robot, kecoa, dan jangkauan serangan maksimum.
menegembalikan hasil validasi berupa boolean */
bool bisaSerang( Titik posisi, Titik posisiKecoa, float jarakMax){
	if (hitungJarak(posisi, posisiKecoa) < jarakMax){
		return true;
	} else{
		cout << "Jarak terlalu jauh, robot tidak bisa menembak dan harus bergerak" << endl;
		return false;
	}
}

/* prosedur mengeluarkan info
I.S : posisiRobot, posisiKecoa, health terdefinisi
F.S : mengeluarkan deskripsi berdasarkan parameter di atas */
void info(Titik posisiRobot, Titik posisiKecoa, int health){
	cout << "  Posisi robot : (" << posisiRobot.x << "," << posisiRobot.y << ")" << endl;
	cout << "  Nyawa robot : " << health << endl;
	cout << "  Posisi kecoa : (" << posisiKecoa.x << "," << posisiKecoa.y << ")" << endl;
	cout << endl;
}

/* prosedur mengeluarkan intro di awal program
I.S : posisiRobot, posisiKecoa, health terdefinisi
F.S : mengeluarkan deskripsi awal program berdasarkan parameter di atas */
void intro(Titik posisiRobot, Titik posisiKecoa, int health, float jarakMax){
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                          Selamat datang dalam program Urang Robot Orang                                |" << endl;
	cout << "|                                                                                                        |" << endl;
	cout << "|    Ini adalah program game robot pemburu kecoa. Anda diminta untuk membunuh kecoa sebanyak mungkin.    |" << endl;
	cout << "|            Anda dapat memanfaatkan perintah-perintah yang tersedia di dalam program ini.               |" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "  Posisi awal robot : (" << posisiRobot.x << "," << posisiRobot.y << ")" << endl;
	cout << "  Nyawa awal robot : " << health <<endl;
	cout << "  Posisi awal kecoa : (" << posisiKecoa.x << "," << posisiKecoa.y << ")" << endl;
	cout << "  Jangkauan serang robot : " << jarakMax << endl;
	cout << endl;
}

/* prosedur mengeluarkan outro
I.S : countKecoa terdefinisi
F.S : mengeluarkan penutup program berdaasarkan parameter di atas */
void outro(int countKecoa){
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                         Program telah selesai.                                         |"<<endl;
	cout << "|                               Selamat, Robot Anda telah membunuh " << countKecoa << " kecoa                               |" << endl;
	cout << "|                              Terima kasih telah menggunakan program kami.                              |" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

/* fungsi untuk menggerakkan robot.
memerlukan parameter posisi robot dan kecoa serta pilihan bergerak.
kemudian mengembalikan posisi robot setelah bergerak */
Titik totalBergerak(Titik posisiRobot, Titik posisiKecoa, char inp){
	while (!validBergerak(posisiRobot, posisiKecoa, inp)){
		cout << "Masukan invalid, robot tidak dapat bergerak ke arah yang dipilih" << endl;
		cout << "Ketik 'f' untuk forward, 'b' untuk backward, 'l' untuk left, 'r' untuk right, 's' untuk stop"<< endl;
		cin >> inp;
	}
	return bergerak(posisiRobot, inp);
}

/* fungsi diserang
memerlukan parameter posisis robot dan kecoa dan mengembalikan 
boolean apakah robot dalam radius serang kecoa */
bool diserang(Titik posisiRobot, Titik posisiKecoa) {
	if (hitungJarak(posisiRobot, posisiKecoa) < 5) {
		return true;
	} else {
		return false;
	}
}

/* MAIN PROGRAM */
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

	while (true) {
		system("cls");
		intro(posisiRobot, posisiKecoa, health, jarakMax);
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
