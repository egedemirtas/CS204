#include <iostream>
#include <chrono>

using namespace std; 

#define FIRSTDATATYPE unsigned int//32bits
#define SECONDDATATYPE unsigned short//16bits

FIRSTDATATYPE gcd(FIRSTDATATYPE a, FIRSTDATATYPE b) {
  return b == 0 ? a : gcd(b, a % b);
}

class RSA {
private:
  SECONDDATATYPE p;
  SECONDDATATYPE q;
  FIRSTDATATYPE d;
public:
  FIRSTDATATYPE e;
  FIRSTDATATYPE n;

  RSA(SECONDDATATYPE p, SECONDDATATYPE q) {
	n=((FIRSTDATATYPE)p)*((FIRSTDATATYPE)q); //typecasting to prevent overflow

	unsigned long long phi_n = (((FIRSTDATATYPE)p)-1)*(((FIRSTDATATYPE)q)-1); //typecasting to prevent overflow

	e = 2; //to able to find the gcd of two numbers both of them must be >=2, else gcd will always be 1
	while(1){ //increments e, until gcd(e,phi_n) = 1, meaning e is relatively prime to phi(n)
		if( gcd(e , phi_n) != 1){ 
			e++;
		}else{
			break;
		}
	}

	d = 1;
	while(1){ //increments d until d * e = 1 mod phi(n) is reached
		if( ((d % (phi_n)) * (e)) % phi_n != 1){ // e is always smaller than phi_n so no need to do e%phi_n, (but d might be bigger than phi_n so modulus is done)
			d++;
		}else{
			break;
		}
	}
  }

  FIRSTDATATYPE encrypt(FIRSTDATATYPE m) {
	unsigned long long encrypted = m; //the biggest data type is used in order for the program to work even with very large numbers
	for(long long i = 1; i < e; i++){ // finds pow(m, e) (mod n)
		encrypted = ((encrypted % n) * m) % n; //encryped might be bigger than n so moudlus is taken right away, this also prevents overflow if the multiplication of encrypted * m is too large
	}
	return encrypted;
  }

  FIRSTDATATYPE decrypt(FIRSTDATATYPE c) { //same algorithm as RSA::encrypt but used different values for the decryption purpose
	unsigned long long decrypted = c; //large data is especially needed for decryption from my expereinces
	for(long long i = 1; i < d; i++){ //find pow(c, d) (mod n)
		decrypted = ((decrypted % n) * c) % n;
	}
	return decrypted;
  }

  FIRSTDATATYPE decrypt_bit(FIRSTDATATYPE c) {
	unsigned long long result = 1; //big data type is needed because of the multiplication in the following for loop
	unsigned long long tempC = (unsigned long long)c; //typecasting to prevent overflow in the next loop
	int iterate = 0;
	FIRSTDATATYPE MSB = 1; //idea is simple create 000....0001,
	MSB = MSB << 31; //then make it 10000....000 then use this to find 1's by iteration
	while(iterate < 32){ //itearets through d, not c!, since d is unsigned int, it is 32 bits!
		if((d | MSB) == d){ //if the bit is 1, do this:
			result = ((result% n) * (tempC% n)) % n;
		}
		if(iterate < 31){ //do this operation for each bit except the last bit of d
			result = ((result% n) * (result% n)) % n;
		}
		MSB = MSB >> 1; //shift MSB to right to look for the next bit
		iterate++;
	}
	return result;
  }
};

int main () {

  RSA rsa(62137, 62141);
  //RSA rsa(5, 11);

  auto start = std::chrono::system_clock::now();
  FIRSTDATATYPE c = rsa.encrypt(15);
  auto end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Encryption time: " << elapsed_seconds.count() << "s -- " << " ciphertext is " << c << "\n";
  
  start = std::chrono::system_clock::now();
  FIRSTDATATYPE m = rsa.decrypt(c);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Decryption time: " << elapsed_seconds.count() << "s -- " << " message is " << m << "\n";
  
  start = std::chrono::system_clock::now();
  FIRSTDATATYPE m_bit = rsa.decrypt_bit(c);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Decryption time: " << elapsed_seconds.count() << "s -- " << " message is " << m_bit << "\n";

  return 0;
}
