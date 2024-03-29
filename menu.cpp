#include "menu.h"

bool IsContinue() {
	char d;
	string strInp;
	bool isOk = false;
	do {
		cout << "����������? (Y/N): ";
		getline(cin, strInp);
		if (regex_match(strInp, kRxYn)) {
			isOk = true;
			d = strInp[0];
			switch (d) {
			case 'Y':
			case 'y':
				return true;
			case 'N':
			case 'n':
				return false;
			}
		}
		else {
			isOk = false;
			cout << "������������ ����!\n";
		}
	} while (!isOk);
}

void PrintMenu() {
	cout << kDelimeter << '\n';
	for (int i = 0; i <= MENU_ITEMS_MAX; i++) {
		cout << std::setw(3) << i << ": " << kMenuItemsArr[i] << '\n';
	}
	cout << kDelimeter << '\n';
}

bool GetInputInt(int& iInp, int min, int max) {
	string strInp;
	bool res;
	getline(cin, strInp);
	if (regex_match(strInp, kRxNumber)) {
		iInp = stoi(strInp);
		if (IS_IN_RANGE(iInp, min, max)) {
			res = true;
		}
		else {
			res = false;
		}
	}
	else {
		res = false;
	}
	if (res) {
		return true;
	}
	else {
		cout << "������������ ����!\n";
		return false;
	}
}


MyGraph GenGraph() {
	int vertCnt;
	do {
		cout << "������� ���������� ������ ����� n (" << VERT_CNT_MIN << " <= n <= " << VERT_CNT_MAX << "):\n";
	} while (!GetInputInt(vertCnt, VERT_CNT_MIN, VERT_CNT_MAX));
	cout << '\n';

	MyGraph graph(vertCnt);

	cout << "������� ��������� ������:\n";
	PrintMatrix(graph.GetAdjMatrix());
	cout << '\n';

	return graph;
}

void ExecShimbell(const MyGraph& graph) {
	int edgesCnt, mType;
	do {
		cout << "������� ���������� �����:\n";
	} while (!GetInputInt(edgesCnt, 1, graph.GetVertexCount() - 1));
	cout << '\n';
	do {
		cout << "�������� ���������� � �������:\n������� ���������� ��������� (0), ������� ���������� ��������� (1)\n";
	} while (!GetInputInt(mType, 0, 1));
	cout << '\n';
	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kPositive));
	cout << '\n';
	cout << "������� ��������:\n";
	PrintMatrix(graph.CalcShimbell(edgesCnt, static_cast<ShimbellMode>(mType)));
	cout << '\n';
}

void ExecReachability(const MyGraph& graph) {
	int vert1, vert2;
	vector<vector<int>> reachMatrix = graph.GetReachMatrix();
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert1, 1, graph.GetVertexCount()));
	cout << '\n';
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert2, 1, graph.GetVertexCount()));
	cout << '\n';
	vert1--;
	vert2--;
	cout << "������� ������������:\n";
	PrintMatrix(reachMatrix);
	cout << '\n';
	if (reachMatrix[vert1][vert2]/* != 0*/) {
		cout << "C��������� " << reachMatrix[vert1][vert2] << " ��������� ����� ������� ���������!\n";
	}
	else {
		cout << "�� ���������� ��������� ����� ������� ���������!\n";
	}
	cout << '\n';
}

void ExecDijkstra(const MyGraph& graph) {
	int inpVert, counter = 0;

	do {
		cout << "������� �������� �������:\n";;
	} while (!GetInputInt(inpVert, 1, graph.GetVertexCount()));
	cout << '\n';
	inpVert--;

	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kPositive));
	cout << '\n';

	cout << "� � � � � � �:\n";

	vector<int> distances = graph.Dijkstra(inpVert, counter);
	vector<vector<int>> paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedPos));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������:" << std::setw(4) << counter << '\n';
	cout << '\n';

	cout << "� � � � � � �:\n";

	distances = graph.Dijkstra_queue(inpVert, counter);
	paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedPos));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������:" << std::setw(4) << counter << '\n';
	cout << '\n';

	//cout << "� �:\n";

	//distances = graph.BellmanFord(inpVert, counter);
	//paths = graph.RestorePaths(inpVert, distances);

	//for (int i = 0; i < graph.GetVertexCount(); i++) {
	//	if (i != inpVert) {
	//		if (paths[i][0] != INF) {
	//			cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
	//			for (int j = paths[i].size() - 1; j > 0; j--) {
	//				cout << std::setw(2) << paths[i][j] + 1 << " -> ";
	//			}
	//			cout << std::setw(2) << paths[i][0] + 1 << '\n';
	//		}
	//		else {
	//			cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
	//		}
	//	}
	//}
	//cout << '\n';
	//cout << "���������� ��������:" << std::setw(4) << counter << '\n';
	//cout<< '\n';
}

void ExecBellmanFord(const MyGraph& graph) {
	int inpVert, counter = 0;

	do {
		cout << "������� �������� �������:\n";;
	} while (!GetInputInt(inpVert, 1, graph.GetVertexCount()));
	cout << '\n';
	inpVert--;

	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kMixed));
	cout << '\n';

	vector<int> distances = graph.BellmanFord(inpVert, counter);
	vector<vector<int>> paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedMixed));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������:" << std::setw(4) << counter << '\n';
	cout << '\n';
}