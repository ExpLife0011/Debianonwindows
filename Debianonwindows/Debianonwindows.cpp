// Debianonwindows.cpp: definisce il punto di ingresso dell'applicazione.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Device.h"

#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#define MAX_LOADSTRING 100
#define EXECUTE_EXPLOIT 0x1

#define MENU_HELP_EXIT 0x2
#define MENU_HELP_SOURCE_ADD 0x3
#define MENU_HELP_FOLLOW_INSTAGRAM 0x4

using namespace std;

// Variabili globali:
const string path_exploit_base = "C:\\Windowa\\Exploit\\App\\";
const string url_web_site = "http://www.debianonwindows.altervista.org/";
HICON hIcon = ( HICON )LoadImage(NULL, L"images.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
HMENU hMenu;

// Dichiarazioni con prototipo delle funzioni incluse in questo modulo di codice:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* Funzioni */
void event_call();
void form_1(HWND);
void menu_bar(HWND);
void control(void);																	// Controllo memoria
void open_website(void);															// Apre il sito web
void intro(void);																	// Introduzione del programma
void active_modality_developer(void);												// Attiva la modalità developer
void create_directory_app(void);													// Crea una cartella nel quale verrà installata un exploit che verrà eseguito dal programma automaticamente
void add_console_gnu(void);															// Apre lo store ed installa Debian terminal
void create_help_file(void);														// Crea dei file per l'aiuto per l'istallazione del terminale

int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	// Titolo console
	SetConsoleTitleW(L"Debian on Windows");

	// Controllo connessione
	Device dv;
	dv.connect();

	WNDCLASSW wc = { 0 };

	wc.hbrBackground = ( HBRUSH )COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"Exploit";
	wc.lpfnWndProc = WndProc;
	wc.hIcon = hIcon;

	if ( !RegisterClassW(&wc) ) {
		return FALSE;
	}

	CreateWindowW(L"Exploit", L"Debian on Windows", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 290, 250, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while ( GetMessage(&msg, NULL, NULL, NULL) ) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//
//  FUNZIONE: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  SCOPO:  elabora i messaggi per la finestra principale.
//
//  WM_COMMAND - elabora il menu dell'applicazione
//  WM_PAINT - disegna la finestra principale
//  WM_DESTROY - inserisce un messaggio di uscita e restituisce un risultato
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message ) {
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizzare le selezioni di menu:
		switch ( wmId ) {
		case EXECUTE_EXPLOIT:
			event_call();
			break;
		case MENU_HELP_SOURCE_ADD:
			MessageBoxA(hWnd, "Non disponibile", "Debina on Windows", MB_OK | MB_ICONERROR);
			//system("start https://www.github.com/Lele03");
			break;
		case MENU_HELP_FOLLOW_INSTAGRAM:
			system("start https://www.instagram.com/_gabrielelanzafame_/");
			system("start https://www.instagram.com/dvlpr_site/");
			break;
		case MENU_HELP_EXIT:
			exit(EXIT_SUCCESS);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: aggiungere qui il codice di disegno che usa HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		menu_bar(hWnd);
		form_1(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/* Funzioni */
void form_1(HWND hWnd) {
	CreateWindow(L"button", L"Esegui l'exploit", WS_VISIBLE | WS_CHILD, 10, 10, 250, 75, hWnd, ( HMENU )EXECUTE_EXPLOIT, NULL, NULL);
	CreateWindow(L"static", L"Dopo aver cliccato su \"Esegui l'exploit\" controlla la console.", WS_CHILD | WS_VISIBLE, 10, 95, 250, 100, hWnd, NULL, NULL, NULL);
}

void menu_bar(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();

	// File
	AppendMenu(hFileMenu, MF_STRING, NULL, L"Add log");

	// ?
	AppendMenu(hHelpMenu, MF_STRING, MENU_HELP_SOURCE_ADD, L"Add source code");
	AppendMenu(hHelpMenu, MF_STRING, MENU_HELP_FOLLOW_INSTAGRAM, L"Follow me on instagram");
	AppendMenu(hHelpMenu, MF_STRING, MENU_HELP_EXIT, L"Exit");

	AppendMenu(hMenu, MF_POPUP, ( UINT_PTR )hFileMenu, L"File");
	AppendMenu(hMenu, MF_POPUP, ( UINT_PTR )hHelpMenu, L"?");

	SetMenu(hWnd, hMenu);
}

// Chiama tutte le funzioni
void event_call() {
	// Controlli
	control();

	// Intro
	intro();

	// Wait
	printf("\nPremi INVIO per continuare...");
	getchar();

	// Rendere il pc in modalità sviluppatore
	printf("Sto attivando la modalita' sviluppatore...\n");
	active_modality_developer();
	printf("Modalita' sviluppatore attivata.\n");

	// Quando finisce l'attivazione della modalità sviluppatore scaricare nella posizione: "C:\Windows\Exploit\App\nomefile.exe"
	printf("Sto creando la directory...\n");
	Sleep(3000);
	create_directory_app();
	printf("Directory creata.\n");

	// Inserisco il file
	printf("Sto inserendo il file nella cartella.\n");
	string path_exploit = "C:\\Windows\\Exploit\\App\\exploit.exe";
	Sleep(3000);
	ofstream exploit(path_exploit);
	printf("File inserito nella caltella.\n");

	// Condivido il download del terminale linux debian x86
	printf("Sto cercando il link del terminale debian...\n");
	Sleep(9000);
	add_console_gnu();
	Sleep(3000);
	printf("Il link \212 stato aperto nello store ufficiale Microsoft.\n");

	// Informazioni per eventuali prograblemi
	int scelta;

	printf("\nProblemi.\n");
	printf("\n[1]-> Mi da un errore quando attivo il terminale(Errore: 0x...).\n");
	printf("[2]->\n");
	printf("[3]-> Nessun problema\n");

	printf("\n-->");
	scanf("%d", &scelta);

	switch ( scelta ) {
	case 1:
		create_help_file();
		printf("\nApro il file...\n");
		Sleep(3000);
		system("start C:\\Windows\\Exploit\\App\\Problems\\errore_0x.txt");
		printf("File aperto con successo!\n");
		break;
	case 2:
		break;
	case 3:
		printf("\nOttimo!");
		break;
	}
}

void intro(void) {
	printf("==============================================================================================\n");
	printf(":: \n");
	printf(":: Benvenuto!!!\n");
	printf(":: Questo programma \212 stato sviluppato da Gabriele Lanzafame.\n");
	printf(":: \n");
	printf(":: Prima di tutto per qualsiasi problema contattatemi qui: gabrylanz@gmail.com\n");
	printf(":: \n");
	printf(":: Follow me: \n");
	printf(":: Instagram: https://www.instagram.com/_gabrielelanzafame_/ \n");
	printf(":: Facebook: https://www.facebook.com/0x0000100/ \n");
	printf(":: GitHub: https://github.com/Lele03/ \n");
	printf(":: \n");
	printf(":: Per il codice sorgente andate in questa repository di GitHub:\n");
	printf(":: Link: https://github.com/Lele03/ \n");
	printf(":: \n");
	printf(":: Ecco qui il mio sito web:\n");
	printf(":: Link: %s\n", url_web_site.c_str());
	printf(":: \n");
	printf("==============================================================================================\n");
}

void active_modality_developer(void) {
	system("reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppModelUnlock\\\" /t REG_DWORD /f /v \"AllowAllTrustedApps\" /d \"1\"");
}

void create_directory_app(void) {
	system("mkdir C:\\Windows\\Exploit\\App");
	system("mkdir C:\\Windows\\Exploit\\App\\Problems");
}

void add_console_gnu(void) {
	system("start https://www.microsoft.com/store/productId/9MSVKQC78PK6");
}

void create_help_file(void) {
	// FILE ERRORE 0x....
	ofstream file_0x08FF("C:\\Windows\\Exploit\\App\\Problems\\errore_0x.txt");
	file_0x08FF << "Per risolvere il problema seguire i passaggi..." << endl;
	file_0x08FF << "[1]-> Aprire il pannello di controllo..." << endl;
	file_0x08FF << "[2]-> Clicca su \"Disinstalla un programma\"..." << endl;
	file_0x08FF << "[3]-> Clicca su \"Attivazione o disattivazione delle funzionalita' di windows\"..." << endl;
	file_0x08FF << "[4]-> Attivare la checkbox \"Sottosistema Windows per linux\"..." << endl;
	file_0x08FF << "[5]-> Riaprire il file..." << endl;
	file_0x08FF.close();
	Sleep(3000);
}

void open_website(void) {
	string command = "start " + url_web_site;
	system(command.c_str());
}

void control(void) {
	// Creo un puntatore di int e assegno a provra 1MB
	int* prova = ( int* )malloc(1000000 * sizeof(int));

	if ( prova == NULL ) {
		printf("Errore: memoria piena!\n");
		system("cls");
		exit(-1);
	} else {
		free(prova); // Cancella prova dalla memoria
	}
}