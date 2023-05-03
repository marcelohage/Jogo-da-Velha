#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
using namespace std;

void inicializa(int);
void desenha(int);
void joga(int, char);
bool ganhaLinha(int, char);
bool ganhaColuna(int, char);
bool ganhaPrincipal(int, char);
bool ganhaSecundaria(int, char);
bool testaVitoria(int, char);
void imprimeResultado(int, int);
int menu();
void gravaHistorico(int, int);
void historico();
 
char mat[3][3][3];
char p1[300], p2[300];
int score1, score2;
main()
{
	int i, partida, score1=0, score2=0, opcao;
	char jogador;
	setlocale(LC_ALL, "Portuguese");
	system("color 4F");
	do
	{
		opcao = menu();
		switch (opcao)
		{
			case 1:
				cout<<"*--------JOGO DA VELHA--------*"<<endl;
				cout<< endl;
				cout<<"*----Partida Melhor De Tr�s---*"<<endl;
				cout<< endl;
				cout<< endl;
				cout<< "Informe o nome do Player 1 (X): ";
				cin>> p1;
				cout<< endl;
  				cout<< "Informe o nome do Player 2 (O): ";
  				cin>> p2;
  				for(partida=0; partida < 3; partida++)
				{
					if (partida == 0)
					{
						system("color 50");
					}
					if (partida == 1)
					{
						system("color D0");
					}
					if (partida == 2)
					{
						system("color E0");
					}
  					inicializa(partida);
  					desenha(partida);
  					for (i=0; i < 9; i++)
  					{
  						if ((i % 2)==0)
  						{
  							cout<< "(X) Vez de " <<p1 <<endl;
  							jogador = 'X';
						}
						else
						{
		  					cout<<"(O) Vez de "<<p2 <<endl;
		  					jogador = 'O';
						}
						joga(partida, jogador);
  						desenha(partida);
  						if (testaVitoria(partida, jogador) == true)
  						{
  							if (jogador == 'X')
  							{
  								cout<< p1 <<" GANHOU!!! " <<endl;
  								score1++;
							}
							else
							{
								cout<< p2 <<" GANHOU!!! " <<endl;
								score2++;
							}
							break;
						}
					}
				}
				imprimeResultado(score1, score2);
				break;
			case 2: historico();	
			break;
		}
				
	}while (opcao != 3);
}

void historico()
{
	char nome1[50], nome2[50], data[11], score1[20], score2[20];
	string linha;
	fstream meuArquivo("historico.txt");
	if (meuArquivo.is_open())
	{
		cout<< "*** Hist�rico ***" <<endl;
		while (getline(meuArquivo, linha))
		{
			cout <<linha <<endl;
		}
	}
	else
	{
		cout<<"Erro na abertura do arquivo" <<endl;
	}
	meuArquivo.close();
}

void gravaHistorico (int score1, int score2)
{
	char data[11];
	ofstream meuArquivo("historico.txt", ios::app);
	if (meuArquivo.is_open())
	{
		cout<< "Informe a data: "<<endl;
		cin>> data;
		meuArquivo <<p1 << " = " <<score1 <<" X " <<p2 <<" = " <<score2;
	}
	else
	{
		cout<<"N�o foi possivel abrir o arquivo";
	}
	meuArquivo.close();
}

void imprimeResultado(int score1, int score2)
{
	int partida;
	cout<<"-----FINAL DO JOGO - CONFIRA O RESULTADO-----"<<endl;
	for(partida=0; partida < 3; partida++)
	{
		desenha(partida);
	}
	if (score1 > score2)
	{
		cout<< p1 <<" Foi melhor na disputa"<<endl;
		system("color F0");
	}
	else
	{
		if (score2 > score1)
		{
			cout<< " Foi melhor na disputa"<< endl;
			system("color F0");
		}
		else
		{
			cout<< "Ocorreu empate na disputa" <<endl;
			system("color 0F");
		}
	}
	gravaHistorico(score1, score2);
}

void joga(int partida, char jogador)
{
	char caracter;
  	int linha, coluna;
  	do
  	{
  		do 
  		{
  			cout<< "Informe a linha que quer jogar: "<<endl;
  			cin>> linha;
		}while((linha < 0) || (linha > 2));
	
		do
		{
			cout<< "Informe a coluna que quer jogar: "<<endl;
  			cin>> coluna;
		}while((coluna < 0) || (coluna > 2));
		
	}while(mat[partida][linha][coluna]!= ' ');
    mat[partida][linha][coluna]=jogador;
}

void inicializa(int partida)
{
	int i, j;
	for (i=0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
  			mat[partida][i][j] = ' ';
		}
	}
}

void desenha (int partida)
{
	int i, j;
  	cout<< "   0    1    2"<<endl;
	cout<< "  -------------"<<endl;
  	for (i = 0; i < 3; i++)
  	{
  		cout<< i << " | ";
  		for (j= 0; j < 3; j++)
  		{
  			cout<< mat[partida][i][j]<< " | ";
 		}
 		cout<< endl;
 		if (i < 2)
		{
			cout<< "  -------------"<<endl;
 		}
 	}
}

bool testaVitoria(int partida, char jogador)
{
	bool ganhou = false;
	ganhou = ganhaLinha(partida, jogador);
	if (ganhou == false)
	{
		ganhou = ganhaColuna(partida, jogador);
	}
	if (ganhou == false)
	{
		ganhou = ganhaSecundaria(partida, jogador);
	}
	if (ganhou == false)
	{
		ganhou = ganhaPrincipal(partida, jogador);
	}
	return ganhou;
}

bool ganhaLinha(int partida, char jogador)
{	
	bool ganhou = false;
	int i, j, ganhaLinha=0;
	
	for (i=0; i < 3; i++)
	{
		for (j=0; j < 3; j++)
		{
			if (mat[partida][i][j] == jogador)
			{
				ganhaLinha++;
			}
		}
		if (ganhaLinha == 3)
		{
			ganhou = true;
		}
		else
		{
			ganhaLinha = 0;
		}
	}
	return ganhou;
}

bool ganhaColuna(int partida, char jogador)
{   
	bool ganhou = false;
	int i, j, ganhaColuna=0;

	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if (mat[partida][i][j] == jogador)
			{
				ganhaColuna++;
			}
		}
		if (ganhaColuna == 3)
		{
			ganhou = true;
		}
		else 
		{
			ganhaColuna = 0;
		}
	}
	return ganhou;
}

bool ganhaSecundaria (int partida, char jogador)
{
	bool ganhou = false;
	int i, j, ganhaSecundaria=0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (((i + j) == 2) && (mat[partida][i][j] == jogador))
			{
				ganhaSecundaria++;
			}
		}
	}
	if (ganhaSecundaria == 3)
	{
		ganhou = true;
	}
	return ganhou;
}

bool ganhaPrincipal(int partida, char jogador)
{
	bool ganhou = false;
	int i, j, ganhaPrincipal=0;
	
	for (i = 0; i < 3; i++)
	{
		if ((mat[partida][i][i]) == jogador)
		{
			ganhaPrincipal++;
		}
	}
	if (ganhaPrincipal == 3)
	{
		ganhou = true;
	}
	return ganhou;
}

int menu()
{
	int opcao;
	cout<< "*** Menu de opcoes ***" <<endl;
	cout<< "(1) Jogar " <<endl;
	cout<< "(2) Hist�rico " <<endl;
	cout<< "(3) Fim " <<endl;
	cin >> opcao;
	return opcao;
}




