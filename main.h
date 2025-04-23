#include "nwpwin.h"
#include "nwpdlg.h"

class sin_dialog : public vsite::nwp::dialog {
 public:
  sin_dialog(tstring legend, double interval) : legend_(legend), interval_(interval) {}
  tstring get_legend_text() const { return legend_; }
  double get_interval() const { return interval_; }
 protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
private:
	tstring legend_;
	double interval_;
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	tstring legend_ = L"Interval";
	double interval_ = 9.;
};
