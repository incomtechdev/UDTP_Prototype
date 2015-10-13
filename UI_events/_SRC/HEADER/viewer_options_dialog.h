#include "ui_viewer_options.h"

using namespace std;

class UI_config;

class Viewer_Options_dialog : public QDialog
{
	Q_OBJECT

private:
	Ui::Viewer_Options_Dialog ui;
	UI_config *data;

public:
	Viewer_Options_dialog(UI_config *_data, QWidget *parent = 0);


public slots:
	void DefaultEditorBrowse();
	void UserdefEditorBrowse();
	void SaveChanges();
	void SetDefaults();
};