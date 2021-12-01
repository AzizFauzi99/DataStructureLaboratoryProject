// Daftar library
#include <bits/stdc++.h>
using namespace std;

// Daftar struct pemesan
struct Pemesan{
	string nama;

	Pemesan *next;
};

// Variabel Global
Pemesan *head = NULL, *tail = NULL, *cur, *del, *NB; // Deklarasi Queue
int maks = 10;

Pemesan *kepala = NULL, *ekor; // Deklarasi Stack
string namaSampah;

// Stok 
int jumlah[8] = {50,50,50,50,50,50,50,50};
int harga[8] = {20000,15000,12000,10000,10000,10000,10000,10000};
string menu[8] = {"Nasi Goreng", "Seblak", "Ayam Goreng", "Pecel", "Jus Mangga", "Jus Jeruk", "Jus Alpukat", "Jus Nanas"};

// Hitung jumlah data
int countData(){
	if(head == NULL){
		return 0;
	}else{
		int banyak = 0;
		cur = head;
		while(cur != NULL){
			cur = cur->next;
			banyak++;
		}
		return banyak;
	}
}

// isFull	// Cek data penuh atau tidak
bool isFull(){
	if(countData() == maks){
		return true;
	}else{
		return false;
	}
}

// isEmpty	// Cek data kosong atau tidak
bool isEmpty(){
	if(countData() == 0){
		return true;
	}else{
		return false;
	}
}

// Enqueue / isi data Pemesan
void tambahData(string nama){
	if(isFull()){
		cout << "Antrian telah penuh! Harap sabar!" << endl;
	}else{
		if(isEmpty()){
			head = new Pemesan();
			head->nama = nama;
			head->next = NULL;
			tail = head;
		}else{
			NB = new Pemesan();
			NB->nama = nama;
			NB->next = NULL;
			tail->next = NB;
			tail = NB;
		}
	}
}

// Penampung tumpukan data pemesan
void antrianSampah(string namaSampah){
	if(kepala == NULL){
		kepala = new Pemesan();
		kepala->nama = namaSampah;
		kepala->next = NULL;
		ekor = kepala;
	}else{
		Pemesan *sampah;
		sampah = new Pemesan();
		sampah->nama = namaSampah;
		sampah->next = kepala;
		kepala = sampah;
	}
}
// Dequeue / hapus dan dipindah ke riwayat
void hapusData(){
	if(isEmpty()){
		cout << "Antrian kosong! Silahkan isi dulu!" << endl;
	}else{
		del = head;
		namaSampah = del->nama;
		antrianSampah(namaSampah);
		head = head->next;
		delete del;
	}
}

// Display Daftar Pemesan
void displayData(){
	if(isEmpty()){
		cout << "Antrian kosong!" << endl;
	}else{
		cout << "Banyak data antrian saat ini: " << countData() << endl;
		cout << "Data antrian:" << endl;
		int nomor = 1;
		cur = head;
		while(nomor <= maks){
			if(cur != NULL){
				cout << nomor << ". " << cur->nama << endl;
				cur = cur->next;
			}
			nomor++;
		}
	}
	cout << endl;
}

// Display Riwayat Pemesan
void displaySampah(){
	if(kepala == NULL){
		cout << "\nRiwayat pemesan kosong!" << endl;
	}else{
		cout << "\nDaftar riwayat pemesan yang telah selesai memesan\n" << endl;
		cur = kepala;
		while(cur != NULL){
			cout << "-> " << cur->nama << endl;
			cur = cur->next;
		}
	}
	cout << endl;
}

// Banner Resto
void header_utama(){
	cout << setw(40) << setfill('=') << right << "" << endl;
	cout << setw(5) << setfill(' ') << right << "" << "SELAMAT DATANG DI RESTO ASRI!\n";
	cout << setw(40) << setfill('=') << right << "" << endl;
}

// Daftar Menu
void daftarMenu(){
	cout << endl;
	cout << setw(40) << setfill('=') << right << "" << endl;
	cout << setw(7) << setfill(' ') << right << "" << "DAFTAR MENU RESTO ASRI\n";
	cout << setw(40) << setfill('=') << right << "" << endl;
	
	cout << "\nMenu Makanan:\n";
	for(int i = 0 ; i < 4 ; i++){
		if(jumlah[i] > 0){
			cout << i+1 << ". " << menu[i] << "\tRp " << harga[i] << "\tStok : " << jumlah[i] << endl;
		}else{
			cout << i+1 << ". " << menu[i] << " Habis" << endl;
			harga[i] = 0;
		}
	}
	cout << "\nMenu Minuman:\n";
	for(int i = 4 ; i < 8 ; i++){
		if(jumlah[i] > 0){
			cout << i+1 << ". " << menu[i] << "\tRp " << harga[i] << "\tStok : " << jumlah[i] << endl;
		}else{
			cout << i+1 << ". " << menu[i] << " Habis" << endl;
			harga[i] = 0;
		}
	}
	cout << endl;
}

