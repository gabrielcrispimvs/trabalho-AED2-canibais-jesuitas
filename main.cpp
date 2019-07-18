#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum side {esq, dir};

char moveUmCanibal (char estado);
char moveUmJesuita (char estado);
char moveDoisCanibais (char estado);
char moveDoisJesuitas (char estado);
char moveCanibalJesuita (char estado);
bool checkEstado (char estado);
char estadoToChar (char qntCanibaisDir, char qntJesuitasDir, side ladoBarco);
void printEstado (char estado);

int main ()
{
	// Valor de 0 a 31, representando todos os possíveis estados
	// 2 primeiros bits: quantidade de jesuítas no lado direito. 00 a 11 (0 a 3)
	// próximos 2 bits: quantidade de canibais no lado direito. 00 a 11 (0 a 3)
	// Último bit: lado do barco. 0 ou 1 (esquerdo ou direito)
	// Valor de 32 representa um estado impossível
	unsigned char estadoAtual = 0, proxEstado, estadoAnt;
	queue<unsigned char> fila;
	queue<unsigned char> filaOrig;
	bool visited[32];
	unsigned char origem[32];

	for (int i = 0; i < 32; i++)
	{
		visited[i] = false;
		origem[i] = 32;
	}

	fila.push(0);
	filaOrig.push(0);

	while (!fila.empty())
	{
		estadoAtual = fila.front();
		fila.pop();
		estadoAnt = filaOrig.front();
		filaOrig.pop();

		if (!checkEstado(estadoAtual)) continue;
		if (visited[estadoAtual] == true) continue;
		visited[estadoAtual] = true;
		origem[estadoAtual] = estadoAnt;
		if (estadoAtual == 31) break;

		fila.push(moveUmCanibal(estadoAtual));
		fila.push(moveUmJesuita(estadoAtual));
		fila.push(moveDoisCanibais(estadoAtual));
		fila.push(moveDoisJesuitas(estadoAtual));
		fila.push(moveCanibalJesuita(estadoAtual));

		for (int i = 0; i < 5; i++) filaOrig.push(estadoAtual);
	}

	vector<unsigned char> path;
	while (true)
	{
		path.insert(path.begin(),estadoAtual);
		if (estadoAtual == origem[estadoAtual]) break;
		estadoAtual = origem[estadoAtual];
	}

	for (int i = 0; i < path.size(); i++)
	{
		printEstado(path[i]);
		cout << endl;
	}

	return 0;
}

char estadoToChar (char qntJesuitasDir, char qntCanibaisDir, side ladoBarco)
{
	char ret = (qntJesuitasDir << 3) ^ (qntCanibaisDir << 1) ^ ladoBarco;
	return ret;
}

bool checkEstado (char estado)
{
	if (estado >= 32)
		return false;

	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (qntCanibaisDir > qntJesuitasDir && qntJesuitasDir != 0)
		return false;
	if (3 - qntCanibaisDir > 3 - qntJesuitasDir && 3-qntJesuitasDir != 0)
		return false;
	return true;
}

char moveUmCanibal (char estado)
{
	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (ladoBarco == dir)
	{
		if (qntCanibaisDir == 0)
			return 32;
		ladoBarco = esq;
		qntCanibaisDir--;
	}
	else if (ladoBarco == esq)
	{
		if (qntCanibaisDir == 3)
			return 32;
		ladoBarco = dir;
		qntCanibaisDir++;
	}
	return estadoToChar(qntJesuitasDir,qntCanibaisDir,ladoBarco);
}

char moveUmJesuita (char estado)
{
	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (ladoBarco == dir)
	{
		if (qntJesuitasDir == 0)
			return 32;
		ladoBarco = esq;
		qntJesuitasDir--;
	}
	else if (ladoBarco == esq)
	{
		if (qntJesuitasDir == 3)
			return 32;
		ladoBarco = dir;
		qntJesuitasDir++;
	}
	return estadoToChar(qntJesuitasDir,qntCanibaisDir,ladoBarco);
}

char moveDoisCanibais (char estado)
{
	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (ladoBarco == dir)
	{
		if (qntCanibaisDir < 2)
			return 32;
		ladoBarco = esq;
		qntCanibaisDir -= 2;
	}
	else if (ladoBarco == esq)
	{
		if (qntCanibaisDir > 2)
			return 32;
		ladoBarco = dir;
		qntCanibaisDir += 2;
	}
	return estadoToChar(qntJesuitasDir,qntCanibaisDir,ladoBarco);
}

char moveDoisJesuitas (char estado)
{
	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (ladoBarco == dir)
	{
		if (qntJesuitasDir < 2)
			return 32;
		ladoBarco = esq;
		qntJesuitasDir -= 2;
	}
	else if (ladoBarco == esq)
	{
		if (qntJesuitasDir > 2)
			return 32;
		ladoBarco = dir;
		qntJesuitasDir += 2;
	}
	return estadoToChar(qntJesuitasDir,qntCanibaisDir,ladoBarco);
}

char moveCanibalJesuita (char estado)
{
	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	if (ladoBarco == dir)
	{
		if (qntJesuitasDir == 0 || qntCanibaisDir == 0)
			return 32;
		ladoBarco = esq;
		qntJesuitasDir--;
		qntCanibaisDir--;
	}
	else if (ladoBarco == esq)
	{
		if (qntJesuitasDir == 3 || qntCanibaisDir == 3)
			return 32;
		ladoBarco = dir;
		qntJesuitasDir++;
		qntCanibaisDir++;
	}
	return estadoToChar(qntJesuitasDir,qntCanibaisDir,ladoBarco);
}

void printEstado (char estado)
{
	if (estado == 32)
	{
		cout << "Estado impossível" << endl;
		return;
	}

	side ladoBarco = (side)(estado % 2);
	char qntCanibaisDir = (estado >> 1) % 4;
	char qntJesuitasDir = (estado >> 3) % 4;

	cout << "Jesuitas Esquerda: " << (int)(3-qntJesuitasDir);
	cout << "    Jesuitas Direita: " << (int)qntJesuitasDir << endl;
	cout << "Canibais Esquerda: " << (int)(3-qntCanibaisDir);
	cout << "    Canibais Direita: " << (int)qntCanibaisDir << endl;
	cout << "Lado do barco: ";
	if (ladoBarco == esq) cout << "Esquerda" << endl;
	else cout << "Direita" << endl;
}
