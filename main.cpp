#include <sstream>

#include "Stack.h"
#include "List.h"
#include "Graph.h"
#include "Array.h"
#include "SearchBinaryTree.h"
#include "Hash.h"
#include "Set.h"
#include "Pair.h"
#include "SetPair.h"

using namespace std;

void chekTheOpenFile(ifstream& file) {
	if (!file.is_open()) throw runtime_error("Error open file");
}

void chekTheOpenFile(ofstream& file) {
	if (!file.is_open()) throw runtime_error("Error open file");
}

void menu() {
	cout << "[1] - Стек" << endl;
	cout << "[2] - АТД Множество" << endl;
	cout << "[3] - Множество" << endl;
	cout << "[4] - Массив" << endl;
	cout << "[5] - Двоичное дерево" << endl;
	cout << "[6] - Хеш-таблица" << endl;
	cout << "[0] - Выход" << endl;
	cout << "Введите вариант: ";
}

void menuGraph() {
	cout << "[1] - Добавление ребра в граф" << endl;
	cout << "[2] - Просмотр таблицы смежности вершин" << endl;
	cout << "[3] - Обход в глубину" << endl;
	cout << "[0] - Выход" << endl;
}

void depthFirstSearch(Graph& graph, Stack<int32_t>& stack, List<int32_t>& visited) {
	int32_t vertex = stack.pop();
	if (visited.find(vertex) == nullptr) {
		visited.push_back(vertex);
		for (int32_t i = 1; i <= graph.chainSize(vertex); i++) {
			stack.push(graph.getItemFromChain(vertex, i));
		}
		cout << vertex << " ";
	}
	if (stack.is_empty()) return;
	depthFirstSearch(graph, stack, visited);
}

void preparingForDFS(Graph& graph) {
	Stack<int32_t> stack;
	List<int32_t> visited;
	cout << "Выберите вершину от которой начнется обход: ";
	int32_t vertex;
	cin >> vertex;
	stack.push(vertex);
	depthFirstSearch(graph, stack, visited);
	cout << endl;
}

void addEdgeInGraph(Graph& graph) {
	cout << "Введите две вершины через пробел: ";
	int32_t first, second;
	cin >> first;
	cin >> second;
	graph.addEdge(first, second);
}

void handleCommandGraph(Graph& graph) {
	unsigned char inputData;
	menuGraph();
	while (cin >> inputData) {	
		if (inputData == '1') addEdgeInGraph(graph);
		else if (inputData == '2') graph.print();
		else if (inputData == '3') preparingForDFS(graph);
		else if (inputData == '0') return;
		else throw runtime_error("Incorrect input command");
		menuGraph();
	}
}

void graphInitialization() {
	cout << "Введите количество вершин в графе: ";
	int32_t vertex;
	cin >> vertex;
	Graph graph(vertex);
	handleCommandGraph(graph);
}

void OperatingWithSetHelp() {
	cout << "Запуск задания в консоли : ./<имя вашей программы> --file <путь до файла с данными> --query <запрос к файлу с данными>" << endl;
}

void readInputValuesTurtle(int32_t amountOfTurtle, SetP& turtles) {
	int32_t inputValueFirst, inputValueSecond;
	for (int32_t i = 0; i < amountOfTurtle; i++) {
		cin >> inputValueFirst;
		cin >> inputValueSecond;
		turtles.SETADD(inputValueFirst, inputValueSecond);
	}
}

void checkingTurtles(int32_t amountOfTurtle, SetP& turtles) {
	int32_t truthsAmount = 0;
	for (int32_t i = 0, j = amountOfTurtle - 1; i < amountOfTurtle; i++, j--) {
		if (turtles.SET_AT(i, j)) truthsAmount++;
	}
	cout << truthsAmount;
}

void taskAboutTurtles() {
	int32_t amountOfTurtle;
	cout << "Введите количество черепах: ";
	cin >> amountOfTurtle;
	cout << "Введите значения: " << endl;
	SetP turtles(1000);
	readInputValuesTurtle(amountOfTurtle, turtles);
	checkingTurtles(amountOfTurtle, turtles);
}

void removeDuplicateChar(Array<char>& arr, int32_t& counterChar, int32_t& i) {
	for (counterChar--; counterChar != 0; counterChar--) {
		arr.erase(i - 1);
		i--;
	}
}

void sort(Array<char>& arr) {
	for (int32_t i = 1; i < arr.size(); i++) {
		int32_t j = i - 1;
		while (j >= 0 && arr[j] > arr[j + 1]) {
			swap(arr[j], arr[j + 1]);
			j--;
		}
	}
}

int32_t searchMaxColumn(Array<int32_t>& amountOfChar) {
	int32_t maxColumn = 0;
	for (int32_t i = 0; i < amountOfChar.size(); i++) {
		if (amountOfChar[i] > maxColumn) maxColumn = amountOfChar[i];
	}
	return maxColumn;
}

