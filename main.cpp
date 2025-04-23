#include "main.h"
#include "rc.h"

double calculate_y(RECT graph, double interval, double x) {
  return (1 - sin((x - graph.right / 2) * interval / graph.right)) * graph.bottom / 2;
}

int sin_dialog::idd() const {
	return IDD_LEGEND; 
}

bool sin_dialog::on_init_dialog(){
	set_real(IDC_EDIT1, interval_);
	set_text(IDC_EDIT2, legend_);
	return true;
}

bool sin_dialog::on_ok(){
	try {
		interval_ = get_real(IDC_EDIT1);
		legend_ = get_text(IDC_EDIT2);
	} catch (std::exception) {
		MessageBox(*this, L"Input is not valid", nullptr, MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc){
  RECT graph;
  GetClientRect(*this, &graph);

  SetTextColor(hdc, RGB(0, 0, 255));
  DrawText(hdc, legend_.c_str(), -1, &graph,
           DT_RIGHT | DT_TOP | DT_SINGLELINE);

  MoveToEx(hdc, 0, graph.bottom / 2, nullptr);
  LineTo(hdc, graph.right, graph.bottom / 2);
  MoveToEx(hdc, graph.right / 2, 0, nullptr);
  LineTo(hdc, graph.right / 2, graph.bottom);

  MoveToEx(hdc, graph.left, calculate_y(graph, interval_, 0), nullptr);
  for (double x = graph.left, y = 0; x <= graph.right; x++) {
    y = calculate_y(graph, interval_, x);
    LineTo(hdc, x, y);
  }
}

void main_window::on_command(int id){
	switch(id){
		case ID_EXIT:
		  ::DestroyWindow(*this);
		  break;
		case ID_LEGEND: 
			sin_dialog dialog(legend_, interval_);
			if (dialog.do_modal(0, *this) == IDOK) {
				interval_ = dialog.get_interval();
				legend_ = dialog.get_legend_text();
				InvalidateRect(*this, nullptr, true);
			}
            break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
} 


int WINAPI WinMain(HINSTANCE hi, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (UINT_PTR)LoadMenu(hi, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
