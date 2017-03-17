// server_nha.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "server_nha.h"
#include "afxsock.h"
#include <fstream>
#include <string.h>
#include <ctime>
#include <iostream>
#include<stdio.h>
#include<string>
#include<Windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define MAX_BO 5

// The one and only application object

static int Vitri_Contro_File=0;

CWinApp theApp;

using namespace std;

typedef struct Q_A
{
	char * _cauhoi;
	char * _dapan;
};



void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void chayvaotrong(char *a, int x, int y)
{
	int T = strlen(a);
	int M = T;
	for (int i = 0; i < T; i++)
	{
		gotoxy(x + i, y);
		for (int j = 0; j < M; j++)
		{
			printf("%c", a[j]);
		}
		M--;
		Sleep(100);
		gotoxy(x, y);
		for (int k = 0; k < T; k++)
			printf(" ");

	}

}

void chaychu(char *a, int x, int y, int p, int ok)
{

	int T = strlen(a);
	int ik = 0;
	while (ok > ik)
	{
		gotoxy(x, y);
		for (int k = 0; k < T; k++)
			printf(" ");
		gotoxy(x, y);
		for (int i = T - 1; i >= 0; i--)
		{
			int j;
			for (j = i; j < T; j++)
			{
				printf("%c", a[j]);
			}
			gotoxy(x, y);
			for (int k = 0; k < T - j; k++)
				printf(" ");
			Sleep(100);
			if (i == 0 && p == 1) chayvaotrong(a, x, y);
		}
		ik++;
	}
}

void beep(int x, int y, int M)
{
	int T = 0;
	while (T < M)
	{
		gotoxy(x, y);
		printf(".");
		Beep(310, 300);
		gotoxy(x + 1, 16);
		printf(".");
		Beep(310, 300);
		gotoxy(x + 1, y + 1);
		printf(".");
		Beep(310, 300);
		gotoxy(x, y + 1);
		printf(".");
		Beep(310, 300);
		gotoxy(x, 16);
		printf(" ");
		gotoxy(x + 1, 16);
		printf(" ");
		gotoxy(x + 1, y + 1);
		printf(" ");
		gotoxy(x, y + 1);
		printf(" ");
		Sleep(63);
		T++;
	}
}

void XuatThongTin()
{
	for (int i = 0; i <= 70; i++)
	{
		gotoxy(i, 0);
		printf("*");
		gotoxy(i, 13);
		printf("*");
		Beep(5000, 25);
	}
	for (int i = 1; i <= 13; i++)
	{
		gotoxy(0, i);
		printf("*");
		gotoxy(70, i);
		printf("*");
		Beep(5000, 10);
	}
	gotoxy(15, 2);
	printf("       TRUONG DH KHOA HOC TU NHIEN");
	gotoxy(24, 3);
	printf("Khoa Cong Nghe Thong Tin");
	gotoxy(27, 5);
	Sleep(600);
	printf("DO AN SOCKET");
	gotoxy(27, 6);
	printf("TRO CHOI DOI MAT");
	gotoxy(20, 8);
	Sleep(600);
	printf("Ten:  TRAN THI NHA	MSSV:1412363");
	gotoxy(20, 10);
	printf("Ten:  LE TIEN THINH	MSSV:1312560");
	gotoxy(20, 10);
	
	char mo[] = "Tp. Ho Chi Minh, 26 thang 06 nam 2016";
	chaychu(mo, 27, 12, 0, 1);
	//beep(1, 16, 2);
	gotoxy(0, 16);
}



//mảng đánh dấu bộ câu hỏi nào đã được sử dụng
int *STT_chon;

void khoitao()
{
	for (int i = 0; i < MAX_BO; i++)
	{
		STT_chon[i] = 0;//chưa chọn
	}
}