void printHistogram(Array<char>& arr, Array<int32_t>& amountOfChar) {
	int32_t maxColumn = searchMaxColumn(amountOfChar);
	for (int32_t i = 0; i < maxColumn; i++) {
		for (int32_t j = 0; j < amountOfChar.size(); j++) {
			if (amountOfChar[j] == maxColumn - i) {
				cout << '#';
				amountOfChar[j] = amountOfChar[j] - 1;
			}
			else cout << ' ';
		}
		cout << endl;
	}
	arr.print();
}

void countingLetters(Array<char>& arr) {
	Array<int32_t> amountOfChar;
	int32_t counterChar = 1;
	for (int32_t i = 0; i < arr.size() - 1; i++) {
		if (arr[i] == arr[i + 1]) counterChar++;
		else {
			amountOfChar.push_back(counterChar);
			removeDuplicateChar(arr, counterChar, i);
			counterChar = 1;
		}
	}
	printHistogram(arr, amountOfChar);
}

void readingInputString() {
	cout << "Введите строку: ";
	char character;
	Array<char> arr;
	cin >> character;
	while (character != '\n') {
		if (character != ' ') arr.push_back(character);
		character = getchar();
	}
	sort(arr);
	arr.push_back('\n');
	countingLetters(arr);
}

void printLeavesWithoutDescendants() {
	cout << "Введите элементы двоичного дерева поиска: ";
	string numbers;
	SBT<int32_t> tree;
	cin >> numbers;
	tree.insert(stoi(numbers));
	getline(cin, numbers);
	istringstream numbersStream(numbers);
	string number;
	while (numbersStream >> number) {
		tree.insert(stoi(number));
	}
	tree.print();
}

void readRoute(istringstream& inputDataStream, Hash& routes) {
	char tempChr;
	int32_t amountOfPoints = 0;
	string first, second, delay;
	while (inputDataStream >> tempChr) {
		if (tempChr == '"') {
			if (amountOfPoints == 0) getline(inputDataStream, first, '"');
			else if (amountOfPoints == 1) getline(inputDataStream, second, '"');
			amountOfPoints++;
			if (amountOfPoints == 2) amountOfPoints = 0;
		}
		if (tempChr == ':') {
			inputDataStream >> tempChr;
			while (tempChr != ',' and tempChr != '}') {
				delay += tempChr;
				inputDataStream >> tempChr;
			}
			routes.HSET(first, second, stoi(delay));
			if (tempChr == '}') {
				inputDataStream >> tempChr;
				return;
			}
			first.clear();
			second.clear();
			delay.clear();
		}
	}
}

string readInitialServer(istringstream& inputDataStream) {
	char tempChr;
	string initialServer;
	while (inputDataStream >> tempChr) {
		if (tempChr == '"') {
			getline(inputDataStream, initialServer, '"');
			return initialServer;
		}
	}
}

string readDestinationServer(istringstream& inputDataStream) {
	char tempChr;
	string destinationServer;
	while (inputDataStream >> tempChr) {
		if (tempChr == '"') {
			getline(inputDataStream, destinationServer, '"');
			return destinationServer;
		}
	}
}

void routeSearch(Hash& routes, string& currentServer, const string& destinationServer, int32_t& minDelay, int32_t& currentDelay, string& Path, string& currentPath) {
	int32_t saveForeachState = routes.itemsAmountForeach;
	for (int32_t i = 0; i < routes.SIZE(); i++) {
		PAIR tempPair = routes.foreach(currentServer);
		if (tempPair.second == destinationServer) {
			currentDelay += tempPair.delay;
			if (minDelay > currentDelay) {
				minDelay = currentDelay;
				Path = currentPath;
			}
			currentDelay = 0;
		}
		else if (tempPair.delay == NULL) break;
		else {
			currentPath = currentPath + "->" + tempPair.second;
			currentDelay += tempPair.delay;
			currentServer = tempPair.second;
			saveForeachState = routes.itemsAmountForeach;
			routes.itemsAmountForeach = 0;
			routeSearch(routes, currentServer, destinationServer, minDelay, currentDelay, Path, currentPath);
			routes.itemsAmountForeach = saveForeachState;
		}
	}
}

//routes = {("A", "B"): 1, ("B", "C"): 2}, initial server = "A", destination server = "C"
//routes = { ("A", "B") : 1, ("B", "C") : 2, ("A", "C") : 4 }, initial server = "A", destination server = "C"
//routes = { ("A", "B") : 1, ("B", "C") : 2, ("Ab", "C") : 4 }, initial server = "A", destination server = "C"

void printResult(int32_t delay, string& Path, string& initialServer, string& destinationServer) {
	cout << "Задержка: " << delay << " Путь: " << initialServer << Path << "->" << destinationServer;
}

