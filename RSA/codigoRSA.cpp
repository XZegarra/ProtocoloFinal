#include "codigoRSA.h"



codigoRSA::codigoRSA() {
	keyGen();
}
codigoRSA::codigoRSA(int key1, int key2) {
	p = key1;
	q = key2;
}
void codigoRSA::keyGen() {
	vector <int> lista = criba(100);
	int tam = lista.size() - 100;
	srand(time(NULL));
	int generator1 = tam - modulo(rand(), tam);
	int generator2 = tam - modulo(rand(), tam);
	p = lista[generator1];
	q = lista[generator2];
	int n = p * q;
	int phiN = (p - 1) * (q - 1);
	int e;
	cout << p * q;
	while (true) {
		e = rand() + 21232;
		if (euclides(e, phiN) == 1) {
			break;
		}
	}
	long long int eNegativo = euclidesExtendido(e, phiN);
	long long int d = modulo(eNegativo, phiN);
	cout << "Clave publica: " << d << " " << n << endl;
	cout << "Clave privada: " << e << " " << n << endl;
	dd = d;
	ee = e;
	nn = n;
}
vector <int> codigoRSA::encrypt(string message1) {
	message = message1;
	
	vector <int> encrypted;
	for (int i = 0;i<message.length();i++) {
		encrypted.push_back(exp(alphabet.find(message[i]), ee, alphabet.length()));
	}
	return encrypted;
}
string codigoRSA::decrypt(vector <int> encryptedMessage) {
	string decrypted;
	for (int i = 0;i < encryptedMessage.size();i++) {
		decrypted.push_back(alphabet[exp(encryptedMessage[i], dd, alphabet.length())]);
	}
	return decrypted;
}
string codigoRSA::getMessage() {
	return message;
}
