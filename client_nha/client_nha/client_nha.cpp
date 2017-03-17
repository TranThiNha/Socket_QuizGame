// client_nha.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "client_nha.h"
#include "afxsock.h"
#include <fstream>
#include<string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

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
			CSocket client;
			AfxSocketInit(NULL);
			client.Create();
			char name[20];

			if (client.Connect(_T("127.0.0.1"), 1234))
			{
				cout << "Da ket noi den server!\n";

				char check[5];

				do
				{
					cout << "Nhap ten:";
					gets_s(name);
					int len = strlen(name);
					name[len] = '\0';
					client.Send(name, len + 1, 0);

					char res[60];

					int l = client.Receive(res, 60, 0);
					res[l] = '\0';
					cout << res << endl;

					char ok[3] = "ok";
					client.Send(ok, strlen(ok), 0);

					int l2 = client.Receive(check, 5, 0);
					check[l2] = '\0';


					char ok1[3] = "ok";
					client.Send(ok1, strlen(ok1), 0);


					//cout << check << endl;
				} while (strcmp(check, "no") == 0);

				cout << "         ------------------------------------------------------------------          " << endl;

				cout << "	               *NHAN THONG SO*                 " << endl;


				//nhận số người chơi
				char thongbao_songuoi[100];
				int l2 = client.Receive(thongbao_songuoi, 100, 0);
				thongbao_songuoi[l2] = '\0';
				cout << thongbao_songuoi;

				char ok[3] = "ok";
				client.Send(ok, strlen(ok), 0);


				int So_ng;
				client.Receive((char*)&So_ng, sizeof(int), 0);
				cout << So_ng << endl;


				char ok1[3] = "ok";
				client.Send(ok1, strlen(ok1), 0);


				//nhận số thứ tự đoán
				char thongbao_thutu[100];
				int l4 = client.Receive(thongbao_thutu, 100, 0);
				thongbao_thutu[l4] = '\0';
				cout << thongbao_thutu;

				char ok2[3] = "ok";
				client.Send(ok2, strlen(ok2), 0);


				int So_TT;
				client.Receive((char*)&So_TT, sizeof(int), 0);
				
				cout << So_TT << endl;

				char ok3[3] = "ok";
				client.Send(ok3, strlen(ok3), 0);


				//nhận số câu hỏi
				char thongbao_socauhoi[100];
				int l6 = client.Receive(thongbao_socauhoi, 100, 0);
				thongbao_socauhoi[l6] = '\0';
				cout << thongbao_socauhoi;


				char ok4[3] = "ok";
				client.Send(ok4, strlen(ok4), 0);

				int So_cauhoi;
				client.Receive((char*)&So_cauhoi, sizeof(int), 0);
				
				cout << So_cauhoi << endl;

				char ok5[3] = "ok";
				client.Send(ok5, strlen(ok5), 0);

				cout << "--------------------------------PLAY------------------------------------" << endl << endl;

				//bắt đầu chơi

				if (So_ng !=1){


					char quyen[100];
					do{
						char bao_luot[40];
						int l_luot = client.Receive(bao_luot, 40, 0);
						bao_luot[l_luot] = '\0';
						cout << ">>" << bao_luot << endl;

						char ok6[3] = "ok";
						client.Send(ok6, strlen(ok6), 0);



						//báo câu hỏi
						char cauhoi[1000];
						int l_cauhoi = client.Receive(cauhoi, 1000, 0);
						cauhoi[l_cauhoi] = '\0';
						cout << "	Cau hoi: " << cauhoi << endl << endl;
						cout << "	Chon phuong an choi: 1: TRA LOI, 2: NHUONG QUYEN.\n	NHAP PHONG AN: ";
						char phuongan[5];
						gets_s(phuongan);
						phuongan[strlen(phuongan)] = '\0';


						//nếu người dùng nhập sai thi cho nhập lại
						while (strcmp(phuongan, "1") != 0 && strcmp(phuongan, "2") != 0)
						{
							cout << "	Chi duoc chon 1 hoac 2, vui long nhap la!\n	NHAP PHUONG AN: ";
							gets_s(phuongan);
							phuongan[strlen(phuongan)] = '\0';

						}



						client.Send(phuongan, strlen(phuongan), 0);
						char bao_phuongan[100];
						int l_bao_p_a = client.Receive(bao_phuongan, 100, 0);
						bao_phuongan[l_bao_p_a] = '\0';
						cout << bao_phuongan << endl;


						//trường hợp chọn phương án
						if (strcmp(phuongan, "2") == 0)
						{
							char ok7[3] = "ok";
							client.Send(ok7, strlen(ok7), 0);


							//nhận phản hồi nếu đã nhường quyền thì phải nhập lại
							char dauhieunhuongquyen[100];
							int l_dauhieu = client.Receive(dauhieunhuongquyen, 100, 0);
							dauhieunhuongquyen[l_dauhieu] = '\0';

							char ok8[3] = "ok";
							client.Send(ok8, strlen(ok8), 0);


							//chưa nhường quyền
							if (strcmp(dauhieunhuongquyen, "true") == 0)
							{
								int l_quyen = client.Receive(quyen, 100, 0);
								quyen[l_quyen] = '\0';

								char ok9[3] = "ok";
								client.Send(ok9, strlen(ok9), 0);

							}

							//đã nhường quyền
							else if (strcmp(dauhieunhuongquyen, "false") == 0)
							{
								char chontraloi[5];
								gets_s(chontraloi);
								chontraloi[strlen(chontraloi)] = '\0';


								//chỉ được nhập một số là 1
								while (strcmp(chontraloi, "1"))
								{
									cout << "	Chi duoc chon 1, vui long nhap la!\n	NHAP PHUONG AN: ";
									gets_s(chontraloi);
									chontraloi[strlen(chontraloi)] = '\0';
								}
								char bao_phuongan[100];
								int l_bao_p_a = client.Receive(bao_phuongan, 100, 0);
								bao_phuongan[l_bao_p_a] = '\0';
								cout << bao_phuongan << endl;


								//trả lời
								char traloi[100];
								cout << "	>>>> Nhap cau tra loi (BANG CHU CAI IN HOA): ";
								gets_s(traloi);
								traloi[strlen(traloi)] = '\0';
								client.Send(traloi, strlen(traloi), 0);


								//nhận phản hồi đáp án
								char bao_dapan[100];
								int l_dapan = client.Receive(bao_dapan, 100, 0);
								bao_dapan[l_dapan] = '\0';
								cout << bao_dapan << endl;

								char ok10[3] = "ok";
								client.Send(ok10, strlen(ok10), 0);

								int l_quyen = client.Receive(quyen, 100, 0);
								quyen[l_quyen] = '\0';
								char ok11[3] = "ok";
								client.Send(ok11, strlen(ok11), 0);


							}
						}

						else
						{
							char traloi[100];
							cout << "	>>>> Nhap cau tra loi (BANG CHU CAI IN HOA): ";
							gets_s(traloi);
							traloi[strlen(traloi)] = '\0';
							client.Send(traloi, strlen(traloi), 0);



							char bao_dapan[100];
							int l_dapan = client.Receive(bao_dapan, 100, 0);
							bao_dapan[l_dapan] = '\0';
							cout << bao_dapan << endl;

							char ok12[3] = "ok";
							client.Send(ok12, strlen(ok12), 0);

							int l_quyen = client.Receive(quyen, 100, 0);
							quyen[l_quyen] = '\0';

							char ok13[3] = "ok";
							client.Send(ok13, strlen(ok13), 0);
						}

					} while (strcmp(quyen, "con luot") == 0);


					char ketthuc[100];
					int l_kt = client.Receive(ketthuc, 100, 0);
					ketthuc[l_kt] = '\0';
					cout << ketthuc << endl;

					char ok14[3];
					client.Send(ok14, strlen(ok14), 0);


				}


				else cout << "BAN LA NGUOI CHIEN THANG!" << endl;

				cout << endl;
				system("pause");


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