void readInputValues(istringstream& inputDataStream) {
	string tempStr, initialServer, destinationServer, currentPath, Path;
	int32_t minDelay = 1000, currentDelay = 0;
	Hash routes;
	getline(inputDataStream, tempStr, '=');
	readRoute(inputDataStream, routes);
	getline(inputDataStream, tempStr, '=');
	if (tempStr == " initial server ") initialServer = readInitialServer(inputDataStream);
	string initialServerSave = initialServer;
	getline(inputDataStream, tempStr, '=');
	if (tempStr == ", destination server ") destinationServer = readDestinationServer(inputDataStream);
	routeSearch(routes, initialServer, destinationServer, minDelay, currentDelay, currentPath, Path);
	printResult(minDelay, Path, initialServerSave, destinationServer);
}

void readRoutes() {
	cout << "Введите маршруты: ";
	string inputData;
	cin >> inputData;
	getline(cin, inputData);
	istringstream inputDataStream(inputData);
	readInputValues(inputDataStream);
}

void hadleCommand() {
	unsigned char inputData;
	cin >> inputData;
	if (inputData == '1') graphInitialization();
	else if (inputData == '2') OperatingWithSetHelp();
	else if (inputData == '3') taskAboutTurtles();
	else if (inputData == '4') readingInputString();
	else if (inputData == '5') printLeavesWithoutDescendants();
	else if (inputData == '6') readRoutes();
	else if (inputData == '0') return;
	else throw runtime_error("Incorrect input command");
}

struct Data {
	string command;
	string nameStructure;
	string firstValue = "NULL";
	string secondValue = "NULL";
};

void checkForExtraCharacters(Data& data) {
	if (data.command[0] == '\'') data.command.erase(0, 1);
	if (data.firstValue[data.firstValue.size() - 1] == '\'') data.firstValue.erase(data.firstValue.size() - 1);
	if (data.secondValue[data.secondValue.size() - 1] == '\'') data.secondValue.erase(data.secondValue.size() - 1);
}

void checkForExtraCharacters(string& item) {
	if (item[0] == '\n') item.erase(0, 1);
}

void readInputData(Data& data, string inputData) {
	string name;
	int32_t i = 0;
	for (unsigned char character : inputData) {
		if (character == ' ') {
			if (i == 0) data.command = name;
			if (i == 1) data.nameStructure = name;
			if (i == 2) data.firstValue = name;
			name = "";
			i++;
		}
		else name += character;
	}
	if (i == 1) data.nameStructure = name;
	if (i == 2) data.firstValue = name;
}

void performingAnActionSet(const Data& data, Set set, int32_t& amountOfItem) {
	if (data.command == "SETADD") {
		if (!set.SET_AT(stoi(data.firstValue))) amountOfItem++;
		set.SETADD(stoi(data.firstValue));
	}
	else if (data.command == "SETDEL") {
		if (set.SET_AT(stoi(data.firstValue))) amountOfItem--;
		set.SETDEL(stoi(data.firstValue));
	}
	else if (data.command == "SET_AT") {
		if (!set.SET_AT(stoi(data.firstValue))) cout << "false";
		else cout << "true";
	}
	else throw runtime_error("Incorrect input command");
}

void writeToFileSet(const string& nameFile, Set& set, int32_t amountOfItem) {
	ofstream dataFile(nameFile);
	chekTheOpenFile(dataFile);
	set.printInFile(dataFile, amountOfItem);
	dataFile.close();
}

void readFromFileInSet(const string& nameFile, Data& data) {
	ifstream fileData(nameFile);
	chekTheOpenFile(fileData);
	int32_t amountOfItems;
	fileData >> amountOfItems;
	int32_t amountOfItem = amountOfItems;
	Set set(1000);
	string item1;
	for (; amountOfItems > 0;  amountOfItems--) {
		fileData >> item1;
		set.SETADD(stoi(item1));
	}
	fileData.close();
	performingAnActionSet(data, set, amountOfItem);
	writeToFileSet(nameFile, set, amountOfItem);
}

void executingSetCommands(int argc, const char** argv) {
	string nameFile;
	Data data;
	for (int32_t i = 0; i < argc; i++) {
		string str = argv[i];
		if (str == "--file" and i + 1 < argc) {
			nameFile = argv[i + 1];
		}
		if (str == "--query" and i + 1 < argc) {
			readInputData(data, argv[i + 1]);
		}
	}
	checkForExtraCharacters(data);
	readFromFileInSet(nameFile, data);
}

int main(int argc, const char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
	try {
		if (argc > 2) executingSetCommands(argc, argv);
		else {
			menu();
			hadleCommand();		
		}
	}
	catch (exception& e) {
		cout << e.what();
	}
}
