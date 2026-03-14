#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

struct Film{
	char codeID[20];
	string judul;
	int harga;
	int tahun;
	double rating;
};  
	Film arr[100];
	int jumlahFilm = 0;
	
void olahData();
void inputData();
void tampilData();
void quickSort(Film arr[], int awal, int akhir);
void bubbleSort();
void linearSearch();
void binarySearch();
void tambahData();

int main(){
	olahData();
	string lanjut;
	do{
		cout << "+========================================+" << endl;
		cout << "|	  NETFILM -DASHBOARD		 |" << endl;
		cout << "+========================================+" << endl;
		cout << "| 1. KATALOG FILM                        |" << endl;
		cout << "| 2. SORT BY RATING                      |" << endl;
		cout << "| 3. SORT BY ABJAD                       |" << endl;
		cout << "| 4. CARI FILM (linear serach)           |" << endl;
		cout << "| 5. CARI FILM (Binary serach)           |" << endl;
		cout << "| 6. ADD NEW FILM                        |" << endl;
		cout << "| 0. SAVE & EXIT                         |" << endl;
		cout << "=========================================+" << endl;
			
		int menu;
		cout << "Input Menu >> ";
		cin >> menu;
	
			switch (menu) {
				case 1:
					tampilData();
					break;
				case 2:
					quickSort(arr, 0, jumlahFilm - 1);
					break;
				case 3:
					bubbleSort();
					break;
				case 4:
					linearSearch();
					break;
				case 5:
					binarySearch();
					break;
				case 6:
					tambahData();
					break;
				case 0:
					cout << "Program Keluar";
					return 0;
				default:
					cout << "Opsi di luar jangkauan!!!" << endl;
			}

		cout << "Lanjut ke Menu (Y/N): ";
		cin >> lanjut;
		system("cls");
	} while (lanjut == "Y" || lanjut == "y");
}

void olahData(){
	FILE *file = fopen("netfilm.txt", "r");
    if (!file) {
        cout << "ERROR! \n";
        return;
    }

    jumlahFilm = 0;
    char tempJudul[100];

    while (fscanf(file, "%[^;];%[^;];%d;%d;%lf\n",
				  arr[jumlahFilm].codeID,
                  tempJudul,
                  &arr[jumlahFilm].harga,
                  &arr[jumlahFilm].tahun,
                  &arr[jumlahFilm].rating) != EOF) {
        arr[jumlahFilm].judul = tempJudul;
        jumlahFilm++;
    }
    fclose(file);
}

void inputData() {
    FILE *file = fopen("netfilm.txt", "w");
    if (!file) {
        cout << "ERROR! \n";
        return;
    }
    fprintf(file, "F0E5;Enola Holmes 2;100000;2022;4.8\n");
    fprintf(file, "F0S4;Sore Istri Dari Masa Depan;150000;2025;4.9\n");
    fprintf(file, "F0F6;Family Switch;200000;2023;4.2\n");
    fprintf(file, "F0T3;The Parent Trap;175000;1998;4.8\n");
    fprintf(file, "F0N5;Night At The Museum;160000;2006;3.7\n");
    fclose(file);
}

void tampilData() {
    system("cls");
    cout << "================================================================================================================\n";
    cout << "\t\t\t\tLIST KATALOG FILM\n";
    cout << "================================================================================================================\n";
    cout << left << setw(5)  << "No."
         << setw(10) << "Kode ID"
         << setw(30) << "Judul Film"
         << setw(15) << "Lisensi"
         << setw(10) << "Tahun"
         << setw(10) << "Rating" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------\n";

    for (int j = 0; j < jumlahFilm; j++) {
        cout << left << setw(5)  << j+1
             << setw(10) << arr[j].codeID
             << setw(30) << arr[j].judul
             << "Rp " << setw(12) << arr[j].harga
             << setw(10) << arr[j].tahun
             << setw(10) << arr[j].rating 
             << endl;
    }

    cout << "================================================================================================================\n";
    cout << "Total Film: " << jumlahFilm << "\t\t\t\t\t\t\t\t\t\t\t-netfilm" << endl;
    cout << "================================================================================================================\n";
}

void quickSort(Film arr[], int awal, int akhir) {
    int low = awal, high = akhir;
    double pivot = arr[(awal + akhir) / 2].rating;

    do {
        while (arr[low].rating > pivot)
            low++;
        while (arr[high].rating < pivot)
            high--;
        if (low <= high) {
            swap(arr[low], arr[high]);
            low++;
            high--;
        }
    } while (low <= high);

    if (awal < high)
        quickSort(arr, awal, high);
    if (low < akhir)
        quickSort(arr, low, akhir);
        
    tampilData();
}


