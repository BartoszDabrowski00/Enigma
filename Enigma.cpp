#include <iostream>
#pragma warning(disable : 4996)
#define END_MESSAGE 0
#define FIRST_ITERATION i==0
#define CURRENT_ROTOR rotors[i]
#define REFLECTOR reflectorptr[reflectorIndex]
#define PREVIOUS_ROTOR rotors[i-1]
#define SECOND_ROTOR rotors[1]
#define THIRD_ROTOR rotors[2]
class Reflector {
private:
	int size;
	int* delta;
public:
	Reflector() {
		delta = NULL;
		size = 0;
	}
	void initialize(int sizeOfAlphabet) {
		size = sizeOfAlphabet;
		delta = new int[sizeOfAlphabet];
	}
	void setting() {
		for (int i = 0; i < size; i++) {
			scanf("%d", &delta[i]);
			delta[i] = delta[i] - i - 1;
		}
	}
	int encrypt(int letter) const {
		letter += delta[letter - 1];
		if (letter > size) {
			letter %= size;
		}
		if (letter < 1) {
			letter += size;
		}
		return letter;
	}
	~Reflector() {
		delete[] delta;
	}
};
class Rotor {
private:
	int* delta;
	int* notch;
	int* reflected;
	int size, numOfNotches, position;
	bool moved, onNotch;
public:
	Rotor() {
		size = 0;
		numOfNotches = 0;
		position = 0;
		onNotch = false;
		moved = false;
		reflected = NULL;
		delta = NULL;
		notch = NULL;
	}
	void initialize(int sizeOfAlphabet) {
		size = sizeOfAlphabet;
		reflected = new int[size];
		delta = new int[size];
	}
	void Setting() {
		for (int i = 0; i < size; i++) {
			scanf("%d", &delta[i]);
			delta[i] = delta[i] - i - 1;
		}
		scanf("%d", &numOfNotches);
		notch = new int[numOfNotches];
		for (int i = 0; i < numOfNotches; i++) {
			scanf("%d", &notch[i]);
			notch[i] = (notch[i] - 1) % size;
		}
	}
	void setReflected() {
		int index;
		for (int i = 0; i < size; i++) {
			index = i + delta[i];
			if (index < 0) {
				index += size;
			}
			if (index >= size) {
				index -= size;
			}
			reflected[index] = (-1) * delta[i];
		}
	}
	bool checkNotch() {
		onNotch = false;
		if (numOfNotches > 0) {
			for (int i = 0; i < numOfNotches; i++) {
				if ((position) == notch[i]) {
					onNotch = true;
					break;
				}
			}
		}
		return onNotch;
	}
	bool checkNext() {
		onNotch = false;
		if (numOfNotches > 0) {
			for (int i = 0; i < numOfNotches; i++) {
				if ((position + 1) % size == notch[i]) {
					onNotch = true;
					break;
				}
			}
		}
		return onNotch;
	}
	bool checkIfMoved() const {
		return moved;
	}
	void setPosition(int pos) {
		position = pos - 1;
	}
	void rotate() {
		position++;
		if (position >= size) {
			position %= size;
		}
		moved = true;
	}
	int encrypt(int letter, bool reflectedSignal) const {
		int index = (letter - 1 + position) % size;
		if (!reflectedSignal) {
			letter += delta[index];
		}
		else {
			letter += reflected[index];
		}
		if (letter < 1) {
			letter += size;
		}
		if (letter > size) {
			letter %= size;
		}
		return letter;
	}
};
void createMachine(Rotor* rotorptr, Reflector* reflectorptr) {
	int numberOfRotors, reflectorIndex;
	int index, position, letter;
	bool reflectedSignal = false;
	bool firstRotation = true;
	bool doubleStep = false;
	scanf("%d", &numberOfRotors);
	Rotor* rotors = new Rotor[numberOfRotors];
	for (int i = 0; i < numberOfRotors; i++) {
		scanf("%d", &index);
		scanf("%d", &position);
		rotorptr[index].setReflected();
		rotorptr[index].setPosition(position);
		CURRENT_ROTOR = *(rotorptr + index);
	}
	scanf("%d", &reflectorIndex);
	scanf("%d", &letter);
	while (letter != END_MESSAGE) {
		for (int i = 0; i < numberOfRotors && i < 2; i++) {
			if (FIRST_ITERATION) {
				CURRENT_ROTOR.rotate();
			}
			else if (doubleStep) {
				THIRD_ROTOR.rotate();
				SECOND_ROTOR.rotate();
				if (CURRENT_ROTOR.checkNext()) {
					doubleStep = true;
				}
				else {
					doubleStep = false;
				}
				break;
			}
			else if (PREVIOUS_ROTOR.checkIfMoved() && PREVIOUS_ROTOR.checkNotch() && !firstRotation) {
				CURRENT_ROTOR.rotate();
				if (numberOfRotors > 2) {
					if (CURRENT_ROTOR.checkNext()) {
						doubleStep = true;
					}
				}
			}
		}
		for (int i = 0; i < numberOfRotors; i++) {
			letter = CURRENT_ROTOR.encrypt(letter, reflectedSignal);
		}
		letter = REFLECTOR.encrypt(letter);
		reflectedSignal = true;
		for (int i = numberOfRotors - 1; i >= 0; i--) {
			letter = CURRENT_ROTOR.encrypt(letter, reflectedSignal);
		}
		reflectedSignal = false;
		firstRotation = false;
		printf("%d ", letter);
		scanf("%d", &letter);
	}
	delete[] rotors;
}
void prepare(Rotor* rotorptr, Reflector* reflectorptr) {
	int numberOfMessages;
	scanf("%d", &numberOfMessages);
	while (numberOfMessages != 0) {
		createMachine(rotorptr, reflectorptr);
		printf("\n");
		numberOfMessages--;
	}
}
int main() {
	int sizeOfAlphabet, numberOfRotors, numberOfReflectors;
	scanf("%d", &sizeOfAlphabet);
	scanf("%d", &numberOfRotors);
	Rotor* rotorptr = new Rotor[numberOfRotors];
	for (int i = 0; i < numberOfRotors; i++) {
		rotorptr[i].initialize(sizeOfAlphabet);
		rotorptr[i].Setting();
	}
	scanf("%d", &numberOfReflectors);
	Reflector* reflectorptr = new Reflector[numberOfReflectors];
	for (int i = 0; i < numberOfReflectors; i++) {
		reflectorptr[i].initialize(sizeOfAlphabet);
		reflectorptr[i].setting();
	}
	prepare(rotorptr, reflectorptr);
	delete[] rotorptr;
	delete[] reflectorptr;
	return 0;
}