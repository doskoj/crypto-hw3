# Cryptography I CPA and CCA Homework 3

This assignment consists of a single program that uses the Blum-Goldwasser Probabilistic Crypto-System using several prechosen values.

## Project Details
The program is written in C++, and is implemented so that while the preset values are coded in, it is simple to change them and run the program with different parameters.

### Setup
The program takes a message, that is stored as 32-bit unsigned integers. There is also a value ```mlength``` that tells how long the message is. The messages take up the most significant bits of the integer, and the unused bits are 0s. The inputs are ```p``` and ```q``` which are the roots to a Blum Integer ```n```. Also are two integers ```a``` and ```b``` such that ```aq + bp = 1```. The messages is processed in chunks of size ```h``` such that ```h = log(k)``` and ```k = log(n)```. For this example these chucks are 4 bits. There is also a chosen starting seed ```x0```.

### Encryption
The encryption works using a pseudo-random number generator, ```x_(i) = x_(i-1)^2 mod n```. The first value is the seed ```x0```, and the encryption is done by taking the 4-bit chunks and XORing them with the last 4-bits of the ```x_i``` value. The 4-bit chunks are appended to each other and sent as the encrypted message, along with the ```x_(t+1)``` value, where ```t``` is the number of chunks in the message.

### Decryption
The key of decryption for this system is using ```x_(t_1)``` to find ```x0```. Several values are calculated:
```
d1 = ((p+1)/4)^(t+1) mod (p-1)
d2 = ((q+1)/4)^(t+1) mod (q-1)
u = x_(t+1)^d1 mod p
v = x_(t+1)^d2 mod q
x0 = vap + ubq mod n
```
Now that ```x0``` is calculated, the decryption is done the same way as the encryption, calculating the next values for ```x_i``` using the pseudo-random number generator and XORing the least significant 4-bits with the encrypted 4-bit chunks to get the original message values.

## Usage

### Building the Project
The project is compiled using g++ as shown below.
```
g++ bgprob.cpp -o bgprob.exe
```

### Running the Program
The program is run from commandline.
```
$ ./bgprob
```
The output is as follows:
```
x0: 159201
Message: 10011100000100001100
Encrypted Message: 00100000110011100100
x_(t+1): 139680
x0: 159201
Decrypted Message: 10011100000100001100
```

## Authors

* **Jacob Doskocil**