void bubbleSort(){
	for (int i = 0; i < jumlahFilm - 1; i++) {
		for (int j = 0; j < jumlahFilm - i - 1; j++) {
			if (arr[j].judul > arr[j + 1].judul) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	tampilData();
}

void linearSearch(){
	system("cls");
    cout << "===========================================================\n";
    cout << "\t\tLINEAR SEARCH" << endl;
    cout << "===========================================================\n";
	if (jumlahFilm < 30){
		string cariLagi;
		do{
			string cari;
			cout << "Masukkan judul film yang ingin dicari: ";
			cin.ignore();
			getline(cin, cari);
	
			bool found = false;
			for (int i = 0; i < jumlahFilm; i++) {
				if (arr[i].judul == cari) {
					cout << "Film ditemukan:\n";
					cout << "Judul: " << arr[i].judul << endl;
					cout << "Harga: Rp " << arr[i].harga << endl;
					cout << "Tahun: " << arr[i].tahun << endl;
					cout << "Rating: " << arr[i].rating << endl;
					found = true;
					cariLagi = "N";
					break;
				}
			}
	
			if (!found) {
				cout << "Mohon maaf judul film belum tersedia.\n";
				cout << "Ingin mencari film lain? (Y/N): ";
				cin >> cariLagi;
				cout << endl;
			}	
		} while(cariLagi == "Y" || cariLagi == "y");
	} else {
		cout << "Note: Linear Search digunakan untuk data film kurang dari 30 judul\n";
		cout << "Jumlah film saat ini terlalu banyak untuk pencarian linear.\n";
		cout << "Gunakan pencarian binary!!.\n";
		
		string alih;
		cout << "Beralih ke Pencarian Linear? (Y/N): ";
		cin >> alih;
		if (alih == "y" || alih == "Y"){
			binarySearch();
		}
	}
}

void binarySearch(){
	system("cls");
    cout << "===========================================================\n";
    cout << "\t\tBINARY SEARCH" << endl;
    cout << "===========================================================\n";
	if (jumlahFilm >= 30){
		string cariLagi;
		do{
			for (int i = 0; i < jumlahFilm - 1; i++) {
				for (int j = 0; j < jumlahFilm - i - 1; j++){
					if (arr[j].judul > arr[j + 1].judul){
					swap(arr[j], arr[j + 1]);
					}
				}
			}

			string cari;
			cout << "Masukkan judul film yang ingin dicari: ";
			cin.ignore();
			getline(cin, cari);
	
			int left = 0, right = jumlahFilm - 1;
			bool found = false;
	
			while (left <= right) {
				int mid = left + (right - left) / 2;
	
				if (arr[mid].judul == cari) {
					cout << "Film ditemukan:\n";
					cout << "Judul: " << arr[mid].judul << endl;
					cout << "Harga: Rp " << arr[mid].harga << endl;
					cout << "Tahun: " << arr[mid].tahun << endl;
					cout << "Rating: " << arr[mid].rating << endl;
					found = true;
					cariLagi = "N";
					break;
				} else if (arr[mid].judul < cari) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
	
			if (!found) {
				cout << "Mohon maaf judul film belum tersedia.\n";
				cout << "Ingin mencari film lain? (Y/N): ";
				cin >> cariLagi;
				cout << endl;
			}
		} while(cariLagi == "Y" || cariLagi == "y");
	} else {
		cout << "Note: Binary Search digunakan untuk data film lebih dari 30 judul\n";
		cout << "Jumlah film saat ini terlalu sedikit untuk pencarian binary.\n";
		cout << "Gunakan pencarian linear!!.\n";
		
		string alih;
		cout << "Beralih ke Pencarian Linear? (Y/N): ";
		cin >> alih;
		if (alih == "y" || alih == "Y"){
			linearSearch();
		}
	}
}

void tambahData(){
	system("cls");
    cout << "===========================================================\n";
    cout << "\t\tTAMBAH DATA FILM" << endl;
    cout << "===========================================================\n";
    
    int jmlDataBaru;
    cout << "Tambah berapa data film: ";
    cin >> jmlDataBaru;
    cin.ignore();
    
    for(int i = 0; i < jmlDataBaru; i++){
		if (jumlahFilm < 100) {
			cout << "Masukkan kode ID film: ";
			cin >> arr[jumlahFilm].codeID;

			cout << "Masukkan judul film: ";
			cin.ignore();
			getline(cin, arr[jumlahFilm].judul);
		
			cout << "Masukkan harga film: ";
			cin >> arr[jumlahFilm].harga;
			
			cout << "Masukkan tahun rilis film: ";
			cin >> arr[jumlahFilm].tahun;
		
			cout << "Masukkan rating film: ";
			cin >> arr[jumlahFilm].rating;
			cin.ignore();
		
			jumlahFilm++;
			cout << "Data film berhasil ditambahkan.\n\n";
		
			FILE *file = fopen("netfilm.txt", "a");
			if (!file) {
				cout << "ERROR membuka file!\n";
				return;
			}
			fprintf(file, "%s;%s;%d;%d;%.1f\n",
					arr[jumlahFilm-1].codeID,
					arr[jumlahFilm-1].judul.c_str(),
					arr[jumlahFilm-1].harga,
					arr[jumlahFilm-1].tahun,
					arr[jumlahFilm-1].rating);
			fclose(file);

		} else {
			cout << "Kapasitas data film sudah penuh. Tidak dapat menambahkan data baru.\n";
		}
	}
}
