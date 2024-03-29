#include "global.h"
#include "MyGraph.h"
#include "menu.h"

void main() {
	setlocale(LC_ALL, "Russian");
	int menuItem;
	MenuItems item;

	MyGraph graph = GenGraph();

	do {
		PrintMenu();
		cout << '\n';

		do {
			cout << "�������� ����� ����:\n";
		} while (!GetInputInt(menuItem, MENU_ITEMS_MIN, MENU_ITEMS_MAX));
		cout << '\n';

		item = static_cast<MenuItems>(menuItem);
		switch (item) {
			case MenuItems::kGenGraph:
				graph = GenGraph();
				break;
			case MenuItems::kShimbell:
				ExecShimbell(graph);
				break;
			case MenuItems::kReachability:
				ExecReachability(graph);
				break;
			case MenuItems::kDijkstra:
				ExecDijkstra(graph);
				break;
			case MenuItems::kBellmanFord:
				ExecBellmanFord(graph);
				break;
			default:
				break;
		}
	} while (IsContinue());
	stop
}
