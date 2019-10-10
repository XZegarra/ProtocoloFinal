#include "protocolo.h"

ofstream outfile("textoCodigo.txt");



protocolo::protocolo() {
	keyGen();
}
protocolo::protocolo(int key1, int key2) {
	keyGen();
}
void protocolo::keyGen() {
	//R1:
	string duplicateAlphabet = alphabet;
	string r1;
	for (int i = 0;i < alphabet.length();i++) {
		int v1 = modulo(rand(), duplicateAlphabet.length());
		while (duplicateAlphabet[v1] == 'T') {
			v1 = modulo(rand(), duplicateAlphabet.length());
		}
		r1 = r1 + duplicateAlphabet[v1];

		duplicateAlphabet[v1] = 'T';
	}
	rotor1 = r1;
	outfile << "Rotor 1: " << r1 << " ";

	//R2:
	duplicateAlphabet = alphabet;
	string r2;
	string mensaje = shiftRR(r1);
	escitala user1(2);
	r2 = user1.encrypt(mensaje);
	rotor2 = r2;
	rotor2.pop_back();
	outfile <<"3 primeras letras del rotor 2: " << r2[0] << r2[1] << r2[3] << endl;
	//R3:
	string mensaje2 = shiftLL(shiftLL(r2));
	string r3 = user1.encrypt(mensaje2);
	rotor3 = r3;
	rotor3.pop_back();
	outfile <<"3 primeras letras del rotor 3: "<< r3[0] << r3[1] << r3[3] << endl;
	outfile << "Filas: " << user1.getFilas() << ", Columnas: " << user1.getColumnas() << endl;
	
	
}
string protocolo::encrypt(string message1) {
	cout << "ESTO ES LA ENCRIPTACION: " << endl;
	cout << "MENSAJE: " << message1 << "---->";

	message = message1;
	vigenere user2;
	string mensajeEncriptado = user2.encrypt(message);
	cout << "1.-Vigenere: " << mensajeEncriptado << "---->";
	claveVigenere = user2.getKey();

	codigoEnigma userH(rotor1, rotor2, rotor3);
	mensajeEncriptado = userH.encrypt(mensajeEncriptado);
	cout << "2.- Enigma: " << mensajeEncriptado << "---->";
	claveG = userH.getKey();
	codigoAfin user3;
	mensajeEncriptado = user3.encrypt(mensajeEncriptado);
	cout << "3.-Afin: " << mensajeEncriptado << endl;
	outfile <<"Longitud del mensaje encriptado de Vigenere: "<< mensajeEncriptado.length() << endl;
	outfile <<"Claves del codigo Afin: "<< user3.getKey1() << " " << user3.getKey2() << endl;
	claveAfin1 = user3.getKey1();
	claveAfin2 = user3.getKey2();
	return mensajeEncriptado;
}
string protocolo::decrypt(string encryptedMessage) {
	cout << "ESTO ES LA DESENCRIPTACION: " << endl;
	cout << "ENCRIPTADO: "<< encryptedMessage << "---->";

	string decrypted;
	codigoAfin desencriptador1(claveAfin1, claveAfin2);
	decrypted = desencriptador1.decrypt(encryptedMessage);
	cout << "1.-Afin: " << decrypted << "---->";

	codigoEnigma desencriptador2(rotor1, rotor2, rotor3,claveG);
	decrypted = desencriptador2.decrypt(decrypted);
	cout << "2.-Enigma: " << decrypted << "---->";

	vigenere desencriptador3(claveVigenere);
	decrypted = desencriptador3.decrypt(decrypted);
	cout << "3.-Vigenere: " << decrypted << endl;
	return decrypted;
}
string protocolo::getMessage() {
	return message;
}
string protocolo::shiftRR(string alpha) {
	string newR;
	newR.push_back(alpha[alpha.length() - 1]);
	for (int i = 0; i < alpha.length()-1;i++) {
		newR.push_back(alpha[i]);
	}
	return newR;
}
string protocolo::shiftLL(string alpha) {
	string newR;
	for (int i = 1;i < alpha.length();i++) {
		newR.push_back(alpha[i]);
	}
	newR.push_back(alpha[0]);
	return newR;
}