// Total bayar
string namaPesanan[100];
int jumlahPesanan[100];
int total = 0;
void totalBayar(int nomerMenu, int banyakPesanan, int ke){
	namaPesanan[ke] = menu[nomerMenu-1];
	jumlahPesanan[ke] = banyakPesanan;
	jumlah[nomerMenu-1] -= banyakPesanan;
	total = total + jumlahPesanan[ke] * harga[nomerMenu-1];
}

// Display bayar
int bayar ;
int kembalian = 0;
void displayBayar(int ke){
	cout << "\nDaftar Pembelian:\n";
	for(int i = 0 ; i <= ke ; i++){
		cout << i+1 << ". " << namaPesanan[i] << "\tsebanyak " << jumlahPesanan[i] << " porsi" << endl << endl;
	}
	cout << "Total\t\t: " << total << endl;
	x:
	cout << "Bayar\t\t: " ;
	cin >> bayar;
	if(bayar >= total){
		kembalian = bayar-total;
		cout << "\nKembalian\t: " << kembalian << endl;
		hapusData();
	}else{
		cout << "Pembayaran kurang! Mohon diulangi!" << endl;
		goto x;
	}
	kembalian = 0;
	total = 0;
	bayar = 0;
	cout << endl;
}

// Fungsi utama
int main(){
	string nama, adm, c, d;
	int nomerMenu, banyakPesanan, a, b = 0;
	bool ulang = true;
	int pilih;
	
	// Open file txt
	ifstream file("jumlah.txt", ios::in);
	if(file.is_open()){
		while(file >> a){
			jumlah[b] = a;
			b++;
		}
	}
	file.close();
	ifstream file3("nama.txt", ios::in);
	if(file3.is_open()){
		while(file3 >> c){
			tambahData(c);
		}
	}
	file3.close();
	ifstream file5("riwayat.txt", ios::in);
	if(file5.is_open()){
		while(file5 >> d){
			antrianSampah(d);
		}
	}
	file5.close();
	do{
		system("cls");
		header_utama();
		cout << "\nMenu\n";
		cout << "1. Input Pemesan\n";
		cout << "2. Daftar Pemesan\n";
		cout << "3. Daftar Menu\n";
		cout << "4. Pilih Menu\n";
		cout << "5. Riwayat Pemesan\n";
		cout << "6. Keluar\n";
		cout << "Pilih Menu : "; cin >> pilih;
		if(pilih == 1){
			cout << "\nMasukkan Data Pemesan\n";
			cin.ignore();
			cout << "Nama\t: "; 
			getline(cin, nama);
			tambahData(nama);
			cout << "\nData berhasil diinput!\n" << endl;
		}
		else if(pilih == 2){
			cout << "\n";
			displayData();
		}
		else if(pilih == 3){
			daftarMenu();
		}
		else if(pilih == 4){
			if(isEmpty()){
				cout << "\nAntrian kosong!\n" << endl;
			}else{
				int ke = 0;
				daftarMenu();
				cout << "\nAtas Nama\t: " << head->nama ;
				lagi:
				cout << "\nPilih nomer menu: "; cin >> nomerMenu;
				cout << "Mau Berapa\t: "; cin >> banyakPesanan;
				if(nomerMenu < 1 || nomerMenu > 8 || banyakPesanan > jumlah[nomerMenu-1]){
					cout << "Input salah atau stok tidak mencukupi!"<< endl;
					goto lagi;
				}else{
					totalBayar(nomerMenu, banyakPesanan, ke);
					cout << "Mau Pesan Lagi? (y/n) "; cin >> adm;
					if(adm == "y" || adm == "Y"){
						ke++;
						goto lagi;
					}else{
						displayBayar(ke); 
					}
				}
			}
		}
		else if(pilih == 5){
			displaySampah();
		}
		else if(pilih == 6){
			cout << "\nMenyimpan data...\n\nBerhasil menyimpan data!\n";
			cout << "\nKeluar dari Program!!";
			break;
		}
		else{
			cout << "\nMenu yang dipilih tidak tersedia!\n\n";
		}
		
		cout << "Kembali ke Menu Utama?(y/n) " ; 
		cin >> adm;
		if(adm == "y" || adm == "Y"){
			ulang = true;
		}else{
			ulang = false;
		}
	}while(ulang);
	
	// Simpan file txt
	ofstream file2("jumlah.txt", ios::out | ios::trunc);
	for(int i = 0; i < 8; i++){
		file2 << jumlah[i] << endl;
	}
	file2.close();
	ofstream file4("nama.txt", ios::out | ios::trunc);
	cur = head;
	while(cur != NULL){
		file4 << cur->nama << endl;
		cur = cur->next;
	}
	file4.close();
	ofstream file6("riwayat.txt", ios::out | ios::trunc);
	cur = kepala;
	while(cur != NULL){
		file6 << cur->nama << endl;
		cur = cur->next;
	}
	file6.close();
}