void KiemTra_Nickname(CSocket *cl, char ** Name,int i,int So_Client)
{
	char name[20];
	int kt = 1;
	
	while (kt == 1)
	{
		cl[i].Receive(name, 20, 0);
		kt = 0;

		int j = 0;
		while (name[j] != '\0')
		{
			if (!((name[j] >= 'a' && name[j] <= 'z')
				|| (name[j] >= 'A' && name[j] <= 'Z')
				|| (name[j] >= '0' && name[j] <= '0')))
			{
				char *res = "Nickname khong hop le, vui long kiem tra lai!\n";
				cl[i].Send(res, strlen(res), 0);

				char *ok = new char[3];
				cl[i].Receive(ok, 3, 0);

				char check[5] = "no";
				int len = strlen(check);
				cl[i].Send(check, len, 0);

				char *ok1 = new char[3];
				cl[i].Receive(ok1, 3, 0);

				kt = 1;
				break;
			}
			j++;
		}

		for (int k = 0; k < So_Client; k++)
		{
			if (strcmp(name, Name[k]) == 0)
			{
				char *res = "Nickname da bi trung, vui long dang ky voi ten khac!\n";
				cl[i].Send(res, strlen(res), 0);

				char *ok = new char[3];
				cl[i].Receive(ok, 3, 0);
				char check[5] = "no";
				int len = strlen(check);
				cl[i].Send(check, len, 0);

				char *ok1 = new char[3];
				cl[i].Receive(ok1, 3, 0);

				
				kt = 1;
				break;
			}
		}
	}



	char res[30] = "dang ky thanh cong\n";
	int len = strlen(res);
	cl[i].Send(res, len , 0);


	char ok[5];
	cl[i].Receive(ok, 5, 0);

	char check[5] = "yes";
	int len2 = strlen(check);
	cl[i].Send(check, len2 , 0);

	char ok1[5];
	cl[i].Receive(ok1, 5, 0);

	int l = strlen(name);
	Name[i] = new char[l];
	strcpy_s(Name[i], 100, name);
	cout << "vua ket noi voi " << name << endl;
}



void LayCauHoi( char *filename,Q_A *DeBai)
{
	
	fstream f;

	f.open(filename, ios::in);

	if (f)
	{
		int i = 0;
		while (!f.eof())
		{
			string cauhoi, phuongan, dapan;

			if (!f.eof())
			{
				getline(f, cauhoi);
				if (!f.eof())
				{
					getline(f, phuongan);
					if (!f.eof())
					{
						getline(f, dapan);


						cauhoi += "\n" + phuongan;

						DeBai[i]._cauhoi = new char[cauhoi.length()];
						DeBai[i]._dapan = new char[dapan.length()];
						for (int j = 0; j < cauhoi.length(); j++)
						{

							DeBai[i]._cauhoi[j] = cauhoi[j];
						}

						for (int j = 0; j < dapan.length(); j++)
						{
							DeBai[i]._dapan[j] = dapan[j];
						}
						i++;
					}
				}
			}
		}

		
		f.close();
	}
}


void ThongBao(CSocket * ArrClient,int i,int So_Client)
{
	//thông báo số người chơi
	char thongbao_songuoi[100] = "-	So nguoi choi la: ";
	ArrClient[i].Send(thongbao_songuoi, strlen(thongbao_songuoi), 0);

	char *ok = new char[5];
	ArrClient[i].Receive(ok, 5, 0);

	int So_ng = So_Client;
	ArrClient[i].Send((char *)&So_ng, sizeof(int), 0);

	char *ok1 = new char[5];
	ArrClient[i].Receive(ok1, 5, 0);

	//thông báo thứ tự đoán
	char thongbao_thutu[100] = "-	Thu tu doan la: ";
	ArrClient[i].Send(thongbao_thutu, strlen(thongbao_thutu), 0);

	char *ok2 = new char[5];
	ArrClient[i].Receive(ok2, 5, 0);

	int So_TT=i+1;

	//x = i + 1;

	
	ArrClient[i].Send((char*)&So_TT, sizeof(int), 0);

	char *ok3 = new char[5];
	ArrClient[i].Receive(ok3, 5, 0);

	//thông báo số câu hỏi
	char thongbao_socauhoi[100] = "-	So cau hoi la: ";
	ArrClient[i].Send(thongbao_socauhoi, strlen(thongbao_socauhoi), 0);

	char *ok4 = new char[5];
	ArrClient[i].Receive(ok4, 5, 0);

	int So_cauhoi=So_Client*8;
	
	ArrClient[i].Send((char*)&So_cauhoi, sizeof(int), 0);

	char *ok5 = new char[5];
	ArrClient[i].Receive(ok5, 5, 0);
}


