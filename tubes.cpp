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
using namespace std;

typedef struct {
	int x;
	int y;
} Titik ;

char masukan(Titik posisi) {
	/* Menerima input user dan validasi */

	char pilihan;
	bool lanjut;

	lanjut = false;

	while (!lanjut) {
		lanjut = true;
		
		cout << "Ketik 'a' untuk attack, 'f' untuk forward, 'b' untuk backward, 'l' untuk left, 'r' untuk right, 's' untuk stop"<< endl;
		cin >> pilihan;

		if (posisi.x <= 0 && pilihan == 'l') {
			cout << "Masukan salah"<<endl;
			lanjut = false;
		} else if (posisi.y <= 0 && pilihan == 'b') {
			cout << "Masukan salah"<<endl;
			lanjut = false;
		} else if (pilihan != 'a' && pilihan != 'f' && pilihan != 'b' && pilihan != 'l' && pilihan != 'r' && pilihan != 's') {
			cout << "Masukan salah"<<endl;
			lanjut = false;
		}
	}
	return pilihan;
}

Titik bergerak(Titik posisi, char pilihan) {
	/* Bergerak */

	if (pilihan == 'f') {
		posisi.y += 1;
	} else if (pilihan == 'b' && posisi.y > 0) {
		posisi.y -= 1;
	} else if (pilihan == 'l' && posisi.x > 0) {
		posisi.x -= 1;
	} else if (pilihan == 'r') {
		posisi.x += 1;
	}
	return posisi;
}

int nyawa(int health, bool terserang) {
	/* Update Nyawa */

	int pengurangNyawa;
	
	/* pengurangNyawa = ... */

	if (terserang) {
		health -= pengurangNyawa;
	}
	return health;
}

void info(Titik posisi, int health){
	/* Menampilkan info ke layar */
	/* Posisi kecoak belum ditampilkan */

	cout << "Posisi robot : ("<<posisi.x<<","<<posisi.y<<")"<<endl;
	cout << "Nyawa robot : "<<health<<endl;
}

void intro(){
	cout << "Selamat datang dalam program Urang Robot Orang"<<endl;
	cout<<endl;
	/* Intronya diubah wae mangga wkwk aku bingung */
}

void outro(){
	cout<< "Program selesai. Terima kasih"<<endl;
	/* Outro ne diubah yo wkwkw aku bingung*/
}

int main() {
	char inp;	
	Titik posisi;
	int health;
	bool terserang;

	posisi.x = 0;
	posisi.y = 0;
	health = 20; /* Nyawa awal bisa diubah*/

	intro();

	while (true) {
		inp = masukan(posisi);
		if (inp == 's') {
			break; /* Terminasi Program */
		} else if (inp == 'a') {
			/* Menyerang */
		} else {
			posisi = bergerak(posisi, inp);
		}

		/* terserang = diserang(...) */
		health = nyawa(health, terserang);

		info(posisi, health);
	}
	outro();

	return 0;
}