bool KiemTraConMotNguoiChoi(int *QuyenChoi,int So_Client)
{
	int dem = 0;
	for (int i = 0; i < So_Client; i++)
	{
		if (QuyenChoi[i] == 1)
		{
			dem++;
		}
	}
	if (dem == 1)
		return true;
	return false;
}


void choi(CSocket *ArrClient, int So_Client, char **Arr_name_Client,Q_A* DeBai)
{
	//DanhSach = new Q_A;


	//mảng cho biết phương án nhường quyền đã dùng chưa, 0: chưa, 1: rồi
	int *NhuongQuyen = new int[So_Client];
	for (int i = 0; i < So_Client; i++)
	{
		NhuongQuyen[i] = 0;
	}


	//mảng đánh dấu xem người chơi có được quyền chơi nữa hay không. 0: không, 1: có
	int *QuyenChoi;
	QuyenChoi = new int[So_Client];
	for (int i = 0; i < So_Client; i++)
	{
		QuyenChoi[i] = 1;
	}


	int *Diem = new int[So_Client];//mảng chứa điểm của từng người chơi
	for (int i = 0; i < So_Client; i++)
	{
		Diem[i] = 0;
	}


	//bắt đầu chơi
	int i = 0; //biến đếm số câu hỏi đã hỏi
	char *quyen = new char; //biến gửi phản hồi cho người chơi là mất lượt


	bool KiemtraHetNguoiChoi = false;


	if (So_Client > 1)

	{
		while ((i != 8 * So_Client))
		{
			if (KiemtraHetNguoiChoi)
				break;

			for (int j = 0; j < So_Client; j++)
			{

				if (QuyenChoi[j] == 1)
				{

					//báo lượt
					char bao_luot[40] = "	Den luot choi, ban san sang chua?\n";
					ArrClient[j].Send(bao_luot, strlen(bao_luot), 0);

					char ok6[5];
					ArrClient[j].Receive(ok6, 5, 0);

					//gửi câu hỏi
					char *cauhoi = DeBai[Vitri_Contro_File]._cauhoi;//= DanhSach[i]._cauhoi;
					ArrClient[j].Send(cauhoi, strlen(cauhoi), 0);


					//nhận phản hồi 1:trả lời, 2:nhường quyền
					char phuongan[2];
					char *bao_phuongan = new char;
					int l = ArrClient[j].Receive(phuongan, 5, 0);
					phuongan[l] = '\0';

					char *dauhieunhuongquyen;
					if (strcmp(phuongan, "2") == 0 && NhuongQuyen[j] == 1)
					{
						bao_phuongan = "	Ban chi duoc nhuong quyen 1 lan, vui long nhan 1 de tra loi cau hoi!\n";
						ArrClient[j].Send(bao_phuongan, strlen(bao_phuongan), 0);


						char ok7[5];
						ArrClient[j].Receive(ok7, 5, 0);

						dauhieunhuongquyen = "false";
						ArrClient[j].Send(dauhieunhuongquyen, strlen(dauhieunhuongquyen), 0);

						char ok8[5];
						ArrClient[j].Receive(ok8, 5, 0);


						bao_phuongan = "	Bạn da chon phuong an tra loi cau hoi, xin moi ban tra loi!\n";
						ArrClient[j].Send(bao_phuongan, strlen(bao_phuongan), 0);


						char traloi[50];
						int l_tl = ArrClient[j].Receive(traloi, 50, 0);
						traloi[l_tl] = '\0';
						char *bao_dapan;
						char nodo[1];
						nodo[0] = DeBai[Vitri_Contro_File]._dapan[0];
						if (strcmp(traloi, nodo) == 0)
						{
							bao_dapan = "	Cau tra loi DUNG, vui long doi luot choi tiep!:))\n";
							ArrClient[j].Send(bao_dapan, strlen(bao_dapan), 0);

							if (i == So_Client * 8 - 1 || (KiemTraConMotNguoiChoi(QuyenChoi, So_Client)))
							{
								quyen = "mat luot";
								KiemtraHetNguoiChoi = true;

							}

							else quyen = "con luot";

							Diem[j]++;

							char ok10[5];
							ArrClient[j].Receive(ok10, 5, 0);


							ArrClient[j].Send(quyen, strlen(quyen), 0);

							char ok11[5];
							ArrClient[j].Receive(ok11, 5, 0);
						}
						else
						{
							bao_dapan = "	Cau tra loi SAI, ban da mat luot choi!:((\n";
							ArrClient[j].Send(bao_dapan, strlen(bao_dapan), 0);

							char ok10[5];
							ArrClient[j].Receive(ok10, 5, 0);


							quyen = "mat luot";
							ArrClient[j].Send(quyen, strlen(quyen), 0);
							if (KiemTraConMotNguoiChoi(QuyenChoi, So_Client))
							{
								QuyenChoi[j] = 1;
								KiemtraHetNguoiChoi = true;

							}

							else QuyenChoi[j] = 0;

							char ok11[5];
							ArrClient[j].Receive(ok11, 5, 0);

						}
						i++;
					}

					else if (strcmp(phuongan, "2") == 0 && NhuongQuyen[j] == 0)
					{
						bao_phuongan = "	Ban da chon phuong an nhuong quyen!\n";
						ArrClient[j].Send(bao_phuongan, strlen(bao_phuongan), 0);
						dauhieunhuongquyen = "true";

						NhuongQuyen[j] = 1;

						char ok7[5];
						ArrClient[j].Receive(ok7, 5, 0);

						ArrClient[j].Send(dauhieunhuongquyen, strlen(dauhieunhuongquyen), 0);

						if (i == So_Client * 8 - 1 || (KiemTraConMotNguoiChoi(QuyenChoi, So_Client)))
						{
							quyen = "mat luot";
							KiemtraHetNguoiChoi = true;
							Vitri_Contro_File--;


						}

						else quyen = "con luot";

						char ok8[5];
						ArrClient[j].Receive(ok8, 5, 0);

						ArrClient[j].Send(quyen, strlen(quyen), 0);

						char ok9[5];
						ArrClient[j].Receive(ok9, 5, 0);


						continue;
					}
					else if (strcmp(phuongan, "1") == 0)
					{
						bao_phuongan = "	Bạn da chon phuong an tra loi cau hoi, xin moi ban tra loi!\n";
						ArrClient[j].Send(bao_phuongan, strlen(bao_phuongan), 0);



						char traloi[50];
						int l_tl = ArrClient[j].Receive(traloi, 50, 0);
						traloi[l_tl] = '\0';



						char *bao_dapan;
						char nodo[1];
						nodo[0]=DeBai[Vitri_Contro_File]._dapan[0];
						if (strcmp(traloi, nodo) == 0)
						{
							bao_dapan = "	Cau tra loi DUNG, vui long doi luot choi tiep! :))\n";
							ArrClient[j].Send(bao_dapan, strlen(bao_dapan), 0);

							Diem[j]++;

							char ok12[5];
							ArrClient[j].Receive(ok12, 5, 0);

							if (i == So_Client * 8 - 1 || (KiemTraConMotNguoiChoi(QuyenChoi, So_Client)))
							{
								quyen = "mat luot";
								KiemtraHetNguoiChoi = true;


							}
							else quyen = "con luot";
							ArrClient[j].Send(quyen, strlen(quyen), 0);

							char ok13[5];
							ArrClient[j].Receive(ok13, 5, 0);
						}
						else
						{
							bao_dapan = "	cau tra loi SAI, ban da mat luot choi! :((\n";
							ArrClient[j].Send(bao_dapan, strlen(bao_dapan), 0);

							char ok12[5];
							ArrClient[j].Receive(ok12, 5, 0);

							if (KiemTraConMotNguoiChoi(QuyenChoi, So_Client))
							{
								QuyenChoi[j] = 1;
								KiemtraHetNguoiChoi = true;


							}
							else QuyenChoi[j] = 0;

							quyen = "mat luot";
							ArrClient[j].Send(quyen, strlen(quyen), 0);


							char ok13[5];
							ArrClient[j].Receive(ok13, 5, 0);

						}
						i++;
					}

					Vitri_Contro_File++;

				}

				if (KiemtraHetNguoiChoi || i == So_Client * 8)

					break;
			}


		}

		int max = 0;
		int nguoi;

		if (i == So_Client * 8 || KiemTraConMotNguoiChoi(QuyenChoi, So_Client))
		{
			for (int j = 0; j < So_Client; j++)
			{
				if (QuyenChoi[j] == 0)
				{
					char ketthuc[60] = " --------LUOT CHOI KET THUC-------\n	BAN DA THUA CUOC! :((((";
					ArrClient[j].Send(ketthuc, strlen(ketthuc), 0);

					char ok14[5];
					ArrClient[j].Receive(ok14, 5, 0);
				}
				else
				{
					if (Diem[j] >= max)
					{
						max = Diem[j];
					}
				}

			}

			for (int k = 0; k < So_Client; k++)
			{
				if (Diem[k] == max && QuyenChoi[k] == 1)
				{
					char ketthuc[60] = "-----LUOT CHOI KET THUC-----\n	BAN LA NGUOI CHIEN THANG! :))";
					ArrClient[k].Send(ketthuc, strlen(ketthuc), 0);
				}
			}
		}
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			//khai báo biến socket
			
			CSocket server;
			AfxSocketInit(NULL);
			server.Create(1234);

			//khởi tạo
			

			XuatThongTin();

			int So_luot;
			cout << "Nhap so luot choi: ";

			cin >> So_luot;

			cout << endl<<"----------------------------BAT DAU VAO LUOT CHOI----------------------------" << endl;

			cout << "Nhan enter de chuyen sang man choi dau tien...\n"<<">>"<<endl;
			system("pause");
			system("cls");

			int So_Client;

			Q_A  DeBai[500];

			LayCauHoi( "cauhoi.txt", DeBai);


			for (int luot = 0; luot < So_luot; luot++)
			{
				CSocket *ArrClient;

				
				server.Listen();


				//nhập số người chơi
				 
				cout <<endl<< "-------------------------------LUOT CHOI THU " << luot + 1 << "-----------------------------" << endl << endl;

				cout << "Nhap so nguoi choi: ";
				cin >> So_Client;

				cout << "\nDang lang nghe ket noi tu Client...\n";
				ArrClient = new CSocket[So_Client];

				//danh sách tên
				char **Arr_name_Client;
				Arr_name_Client = new char *[So_Client];
				for (int i = 0; i < So_Client; i++)
				{
					Arr_name_Client[i] = "";
				}


				int i, x;
				//chấp nhận kết nối
				for (i = 0; i < So_Client; i++)
				{
					server.Accept(ArrClient[i]);
					KiemTra_Nickname(ArrClient, Arr_name_Client, i, So_Client);

					ThongBao(ArrClient, i, So_Client);

					}

				

				
				choi(ArrClient, So_Client, Arr_name_Client,DeBai);

				for (int j = 0; j < So_Client; j++)
				{
					ArrClient[j].Close();
				}

				if (luot < So_luot - 1)
				{
					cout <<endl<< "-----------------------------------CHUYEN LUOT-----------------------------------"<<endl<<">>"<<endl;
					system("pause");
					system("cls");
				}
				else {

					system("pause");

				}
			}
			
		}
		
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
